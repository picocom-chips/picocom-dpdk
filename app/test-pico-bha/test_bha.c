/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>

#include <sys/queue.h>
#include <sys/stat.h>

#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

#include <cmdline.h>
#include <cmdline_parse.h>
#include <cmdline_rdline.h>
#include <cmdline_socket.h>
#include <rte_alarm.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_byteorder.h>
#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_debug.h>
#include <rte_dev.h>
#include <rte_eal.h>
#include <rte_errno.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_interrupts.h>
#include <rte_launch.h>
#include <rte_lcore.h>
#include <rte_log.h>
#include <rte_malloc.h>
#include <rte_mbuf.h>
#include <rte_mbuf_pool_ops.h>
#include <rte_memcpy.h>
#include <rte_memory.h>
#include <rte_mempool.h>
#include <rte_pci.h>
#include <rte_per_lcore.h>
#include <rte_string_fns.h>

#include <bha_model.h>
#include <rte_pmd_bha.h>
#include <test_bha.h>



//global variable
int testbha_logtype;
uint16_t bha_portid = 0;

static void
signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n",
            signum);

        signal(signum, SIG_DFL);
        kill(getpid(), signum);
    }
}

static int
is_port_id_invalid(uint16_t port_id, bool warn_en)
{
    uint16_t ptid;

    RTE_ETH_FOREACH_DEV(ptid)
        if (port_id == ptid)
            return 0;

    if (warn_en)
        fprintf(stderr, "Invalid port %d\n", port_id);

    return 1;
}

void
test_bha_ethdev_stop(void)
{
    uint16_t port_id;

    RTE_ETH_FOREACH_DEV(port_id) {
        if (is_port_id_invalid(port_id, true))
            return;
        printf("\nStopping port %d...\n", port_id);
        fflush(stdout);
        rte_eth_dev_stop(port_id);
    }
}

void
test_bha_ethdev_close(void)
{
    uint16_t port_id;

    RTE_ETH_FOREACH_DEV(port_id) {
        if (is_port_id_invalid(port_id, true))
            return;
        printf("\nShutting down port %d...\n", port_id);
        fflush(stdout);
        rte_eth_dev_close(port_id);
    }
}

void
test_bha_exit(void)
{
    test_bha_ethdev_stop();
    test_bha_ethdev_close();
}


int main(int argc, char** argv)
{
    int diag;
    int ret = 0;
    uint16_t count;
    uint16_t nb_ports;
    uint16_t port_id;
    uint16_t ports_ids[RTE_MAX_ETHPORTS];

    testbha_logtype = rte_log_register("testbha");
    if (testbha_logtype < 0)
        rte_exit(EXIT_FAILURE, "Cannot register log type");
    rte_log_set_level(testbha_logtype, RTE_LOG_DEBUG);

    TESTBHA_LOG(DEBUG, "testbha logging");

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n",
            rte_strerror(rte_errno));

    //currently not support secondary startup
    if (rte_eal_process_type() == RTE_PROC_SECONDARY)
        rte_exit(EXIT_FAILURE,
            "Secondary process type not supported.\n");

    //iova don't care 0; iova_pa 1; iova_va 2
    TESTBHA_LOG(DEBUG, "Get iova mode %d\n", rte_eal_iova_mode());

    count = 0;
    RTE_ETH_FOREACH_DEV(port_id)
    {
        ports_ids[count] = port_id;
        count++;
    }
    nb_ports = count;
    if (nb_ports == 0) {
        TESTBHA_LOG(WARNING, "No probed ethernet devices\n");
    } else if (nb_ports == 1) {
        TESTBHA_LOG(DEBUG, "Probed ethernet devices nb_ports %d, the 1st portid %d\n", nb_ports, ports_ids[0]);
        bha_portid = ports_ids[0];
    } else {
        TESTBHA_LOG(ERR, "Probed ethernet devices nb_ports %d > 1, check!\n", nb_ports);
        return EXIT_FAILURE;
    }

    test_bha_cmdline();

    rte_eal_mp_wait_lcore();
    ret = rte_eal_cleanup();
    if (ret != 0)
        rte_exit(EXIT_FAILURE,
            "EAL cleanup failed: %s\n", strerror(-ret));

    return EXIT_SUCCESS;
}
