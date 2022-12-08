#include <stdint.h>

#include <rte_debug.h>
#include <rte_cycles.h>

#include "pc802_logs.h"
#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"
#include "pcxx_ipc.h"

#define _UNUSED_ __attribute__((__unused__))

PC802_Traffic_Type_e QID_DATA[CELL_NUM_PRE_DEV] = { PC802_TRAFFIC_5G_EMBB_DATA, PC802_TRAFFIC_4G_LTE_DATA};
PC802_Traffic_Type_e QID_CTRL[CELL_NUM_PRE_DEV] = { PC802_TRAFFIC_5G_EMBB_CTRL, PC802_TRAFFIC_4G_LTE_CTRL};
#define QID_OAM     PC802_TRAFFIC_OAM

#define DATA_QUEUE_BLOCK_SIZE   (256*1024)

#define NUM_DATA_BUF    64
#define NUM_SFN_IDX     4
#define SFN_IDX_MASK    (NUM_SFN_IDX - 1)

typedef struct {
    uint32_t sfn_idx;

    char     *ctrl_buf;
    uint32_t ctrl_length;
    uint32_t ctrl_cnt;

    char     *data_buf[NUM_SFN_IDX][NUM_DATA_BUF];
    int      data_num[NUM_SFN_IDX];
    uint32_t data_offset;
    uint32_t data_length;

    char     *rx_ctrl_buf;
    char     *rx_data_buf;

    PCXX_RW_CALLBACK pcxx_ctrl_ul_handle;
    PCXX_RW_CALLBACK pcxx_ctrl_dl_handle;

    PCXX_RW_CALLBACK pcxx_data_ul_handle;
    PCXX_RW_CALLBACK pcxx_data_dl_handle;
}pcxx_cell_info_t;

typedef struct {
    uint16_t port_id;

    pcxx_cell_info_t cell_info[CELL_NUM_PRE_DEV];

    char     *oam_buf;
    uint32_t oam_length;
    PCXX_RW_CALLBACK pcxx_oam_dl_handle;
    PCXX_RW_CALLBACK pcxx_oam_ul_handle;
}pcxx_dev_info_t;

static pcxx_dev_info_t pcxx_devs[DEV_INDEX_MAX];
#ifdef ENABLE_CHECK_PC802_UL_TIMING
#define RTE_RDTSC(a) do { a = rte_rdtsc(); } while(0)
static uint32_t cycles_of_a_slot;
static const char *stat_names[NUM_STATS] =
    {"UL_Ctrl_Poll", "UL_Ctrl_Rx", "UL_Ctrl_Proc", "UL_Data_Proc", "UL_pcxxCtrlRecv_Proc",
    "UL_Ctrl_Burst_Got", "UL_Ctrl_Burst_Null", "UL_Data_Burst_Got", "UL_Data_Burst_Null", "UL_Ctrl_Data_Intv",
    "DL_Ctrl_Tx", "DL_Data_Tx"};
static uint32_t max_sample_nums[NUM_STATS] =
    {200000000, 40000, 40000, 40000, 40000, 40000, 100000000, 40000, 100000000, 40000, 40000, 40000};
static int stat_nos[NUM_STATS];
static uint32_t stat_cnts[NUM_STATS];
static uint64_t stat_t[NUM_STATS];
#else
#define RTE_RDTSC(a)
#endif

