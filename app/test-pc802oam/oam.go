package main

/*
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#include <rte_config.h>
#include <rte_common.h>
#include <rte_ethdev.h>
#include <rte_pmd_pc802.h>
#include <pcxx_oam.h>
#include "ecpri_oam_inf.h"
//#cgo LDFLAGS: -static
#cgo LDFLAGS: -Wl,--as-needed -L/usr/local/lib/x86_64-linux-gnu -pthread -lm -ldl -lnuma -lpcap -lrte_common_cpt -lrte_common_dpaax -lrte_common_iavf -lrte_common_octeontx -lrte_common_octeontx2 -lrte_bus_auxiliary -lrte_bus_dpaa -lrte_bus_fslmc -lrte_bus_ifpga -lrte_bus_pci -lrte_bus_vdev -lrte_bus_vmbus -lrte_common_cnxk -lrte_common_sfc_efx -lrte_mempool_bucket -lrte_mempool_cnxk -lrte_mempool_dpaa -lrte_mempool_dpaa2 -lrte_mempool_octeontx -lrte_mempool_octeontx2 -lrte_mempool_ring -lrte_mempool_stack -lrte_net_af_packet -lrte_net_ark -lrte_net_atlantic -lrte_net_avp -lrte_net_axgbe -lrte_net_bnx2x -lrte_net_bnxt -lrte_net_bond -lrte_net_cnxk -lrte_net_cxgbe -lrte_net_dpaa -lrte_net_dpaa2 -lrte_net_e1000 -lrte_net_ena -lrte_net_enetc -lrte_net_enic -lrte_net_failsafe -lrte_net_fm10k -lrte_net_hinic -lrte_net_hns3 -lrte_net_i40e -lrte_net_iavf -lrte_net_ice -lrte_net_igc -lrte_net_ionic -lrte_net_ixgbe -lrte_net_kni -lrte_net_liquidio -lrte_net_memif -lrte_net_netvsc -lrte_net_nfp -lrte_net_ngbe -lrte_net_null -lrte_net_octeontx -lrte_net_octeontx2 -lrte_net_octeontx_ep -lrte_net_pcap -lrte_net_pc802 -lrte_net_pfe -lrte_net_qede -lrte_net_ring -lrte_net_sfc -lrte_net_softnic -lrte_net_tap -lrte_net_thunderx -lrte_net_txgbe -lrte_net_vdev_netvsc -lrte_net_vhost -lrte_net_virtio -lrte_net_vmxnet3 -lrte_raw_cnxk_bphy -lrte_raw_dpaa2_cmdif -lrte_raw_dpaa2_qdma -lrte_raw_ioat -lrte_raw_ntb -lrte_raw_octeontx2_dma -lrte_raw_octeontx2_ep -lrte_raw_skeleton -lrte_crypto_bcmfs -lrte_crypto_caam_jr -lrte_crypto_cnxk -lrte_crypto_dpaa_sec -lrte_crypto_dpaa2_sec -lrte_crypto_nitrox -lrte_crypto_null -lrte_crypto_octeontx -lrte_crypto_octeontx2 -lrte_crypto_scheduler -lrte_crypto_virtio -lrte_compress_octeontx -lrte_compress_zlib -lrte_regex_octeontx2 -lrte_vdpa_ifc -lrte_event_cnxk -lrte_event_dlb2 -lrte_event_dpaa -lrte_event_dpaa2 -lrte_event_dsw -lrte_event_octeontx2 -lrte_event_opdl -lrte_event_skeleton -lrte_event_sw -lrte_event_octeontx -lrte_baseband_acc100 -lrte_baseband_fpga_5gnr_fec -lrte_baseband_fpga_lte_fec -lrte_baseband_null -lrte_baseband_turbo_sw -lrte_node -lrte_graph -lrte_bpf -lrte_flow_classify -lrte_pipeline -lrte_table -lrte_port -lrte_fib -lrte_ipsec -lrte_vhost -lrte_stack -lrte_security -lrte_sched -lrte_reorder -lrte_rib -lrte_regexdev -lrte_rawdev -lrte_pdump -lrte_power -lrte_member -lrte_lpm -lrte_latencystats -lrte_kni -lrte_jobstats -lrte_ip_frag -lrte_gso -lrte_gro -lrte_eventdev -lrte_efd -lrte_distributor -lrte_cryptodev -lrte_compressdev -lrte_cfgfile -lrte_bitratestats -lrte_bbdev -lrte_acl -lrte_timer -lrte_hash -lrte_metrics -lrte_cmdline -lrte_pci -lrte_ethdev -lrte_meter -lrte_net -lrte_mbuf -lrte_mempool -lrte_rcu -lrte_ring -lrte_eal -lrte_telemetry -lrte_kvargs -lrte_node -lrte_graph -lrte_bpf -lrte_flow_classify -lrte_pipeline -lrte_table -lrte_port -lrte_fib -lrte_ipsec -lrte_vhost -lrte_stack -lrte_security -lrte_sched -lrte_reorder -lrte_rib -lrte_regexdev -lrte_rawdev -lrte_pdump -lrte_power -lrte_member -lrte_lpm -lrte_latencystats -lrte_kni -lrte_jobstats -lrte_ip_frag -lrte_gso -lrte_gro -lrte_eventdev -lrte_efd -lrte_distributor -lrte_cryptodev -lrte_compressdev -lrte_cfgfile -lrte_bitratestats -lrte_bbdev -lrte_acl -lrte_timer -lrte_hash -lrte_metrics -lrte_cmdline -lrte_pci -lrte_ethdev -lrte_meter -lrte_net -lrte_mbuf -lrte_mempool -lrte_rcu -lrte_ring -lrte_eal -lrte_telemetry -lrte_kvargs
#cgo CFLAGS: -I/usr/local/include -I/usr/local/include -march=native

sem_t g_sem;
uint32_t g_seq_id;
uint8_t *g_rx_buf;
uint32_t g_rx_len;

#if 0
int pcxx_oam_send_original_msg(uint16_t dev_index, const uint8_t *buf, uint32_t len)
{
	printf("pc802 %d send msg %d: %x ... %x\n", dev_index, len, buf[0], buf[len-1]);
	return 0;
}

int pcxx_oam_recv_register(pcxx_oam_recv_cb_fn cb_fun)
{
	return 0;
}
#endif

static int32_t send_oam_req(uint16_t dev_index, uint8_t *tx_buf, uint32_t tx_len, uint8_t *rx_buf)
{
    struct timespec ts;

	g_rx_buf = rx_buf;
	g_rx_len = 0;
	g_seq_id = rand();
	((oam_msg_head_t*)tx_buf)->seq_id = g_seq_id;

	sem_init(&g_sem, 0, 0);
	if (0 == pcxx_oam_send_original_msg(dev_index, tx_buf, tx_len)) {
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;
        if (0 != sem_timedwait(&g_sem, &ts)){
            printf("oam wait rsp timeout!\n");
#if 0
			memcpy(rx_buf, tx_buf, tx_len+64);
			pcxx_oam_sub_msg_t *sub = (pcxx_oam_sub_msg_t *)(((oam_msg_head_t*)rx_buf)+1);
			sub->msg_id++;
			sub->msg_size = 48;
			((oam_tlvs_t*)(&sub->msb_body[2]))->length = 32;
			return tx_len+64;
#endif
			return 0;
		}
    } else{
        printf("send oam msg err!\n");
		return -1;
	}

    return g_rx_len;
}

int oam_recv_cb(uint16_t dev, const uint8_t* buf, uint32_t len)
{
    //printf( "Dev %d recv oam msg %d\n", dev, len );

	if ( ((oam_msg_head_t*)buf)->seq_id == g_seq_id )
	{
		memcpy(g_rx_buf, buf, len);
		g_rx_len = len;
		sem_post(&g_sem);
	}

	return 0;
}

static int oam_init()
{
    int port_id = 0;
    int pc802_index = 0;
	char *argc[4];

    printf("PC802 OAM tester built AT %s ON %s\n", __TIME__, __DATE__);

	argc[0] = "go_oam";
	argc[1] = "-n4";
	argc[2] = "--proc-type=secondary";
	argc[3] = "-l0";

    if (rte_eal_init(4, argc) < 0)
        rte_panic("Cannot init EAL\n");

    pcxx_oam_init();
    for ( pc802_index=0; pc802_index<PC802_INDEX_MAX; pc802_index++ )
    {
        port_id = pc802_get_port_id(pc802_index);
        if (port_id < 0)
            break;
        rte_eth_dev_start(port_id);
    }

	srand((intptr_t)&g_seq_id);
	sem_init(&g_sem, 0, 0);

	pcxx_oam_recv_register(oam_recv_cb);

	return 0;
}

*/
import "C"

