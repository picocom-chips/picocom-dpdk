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
#include <semaphore.h>
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
#include <rte_bus_pci.h>

#include <cmdline_rdline.h>
#include <cmdline_parse.h>
#include <cmdline_socket.h>
#include <cmdline.h>

#include <rte_pmd_pc802.h>
#include <pc802_ethdev.h>
#include <pcxx_ipc.h>
#include <pcxx_oam.h>

#define PC802_BAR_EXT_OFFSET  (4 * 1024)

static inline void pc802_write_reg(volatile uint32_t *addr, uint32_t value)
{
    __asm__ volatile ("" : : : "memory");
    *addr = value;
    return;
}

#define PC802_WRITE_REG(reg, value) \
    pc802_write_reg((volatile uint32_t *)&(reg), (value))

static inline uint32_t pc802_read_reg(volatile uint32_t *addr)
{
    uint32_t val;
    val = *addr;
    __asm__ volatile ("" : : : "memory");
    return val;
}

#define PC802_READ_REG(reg) \
    pc802_read_reg((volatile uint32_t *)&(reg))

int pc802_port_id;

uint8_t * gBar[3];

#define PRINT_REG(r)    printf(#r " = 0x%08X\n", PC802_READ_REG(bar->r))

#define PRINT_8_REGS(r) do {\
    printf(#r "[] = 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",\
    PC802_READ_REG(bar->r[0]), PC802_READ_REG(bar->r[1]), PC802_READ_REG(bar->r[2]), PC802_READ_REG(bar->r[3]),\
    PC802_READ_REG(bar->r[4]), PC802_READ_REG(bar->r[5]), PC802_READ_REG(bar->r[6]), PC802_READ_REG(bar->r[7]));\
    } while(0)

#define PRINT_4_REGS(r) do {\
    printf(#r "[] = 0x%08X 0x%08X 0x%08X 0x%08X\n",\
    PC802_READ_REG(bar->r[0]), PC802_READ_REG(bar->r[1]), PC802_READ_REG(bar->r[2]), PC802_READ_REG(bar->r[3]));\
    } while(0)


#define PRINT_EXT_REG(r)    printf(#r " = 0x%08X\n", PC802_READ_REG(ext->r))

static void print_bar0(void)
{
    PC802_BAR_t *bar = (PC802_BAR_t *)gBar[0];
    PC802_BAR_Ext_t *ext = (PC802_BAR_Ext_t *)(gBar[0] + PC802_BAR_EXT_OFFSET);
    PRINT_REG(DEVEN);
    PRINT_REG(DEVRDY);
    PRINT_REG(DRVSTATE);
    PRINT_REG(DBAL);
    PRINT_REG(DBAH);
    PRINT_8_REGS(TDNUM);
    PRINT_REG(TDNUM8[0]);
    PRINT_8_REGS(TRCCNT);
    PRINT_REG(TRCCNT8[0]);
    PRINT_8_REGS(TEPCNT);
    PRINT_REG(TEPCNT8[0]);
    PRINT_8_REGS(RDNUM);
    PRINT_REG(RDNUM8[0]);
    PRINT_8_REGS(RRCCNT);
    PRINT_REG(RRCCNT8[0]);
    PRINT_8_REGS(REPCNT);
    PRINT_REG(REPCNT8[0]);
    PRINT_8_REGS(TX_RST_RCCNT);
    PRINT_REG(TX_RST_RCCNT8[0]);
    PRINT_8_REGS(TX_RST_EPCNT);
    PRINT_REG(TX_RST_EPCNT8[0]);
    PRINT_8_REGS(RX_RST_RCCNT);
    PRINT_REG(RX_RST_RCCNT8[0]);
    PRINT_8_REGS(RX_RST_EPCNT);
    PRINT_REG(RX_RST_EPCNT8[0]);
    PRINT_REG(BOOTRCCNT);
    PRINT_REG(BOOTEPCNT);
    PRINT_REG(BOOTERROR);
    PRINT_REG(IO_RCCNT);
    PRINT_REG(IO_EPCNT);
    PRINT_4_REGS(ULDMA_TIMEOUT_FINISHED);
    PRINT_4_REGS(ULDMA_TIMEOUT_ERROR);
    PRINT_4_REGS(DLDMA_TIMEOUT_FINISHED);
    PRINT_4_REGS(DLDMA_TIMEOUT_ERROR);
    PRINT_REG(MB_C2H_RDNUM);
    PRINT_EXT_REG(MB_C2H_EPCNT);
    PRINT_EXT_REG(MB_C2H_RCCNT);
    PRINT_EXT_REG(VEC_RCCNT);
    PRINT_EXT_REG(VEC_EPCNT);
    PRINT_EXT_REG(TRACE_EPCNT[0].v);
    PRINT_EXT_REG(TRACE_RCCNT[0]);
}

