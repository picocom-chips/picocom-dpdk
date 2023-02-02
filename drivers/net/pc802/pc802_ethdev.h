/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#ifndef _PC802_ETHDEV_H_
#define _PC802_ETHDEV_H_

#include <stdint.h>

#include "rte_pmd_pc802.h"

#define MIN_DESC_NUM    8
#define MAX_DESC_NUM  4096

#define MAX_DL_CH_NUM   PC802_TRAFFIC_NUM
#define MAX_UL_CH_NUM   PC802_TRAFFIC_NUM

#define DEFAULT_PC802_5G_DESC_NUM   256

#define PC802_CACHE_LINE_SZ 32

#define PC802_DEBUG_BUF_SIZE    (4 * 1024 * 1024)

struct PC802_CacheLine_t{
    uint32_t _a[8];
} __attribute__((__aligned__(PC802_CACHE_LINE_SZ)));

typedef struct PC802_CacheLine_t PC802_CacheLine_t;

typedef struct PC802_BAR_t {
    union {
        PC802_CacheLine_t _cahce_line;
        struct {
            uint32_t DEVEN;
            uint32_t DEVRDY;
            uint32_t DBAL;
            uint32_t DBAH;
            uint32_t ULDMAN;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_tdnum;
        uint32_t TDNUM[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_trccnt;
        uint32_t TRCCNT[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_tepcnt;
        uint32_t TEPCNT[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_rdnum;
        uint32_t RDNUM[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_rrccnt;
        uint32_t RRCCNT[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_repcnt;
        uint32_t REPCNT[PC802_TRAFFIC_NUM];
    };
    union {
        PC802_CacheLine_t _cahce_line_brccnt;
        struct {
            uint32_t BOOTSRCL;
            uint32_t BOOTSRCH;
            uint32_t BOOTDST;
            uint32_t BOOTSZ;
            uint32_t BOOTRCCNT;
            uint32_t BOOTRSPL;
            uint32_t BOOTRSPH;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_bepcnt;
        struct {
            uint32_t BOOTEPCNT;
            uint32_t BOOTERROR;
            uint32_t BOOTDEBUG;
            uint32_t MB_HANDSHAKE;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_macaddr;
        struct {
            uint32_t MACADDRL;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_debug_rcm;
        struct {
            uint32_t DBGRCAL;
            uint32_t DBGRCAH;
            uint32_t MB_ANDES_DIS;
            uint32_t MB_DSP_DIS;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_debug_rcc;
        struct {
            uint32_t DBGEPADDR;
            uint32_t DBGBYTESNUM;
            uint32_t DBGCMD;
            uint32_t DBGRCCNT;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_debug_ep;
        uint32_t DBGEPCNT;
    };
    union {
        PC802_CacheLine_t _cahce_line_sync_ecpri;
        struct {
            uint32_t DRVSTATE;
            uint32_t MEMCFGADDR;
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_ul_dma;
        struct {
            uint32_t ULDMA_TIMEOUT_FINISHED[4];
            uint32_t ULDMA_TIMEOUT_ERROR[4];
        };
    };
    union {
        PC802_CacheLine_t _cahce_line_dl_dma;
        struct {
            uint32_t DLDMA_TIMEOUT_FINISHED[4];
            uint32_t DLDMA_TIMEOUT_ERROR[4];
        };
    };
    union {
        PC802_CacheLine_t _cache_line_rx_tstamp;
        struct {
            uint32_t RX_TIMESTAMP0;
            uint32_t RX_TIMESTAMP1;
            uint32_t RX_TIMESTAMP2;
            uint32_t RX_TIMESTAMP3;
            uint32_t RX_TS_EPCNT;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_tx_tstamp;
        struct {
            uint32_t TX_TIMESTAMP0;
            uint32_t TX_TIMESTAMP1;
            uint32_t TX_TIMESTAMP2;
            uint32_t TX_TIMESTAMP3;
            uint32_t TX_TS_EPCNT;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_tstamp_mode;
        struct {
            uint32_t PTP_TIMESTAMP_MODE;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_timeadj;
        struct {
            uint32_t TIMEADJ0;
            uint32_t TIMEADJ1;
            uint32_t TIMEADJ2;
            uint32_t TIMEADJ_CNT;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_freqadj;
        struct {
            int32_t  FREQADJ;
            uint32_t FREQADJ_CNT;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_tstamp_rccnt;
        struct {
            uint32_t RX_TS_RCCNT;
            uint32_t TX_TS_RCCNT;
            uint32_t SYSTIM_RCCNT;
            uint32_t SYSTIM_CMD;
            uint32_t SYSTIM_RC1;
            uint32_t SYSTIM_RC2;
            uint32_t SYSTIM_RC3;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_systim_ep;
        struct {
            uint32_t SYSTIM_EPCNT;
            uint32_t SYSTIM_EP1;
            uint32_t SYSTIM_EP2;
            uint32_t SYSTIM_EP3;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_io_req;
        struct {
            uint32_t IO_RCCNT;
            uint32_t IO_CMD;
            uint32_t IO_OFFSET;
            uint32_t IO_REQ_DATA;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_io_rsp;
        struct {
            uint32_t IO_EPCNT;
            uint32_t IO_ERROR;
            uint32_t IO_RSP_DATA;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_ul_slot_0;
        struct {
            uint32_t SFN_SLOT_0;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_ul_slot_1;
        struct {
            uint32_t SFN_SLOT_1;
        };
    };
    union {
        PC802_CacheLine_t _cache_line_tx_rst_req;
        struct {
            uint32_t TX_RST_RCCNT[PC802_TRAFFIC_NUM];
        };
    };
    union {
        PC802_CacheLine_t _cache_line_tx_rst_rsp;
        struct {
            uint32_t TX_RST_EPCNT[PC802_TRAFFIC_NUM];
        };
    };
    union {
        PC802_CacheLine_t _cache_line_rx_rst_req;
        struct {
            uint32_t RX_RST_RCCNT[PC802_TRAFFIC_NUM];
        };
    };
    union {
        PC802_CacheLine_t _cache_line_rx_rst_rsp;
        struct {
            uint32_t RX_RST_EPCNT[PC802_TRAFFIC_NUM];
        };
    };
} PC802_BAR_t;

#define PC802_DEVEN             (offsetof(PC802_BAR_t,   DEVEN))
#define PC802_DEVRDY            (offsetof(PC802_BAR_t,   DEVRDY))
#define PC802_DBAL              (offsetof(PC802_BAR_t,   DBAL))
#define PC802_DBAH              (offsetof(PC802_BAR_t,   DBAH))

#define PC802_TDNUM(n)          (offsetof(PC802_BAR_t, TDNUM[0]) + sizeof(uint32_t) * (n))
#define PC802_TRCCNT(n)         (offsetof(PC802_BAR_t, TRCCNT[0]) + sizeof(uint32_t) * (n))
#define PC802_TEPCNT(n)         (offsetof(PC802_BAR_t, TEPCNT[0]) + sizeof(uint32_t) * (n))

#define PC802_RDNUM(n)          (offsetof(PC802_BAR_t, RDNUM[0]) + sizeof(uint32_t) * (n))
#define PC802_RRCCNT(n)         (offsetof(PC802_BAR_t, RRCCNT[0]) + sizeof(uint32_t) * (n))
#define PC802_REPCNT(n)         (offsetof(PC802_BAR_t, REPCNT[0]) + sizeof(uint32_t) * (n))


#define NPU_CACHE_LINE_SZ   64

typedef struct stPC802_Descriptor_t{
    uint64_t phy_addr;  // pointer to start physical address of a buffer in NPU memory
    uint32_t length;    // length of content to be sent in bytes
    uint8_t  eop;       // end of packet, 0=not the last descriptor for a whole message, 1=last descriptor
    uint8_t  type;      // packet type, 1=control, 0=data, this field is not used for Ethernet
} PC802_Descriptor_t;

struct stPC802_EP_Counter_Mirror_t {
    union {
        PC802_CacheLine_t   cache_line_tepcnt;
        volatile uint32_t TEPCNT[MAX_DL_CH_NUM];
    };
    union {
        PC802_CacheLine_t   cache_line_repcnt;
        volatile uint32_t REPCNT[MAX_UL_CH_NUM];
    };
} __attribute__((__aligned__(NPU_CACHE_LINE_SZ)));

typedef struct stPC802_EP_Counter_Mirror_t PC802_EP_Counter_Mirror_t;

typedef struct PC802_Descs_t {
    PC802_Descriptor_t  dl[MAX_DL_CH_NUM][MAX_DESC_NUM];
    PC802_Descriptor_t  ul[MAX_UL_CH_NUM][MAX_DESC_NUM];
    PC802_EP_Counter_Mirror_t  mr;
} PC802_Descs_t;

static inline uint32_t get_dl_desc_offset(uint32_t ch, uint32_t idx)
{
    return (ch * MAX_DESC_NUM + idx) * sizeof(PC802_Descriptor_t);
}

static inline uint32_t get_ul_desc_offset(uint32_t ch, uint32_t idx)
{
    return (MAX_DL_CH_NUM * MAX_DESC_NUM + ch * MAX_DESC_NUM + idx) * sizeof(PC802_Descriptor_t);
}

static inline uint32_t get_ep_counter_mirror_offset(void)
{
    return (MAX_DL_CH_NUM + MAX_UL_CH_NUM) * MAX_DESC_NUM * sizeof(PC802_Descriptor_t);
}

static inline int isPowerOf2(uint32_t n)
{
    return n && !(n & (n - 1));
}

typedef union TraceEpCnt_u {
    uint32_t _d[8];
    struct {
        uint32_t v;
        uint32_t s;
    };
} TraceEpCnt_u;

#define PC802_TRACE_FIFO_SIZE   16

typedef struct {
    uint32_t d[PC802_TRACE_FIFO_SIZE];
} TraceData_t;

typedef struct {
    uint8_t rccnt;
    uint8_t result;
} Mailbox_RC_t;

struct PC802_BAR_Ext_t {
    union {
        uint32_t _mb_dsp[8];
        Mailbox_RC_t MB_DSP[3];
    };
    union {
        uint32_t _mb_pfi[8];
        Mailbox_RC_t MB_PFI[16];
    };
    union {
        uint32_t _mb_ecpri[8];
        Mailbox_RC_t MB_eCPRI[16];
    };
    union {
        uint32_t _a0[8];
        struct {
            uint32_t VEC_EPCNT;
        };
    };
    union {
        uint32_t _a1[8];
        struct {
            uint32_t MB_RESULT;
            uint32_t VEC_RCCNT;
            uint32_t VEC_BUFSIZE;
            uint32_t VEC_BUFADDRL;
            uint32_t VEC_BUFADDRH;
        };
    };
    uint32_t TRACE_RCCNT[32];
    TraceEpCnt_u TRACE_EPCNT[32];
    TraceData_t TRACE_DATA[32];
} __attribute__((__aligned__(32)));

typedef struct PC802_BAR_Ext_t  PC802_BAR_Ext_t;

#define NUM_CORES_PFI       16
#define NUM_CORES_ECPRI     16
#define NUM_CORES_DSP       3

#define MB_NUM_ARGS              8
#define MB_NUM_HANDLERS          8
#define MB_HANDSHAKE_HOST_LEGACY 0xBEEFBEEF
#define MB_HANDSHAKE_HOST_RINGS  0xCAFECAFE
#define MB_HANDSHAKE_CPU         0xF00DF00D
#define MB_HANDSHAKE_READY       0xDEADDEAD

typedef enum {
    MB_EMPTY=0,                 //  0 - Idle, no action to perform
    MB_PRINTF,                  //  1 - Semi-hosted printf function
    MB_SIM_STOP,                //  2 - Stop simulation with exit code (0 - ok, 1+ - error)
    MB_RUN_TESTCASE,            //  3 - Trigger a testcase scenario
    MB_READ_REGISTER,           //  4 - Perform a word read operation
    MB_WRITE_REGISTER,          //  5 - Perform a word write operation
    MB_CONTROL_CPU,             //  6 - Control CPU features (like caching)
    MB_RUN_SYS_CRG,             //  7 - Trigger system CRG configuration
    MB_RUN_GRAPH_DEMO_TESTCASE, //  8 - Trigger graph demo test sequence
    MB_RUN_LPDDR4_TESTCASE,     //  9 - Trigger LPDDR4 test sequence
    MB_TG_LOAD,                 // 10 - Trigger task graph load (host side)
    MB_TG_CHECK,                // 11 - Trigger task graph check (host side)
    MB_VEC_READ,                // 12 - Trigger vector read (host side)
    MB_VEC_DUMP,                // 13 - Trigger vector dump (host side)
    MB_ATLL_ALLOC,              // 14 - ATLL allocate
    MB_ATLL_RECV_END,           // 15 - ATLL receive
    MB_ATLL_SEND,               // 16 - ATLL transmit
    MB_CACHE_WRITEBACK,         // 17 - Trigger cache writeback
    MB_CACHE_INVALIDATE,        // 18 - Trigger cache invalidation
    MB_CACHE_FLUSH,             // 19 - Trigger cache flush
    MB_PING,                    // 20 - Keepalive test (returns arg 0)
    MB_IRQ_CONTROL,             // 21 - Control IRQ handling
    MB_IRQ_CAUGHT,              // 22 - Notify interrupt was caught
    MB_CRC32,                   // 23 - Calculate crc32
    GPIO_CTRL,                  // 24 - Access and control GPIO
    VIC_TIMER,                  // 25 - Access and control the XC12 VIC's timer
    ANALYTICS,                  // 26
    MB_VEC_BIN_READ,            // 27 - Trigger binary file read (host side)
    MB_VEC_BIN_DUMP,            // 28 - Trigger binary file dump (host side)
    MB_RPC_CALL,                // 29 - Trigger RPC call
    MB_DDR_RUNNING,             // 30 - Notify host DDR is running
} mailbox_action_t;

typedef struct {
    uint32_t         action;                 // 0x00
    uint32_t         num_args;               // 0x04
    uint32_t         retval;                 // 0x08
    uint32_t         error;                  // 0x0C
    uint32_t         arguments[MB_NUM_ARGS]; // 0x10+
} magic_mailbox_t;

typedef struct {
    uint32_t                   handshake;
    uint32_t                   ptr_cpu_to_host;
    uint32_t                   ptr_host_to_cpu;
    uint32_t                   c2h_ring_count;
    uint32_t                   h2c_ring_count;
    uint32_t                   mailbox_size;
} mailbox_registry_t;

#define MB_MAX_C2H_MAILBOXES 16
#define MB_MAX_H2C_MAILBOXES 4

typedef struct {
    mailbox_registry_t m_mailboxes;
    magic_mailbox_t    m_cpu_to_host[MB_MAX_C2H_MAILBOXES];
    magic_mailbox_t    m_host_to_cpu[MB_MAX_H2C_MAILBOXES];
} mailbox_exclusive;

typedef struct {
    uint32_t action;
    uint32_t func_ptr;
} mailbox_handler_t;

typedef struct {
    volatile uint32_t  m_registry_ptr;
    volatile uint32_t  m_c2h_ptr;
    volatile uint32_t  m_h2c_ptr;
    uint32_t          m_handler_count;
    mailbox_handler_t m_handlers[MB_NUM_HANDLERS];
    uint32_t m_next_c2h;
    uint32_t m_next_h2c;
} mailbox_info_exclusive;

typedef struct {
    union {
        uint32_t wrs[8];
        uint8_t wr[16];
    };
    union {
        uint32_t rds[2][4];
        uint8_t rd[2][16];
    };
    uint32_t rg;
} mailbox_counter_t;

#define MAILBOX_COUNTER_OFFSET_PFI \
    (sizeof(mailbox_info_exclusive) * NUM_CORES_PFI + sizeof(mailbox_exclusive) * NUM_CORES_PFI)

#define MAILBOX_COUNTER_OFFSET_ECPRI \
    (sizeof(mailbox_exclusive) * NUM_CORES_ECPRI + sizeof(mailbox_info_exclusive) * NUM_CORES_ECPRI)

#define MAILBOX_MEM_SIZE_PER_DSP    0x400
#define MAILBOX_COUNTER_OFFSET_DSP (MAILBOX_MEM_SIZE_PER_DSP * NUM_CORES_DSP)

int pc802_kni_add_port(uint16_t port);
uint32_t pc802_get_sfn_slot(uint16_t port_id, uint32_t cell_index);
uint16_t pc802_get_index_by_name(const char *name);

enum {
	PC802_FLAG_RX = 1,
	PC802_FLAG_TX = 2,
};

int pc802_pdump_init(void);
int pc802_pdump_uninit(void);
uint16_t pdump_cb(uint16_t pc802_index, uint16_t queue_id, uint16_t rxtx_flag, PC802_Mem_Block_t **blks, uint16_t nb_blks, uint64_t last_tsc);

#endif /* _PC802_ETHDEV_H_ */