import (
	"bytes"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	"strconv"
	"strings"
	"unsafe"

	"github.com/c-bata/go-prompt"
)

type macAddr struct {
	b [6]byte
}

func (m macAddr) MarshalJSON() ([]byte, error) {
	var s = fmt.Sprintf("\"%02x:%02x:%02x:%02x:%02x:%02x\"", m.b[0], m.b[1], m.b[2], m.b[3], m.b[04], m.b[5])
	return []byte(s), nil
}

func (m *macAddr) UnmarshalJSON(b []byte) error {
	fmt.Sscanf(string(b), "\"%02x:%02x:%02x:%02x:%02x:%02x\"", &m.b[0], &m.b[1], &m.b[2], &m.b[3], &m.b[04], &m.b[5])
	return nil
}

type antMask uint8

func (m antMask) MarshalJSON() ([]byte, error) {
	var s = fmt.Sprintf("\"%08b\"", m)
	return []byte(s), nil
}

func (m *antMask) UnmarshalJSON(b []byte) error {
	var v uint8
	fmt.Sscanf(string(b), "\"%b\"", &v)
	*m = antMask(v)
	return nil
}

type ecpri_base_config struct {
	Du_port_id_width     uint8 `json:"eAxC_ID du port id bits"`
	Bandsector_id_width  uint8 `json:"eAxC_ID bandsector id bits"`
	Cc_id_width          uint8 `json:"eAxC_ID cc id bits"`
	Ru_port_id_width     uint8 `json:"eAxC_ID ru port id bits"`
	One_way_delay_enable uint8 `json:"one way delay measurement switch(0:disable 1:enable)"`
	Ecpri_step_mode      uint8 `json:"ecpri step mode(0:1-step 1:2-step)"`
	Reserve              uint16
}