static void print_pfi_mailbox(void)
{
    mailbox_counter_t *pfi_mb = (mailbox_counter_t *)(gBar[1] + MAILBOX_COUNTER_OFFSET_PFI);
    printf("PFI MB Wr[] = 0x%08X 0x%08X 0x%08X 0x%08X\n", pfi_mb->wrs[0], pfi_mb->wrs[1], pfi_mb->wrs[2], pfi_mb->wrs[3]);
    printf("PFI MB Rg = %1u\n", pfi_mb->rg);
    printf("PFI MB Rd[0][] = 0x%08X 0x%08X 0x%08X 0x%08X\n", pfi_mb->rds[0][0], pfi_mb->rds[0][1], pfi_mb->rds[0][2], pfi_mb->rds[0][3]);
    printf("PFI MB Rd[1][] = 0x%08X 0x%08X 0x%08X 0x%08X\n", pfi_mb->rds[1][0], pfi_mb->rds[1][1], pfi_mb->rds[1][2], pfi_mb->rds[1][3]);
}

static void print_ecpri_mailbox(void)
{
    mailbox_counter_t *ecpri_mb = (mailbox_counter_t *)(gBar[2] + MAILBOX_COUNTER_OFFSET_ECPRI);
    printf("eCPRI MB Wr[] = 0x%08X 0x%08X 0x%08X 0x%08X\n", ecpri_mb->wrs[0], ecpri_mb->wrs[1], ecpri_mb->wrs[2], ecpri_mb->wrs[3]);
    printf("eCPRI MB Rg = %1u\n", ecpri_mb->rg);
    printf("eCPRI MB Rd[0][] = 0x%08X 0x%08X 0x%08X 0x%08X\n", ecpri_mb->rds[0][0], ecpri_mb->rds[0][1], ecpri_mb->rds[0][2], ecpri_mb->rds[0][3]);
    printf("eCPRI MB Rd[1][] = 0x%08X 0x%08X 0x%08X 0x%08X\n", ecpri_mb->rds[1][0], ecpri_mb->rds[1][1], ecpri_mb->rds[1][2], ecpri_mb->rds[1][3]);
}

static void print_mirrored_ep_cnts(PC802_EP_Counter_Mirror_t *mr)
{
    printf("mrTEPCNT[] = 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
        mr->TEPCNT[0], mr->TEPCNT[1], mr->TEPCNT[2], mr->TEPCNT[3],
        mr->TEPCNT[4], mr->TEPCNT[5], mr->TEPCNT[6], mr->TEPCNT[7],
        mr->TEPCNT8[0]);
    printf("mrREPCNT[] = 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
        mr->REPCNT[0], mr->REPCNT[1], mr->REPCNT[2], mr->REPCNT[3],
        mr->REPCNT[4], mr->REPCNT[5], mr->REPCNT[6], mr->REPCNT[7],
        mr->REPCNT8[0]);
    printf("mrMB_C2H_EPCNT = 0x%08X\n", mr->MB_C2H_EPCNT);
    printf("mrTRACE_EPCNT[0] = 0x%08X\n", mr->TRACE_EPCNT[0].v);
}

static void print_descriptor(PC802_Descriptor_t *d, char *name, uint32_t idx)
{
    printf("%s[%3u]: phy_addr 0x%lx length %6u eop %1u type %1u sfn %4u slot %3u\n",
        name, idx, d->phy_addr, d->length, d->eop, d->type, d->sfn, d->slot);
}

