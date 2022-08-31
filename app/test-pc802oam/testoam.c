/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <signal.h>
#include <semaphore.h>
#include <unistd.h>

#include <rte_common.h>
#include <rte_ethdev.h>
#include <rte_pmd_pc802.h>
#include <pcxx_ipc.h>
#include <pcxx_oam.h>

#include "ecpri_oam_inf.h"

extern void odu_cmd_main(void);

static void signal_handler(int signum)
{
    if ( signum == SIGINT || signum == SIGTERM ) {
        printf( "\n\nSignal %d received, preparing to exit...\n", signum );
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

static int port_init( uint16_t pc802_index )
{
    static pcxxInfo_s   ctrl_cb_info = {NULL, NULL};
    static pcxxInfo_s   data_cb_info = {NULL, NULL};
    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf tx_conf;
    char temp_name[32] = {0};
    int socket_id;
    uint16_t cell;
    int port = pc802_get_port_id(pc802_index);
    if ( port < 0 )
        rte_exit( EXIT_FAILURE, "pc802 %d is notexist !\n", pc802_index );

    rte_eth_dev_info_get(port, &dev_info);
    socket_id = dev_info.device->numa_node;

    sprintf(temp_name, "MBUF_POOL_ETH%d_RX", pc802_index );
    mbuf_pool = rte_pktmbuf_pool_create(temp_name, 2048,
            128 , 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket_id);
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool on Line %d\n", __LINE__);

    rte_eth_dev_configure(port, 1, 1, &dev_conf);
    tx_conf = dev_info.default_txconf;
    rte_eth_tx_queue_setup(port, 0, 128, socket_id, &tx_conf);
    rte_eth_rx_queue_setup(port, 0, 128, socket_id, NULL, mbuf_pool);

    for (cell = 0; cell < CELL_NUM_PRE_DEV; cell++)
    {
        pcxxDataOpen(&data_cb_info, pc802_index, cell);
        pcxxCtrlOpen(&ctrl_cb_info, pc802_index, cell);
    }
    rte_eth_dev_start(port);

    printf("Finished %d port_init !\n", pc802_index );

    return 0;
}

int main(int argc, char** argv)
{
    int diag;
    int port_id = 0;
    int pc802_index = 0;

    printf("PC802 OAM tester built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    pcxx_oam_init();
    for ( pc802_index=0; pc802_index<PC802_INDEX_MAX; pc802_index++ )
    {
        port_id = pc802_get_port_id(pc802_index);
        if (port_id < 0)
            break;
        port_init(pc802_index);
    }

    odu_cmd_main();

	rte_eal_mp_wait_lcore();
	//rte_eal_cleanup();
    return 0;
}
