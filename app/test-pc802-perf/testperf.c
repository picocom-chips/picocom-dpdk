/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/queue.h>
#include <sys/stat.h>

#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

#include <rte_common.h>
#include <rte_errno.h>
#include <rte_byteorder.h>
#include <rte_log.h>
#include <rte_debug.h>
#include <rte_cycles.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_alarm.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_mempool.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_mbuf_pool_ops.h>
#include <rte_interrupts.h>
#include <rte_pci.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_dev.h>
#include <rte_string_fns.h>
#include <rte_net_crc.h>
#include <rte_cycles.h>

#include <cmdline_rdline.h>
#include <cmdline_parse.h>
#include <cmdline_socket.h>
#include <cmdline.h>

#include <rte_pmd_pc802.h>
#include <pcxx_ipc.h>
#include <pcxx_oam.h>


static void
signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n",
                signum);
        //force_quit = true;
        signal(signum, SIG_DFL);
        kill(getpid(), signum);
    }
}

static const struct rte_eth_conf dev_conf = {
        .rxmode = {
            .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
        },
    };

uint16_t pc802_port = 0;

struct perf_msg{
    uint32_t cell;
    uint32_t group;
    uint32_t no;
    uint32_t sn;
    uint32_t len;
    uint32_t data_len;
    uint32_t crc;
    uint32_t tscs;
    uint32_t tsc[8];
    uint8_t data[];
};

struct dt{
    uint64_t dt7_0;
    uint64_t dt1_0;
    uint64_t dt4_3;
    uint64_t dt7_6;
};
static uint64_t g_rx_ttis = 0;
static struct dt dt_max, dt_sum;

// [t0]app[t1]->udrv[t2]->pcie->core0->[t3]phy)
// [t7]app[t6]<-udrv[t5]<-pcie<-core0<-[t4]phy)

static uint32_t process_ul_ctrl_msg(const char* buf, uint32_t payloadSize, uint16_t dev, uint16_t cell)
{
#define US(t) (uint32_t)((uint64_t)(t)*1000000/rte_get_tsc_hz())
    static uint8_t rx_data[256*1024];
    struct perf_msg *c = (struct perf_msg *)((char *)buf);
    struct perf_msg *d = pcxxDataRecv(0, c->data_len, dev, cell);
    uint32_t dt7_0, dt1_0, dt4_3, dt7_6;

    c->tsc[6] = (uint32_t)rte_rdtsc();
    if ( NULL == d )
        printf("cann't recv data(no=%u)!\n", c->no);
    else
        rte_memcpy(rx_data, d, c->data_len);
    
    if (c->crc != rte_raw_cksum(c->data, c->len)){
        printf("ctrl msg crc=%u err!\n", c->crc);
        RTE_ASSERT(0);
    }

    g_rx_ttis++;
    c->tsc[7] = (uint32_t)rte_rdtsc();

    if (dt_max.dt7_0 < (dt7_0 = US(c->tsc[7] - c->tsc[0]))) dt_max.dt7_0 = dt7_0;
    dt_sum.dt7_0 += dt7_0;
    RTE_ASSERT(dt7_0>50);

    if (dt_max.dt1_0 < (dt1_0 = US(c->tsc[2] - c->tsc[0]))) dt_max.dt1_0 = dt1_0;
    dt_sum.dt1_0 += dt1_0;

    if (dt_max.dt7_6 < (dt7_6 = US(c->tsc[7] - c->tsc[6]))) dt_max.dt7_6 = dt7_6;
    dt_sum.dt7_6 += dt7_6;

    if (dt_max.dt4_3 < (dt4_3 = c->tsc[4] - c->tsc[3])) dt_max.dt4_3 = dt4_3;
    dt_sum.dt4_3 += dt4_3;

    //printf("RX msg %2x-%4u: t7-t0=%3u t1-t0=%2u t4-t3=%2u t7-t6=%2u\n", c->crc, c->no, dt7_0, dt1_0, dt4_3, dt7_6);
    //printf("Rx ctrl: cell=%u, group=%u, no=%u, sn=%u, len=%u, crc=%u, tscs=%u.\n", c->cell, c->group, c->no, c->sn, c->len, c->crc, c->tscs);
    //printf("TSC: %8u %8u %8u %8u %8u %8u %8u %8u %8u\n", tsc, c->tsc[0], c->tsc[1], c->tsc[2], c->tsc[3], c->tsc[4], c->tsc[5], c->tsc[6], c->tsc[6]);
    
    return payloadSize;
}