type eth_config struct {
	Eth_type   uint8   `json:"ethernet type(0:25G 1:10G)"`
	Nic_enable uint8   `json:"NIC enable(0:disable 1:enable)"`
	Mac        macAddr `json:"MAC address"`
	Mtu        uint16  `json:"MTU(1536~9600)"`
	Mvlan      uint16  `json:"M-Plane vlan(0~4095 0:untag)"`
	Reserve    uint32
}

type ptp_config struct {
	Enable          uint8 `json:"enable(0:disable 1:enable)"`
	Step_mode       uint8 `json:"ptp step mode(0:1-step 1:2-step)"`
	Domain          uint8 `json:"domain(0~31)"`
	Announce_freq   uint8 `json:"announce freq(0~6:2^0~2^6)"`
	Sync_freq       uint8 `json:"sync freq(0~6:2^0~2^6)"`
	Delay_freq      uint8 `json:"delay freq(0~6:2^0~2^6)"`
	Clock_class     uint8 `json:"clock class(0~255)"`
	Clock_priority1 uint8 `json:"clock priority1(0~255)"`
	Clock_priority2 uint8 `json:"clock priority2(0~255)"`
	Reserve0        uint8
	Reserve1        uint16
}

type ru_base_config struct {
	Mac       macAddr
	Uvlan     uint16 `json:"U-Plane vlan(0~4095 0:untag)"`
	Cvlan     uint16 `json:"C-Plane vlan(0~4095 0:untag)"`
	Cp_enable uint8  `json:"C-Plane enable(0:disable 1:enable)"`
	Reserve0  uint8
	Reserve1  uint32
}