static void print_descs(void)
{
    static const char *q_name[] = {"Eth", "NR0-D", "NR0-C", "NMM", "NR1-D", "NR1-C", "OAM", "LTE0", "LTE1"};
    char temp_name[32] = {0};
    sprintf(temp_name, "PC802_DESCS_MR%d", pc802_port_id);
    const struct rte_memzone *mz = rte_memzone_lookup(temp_name);
    PC802_Descs_t *pDescs = (PC802_Descs_t *)mz->addr;
    print_mirrored_ep_cnts(&pDescs->mr);
    PC802_BAR_t *bar = (PC802_BAR_t *)gBar[0];
    PC802_BAR_Ext_t *ext = (PC802_BAR_Ext_t *)(gBar[0] + PC802_BAR_EXT_OFFSET);
    uint32_t dl_num[PC802_TRAFFIC_NUM];
    uint32_t ul_num[PC802_TRAFFIC_NUM+1];
    uint32_t t;
    uint32_t n, idx, mask;
    for (t = 0; t < 8; t++) {
        dl_num[t] = PC802_READ_REG(bar->TDNUM[t]);
        ul_num[t] = PC802_READ_REG(bar->RDNUM[t]);
    }
    dl_num[8] = PC802_READ_REG(bar->TDNUM8[0]);
    ul_num[8] = PC802_READ_REG(bar->RDNUM8[0]);
    for (t = 0; t <= PC802_TRAFFIC_OAM; t++) {
        mask = dl_num[t] - 1;
        idx = pDescs->mr.TEPCNT[t] & mask;
        char dl_name[32];
        char ul_name[32];
        sprintf(dl_name, "DL-%s", q_name[t]);
        for (n = 0; n < dl_num[t]; n++) {
            print_descriptor(&pDescs->dl[t][idx], dl_name, idx);
            idx = (idx+1) & mask;
        }
        mask = ul_num[t] - 1;
        idx = pDescs->mr.REPCNT[t] & mask;
        sprintf(ul_name, "UL-%s", q_name[t]);
        for (n = 0; n < ul_num[t]; n++) {
            print_descriptor(&pDescs->ul[t][idx], ul_name, idx);
            idx = (idx+1) & mask;
        }
    }
    {
        t = PC802_TRAFFIC_CTRL_4;
        mask = dl_num[t] - 1;
        idx = pDescs->mr.TEPCNT[t] & mask;
        char dl_name[32];
        char ul_name[32];
        sprintf(dl_name, "DL-%s", q_name[t]);
        for (n = 0; n < dl_num[t]; n++) {
            print_descriptor(&pDescs->dl7[0][idx], dl_name, idx);
            idx = (idx+1) & mask;
        }
        mask = ul_num[t] - 1;
        idx = pDescs->mr.REPCNT[t] & mask;
        sprintf(ul_name, "UL-%s", q_name[t]);
        for (n = 0; n < ul_num[t]; n++) {
            print_descriptor(&pDescs->ul7[0][idx], ul_name, idx);
            idx = (idx+1) & mask;
        }
    }
    {
        t = PC802_TRAFFIC_CTRL_5;
        mask = dl_num[t] - 1;
        idx = pDescs->mr.TEPCNT8[0] & mask;
        char dl_name[32];
        char ul_name[32];
        sprintf(dl_name, "DL-%s", q_name[t]);
        for (n = 0; n < dl_num[t]; n++) {
            print_descriptor(&pDescs->dl7[1][idx], dl_name, idx);
            idx = (idx+1) & mask;
        }
        mask = ul_num[t] - 1;
        idx = pDescs->mr.REPCNT8[0] & mask;
        sprintf(ul_name, "UL-%s", q_name[t]);
        for (n = 0; n < ul_num[t]; n++) {
            print_descriptor(&pDescs->ul7[1][idx], ul_name, idx);
            idx = (idx+1) & mask;
        }
    }
    {
        ul_num[PC802_TRAFFIC_NUM] = PC802_READ_REG(bar->MB_C2H_RDNUM);
        mask = ul_num[PC802_TRAFFIC_NUM] - 1;
        idx = PC802_READ_REG(ext->MB_C2H_EPCNT) & mask;
        sprintf(temp_name, "%s", "Mailbox");
        for (n = 0; n < ul_num[PC802_TRAFFIC_NUM]; n++) {
            print_descriptor(&pDescs->ul[PC802_TRAFFIC_OAM+1][idx], temp_name, idx);
            idx = (idx+1) & mask;
        }
    }
}

static void init_gBar(void)
{
    struct rte_eth_dev *eth_dev = &rte_eth_devices[pc802_port_id];
    struct rte_pci_device *pci_dev = RTE_ETH_DEV_TO_PCI(eth_dev);
    gBar[0] = pci_dev->mem_resource[0].addr;
    gBar[1] = pci_dev->mem_resource[1].addr;
    gBar[2] = pci_dev->mem_resource[2].addr;
}


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

int main(int argc, char** argv)
{
    int diag;

    printf("%s\n", picocom_pc802_version());
    printf("PC802 Reviewer built AT %s ON %s\n", __TIME__, __DATE__);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    diag = rte_eal_init(argc, argv);
    if (diag < 0)
        rte_panic("Cannot init EAL\n");

    if (RTE_PROC_PRIMARY == rte_eal_process_type()) {
        printf("This APP must be run as DPDK secondary task !");
        return -1;
    }

    pc802_port_id = pc802_get_port_id(0);

    init_gBar();
    print_bar0();
    print_pfi_mailbox();
    print_ecpri_mailbox();
    print_descs();

#if 0
    rte_eal_remote_launch(prompt, NULL, rte_lcore_count()-1);

    while(!main_stop) {
        usleep(1000);
    }

    usleep(5000);
#endif

    return 0;
}