static int port_init(uint16_t port)
{
    static pcxxInfo_s ctrl_cb_info = {process_ul_ctrl_msg, NULL};
    static pcxxInfo_s data_cb_info = {NULL, NULL};

    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    int socket_id, cell;

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_TX", 2048,
            0, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_RX", 2048,
            0, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    rte_eth_dev_configure(port, 1, 1, &dev_conf);
    tx_conf = dev_info.default_txconf;
    rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
    rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

    for (cell = 0; cell < CELL_NUM_PRE_DEV; cell++)
    {
        pcxxDataOpen(&data_cb_info, 0, cell);
        pcxxCtrlOpen(&ctrl_cb_info, 0, cell);
    }
#ifdef MULTI_PC802
    pcxxCtrlOpen(&ctrl_cb_info, 0, LEGACY_CELL_INDEX);
#endif
    pc802_create_tx_queue( port, PC802_TRAFFIC_OAM, 256*1024, 256, 128);
    pc802_create_rx_queue( port, PC802_TRAFFIC_OAM, 256*1024, 256, 128);

    rte_eth_dev_start(port);

    printf("Finished port_init !\n");

    return 0;
}


static uint32_t * alloc_tx_blk(uint16_t qId)
{
    PC802_Mem_Block_t *mblk;
    mblk = pc802_alloc_tx_mem_block(pc802_port, qId);
    if (mblk)
        return (uint32_t *)&mblk[1];
    return NULL;
}

static void free_blk(uint32_t *blk)
{
    char *p = (char *)blk;
    if (p) {
        p -= sizeof(PC802_Mem_Block_t);
        pc802_free_mem_block((PC802_Mem_Block_t *)p);
    }
}

static void produce_random_data(uint32_t *buf, uint32_t len)
{
    while ( (len -= sizeof(buf[0])) )
        *buf++ = (uint32_t)rte_rand();
}

static uint16_t tx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    PC802_Mem_Block_t *tx_blks[32];
    RTE_ASSERT(nb_blks <= 32);
    for (k = 0; k <nb_blks; k++)
        tx_blks[k] = (PC802_Mem_Block_t *)((char *)blks[k] - sizeof(PC802_Mem_Block_t));
    return pc802_tx_mblk_burst(pc802_port, qId, tx_blks, nb_blks);
}

static uint16_t rx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    nb_blks = pc802_rx_mblk_burst(pc802_port, qId, (PC802_Mem_Block_t **)blks, nb_blks);
    for (k = 0; k < nb_blks; k++) {
        blks[k] += (sizeof(PC802_Mem_Block_t) / sizeof(uint32_t));
    }
    return nb_blks;
}

static void set_blk_attr(uint32_t *blk, uint32_t length, uint8_t type, uint8_t eop)
{
    PC802_Mem_Block_t *mblk;
    if (blk) {
        mblk = (PC802_Mem_Block_t *)((char *)blk - sizeof(PC802_Mem_Block_t));
        mblk->pkt_length = length;
        mblk->pkt_type = type;
        mblk->eop = eop;
    }
}

static void get_blk_attr(uint32_t *blk, uint32_t *length, uint8_t *type, uint8_t *eop)
{
    PC802_Mem_Block_t *mblk;
    if (blk) {
        mblk = (PC802_Mem_Block_t *)((char *)blk - sizeof(PC802_Mem_Block_t));
        *length = mblk->pkt_length;
        *type = mblk->pkt_type;
        *eop = mblk->eop;
    }
}

