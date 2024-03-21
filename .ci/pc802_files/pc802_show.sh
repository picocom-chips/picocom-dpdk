#!/bin/bash
#
# PICOCOM PROPRIETARY INFORMATION
#
# This software is supplied under the terms of a license agreement or
# nondisclosure agreement with PICOCOM and may not be copied
# or disclosed except in accordance with the terms of that agreement.
#
# Copyright PICOCOM.
#

if [ $1 ];then
    index=$1
    bus=`lspci | awk  '/802/{i++;if(i=="'$index'"){print $1;exit;}}'`
else
    bus=`lspci | awk  '/802/{print $1;exit;}'`
fi
[ -z "$bus" ] && echo "Not found pc802 device" && exit 0
echo bus=$bus
lspci -v -s $bus 2> /dev/null
bar0=`lspci -v -s $bus 2> /dev/null | awk  '/Memory/{print $3;exit;}'`
bar1=`lspci -v -s $bus 2>/dev/null | awk '/Memory/{i++;if(i=="2"){print $3;exit;}}'`
bar2=`lspci -v -s $bus 2>/dev/null | awk '/Memory/{i++;if(i=="3"){print $3;exit;}}'`
[ -z "$bar0" ] && echo "Bar0 not found" && exit 0
echo BAR0:  0X$bar0
echo BAR1:  0X$bar1
echo BAR2:  0X$bar2
bar0=`printf %d 0x$bar0`
bar1=`printf %d 0x$bar1`
bar2=`printf %d 0x$bar2`
pos=0
cache=0
addr=0

function dislist(){
    a=$1
    str=""
    for((i=1;i<=$2;i++));
    do
        str=$str" "$(busybox devmem $a);
        ((a=$a+4))
    done
    echo $str
}

function discharlist(){
    a=$1
    str=""
    for((i=1;i<=$2;i++));
    do
        str=$str"    "$(busybox devmem $a 8);
        ((a=$a+1))
    done
    echo $str
}