#ifndef MULTI_PC802
int pcxxCtrlOpen(const pcxxInfo_s* info, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
    //va_list ap;
    //va_start(ap, info);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxCtrlOpen(const pcxxInfo_s* info, uint16_t dev_index, uint16_t cell_index )
{
#endif

#ifdef ENABLE_CHECK_PC802_UL_TIMING
    uint64_t hz = rte_get_timer_hz();
    DBLOG("PC802 Driver on NPU side built AT %s ON %s\n", __TIME__, __DATE__);
    DBLOG("NPU CPU Hz = %lu\n", hz);

    cycles_of_a_slot = hz / 2000;
    STAT_InitPool(NUM_STATS);
    uint32_t k;
    for (k = 0; k < NUM_STATS; k++) {
         stat_nos[k] = STAT_Alloc(max_sample_nums[k], stat_names[k]);
         stat_cnts[k] = 0;
         stat_t[k] = 0;
    }
#endif

    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    int32_t port_id = pc802_get_port_id(dev_index);
    if (port_id < 0)
        return -1;
    pcxx_cell_info_t *cell_info = &pcxx_devs[dev_index].cell_info[cell_index];

    if ( cell_info->pcxx_ctrl_ul_handle != NULL ) {
        DBLOG( "Dev %d cell %d ctrl queue already open!\n", dev_index, cell_index );
        return -1;
    }

    if (info == NULL)
        return -1;

    RTE_ASSERT(0 == pc802_create_tx_queue( port_id, QID_CTRL[cell_index], 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue( port_id, QID_CTRL[cell_index], 256*1024, 256, 128));

    cell_info->pcxx_ctrl_ul_handle = info->readHandle;
    cell_info->pcxx_ctrl_dl_handle = info->writeHandle;

    pcxx_devs[dev_index].port_id = port_id;
    return 0;
}

#ifndef MULTI_PC802
void pcxxCtrlClose(void)
{
     uint16_t dev_index = 0;
     uint16_t cell_index = 0;
#else
void pcxxCtrlClose( _UNUSED_ uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
}

#ifndef MULTI_PC802
int pcxxOamOpen(const pcxxInfo_s* info, ...)
{
    uint16_t dev_index = 0;
    //va_list ap;
    //va_start(ap, info);
    //dev_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxOamOpen(const pcxxInfo_s* info, uint16_t dev_index )
{
#endif
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    int32_t port_id = pc802_get_port_id(dev_index);
    if (port_id < 0)
        return -1;

    if (pcxx_devs[dev_index].pcxx_oam_ul_handle != NULL) {
        DBLOG( "Dev %d oam queue already open!\n", dev_index );
        return -1;
    }

    if (info == NULL)
        return -1;

    RTE_ASSERT(0 == pc802_create_tx_queue(port_id, QID_OAM, 8*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(port_id, QID_OAM, 8*1024, 256, 128));

    pcxx_devs[dev_index].pcxx_oam_ul_handle = info->readHandle;
    pcxx_devs[dev_index].pcxx_oam_dl_handle = info->writeHandle;
    pcxx_devs[dev_index].port_id = port_id;
    return 0;
}

#ifndef MULTI_PC802
void pcxxOamClose(void)
{
    uint16_t dev_index = 0;
#else
void pcxxOamClose( _UNUSED_ uint16_t dev_index )
{
#endif
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
}


#ifndef MULTI_PC802
int pcxxDataOpen(const pcxxInfo_s* info, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
    //va_list ap;
    //va_start(ap, info);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxDataOpen(const pcxxInfo_s* info, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    int32_t port_id = pc802_get_port_id(dev_index);
    if (port_id < 0)
        return -1;
    pcxx_cell_info_t *cell_info = &pcxx_devs[dev_index].cell_info[cell_index];

    if ( cell_info->pcxx_data_ul_handle != NULL ) {
        DBLOG( "Dev %d cell %d data queue already open!\n", dev_index, cell_index );
        return -1;
    }

    if (info == NULL)
        return -1;

    RTE_ASSERT(0 == pc802_create_tx_queue(port_id, QID_DATA[cell_index], DATA_QUEUE_BLOCK_SIZE, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(port_id, QID_DATA[cell_index], DATA_QUEUE_BLOCK_SIZE, 256, 128));

    cell_info->pcxx_data_ul_handle = info->readHandle;
    cell_info->pcxx_data_dl_handle = info->writeHandle;
    pcxx_devs[dev_index].port_id = port_id;
    return 0;
}

#ifndef MULTI_PC802
void pcxxDataClose(void)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
#else
void pcxxDataClose( uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
}

#ifndef MULTI_PC802
int pcxxSendStart(void)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
#else
int pcxxSendStart(uint16_t dev_index, uint16_t cell_index )
{
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
#endif
    PC802_Mem_Block_t *mblk;
    int k;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    cell->ctrl_length = 0;
    cell->ctrl_buf = NULL;
    for (k = 0; k < cell->data_num[cell->sfn_idx]; k++) {
        mblk = (PC802_Mem_Block_t *)((char *)cell->data_buf[cell->sfn_idx][k] - sizeof(PC802_Mem_Block_t));
        pc802_free_mem_block(mblk);
        cell->data_buf[cell->sfn_idx][k] = NULL;
    }
    cell->data_num[cell->sfn_idx] = 0;
    cell->data_offset = 0;
    cell->data_length = 0;
    return 0;
}

#ifndef MULTI_PC802
int pcxxSendEnd(void)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
#else
int pcxxSendEnd(uint16_t dev_index, uint16_t cell_index )
{
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
#endif
    PC802_Mem_Block_t *mblk_ctrl;
    PC802_Mem_Block_t *mblk_data;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    if (cell->data_num[cell->sfn_idx]) {
        mblk_data = (PC802_Mem_Block_t *)(cell->data_buf[cell->sfn_idx][cell->data_num[cell->sfn_idx] - 1] - sizeof(PC802_Mem_Block_t));
        mblk_data->pkt_length = cell->data_length;
        mblk_data->pkt_type = 0;
        mblk_data->eop = 1;
        pc802_tx_mblk_burst(pcxx_devs[dev_index].port_id, QID_DATA[cell_index], &mblk_data, 1);            //todo:??only one
    }
    if (NULL != cell->ctrl_buf) {
        mblk_ctrl = (PC802_Mem_Block_t *)(cell->ctrl_buf - sizeof(PC802_Mem_Block_t));
        mblk_ctrl->pkt_length = cell->ctrl_length;
        mblk_ctrl->pkt_type = 1 + (0 == cell->data_offset);
        mblk_ctrl->eop = 1;
        pc802_tx_mblk_burst(pcxx_devs[dev_index].port_id, QID_CTRL[cell_index], &mblk_ctrl, 1);
        cell->sfn_idx = (cell->sfn_idx + 1) & SFN_IDX_MASK;
    }
    return 0;
}

int pcxxOamSendStart(uint16_t dev_index)
{
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    pcxx_devs[dev_index].oam_length = 0;
    pcxx_devs[dev_index].oam_buf = NULL;
    return 0;
}

int pcxxOamSendEnd(uint16_t dev_index)
{
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    PC802_Mem_Block_t *mblk_oam;
    if (NULL != pcxx_devs[dev_index].oam_buf) {
        mblk_oam = (PC802_Mem_Block_t *)(pcxx_devs[dev_index].oam_buf - sizeof(PC802_Mem_Block_t));
        mblk_oam->pkt_length = pcxx_devs[dev_index].oam_length;
        mblk_oam->pkt_type = 2;
        mblk_oam->eop = 1;
        pc802_tx_mblk_burst(pcxx_devs[dev_index].port_id, QID_OAM, &mblk_oam, 1);
    }
    return 0;
}

#ifndef MULTI_PC802
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
    //va_list ap;
    //va_start(ap, availableSize);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    PC802_Mem_Block_t *mblk;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    if (NULL == cell->ctrl_buf) {
        mblk = pc802_alloc_tx_mem_block(pcxx_devs[dev_index].port_id, QID_CTRL[cell_index]);
        if (NULL == mblk)
            return -1;
        cell->ctrl_buf = (char *)&mblk[1];
        cell->ctrl_length = 0;
    }
    if (NULL == cell->ctrl_buf)
        return -1;
    *buf = cell->ctrl_buf + cell->ctrl_length;
    *availableSize = 256 * 1024 - sizeof(PC802_Mem_Block_t) - cell->ctrl_length;
    return 0;
}

#ifndef MULTI_PC802
int pcxxCtrlSend(const char* buf, uint32_t bufLen, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
    //va_list ap;
    //va_start(ap, bufLen);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxCtrlSend(const char* buf, uint32_t bufLen, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    uint32_t ret;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    //RTE_ASSERT(0 == (bufLen & 3));
    if (NULL == cell->pcxx_ctrl_dl_handle) {
        cell->ctrl_length += bufLen;
        return 0;
    }
#ifdef MULTI_PC802
    ret = cell->pcxx_ctrl_dl_handle(buf, bufLen, dev_index, cell_index);
#else
    ret = cell->pcxx_ctrl_dl_handle(buf, bufLen);
#endif
    if (ret)
        return -1;
    cell->ctrl_length += bufLen;
    return 0;
}

#ifdef ENABLE_CHECK_PC802_TIMING
void stat_and_check(uint32_t stat_no)
{
    StatResult_t stat_result;
    uint64_t tins;
    uint64_t tdiff_64;
    uint32_t tdiff = 0;

    tins = rte_rdtsc();
    stat_cnts[stat_no]++;
    if (stat_cnts[stat_no] > 3) { // ignore the first 3 messages
        tdiff_64 = tins - stat_t[stat_no];
        if (tdiff_64 > (uint64_t)0xFFFFFFFF) {
            NPU_SYSLOG("ERROR: %s Overtime = %lu = 0x%lx\n", stat_names[stat_no], tdiff_64, tdiff_64);
            tdiff = 0xFFFFFFFF;
        } else {
            tdiff = (uint32_t)tdiff_64;
        }
    }
    stat_t[stat_no] = tins;
    if (stat_cnts[stat_no] <= 3)
        return;
    if (tdiff > (cycles_of_a_slot * 5/4)) {
        NPU_SYSLOG("ERROR: %s[%u] tdiff = %u > 1.25 slot\n", stat_names[stat_no], stat_cnts[stat_no]-1, tdiff);
    }
    if (0 == STAT_Sample(stat_nos[stat_no], tdiff)) {
        STAT_GetResult(stat_nos[stat_no], &stat_result);
        STAT_Reset(stat_nos[stat_no]);
        NPU_SYSLOG("Info: %s : Max = %u Min = %u Mean = %u Devi = %u\n", stat_names[stat_no],
            stat_result.max, stat_result.min, stat_result.average, stat_result.std_dev);
    }
}

void check_proc_time(uint32_t stat_no, uint64_t tdiff_64)
{
    StatResult_t stat_result;
    uint32_t tdiff;

    if (tdiff_64 > (uint64_t)0xFFFFFFFF) {
        NPU_SYSLOG("ERROR: %s Overtime = %lu = 0x%lx\n", stat_names[stat_no], tdiff_64, tdiff_64);
        tdiff = 0xFFFFFFFF;
    } else {
        tdiff = (uint32_t)tdiff_64;
    }

    stat_cnts[stat_no]++;
    if (tdiff > (cycles_of_a_slot * 9/10)) {
        NPU_SYSLOG("ERROR: %s[%u] cycles = %u > 0.9 slot\n", stat_names[stat_no],
            stat_cnts[stat_no]-1, tdiff);
    }
    if (0 == STAT_Sample(stat_nos[stat_no], tdiff)) {
        STAT_GetResult(stat_nos[stat_no], &stat_result);
        STAT_Reset(stat_nos[stat_no]);
        NPU_SYSLOG("Info: %s : Max = %u Min = %u Mean = %u Devi = %u\n", stat_names[stat_no],
            stat_result.max, stat_result.min, stat_result.average, stat_result.std_dev);
    }
}
#else
#define stat_and_check(a)
#define check_proc_time(a, b)
#endif

#ifndef MULTI_PC802
int pcxxCtrlRecv(void)
{
    uint16_t dev_index = 0, cell_index = 0;
#else
int pcxxCtrlRecv( uint16_t dev_index, uint16_t cell_index )
{
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
#endif
    PC802_Mem_Block_t *mblk_ctrl;
    PC802_Mem_Block_t *mblk_data;
    uint16_t num_rx;
    uint32_t rLen = 0;
    uint32_t offset;
    int ret;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
#ifdef ENABLE_CHECK_PC802_UL_TIMING
    uint64_t tstart, tend;
    uint64_t tstart0, tend0;
    uint64_t tstart1, tend1;
    uint64_t t_rx_data;
    uint64_t tdiff_64;

    stat_and_check(NO_CTRL_POLL);
    RTE_RDTSC(tstart0);
#endif
    if (NULL == cell->rx_ctrl_buf) {
        num_rx = pc802_rx_mblk_burst(pcxx_devs[dev_index].port_id, QID_CTRL[cell_index], &mblk_ctrl, 1);
        if (num_rx) {
            cell->rx_ctrl_buf = (char *)&mblk_ctrl[1];
#ifdef ENABLE_CHECK_PC802_UL_TIMING
            stat_and_check(NO_CTRL_RECV);
            if (1 == mblk_ctrl->pkt_type) {
                RTE_RDTSC(stat_t[NO_CTRL_DATA]);
            }
#endif
        }
    }
    if (NULL == cell->rx_ctrl_buf)
        return -1;
    mblk_ctrl = (PC802_Mem_Block_t *)(cell->rx_ctrl_buf - sizeof(PC802_Mem_Block_t));
    if (1 == mblk_ctrl->pkt_type) {
        num_rx = pc802_rx_mblk_burst(pcxx_devs[dev_index].port_id, QID_DATA[cell_index], &mblk_data, 1);
#ifdef ENABLE_CHECK_PC802_UL_TIMING
        RTE_RDTSC(t_rx_data);
        tdiff_64 = t_rx_data - stat_t[NO_CTRL_DATA];
#endif
        if (0 == num_rx) {
#ifdef ENABLE_CHECK_PC802_UL_TIMING
            if (tdiff_64 > cycles_of_a_slot/2) {
                DBLOG("ERROR: No Data, Interval of ctrl and data = %lu > 1/2 slot\n", tdiff_64);
            }
#endif
            return -1;
        }
        cell->rx_data_buf = (char *)&mblk_data[1];
        check_proc_time(NO_CTRL_DATA, tdiff_64);
    }

    if (cell->rx_data_buf) {
        mblk_data = (PC802_Mem_Block_t *)(cell->rx_data_buf - sizeof(PC802_Mem_Block_t));
        if (NULL != cell->pcxx_data_ul_handle) {
            RTE_RDTSC(tstart1);
#ifdef MULTI_PC802
            cell->pcxx_data_ul_handle(cell->rx_data_buf, mblk_data->pkt_length, dev_index, cell_index );
#else
            cell->pcxx_data_ul_handle(cell->rx_data_buf, mblk_data->pkt_length);
#endif
#ifdef ENABLE_CHECK_PC802_UL_TIMING
            RTE_RDTSC(tend1);
            tdiff_64 = tend1 - tstart1;
            check_proc_time(NO_DATA_PROC, tdiff_64);
#endif
        }
    }
    uint32_t _len = mblk_ctrl->pkt_length;
    if (cell->ctrl_cnt < 100) {
        printf("cell %d Rx-Ctrl[%2u].pkt_length = %u\n", cell_index, cell->ctrl_cnt, _len);
    }
    offset = 0;
    uint32_t subCnt = 0;
    RTE_RDTSC(tstart);
    while (_len > 0) {
        if (NULL == cell->pcxx_ctrl_ul_handle)
            break;
#ifdef MULTI_PC802
        ret = cell->pcxx_ctrl_ul_handle(cell->rx_ctrl_buf + offset, _len, dev_index, cell_index);
#else
        ret = cell->pcxx_ctrl_ul_handle(cell->rx_ctrl_buf + offset, _len);
#endif
        if (ret < 0)
            break;
        rLen = ret;
        RTE_ASSERT(0 == (rLen & 3));
        RTE_ASSERT(rLen <= _len);
        _len -= rLen;
        offset += rLen;
        subCnt++;
        if (subCnt > 5) {
            printf("Number of Sub Ctrl msgs[%2u] = %u > 5\n", cell->ctrl_cnt, subCnt);
        }
    }
#ifdef ENABLE_CHECK_PC802_UL_TIMING
    RTE_RDTSC(tend);
    tdiff_64 = tend - tstart;
    check_proc_time(NO_CTRL_PROC, tdiff_64);
#endif
    cell->ctrl_cnt++;

    RTE_ASSERT(0 == _len);

    pc802_free_mem_block(mblk_ctrl);
    cell->rx_ctrl_buf = NULL;
    if (cell->rx_data_buf) {
        pc802_free_mem_block(mblk_data);
        cell->rx_data_buf = NULL;
    }

#ifdef ENABLE_CHECK_PC802_UL_TIMING
    RTE_RDTSC(tend0);
    tdiff_64 = tend0 - tstart0;
    check_proc_time(NO_FUNC_PROC, tdiff_64);
#endif
    return 0;
}

#ifndef MULTI_PC802
int pcxxOamAlloc(char** buf, uint32_t* availableSize, ...)
{
    uint16_t dev_index = 0;
    //va_list ap;
    //va_start(ap, availableSize);
    //dev_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxOamAlloc(char** buf, uint32_t* availableSize, uint16_t dev_index )
{
#endif
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    PC802_Mem_Block_t *mblk;
    if (NULL == pcxx_devs[dev_index].oam_buf) {
        mblk = pc802_alloc_tx_mem_block(pcxx_devs[dev_index].port_id, QID_OAM);
        if (NULL == mblk)
            return -1;
        pcxx_devs[dev_index].oam_buf = (char *)&mblk[1];
        pcxx_devs[dev_index].oam_length = 0;
    }
    if (NULL == pcxx_devs[dev_index].oam_buf)
        return -1;
    *buf = pcxx_devs[dev_index].oam_buf + pcxx_devs[dev_index].oam_length;
    *availableSize = 256 * 1024 - sizeof(PC802_Mem_Block_t) - pcxx_devs[dev_index].oam_length;
    return 0;
}

#ifndef MULTI_PC802
int pcxxOamSend(const char* buf, uint32_t bufLen, ...)
{
    uint16_t dev_index = 0;
    //va_list ap;
    //va_start(ap, bufLen);
    //dev_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxOamSend(const char* buf, uint32_t bufLen, uint16_t dev_index )
{
#endif
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    uint32_t ret;
    RTE_ASSERT(0 == (bufLen & 3));
    if (NULL == pcxx_devs[dev_index].pcxx_oam_dl_handle) {
        pcxx_devs[dev_index].oam_length += bufLen;
        return 0;
    }
#ifdef MULTI_PC802
    ret = pcxx_devs[dev_index].pcxx_oam_dl_handle(buf, bufLen, dev_index, 0);
#else
    ret = pcxx_devs[dev_index].pcxx_oam_dl_handle(buf, bufLen);
#endif
    if (ret)
        return -1;
    pcxx_devs[dev_index].oam_length += bufLen;
    return 0;
}

#ifndef MULTI_PC802
int pcxxOamRecv(void)
{
    uint16_t dev_index = 0;
#else
int pcxxOamRecv(uint16_t dev_index )
{
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
#endif
    char *rx_oam_buf = NULL;
    PC802_Mem_Block_t *mblk_oam;
    uint16_t num_rx;
    uint32_t rLen = 0;
    uint32_t offset;
    int ret;

    if (NULL == rx_oam_buf) {
        num_rx = pc802_rx_mblk_burst(pcxx_devs[dev_index].port_id, QID_OAM, &mblk_oam, 1);
        if (num_rx)
            rx_oam_buf = (char *)&mblk_oam[1];
    }
    if (NULL == rx_oam_buf)
        return -1;
    mblk_oam = (PC802_Mem_Block_t *)(rx_oam_buf - sizeof(PC802_Mem_Block_t));
    uint32_t _len = mblk_oam->pkt_length;
    offset = 0;
    while (_len > 0) {
        if (NULL == pcxx_devs[dev_index].pcxx_oam_ul_handle)
            break;
#ifdef MULTI_PC802
        ret = pcxx_devs[dev_index].pcxx_oam_ul_handle(rx_oam_buf + offset, _len, dev_index, 0);
#else
        ret = pcxx_devs[dev_index].pcxx_oam_ul_handle(rx_oam_buf + offset, _len);
#endif
        if (ret < 0)
            break;
        rLen = ret;
        RTE_ASSERT(0 == (rLen & 3));
        _len -= rLen;
        offset += rLen;
    }

    RTE_ASSERT(0 == _len);

    pc802_free_mem_block(mblk_oam);
    rx_oam_buf = NULL;

    return 0;
}

#ifndef MULTI_PC802
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset, ...)
{
    uint16_t dev_index = 0, cell_index = 0;
    //va_list ap;
    //va_start(ap, offset);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    PC802_Mem_Block_t *mblk;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    if ((sizeof(PC802_Mem_Block_t) + cell->data_offset + bufSize) > DATA_QUEUE_BLOCK_SIZE)
        return -1;
    mblk = pc802_alloc_tx_mem_block(pcxx_devs[dev_index].port_id, QID_DATA[cell_index]);
    if (NULL == mblk)
        return -1;
    *buf = cell->data_buf[cell->sfn_idx][cell->data_num[cell->sfn_idx]] = (char *)&mblk[1];
    *offset = cell->data_offset;
    return 0;
}

#ifndef MULTI_PC802
int pcxxDataSend(uint32_t offset, uint32_t bufLen, ...)
{
    uint16_t dev_index = 0, cell_index = 0;
    //va_list ap;
    //va_start(ap, bufLen);
    //dev_index = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
int pcxxDataSend(uint32_t offset, uint32_t bufLen, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    PC802_Mem_Block_t *mblk;
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    bufLen = ((bufLen + 3) >> 2) << 2;
    if ((sizeof(PC802_Mem_Block_t) + offset + bufLen) > DATA_QUEUE_BLOCK_SIZE)
        return -1;
    if (cell->pcxx_data_dl_handle) {
#ifdef MULTI_PC802
        if (cell->pcxx_data_dl_handle(cell->data_buf[cell->sfn_idx][cell->data_num[cell->sfn_idx]], bufLen, dev_index, cell_index))
#else
        if (cell->pcxx_data_dl_handle(cell->data_buf[cell->sfn_idx][cell->data_num[cell->sfn_idx]], bufLen))
#endif
            return -2;
    }
    if (cell->data_num[cell->sfn_idx]){
        mblk = (PC802_Mem_Block_t *)(cell->data_buf[cell->sfn_idx][cell->data_num[cell->sfn_idx] - 1] - sizeof(PC802_Mem_Block_t));
        mblk->pkt_length = cell->data_length;
        mblk->pkt_type = 0;
        mblk->eop = 0;
        pc802_tx_mblk_burst(pcxx_devs[dev_index].port_id, QID_DATA[cell_index], &mblk, 1);
    }
    cell->data_offset += bufLen;
    cell->data_length = bufLen;
    cell->data_num[cell->sfn_idx]++;
    return 0;
}

#ifndef MULTI_PC802
void* pcxxDataRecv(uint32_t offset, uint32_t len, ...)
{
    uint16_t dev_index = 0, cell_index = 0;
    //va_list ap;
    //va_start(ap, len);
    //dev_index  = va_arg(ap, int);
    //cell_index = va_arg(ap, int);
    //va_end(ap);
#else
void* pcxxDataRecv(uint32_t offset, uint32_t len, uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    pcxx_cell_info_t *cell = &pcxx_devs[dev_index].cell_info[cell_index];
    if (NULL == cell->rx_data_buf)
        return NULL;
    if ((sizeof(PC802_Mem_Block_t) + offset + len) > DATA_QUEUE_BLOCK_SIZE)
        return NULL;
    return (void *)(cell->rx_data_buf + offset);
}

#ifndef MULTI_PC802
int pcxxCtrlDestroy(void)
{
    return 0;
}

int pcxxOamDestroy(void)
{
    return 0;
}

int pcxxDataDestroy(void)
{
    return 0;
}
#else
int pcxxCtrlDestroy( uint16_t dev_index, uint16_t cell_index )
{
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    return 0;
}
int pcxxDataDestroy( uint16_t dev_index, uint16_t cell_index )
{
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
    return 0;
}
int pcxxOamDestroy( uint16_t dev_index )
{
    RTE_ASSERT(dev_index<DEV_INDEX_MAX);
    return 0;
}
#endif