static int pc802_test_pcie_recv( void *arg )
{
    int ch=0x70;               //channel mask
    uint64_t start, end;
    uint64_t pkts=0, pktlens=0, total=0;
    uint64_t pkt[PC802_TRAFFIC_NUM], pktlen[PC802_TRAFFIC_NUM];
    uint64_t cycles = rte_get_timer_hz();
    int n;
    int c;
    int t = 0;
    uint32_t *buf[32];
    uint32_t length = 0;
    int time = (uint64_t)arg;
    uint8_t type, eop;

	printf( "\nCore %u acting as pc802 recv core %d second.\n", rte_lcore_id(), time );
    rte_delay_us(1);

    pkts = 0;
    pktlens = 0;
    memset( pkt, 0, sizeof(pkt) );
    memset( pktlen, 0, sizeof(pktlen) );
    start = rte_rdtsc( );
	while( t<time ) {
        for( c=0; c<PC802_TRAFFIC_NUM; c++ ) {
            if ( 0 == ((1<<c)&ch) )
                continue;
            while(1) {
                n = rx_blks( c, &buf[0], 32 );
                if (0==n)
                    break;
                pkt[c] += n;
                pkts += n;
                while(n--){
                    get_blk_attr( buf[n], &length, &type, &eop);
                    pktlen[c] += length;
                    pktlens += length;
                    free_blk(buf[n]);
                }
            }
        }

        end = rte_rdtsc( );
        if ( (end-start) > cycles ) {
            printf( "%d(%lu):UL PPS: %lu, BPS: %luKbits/sec (", t, ((end-start)*1000/cycles), pkts, pktlens*8/( ((end-start)*1000/cycles) ) );
            for ( c=0; c<PC802_TRAFFIC_NUM; c++ )
            {
                if ( 0 == ((1<<c)&ch) )
                    continue;
                printf(" %d: %lu, %lu;", c, pkt[c], pktlen[c]*8/( ((end-start)*1000/cycles) ) );
            }
            printf(")\n");
            total += pkts;
            pkts = 0;
            pktlens = 0;
            memset( pkt, 0, sizeof(pkt) );
            memset( pktlen, 0, sizeof(pktlen) );
            start = end;
            t++;
        }
	}
    printf("Rx total recv pkgs %lu.\n", total);
    //printf( "\nCore %u exit as pc802 recv.\n", rte_lcore_id() );

    return 0;
}
int pc802_test_pcie( int len, int time, int ch, int type );
int pc802_test_pcie( int len, int time, int ch, int type )
{
    uint32_t lcore_id = rte_get_next_lcore(-1, 1, 0);
//  int ch=0x46;               //channel mask
//  int len=arg0*1024;
//  int time=60;
    int t, c;
    uint32_t *blk;
    int ret;
    uint64_t start, end;
    uint64_t pkts=0, pktlens=0, total=0;
    uint64_t pkt[PC802_TRAFFIC_NUM]={0}, pktlen[PC802_TRAFFIC_NUM]={0};
    uint64_t cycles = rte_get_timer_hz();
//  uint8_t type = 2;
    uint8_t eop = 1;

    len = (len==0)?1024:len*1024;
    time = (time==0)?60:time;
    ch = (ch==0)?0x70:ch;
    type = (type==0)?12:type;

    printf( "\n\tStart pcie performance test ...\n");
    printf( "\tPackage len:\t%d byte\n", len);
    printf( "\tTest channel:\t%x\n", ch );
    printf( "\tTest duration:\t%d seconds\n", time);
    printf( "\tTest type:\t%d\n", type);
    printf( "\tUL core:\t%u\n\n", lcore_id);

    if (RTE_MAX_LCORE != lcore_id)
    {
        rte_eal_remote_launch( pc802_test_pcie_recv, (void*)((uint64_t)time+5), lcore_id );
        rte_delay_us(1000);
    }

    start = rte_rdtsc( );
    for ( t=0; t<time; )
    {
        for ( c=0; c<PC802_TRAFFIC_NUM; c++ )
        {
            if ( 0 == ((1<<c)&ch) )
                continue;

            blk = alloc_tx_blk( c );
            if( NULL != blk )
            {
                set_blk_attr( blk, len, type, eop );
                ret = tx_blks( c, &blk, 1);
                if ( ret > 0 ) {
                    pkt[c] += ret;
                    pktlen[c] += ret*len;
                    pkts += ret;
                    pktlens += ret*len;
                } else {
                    free_blk(blk);
                    rte_delay_us( 1 );
                }
            }
        }
        end = rte_rdtsc( );
        if ( (end-start) > cycles ) {
            printf("%d(%lu):DL PPS: %lu, BPS: %luKbits/sec (", t, ((end-start)*1000/cycles), pkts, pktlens*8/( ((end-start)*1000/cycles) ) );
            for ( c=0; c<PC802_TRAFFIC_NUM; c++ )
            {
                if ( 0 == ((1<<c)&ch) )
                    continue;
                printf(" %d: %lu, %lu;", c, pkt[c], pktlen[c]*8/( ((end-start)*1000/cycles) ) );
            }
            printf(")\n");
            total += pkts;
            pkts = 0;
            pktlens = 0;
            memset( pkt, 0, sizeof(pkt) );
            memset( pktlen, 0, sizeof(pktlen) );
            t++;
            start = end;
        }
    }

    //send stop
    t = 10;
    while( t-- ) {
        rte_delay_ms( 100 );
        for ( c=0; c<PC802_TRAFFIC_NUM; c++ )
        {
            if ( 0 == ((1<<c)&ch) )
                continue;
            if ( NULL != (blk = alloc_tx_blk( c ) ) ) {
                set_blk_attr( blk, t+1, 10, 1 );
                if(tx_blks(c, &blk, 1)<1)
                    free_blk(blk);
            }
        }
    }

    rte_eal_mp_wait_lcore( );
    printf("Tx total send pkgs %lu.\n", total);

    return total;
}

