#ifndef __PC802_COMMON_H__
#define __PC802_COMMON_H__

#include <stdint.h>
#include <stddef.h>

#define DIR_PCIE_DMA_DOWNLINK   1
#define DIR_PCIE_DMA_UPLINK     0

#define MIN_DESC_NUM    8
#define MAX_DESC_NUM  128

typedef enum PC802_Traffic_Type_e {
    PC802_TRAFFIC_ETHERNET,
    PC802_TRAFFIC_5G_EMBB_DATA,
    PC802_TRAFFIC_5G_EMBB_CTRL,
    PC802_TRAFFIC_5G_URLLC,
    PC802_TRAFFIC_4G_LTE_DATA,
    PC802_TRAFFIC_4G_LTE_CTRL,
    PC802_TRAFFIC_OAM,
    PC802_TRAFFIC_NUM
} PC802_Traffic_Type_e;

#define MAX_DL_CH_NUM   PC802_TRAFFIC_NUM
#define MAX_UL_CH_NUM   PC802_TRAFFIC_NUM

#define DEFAULT_PC802_5G_DESC_NUM   256

#define PC802_CACHE_LINE_SZ 32

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

#define  DBLOG(format, ...) \
    printf("%s : %u : " format, __func__, __LINE__, ##__VA_ARGS__)

#endif