echo
echo "    PC802 BAR0:"
#typedef struct PC802_BAR_t {
#    union {
((addr=$bar0))#        PC802_CacheLine_t _cahce_line;
#        struct {
echo "DEVEN: $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DEVEN;
echo "DEVRDY:$(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DEVRDY;
echo "DBAL:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBAL;
echo "DBAH:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBAH;
echo "ULDMAN:$(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t ULDMAN;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_tdnum;
#        uint32_t TDNUM[PC802_TRAFFIC_NUM];
echo TDNUM[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_trccnt;
#        uint32_t TRCCNT[PC802_TRAFFIC_NUM];
echo TRCCNT[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_tepcnt;
#        uint32_t TEPCNT[PC802_TRAFFIC_NUM];
echo TEPCNT[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_rdnum;
#        uint32_t RDNUM[PC802_TRAFFIC_NUM];
echo RDNUM[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_rrccnt;
#        uint32_t RRCCNT[PC802_TRAFFIC_NUM];
echo RRCCNT[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_repcnt;
#        uint32_t REPCNT[PC802_TRAFFIC_NUM];
echo REPCNT[PC802_TRAFFIC_NUM]:
dislist $addr 8
#    };
echo #	union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_brccnt;
#		struct {
echo "BOOTSRCL: $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTSRCL;
echo "BOOTSRCH: $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTSRCH;
echo "BOOTDST:  $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTDST;
echo "BOOTSZ:   $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTSZ;
echo "BOOTRCCNT:$(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTRCCNT;
echo "BOOTRSPL: $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTRSPL;
echo "BOOTRSPH: $(busybox devmem $addr)";((addr=$addr+4)) #			uint32_t BOOTRSPH;
#		};
#    };
echo #	union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_bepcnt;
#		struct {
echo BOOTEPCNT: $(busybox devmem $addr);((addr=$addr+4))    #		uint32_t BOOTEPCNT;
echo BOOTERROR: $(busybox devmem $addr);((addr=$addr+4))    #		uint32_t BOOTERROR;
echo BOOTDEBUG: $(busybox devmem $addr);((addr=$addr+4))    #       uint32_t BOOTDEBUG;
echo MB_HANDSHAKE: $(busybox devmem $addr);((addr=$addr+4)) #       uint32_t MB_HANDSHAKE;
#		};
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_macaddr;
#        struct {
echo MACADDRL: $(busybox devmem $addr);((addr=$addr+4)) #            uint32_t MACADDRL;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_debug_rcm;
#        struct {
echo DBGRCAL: $(busybox devmem $addr);((addr=$addr+4))      #       uint32_t DBGRCAL;
echo DBGRCAH: $(busybox devmem $addr);((addr=$addr+4))      #       uint32_t DBGRCAH;
echo MB_ANDES_DIS: $(busybox devmem $addr);((addr=$addr+4)) #       uint32_t MB_ANDES_DIS;
echo MB_DSP_DIS:   $(busybox devmem $addr);((addr=$addr+4)) #       uint32_t MB_DSP_DIS;
echo MB_C2H_RDNUM: $(busybox devmem $addr);((addr=$addr+4)) #       uint32_t MB_C2H_RDNUM;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_debug_rcc;
#        struct {
echo "DBGEPADDR:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBGEPADDR;
echo "DBGBYTESNUM:$(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBGBYTESNUM;
echo "DBGCMD:     $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBGCMD;
echo "DBGRCCNT:   $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DBGRCCNT;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_debug_ep;
echo DBGEPCNT: $(busybox devmem $addr);((addr=$addr+4)) #        uint32_t DBGEPCNT;
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_sync_ecpri;
#        struct {
echo "DRVSTATE:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t DRVSTATE;
echo "MEMCFGADDR:$(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t MEMCFGADDR;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cahce_line_ul_dma;
#        struct {
echo "ULDMA_TIMEOUT_FINISHED[4]:";dislist $addr 4  #       uint32_t ULDMA_TIMEOUT_FINISHED[4];
echo "ULDMA_TIMEOUT_ERROR[4]:";dislist $addr 4     #       uint32_t ULDMA_TIMEOUT_ERROR[4];
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))           #       PC802_CacheLine_t _cahce_line_dl_dma;
#        struct {
echo "DLDMA_TIMEOUT_FINISHED[4]:";dislist $addr 4   #       uint32_t DLDMA_TIMEOUT_FINISHED[4];
echo "DLDMA_TIMEOUT_ERROR[4]:";dislist $addr 4      #       uint32_t DLDMA_TIMEOUT_ERROR[4];
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_rx_tstamp;
#        struct {
#            uint32_t RX_TIMESTAMP0;
#            uint32_t RX_TIMESTAMP1;
#            uint32_t RX_TIMESTAMP2;
#            uint32_t RX_TIMESTAMP3;
#            uint32_t RX_TS_EPCNT;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_tx_tstamp;
#        struct {
#            uint32_t TX_TIMESTAMP0;
#            uint32_t TX_TIMESTAMP1;
#            uint32_t TX_TIMESTAMP2;
#            uint32_t TX_TIMESTAMP3;
#            uint32_t TX_TS_EPCNT;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_tstamp_mode;
#        struct {
#            uint32_t PTP_TIMESTAMP_MODE;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_timeadj;
#        struct {
#            uint32_t TIMEADJ0;
#            uint32_t TIMEADJ1;
#            uint32_t TIMEADJ2;
#            uint32_t TIMEADJ_CNT;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_freqadj;
#        struct {
#            int32_t  FREQADJ;
#            uint32_t FREQADJ_CNT;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_tstamp_rccnt;
#        struct {
#            uint32_t RX_TS_RCCNT;
#            uint32_t TX_TS_RCCNT;
#            uint32_t SYSTIM_RCCNT;
#            uint32_t SYSTIM_CMD;
#            uint32_t SYSTIM_RC1;
#            uint32_t SYSTIM_RC2;
#            uint32_t SYSTIM_RC3;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_systim_ep;
#        struct {
#            uint32_t SYSTIM_EPCNT;
#            uint32_t SYSTIM_EP1;
#            uint32_t SYSTIM_EP2;
#            uint32_t SYSTIM_EP3;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_io_req;
#        struct {
#            uint32_t IO_RCCNT;
#            uint32_t IO_CMD;
#            uint32_t IO_OFFSET;
#            uint32_t IO_REQ_DATA;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_io_rsp;
#        struct {
#            uint32_t IO_EPCNT;
#            uint32_t IO_ERROR;
#            uint32_t IO_RSP_DATA;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_ul_slot_0;
#        struct {
echo "SFN_SLOT_0:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t SFN_SLOT_0;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_ul_slot_1;
#        struct {
echo "SFN_SLOT_1:  $(busybox devmem $addr)";((addr=$addr+4)) #            uint32_t SFN_SLOT_1;
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_tx_rst_req;
#        struct {
echo "TX_RST_RCCNT[PC802_TRAFFIC_NUM]:";dislist $addr 8 #            uint32_t TX_RST_RCCNT[PC802_TRAFFIC_NUM];
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_tx_rst_rsp;
#        struct {
echo "TX_RST_EPCNT[PC802_TRAFFIC_NUM]:";dislist $addr 8 #            uint32_t TX_RST_EPCNT[PC802_TRAFFIC_NUM];
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_rx_rst_req;
#        struct {
echo "RX_RST_RCCNT[PC802_TRAFFIC_NUM]:";dislist $addr 8 #            uint32_t RX_RST_RCCNT[PC802_TRAFFIC_NUM];
#        };
#    };
echo #    union {
((cache=$cache+32));((addr=$bar0+$cache))#        PC802_CacheLine_t _cache_line_rx_rst_rsp;
#        struct {
echo "RX_RST_EPCNT[PC802_TRAFFIC_NUM]:";dislist $addr 8 #            uint32_t RX_RST_EPCNT[PC802_TRAFFIC_NUM];
#        };
#    };
#} PC802_BAR_t;

echo
echo
((ext=$bar0+4096));((addr=$ext));((cache=0));printf "ext:0x%x\n" $addr
#struct PC802_BAR_Ext_t {
echo
#    union {
#        uint32_t _mb_dsp[8];
echo "Mailbox_RC_t MB_DSP[0-3]:" #        Mailbox_RC_t MB_DSP[3];
echo "rccnt result"
for value in {1..3}
do
    discharlist $addr 2;((addr=$addr+2))
done
#    };
((cache=$cache+4*8));((addr=$ext+$cache))

echo
#    union {
#        uint32_t _mb_pfi[8];
echo "Mailbox_RC_t MB_PFI[0-16]:"  #        Mailbox_RC_t MB_PFI[16];
echo "rccnt result"
for value in {1..16}
do
    discharlist $addr 2;((addr=$addr+2))
done
#    };
((cache=$cache+4*8));((addr=$ext+$cache))

echo
#    union {
#        uint32_t _mb_ecpri[8];
echo "Mailbox_RC_t MB_eCPRI[0-16]:"  #        Mailbox_RC_t MB_eCPRI[16];
echo "rccnt result"
for value in {1..16}
do
    discharlist $addr 2;((addr=$addr+2))
done
#    };
((cache=$cache+4*8));((addr=$ext+$cache))

echo
#    union {
#        uint32_t _a0[8];
#        struct {
echo "MB_C2H_EPCNT: $(busybox devmem $addr)";((addr=$addr+4))    #uint32_t MB_C2H_EPCNT;
echo "VEC_EPCNT:  	$(busybox devmem $addr)";((addr=$addr+4))    #uint32_t VEC_EPCNT;
#        };
#    };
((cache=$cache+4*8));((addr=$ext+$cache))

echo
#    union {
#        uint32_t _a1[8];
#        struct {
echo "MB_C2H_RCCNT: $(busybox devmem $addr)";((addr=$addr+4))  #uint32_t MB_C2H_RCCNT;
echo "VEC_RCCNT:    $(busybox devmem $addr)";((addr=$addr+4))  #uint32_t VEC_RCCNT;
echo "VEC_BUFSIZE:  $(busybox devmem $addr)";((addr=$addr+4))  #uint32_t VEC_BUFSIZE;
echo "VEC_BUFADDRL: $(busybox devmem $addr)";((addr=$addr+4))  #uint32_t VEC_BUFADDRL;
echo "VEC_BUFADDRH: $(busybox devmem $addr)";((addr=$addr+4))  #uint32_t VEC_BUFADDRH;
#        };
#    };
((cache=$cache+4*8));((addr=$ext+$cache));

echo
echo "TRACE_RCCNT[0-32]:" #uint32_t TRACE_RCCNT[32];
dislist $addr 8;((addr=$addr+4*8))
dislist $addr 8;((addr=$addr+4*8))
dislist $addr 8;((addr=$addr+4*8))
dislist $addr 8;((addr=$addr+4*8))
((cache=$cache+4*32));((addr=$ext+$cache))

echo
echo "TRACE_EPCNT[0-32]:" #TraceEpCnt_u TRACE_EPCNT[32];
echo "    v            s"
for value in {1..32}
do
    dislist $addr 2;((addr=$addr+32))
done
((cache=$cache+4*8*32));((addr=$ext+$cache))

echo
echo "TRACE_DATA[32]:" #TraceData_t TRACE_DATA[32];
for value in {1..32}
do
    dislist $addr 16;((addr=$addr+4*16))
done
((cache=$cache+4*16*32));((addr=$ext+$cache))

echo
    #union {
    #    uint32_t _dump[16];
echo "DUMP_RC[32]:"  #    Mailbox_RC_t DUMP_RC[32];
echo "rccnt result"
for value in {1..32}
do
    discharlist $addr 2;((addr=$addr+2))
done
    #};
#} __attribute__((__aligned__(32)));



#adapter->mailbox_info_pfi = (mailbox_info_exclusive *)((uint8_t*)pci_dev->mem_resource[1].addr);
#adapter->mailbox_pfi   = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[1].addr + 0x580);

#adapter->mailbox_ecpri = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[2].addr);
#adapter->mailbox_info_ecpri = (mailbox_info_exclusive *)((uint8_t *)pci_dev->mem_resource[2].addr + sizeof(mailbox_exclusive) * 16);

#for (dsp = 0; dsp < 3; dsp++) {
#    adapter->mailbox_dsp[dsp] = (mailbox_exclusive *)((uint8_t *)pci_dev->mem_resource[0].addr + 0x2000 + 0x400 * dsp);
#}

#typedef struct {
#    volatile mailbox_registry_t * m_registry_ptr;
#    volatile magic_mailbox_t    * m_c2h_ptr;
#    volatile magic_mailbox_t    * m_h2c_ptr;
#    uint32_t          m_handler_count;
#    mailbox_handler_t m_handlers[8];
#    uint32_t m_next_c2h;
#    uint32_t m_next_h2c;
#} mailbox_info_exclusive[16];   //(4+2*8+2)*4*16 = 1408 = 0x580

#typedef struct {
#    union u0 {
#        volatile uint32_t wrs[8];
#        volatile uint8_t wr[16];
#    } u0;
#    union u1 {
#        volatile uint32_t rds[2][4];
#        volatile uint8_t rd[2][16];
#    } u1;
#    volatile uint32_t rg;
#    uint32_t last_cycle;
#    uint32_t pcie_msg_interval_in_ms;
#    uint32_t pad[5];
#} mailbox_counter_t;           //(8+2*4+8)*4 = 24*4 = 96 = 0x60

echo 
echo pfi mailbox counter:
((cache=1408));((addr=$bar1+$cache))
echo wr[16]:
discharlist $addr 16

((cache=$cache+32));((addr=$bar1+$cache))
echo rd[0][16]:
discharlist $addr 16

((cache=$cache+16));((addr=$bar1+$cache))
echo rd[1][16]:
discharlist $addr 16

((cache=$cache+16));((addr=$bar1+$cache))
echo "rg:                      $(busybox devmem $addr)";((addr=$addr+4))
echo "last_cycle:              $(busybox devmem $addr)";((addr=$addr+4))
echo "pcie_msg_interval_in_ms: $(busybox devmem $addr)";((addr=$addr+4))
echo 

echo ecpri mailbox counter:
((cache=1408));((addr=$bar2+$cache))
echo wr[16]:
discharlist $addr 16

((cache=$cache+32));((addr=$bar2+$cache))
echo rd[0][16]:
discharlist $addr 16

((cache=$cache+16));((addr=$bar2+$cache))
echo rd[1][16]:
discharlist $addr 16

((cache=$cache+16));((addr=$bar2+$cache))
echo "rg:                      $(busybox devmem $addr)";((addr=$addr+4))
echo "last_cycle:              $(busybox devmem $addr)";((addr=$addr+4))
echo "pcie_msg_interval_in_ms: $(busybox devmem $addr)";((addr=$addr+4))
echo 

#typedef struct {
#    volatile mailbox_registry_t m_mailboxes;   //5*4
#    volatile magic_mailbox_t    m_cpu_to_host[16];
#    volatile magic_mailbox_t    m_host_to_cpu[4];
#} mailbox_exclusive[16];       //