int test_cell_perf(uint16_t count);
int test_cell_perf(uint16_t count)
{
    #define HLEN sizeof(struct perf_msg)
    uint16_t i, dev=0, cell=0;
    uint32_t ctrl_len=1024, data_len=64*1024;
    struct perf_msg *ctrl_msg = NULL;
    struct perf_msg *data_msg = NULL;
    uint32_t offset = 0, avail = 0;
    uint32_t group=0, no=0, gourp_size = 2000;
    uint64_t sn=0;
    uint64_t tsc=0, dt2_0=0, max_dt2_0=0, dt7_5=0, max_dt7_5=0, bytes=0, tx_ttis=0, rx_ttis=0;
    uint64_t hz = rte_get_tsc_hz();
    void *ctrl_buf[8] = {NULL};
    void *data_buf[8] = {NULL};

    printf("start perf test: count=%u gourp_size=%u hz=%lu\n\n", count, gourp_size, hz);
    printf("----    [t0]app[t1] -> udrv[t2] -> pcie -> core0 -> [t3]phy)    ----\n");
    printf("----    [t7]app[t6] <- udrv[t5] <- pcie <- core0 <- [t4]phy)    ----\n\n");

    for ( i = 0; i < 8; i++) {
        ctrl_buf[i] = rte_malloc(NULL, ctrl_len, RTE_CACHE_LINE_MIN_SIZE);
        produce_random_data(ctrl_buf[i], ctrl_len);
        data_buf[i] = rte_malloc(NULL, data_len, RTE_CACHE_LINE_MIN_SIZE);
        produce_random_data(data_buf[i], data_len);
    }

    while( 0 == pcxxCtrlRecv(dev, cell) );

    g_rx_ttis = 0;
    memset( &dt_max, 0, sizeof(dt_max));
    memset( &dt_sum, 0, sizeof(dt_sum));

    while ( group < count ) {
        while( 1 ){
            tsc = rte_rdtsc();
            if( 0 != pcxxCtrlRecv(dev, cell) )
                break;
            tsc = rte_rdtsc()-tsc;
            if (tsc > max_dt7_5) max_dt7_5 = tsc;
            dt7_5 += tsc;
            rx_ttis++;
            if ( rx_ttis >= gourp_size){
                printf("recv %4lu TTIs stats: t7-t0=%3lu,%3lu; t1-t0=%2lu,%2lu; t4-t3=%2lu,%2lu; t7-t6=%2lu,%2lu\n", g_rx_ttis,
                    dt_max.dt7_0, dt_sum.dt7_0/g_rx_ttis, dt_max.dt1_0, dt_sum.dt1_0/g_rx_ttis,
                    dt_max.dt4_3, dt_sum.dt4_3/g_rx_ttis, dt_max.dt7_6, dt_sum.dt7_6/g_rx_ttis);
                g_rx_ttis = 0;
                memset( &dt_max, 0, sizeof(dt_max));
                memset( &dt_sum, 0, sizeof(dt_sum));

                printf("test %lu TTIs tx stats: max = %2lu us/TTI, avg = %2lu us/TTI, speed = %4lu MB/sec.\n", tx_ttis, (max_dt2_0*1000000/hz), ((dt2_0/tx_ttis)*1000000/hz), bytes/((dt2_0*1000000/hz)));
                printf("test %lu TTIs rx stats: max = %2lu us/TTI, avg = %2lu us/TTI.\n", rx_ttis, (max_dt7_5*1000000/hz), ((dt7_5/rx_ttis)*1000000/hz));

                bytes = 0;
                tx_ttis = 0;
                dt2_0 = 0;
                max_dt2_0 = 0;

                rx_ttis = 0;
                max_dt7_5 = 0;
                dt7_5 = 0;

                group++;
                no = 0;
            }
        }
        if ( sn - rx_ttis > 0)
            continue;       

        pcxxSendStart(dev, cell);

        while(0 != pcxxCtrlAlloc((char **)&ctrl_msg, &avail, dev, cell));

        ctrl_msg->tscs = 0;
        ctrl_msg->tsc[ctrl_msg->tscs++] = rte_rdtsc();

        ctrl_msg->cell = cell;
        ctrl_msg->group = group;
        ctrl_msg->no = no;
        ctrl_msg->sn = sn++;

        ctrl_msg->len = ctrl_len;
        ctrl_msg->data_len = data_len;

        while(0 != pcxxDataAlloc(data_len+HLEN, (char **)&data_msg, &offset, dev, cell));

        data_msg->cell = cell;
        data_msg->group = group;
        data_msg->no = no;
        data_msg->len = data_len;
        data_msg->data_len = data_len;
        data_msg->sn = sn;

        data_msg->tscs = 0;
        data_msg->tsc[data_msg->tscs++] = rte_rdtsc();

        memcpy(data_msg->data, data_buf[rte_rand()%8], data_len);
        data_msg->tsc[data_msg->tscs++] = rte_rdtsc();

        //data_msg->crc = rte_net_crc_calc(data_msg->data, data_len, RTE_NET_CRC32_ETH);
        //data_msg->tsc[data_msg->tscs++] = rte_rdtsc();

        pcxxDataSend(offset, data_len+HLEN, dev, cell);
        bytes += data_len+HLEN;

        memcpy(ctrl_msg->data, ctrl_buf[rte_rand()%8], ctrl_len);
        ctrl_msg->tsc[ctrl_msg->tscs++] = rte_rdtsc();

        ctrl_msg->data[rte_rand()%ctrl_len] = rte_rdtsc();
        ctrl_msg->crc = rte_raw_cksum(ctrl_msg->data, ctrl_len);
        ctrl_msg->tsc[ctrl_msg->tscs++] = rte_rdtsc();

        pcxxCtrlSend((const char *)ctrl_msg, ctrl_len+HLEN, dev, cell);
        bytes += ctrl_len+HLEN;

        tsc = rte_rdtsc();
        pcxxSendEnd(dev, cell);
        tsc = rte_rdtsc()-tsc;
        if (tsc>max_dt2_0) max_dt2_0 = tsc;
        dt2_0 += tsc;
        //printf("\tTX %lu: len = %2lu us/TTI\n", sn, bytes);

        tx_ttis++;
        no++;
    };
    usleep(1000);
    while( 0 == pcxxCtrlRecv(dev, cell) );

    for ( i = 0; i < 8; i++) {
        rte_free(ctrl_buf[i]);
        rte_free(data_buf[i]);
    }

    usleep(100*1000);
    while( 0 == pcxxCtrlRecv(dev, cell) );

    return 0;
}

extern cmdline_parse_ctx_t main_ctx[];
static int prompt(void* arg)
{
    struct cmdline *cl;
    arg = arg;

    cl = cmdline_stdin_new(main_ctx, "PC802>> ");
    if (cl == NULL) {
        return -1;
    }
    cmdline_interact(cl);
    cmdline_stdin_exit(cl);

    return 0;
}

int main(int argc, char** argv)
{
    int diag;

    printf("%s\n", picocom_pc802_version());
    printf("PC802 perf tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    pc802_port = pc802_get_port_id(0);
    port_init( pc802_port );

    prompt(NULL);

    rte_eal_mp_wait_lcore( );
    return 0;
}

