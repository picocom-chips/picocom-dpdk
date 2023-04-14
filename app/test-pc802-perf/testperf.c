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

#include <cmdline_rdline.h>
#include <cmdline_parse.h>
#include <cmdline_socket.h>
#include <cmdline.h>

#include <rte_pmd_pc802.h>
#include <pcxx_ipc.h>


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

static int port_init(uint16_t port)
{
    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    int socket_id;
    static pcxxInfo_s   ctrl_cb_info = { NULL, NULL };
    static pcxxInfo_s   data_cb_info = { NULL, NULL };

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_TX", 2048,
            128, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL_ETH_RX", 2048,
            128 , 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    rte_eth_dev_configure(port, 1, 1, &dev_conf);
    tx_conf = dev_info.default_txconf;
    rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
    rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

    pcxxDataOpen(&data_cb_info, 0, 0);

    pcxxCtrlOpen(&ctrl_cb_info, 0, 0);

    pc802_create_tx_queue(0, PC802_TRAFFIC_OAM, 256*1024, 256, 128);
    pc802_create_rx_queue(0, PC802_TRAFFIC_OAM, 256*1024, 256, 128);

    rte_eth_dev_start(port);

    printf("Finished port_init !\n");

    return 0;
}


static uint32_t * alloc_tx_blk(uint16_t qId)
{
    PC802_Mem_Block_t *mblk;
    mblk = pc802_alloc_tx_mem_block(0, qId);
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

static uint16_t tx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    PC802_Mem_Block_t *tx_blks[32];
    RTE_ASSERT(nb_blks <= 32);
    for (k = 0; k <nb_blks; k++)
        tx_blks[k] = (PC802_Mem_Block_t *)((char *)blks[k] - sizeof(PC802_Mem_Block_t));
    return pc802_tx_mblk_burst(0, qId, tx_blks, nb_blks);
}

static uint16_t rx_blks(uint16_t qId, uint32_t **blks, uint16_t nb_blks)
{
    uint16_t k;
    nb_blks = pc802_rx_mblk_burst(0, qId, (PC802_Mem_Block_t **)blks, nb_blks);
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
    int ch=0x46;               //channel mask
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

	//printf( "\nCore %u acting as pc802 recv core %d second.\n", rte_lcore_id(), time );

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
    ch = (ch==0)?0x46:ch;
    type = (type==0)?12:type;

    printf( "\n\tStart pcie performance test ...\n");
    printf( "\tPackage len:\t%d byte\n", len);
    printf( "\tTest channel:\t%x\n", ch );
    printf( "\tTest duration:\t%d seconds\n", time);
    printf( "\tTest type:\t%d\n\n", type);

    rte_eal_remote_launch( pc802_test_pcie_recv, (void*)((uint64_t)time+5), rte_get_next_lcore(-1, 1, 0) );

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

    port_init(0);

    prompt(NULL);

    rte_eal_mp_wait_lcore( );
    return 0;
}