type ru_compression struct {
	Static_mode     uint8 `json:"static mode(0:non-static 1:static-mode)"`
	Method          uint8 `json:"method(0:no compression 1:BFP)"`
	Comp_iq_width   uint8 `json:"comp iq width(0|8|9|12|14)"`
	Decomp_iq_width uint8 `json:"decomp iq width(0|8|9|12|14)"`
}

type ru_trans_win struct {
	Ta4_min       uint32
	Ta4_max       uint32
	Tcp_adv_dl    uint32
	T1a_min_cp_ul uint32
	T1a_max_cp_ul uint32
	T1a_min_cp_dl uint32
	T1a_max_cp_dl uint32
	T1a_min_up    uint32
	T1a_max_up    uint32
}

type cell_config struct {
	Ru_id         uint32  `json:"ru id"`
	Tx_ant_mask   antMask `json:"ru TX ant mask"`
	Rx_ant_mask   antMask `json:"ru RX ant mask"`
	Bandsector_id uint8   `json:"bandsector id"`
	Reserve0      uint8   `json:"reserve0"`
	Reserve1      uint32  `json:"reserve1"`
}

type msgHead struct {
	startFlag uint32
	msgType   uint32
	seqId     uint32
	subMsgNum uint32
}

type tagInfo struct {
	tag       uint16
	indexNum  int
	valueSise int
}

type globalConfig struct {
	dev      uint16
	msgType  uint16
	module   uint16
	autoSave bool
	log      bool
}

var cmdCfg globalConfig

func tlvEncode(tag uint16, value []byte) ([]byte, error) {
	buf := new(bytes.Buffer)
	// 写入TAG
	if err := binary.Write(buf, binary.LittleEndian, tag); err != nil {
		return nil, err
	}
	// 写入len
	if err := binary.Write(buf, binary.LittleEndian, uint16(len(value))); err != nil {
		return nil, err
	}
	// 写入数据
	if err := binary.Write(buf, binary.LittleEndian, value); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func tlvDecode(b []byte) (uint16, []byte, error) {
	//fmt.Printf("tlvDecode: %s\n", hex.EncodeToString(b))
	buf := bytes.NewBuffer(b)
	var tag, length uint16
	// 读取tag
	if err := binary.Read(buf, binary.LittleEndian, &tag); err != nil {
		return 0, nil, err
	}
	// 读取length
	if err := binary.Read(buf, binary.LittleEndian, &length); err != nil {
		return 0, nil, err
	}
	// 读取数据
	value := make([]byte, length)
	if err := binary.Read(buf, binary.LittleEndian, &value); err != nil {
		return 0, nil, err
	}
	//fmt.Printf("result: %x %d %s\n", tag, length, hex.EncodeToString(value))
	return tag, value, nil
}

func getIndexNum(tag uint16) uint16 {
	table := tag & 0xff00
	if (table == C.ECPRI_OAM_BASE_CFG&0xFF00) || (table == C.ECPRI_OAM_PTP_CFG&0xFF00) {
		return 0
	} else {
		return 1
	}
	return 0
}

func eCpriGetRspProc(subMsgBody []byte) (string, error) {
	//todo: get Number of TLVs

	tag, value, err := tlvDecode(subMsgBody[2:])
	if err != nil {
		return "", err
	}

	indexNum := getIndexNum(tag)
	indexNum *= 4

	var valueStr []byte
	var result string
	switch tag {
	case C.ECPRI_OAM_BASE_CFG:
		valueStruct := (*ecpri_base_config)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_BASE_INFO:
		valueStruct := *(*C.ecpri_base_info_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_ETHERNET_CFG:
		valueStruct := (*eth_config)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_ETHERNET_INFO:
		valueStruct := *(*C.ecpri_ethernet_status_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_ETHERNET_STATS:
		valueStruct := *(*C.ecpri_ethernet_stats_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_PTP_CFG:
		valueStruct := (*ptp_config)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_PTP_STATS:
		valueStruct := *(*C.ecpri_ptp_stats_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_RU_CFG:
		valueStruct := (*ru_base_config)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_UP_COMP_CFG:
		valueStruct := (*ru_compression)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_TRANSMISSION_WINDOWS_CFG:
		valueStruct := (*ru_trans_win)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_ONE_WAY_DELAY_MEASUREMENT_STATS:
		valueStruct := *(*C.ecpri_one_way_delay_stats_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_CELL_CFG:
		valueStruct := (*cell_config)(unsafe.Pointer(&value[indexNum]))
		valueStr, err = json.MarshalIndent(valueStruct, "", "    ")
	case C.ECPRI_OAM_CELL_STATS:
		valueStruct := *(*C.ecpri_cell_stats_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	case C.ECPRI_OAM_CELL_RESERVED_STATS:
		valueStruct := *(*C.ecpri_cell_reserved_stats_t)(unsafe.Pointer(&value[indexNum]))
		result = fmt.Sprintf("%+v", valueStruct)
	default:
		return "", fmt.Errorf("unknow tag: %x", tag)
	}
	if len(valueStr) > 0 {
		return string(valueStr), nil
	}
	return result, nil
}

func eCpriSetRspProc(subMsgBody []byte) (string, error) {
	val := binary.LittleEndian.Uint16(subMsgBody)
	if val == 0 {
		return "set rsp ok", nil
	}
	return "", fmt.Errorf("set rsp %d tlv err!", val)
}

func oamSubMsgProc(msgId uint16, msgBody []byte) (string, error) {
	switch msgId {
	case C.ECPRI_OAM_GET_RESP:
		return eCpriGetRspProc(msgBody)
	case C.ECPRI_OAM_SET_RESP:
		return eCpriSetRspProc(msgBody)
		//	case C.ECPRI_OAM_TEST_NTFY:
	}
	return "", fmt.Errorf("unknow msgid: %d", msgId)
}

func rspMsgProc(buf []byte) (string, error) {
	head := (*msgHead)(unsafe.Pointer(&buf[0]))
	if head.startFlag != C.OAM_START_FLAG {
		return "", fmt.Errorf("invalid head start flag: %x", head.startFlag)
	}
	switch head.msgType {
	case C.PCXX_OAM_MSG:
		msgId, msgBody, err := tlvDecode(buf[unsafe.Sizeof(*head):])
		if err != nil {
			return "", err
		}
		return oamSubMsgProc(msgId, msgBody)
	}
	return "", fmt.Errorf("unknow msg type: %d", head.msgType)
}

func makeGetReq(tag uint16, index []uint32) []byte {
	head := msgHead{
		startFlag: uint32(C.OAM_START_FLAG),
		msgType:   uint32(cmdCfg.msgType),
		seqId:     0,
		subMsgNum: 1,
	}
	buf := bytes.Buffer{}
	binary.Write(&buf, binary.LittleEndian, head)

	valueBuf := bytes.Buffer{}
	binary.Write(&valueBuf, binary.LittleEndian, index)
	body, _ := tlvEncode(tag, valueBuf.Bytes())

	subMsg := C.pcxx_oam_sub_msg_t{
		msg_id:   C.ECPRI_OAM_GET_REQ,
		msg_size: C.uint16_t(len(body) + 2),
	}

	binary.Write(&buf, binary.LittleEndian, subMsg)
	binary.Write(&buf, binary.LittleEndian, uint16(1))
	binary.Write(&buf, binary.LittleEndian, body)
	binary.Write(&buf, binary.LittleEndian, uint32(C.OAM_START_FLAG))

	return buf.Bytes()
}

func makeSetReq(tag uint16, index []uint32, file string) ([]byte, error) {
	head := msgHead{
		startFlag: uint32(C.OAM_START_FLAG),
		msgType:   uint32(cmdCfg.msgType),
		seqId:     0,
		subMsgNum: 1,
	}
	buf := bytes.Buffer{}
	binary.Write(&buf, binary.LittleEndian, head)

	valueBuf := bytes.Buffer{}
	binary.Write(&valueBuf, binary.LittleEndian, index)

	jsonFile, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	jsonBytes, err := ioutil.ReadAll(jsonFile)
	defer jsonFile.Close()

	switch tag {
	case C.ECPRI_OAM_BASE_CFG:
		var jsonConf ecpri_base_config
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_ETHERNET_CFG:
		var jsonConf eth_config
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_PTP_CFG:
		var jsonConf ptp_config
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_RU_CFG:
		var jsonConf ru_base_config
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_UP_COMP_CFG:
		var jsonConf ru_compression
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_TRANSMISSION_WINDOWS_CFG:
		var jsonConf ru_trans_win
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	case C.ECPRI_OAM_CELL_CFG:
		var jsonConf cell_config
		err = json.Unmarshal(jsonBytes, &jsonConf)
		if err != nil {
			return nil, err
		}
		binary.Write(&valueBuf, binary.LittleEndian, jsonConf)
	default:
		fmt.Printf("unknow tag %x\n", tag)
		return nil, errors.New("unknow tag")
	}

	body, _ := tlvEncode(tag, valueBuf.Bytes())

	subMsg := C.pcxx_oam_sub_msg_t{
		msg_id:   C.ECPRI_OAM_SET_REQ,
		msg_size: C.uint16_t(len(body) + 2),
	}

	binary.Write(&buf, binary.LittleEndian, subMsg)
	binary.Write(&buf, binary.LittleEndian, uint16(1)) //Number of TLVs
	binary.Write(&buf, binary.LittleEndian, body)
	binary.Write(&buf, binary.LittleEndian, uint32(C.OAM_START_FLAG))

	return buf.Bytes(), nil
}

func getTag(table string, tag string) (uint16, uint16) {
	var tagValue, indexNum uint16

	if table == "base" {
		tagValue = C.ECPRI_OAM_BASE_CFG
		indexNum = 0
		if tag == "config" {
			tagValue += 0
		} else if tag == "info" {
			tagValue += 1
		}
	} else if table == "eth" {
		tagValue = C.ECPRI_OAM_ETHERNET_CFG
		indexNum = 1
		if tag == "config" {
			tagValue += 0
		} else if tag == "status" {
			tagValue += 1
		} else if tag == "stats" {
			tagValue += 2
		}
	} else if table == "ptp" {
		tagValue = C.ECPRI_OAM_PTP_CFG
		indexNum = 0
		if tag == "config" {
			tagValue += 0
		} else if tag == "stats" {
			tagValue += 1
		}
	} else if table == "rucommon" {
		tagValue = C.ECPRI_OAM_RU_CFG
		indexNum = 1
		if tag == "config" {
			tagValue += 0
		}
	} else if table == "rucomp" {
		tagValue = C.ECPRI_OAM_UP_COMP_CFG
		indexNum = 1
		if tag == "config" {
			tagValue += 0
		}
	} else if table == "ruwin" {
		tagValue = C.ECPRI_OAM_TRANSMISSION_WINDOWS_CFG
		indexNum = 1
		if tag == "config" {
			tagValue += 0
		} else if tag == "stats" {
			tagValue += 1
		}
	} else if table == "cell" {
		tagValue = C.ECPRI_OAM_CELL_CFG
		indexNum = 1
		if tag == "config" {
			tagValue += 0
		} else if tag == "stats" {
			tagValue += 1
		} else if tag == "vendor" {
			tagValue += 2
		}
	}

	return tagValue, indexNum
}

func getCmd(t string, tag string) error {
	var table, index string

	re := regexp.MustCompile("([^0-9]+)([0-9.]+)")
	parts := re.FindStringSubmatch(t)
	if len(parts) > 2 {
		table = parts[1]
		index = parts[2]
	} else {
		table = t
	}

	tagValue, indexNum := getTag(table, tag)
	idx := make([]uint32, indexNum)

	idxArray := strings.Split(index, ".")
	for i := 0; (i < int(indexNum)) && (i < len(idxArray)); i++ {
		ui64, _ := strconv.ParseUint(idxArray[i], 10, 32)
		idx[i] = uint32(ui64)
	}

	reqMsg := makeGetReq(tagValue, idx)
	if cmdCfg.log {
		fmt.Printf("get req buf: %s\n", hex.EncodeToString(reqMsg))
	}

	//send and wait rsp
	rspBuf := make([]byte, 8192)
	rsplen := C.send_oam_req(C.uint16_t(cmdCfg.dev), (*C.uchar)(&reqMsg[0]), C.uint32_t(len(reqMsg)), (*C.uchar)(&rspBuf[0]))
	if rsplen <= 0 {
		fmt.Printf("oam req err %d!\n", rsplen)
		return nil
	}

	rspBuf = rspBuf[:rsplen]
	if cmdCfg.log {
		fmt.Printf("get rsp buf: %s\n", hex.EncodeToString(rspBuf))
	}
	result, err := rspMsgProc(rspBuf)
	if err != nil {
		fmt.Println(err)
		return nil
	}
	fmt.Println(result)

	if cmdCfg.autoSave {
		saveFile(t, tag, result)
	}
	return nil
}

func saveFile(t string, tag string, data string) {
	os.MkdirAll("get", os.ModePerm)
	fileName := fmt.Sprintf("%s/%s_%s.json", "get", t, tag)
	openFile, e := os.OpenFile(fileName, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0644)
	if e != nil {
		fmt.Println(e)
		return
	}
	openFile.WriteString(data)
	openFile.Close()
	fmt.Println("save to", fileName)
}

func setCmd(table string, tag string, config string) error {
	//fmt.Printf("set %s %s %v %s:\n", table, tag, index, config)
	var index string

	re := regexp.MustCompile("([^0-9]+)([0-9.]+)")
	parts := re.FindStringSubmatch(table)
	if len(parts) > 2 {
		table = parts[1]
		index = parts[2]
	}

	tagValue, indexNum := getTag(table, tag)
	idx := make([]uint32, indexNum)

	idxArray := strings.Split(index, ".")
	for i := 0; (i < int(indexNum)) && (i < len(idxArray)); i++ {
		ui64, _ := strconv.ParseUint(idxArray[i], 10, 32)
		idx[i] = uint32(ui64)
	}

	reqMsg, err := makeSetReq(tagValue, idx, config)
	if err != nil {
		fmt.Printf("make set err: %s\n", err)
		return nil
	}

	if cmdCfg.log {
		fmt.Printf("set req buf: %s\n", hex.EncodeToString(reqMsg))
	}

	//send and wait rsp
	rspBuf := make([]byte, 1024)
	rsplen := C.send_oam_req(C.uint16_t(cmdCfg.dev), (*C.uchar)(&reqMsg[0]), C.uint32_t(len(reqMsg)), (*C.uchar)(&rspBuf[0]))
	if rsplen <= 0 {
		fmt.Printf("oam req err %d:\n", rsplen)
		return nil
	}
	rspBuf = rspBuf[:rsplen]
	if cmdCfg.log {
		fmt.Printf("set rsp buf: %s\n", hex.EncodeToString(rspBuf))
	}
	result, err := rspMsgProc(rspBuf)
	if err != nil {
		fmt.Println(err)
		return nil
	}
	fmt.Println(result)

	return nil
}

func getPrompt(cfg globalConfig) string {
	moduleStr := []string{"oam", "p19", "debug"}
	var module string

	if cfg.msgType == C.PCXX_OAM_MSG {
		if cfg.module < C.ECPRI_OAM_GET_REQ {
			module = "phy"
		} else {
			module = "ecpri"
		}
	} else if cfg.msgType < C.PCXX_MSG_TYPE_MAX {
		module = moduleStr[cfg.msgType]
	}

	return fmt.Sprintf("pc802_%d/%s>", cfg.dev, module)
}

func completer(d prompt.Document) []prompt.Suggest {
	s := []prompt.Suggest{
		{Text: "get", Description: "get table tag"},
		{Text: "set", Description: "set table tag file|config"},
		{Text: "pc802", Description: "pc802 n: switch pc802 device"},
		{Text: "phy", Description: "switch to phy module"},
		{Text: "ecpri", Description: "switch to ecpri module"},
		{Text: "p19", Description: "switch to p19 module"},
		{Text: "debug", Description: "switch to debug module"},
		{Text: "autosave", Description: "switch autosave mode(true|fasle)"},
		{Text: "log", Description: "switch log mode(true|fasle)"},
		{Text: "quit", Description: "quit"},
	}

	table := []prompt.Suggest{
		{Text: "base"},
		{Text: "eth0"},
		{Text: "ptp"},
		{Text: "cell0"},
		{Text: "cell1"},
		{Text: "rucommon0"},
		{Text: "rucomp0"},
		{Text: "ruwin0"},
	}

	settag := []prompt.Suggest{
		{Text: "config", Description: "set table config config"},
	}

	gettag := []prompt.Suggest{
		{Text: "config"},
		{Text: "info"},
		{Text: "status"},
		{Text: "stats"},
		{Text: "vendor"},
	}

	list := strings.Split(d.TextBeforeCursor(), " ")
	list = append(list, "", "", "", "")

	switch list[0] {
	case "get":
		if (list[2] != "") || ((list[1] != "") && (' ' == d.CurrentLine()[d.CursorPositionCol()-1])) {
			return prompt.FilterHasPrefix(gettag, d.GetWordBeforeCursor(), true)
		}
		return prompt.FilterHasPrefix(table, d.GetWordBeforeCursor(), true)
	case "set":
		if (list[2] != "") || ((list[1] != "") && (' ' == d.CurrentLine()[d.CursorPositionCol()-1])) {
			return prompt.FilterHasPrefix(settag, d.GetWordBeforeCursor(), true)
		}
		return prompt.FilterHasPrefix(table, d.GetWordBeforeCursor(), true)
	}

	return prompt.FilterHasPrefix(s, d.GetWordBeforeCursor(), true)
}

func executor(in string) {
	blocks := strings.Split(in, " ")
	if len(blocks) < 1 {
		return
	}

	switch blocks[0] {
	case "pc802":
		fmt.Sscanf(blocks[1], "%d", &cmdCfg.dev)
	case "autosave":
		cmdCfg.autoSave = !cmdCfg.autoSave
		fmt.Printf("set auto save to %v.\n", cmdCfg.autoSave)
	case "log":
		cmdCfg.log = !cmdCfg.log
		fmt.Printf("set log to %v.\n", cmdCfg.log)
	case "ecpri":
		cmdCfg.msgType = C.PCXX_OAM_MSG
		cmdCfg.module = C.ECPRI_OAM_GET_REQ
	case "phy":
		cmdCfg.msgType = C.PCXX_OAM_MSG
		cmdCfg.module = 0
	case "p19":
		cmdCfg.msgType = C.PCXX_P19_MSG
	case "debug":
		cmdCfg.msgType = C.PCXX_DEBUG_MSG
	case "get":
		if len(blocks) != 3 {
			fmt.Printf("Usage: get table tag\n")
			return
		}
		err := getCmd(blocks[1], blocks[2])
		if err != nil {
			fmt.Print(err)
		}
	case "set":
		if len(blocks) != 4 {
			fmt.Printf("Usage: set table tag file|config\n")
			return
		}
		err := setCmd(blocks[1], blocks[2], blocks[3])
		if err != nil {
			fmt.Print(err)
		}
	case "quit":
		os.Exit(0)
	default:
		fmt.Println("unknow cmd!")
	}
}

func main() {
	var his []string
	C.oam_init()

	cmdCfg.module = C.ECPRI_OAM_GET_REQ

	for {
		input := prompt.Input(getPrompt(cmdCfg), completer, prompt.OptionHistory(his))
		executor(strings.TrimSpace(input))
		his = append(his, input)
	}
}
