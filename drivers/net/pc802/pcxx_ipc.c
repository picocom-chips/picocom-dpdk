#include <stdint.h>

#include "rte_common.h"
#include <rte_debug.h>

#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"
#include "pcxx_ipc.h"


PC802_Traffic_Type_e QID_DATA[2] = { PC802_TRAFFIC_5G_EMBB_DATA, PC802_TRAFFIC_4G_LTE_DATA};
PC802_Traffic_Type_e QID_CTRL[2] = { PC802_TRAFFIC_5G_EMBB_CTRL, PC802_TRAFFIC_4G_LTE_CTRL};

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
}pcxx_dev_info_t;

static pcxx_dev_info_t pcxx_devs[DEV_INDEX_MAX];

#ifndef MULTI_PC802
int pcxxCtrlOpen(const pcxxInfo_s* info, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
#else
int pcxxCtrlOpen(const pcxxInfo_s* info, uint16_t dev_index, uint16_t cell_index )
{
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
void pcxxCtrlClose( __rte_unused uint16_t dev_index, uint16_t cell_index )
{
#endif
    RTE_ASSERT( (dev_index<DEV_INDEX_MAX)&&(cell_index<CELL_NUM_PRE_DEV) );
}


#ifndef MULTI_PC802
int pcxxDataOpen(const pcxxInfo_s* info, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
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

#ifndef MULTI_PC802
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize, ...)
{
    uint16_t dev_index = 0;
    uint16_t cell_index = 0;
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

    if (NULL == cell->rx_ctrl_buf) {
        num_rx = pc802_rx_mblk_burst(pcxx_devs[dev_index].port_id, QID_CTRL[cell_index], &mblk_ctrl, 1);
        if (num_rx)
            cell->rx_ctrl_buf = (char *)&mblk_ctrl[1];
    }
    if (NULL == cell->rx_ctrl_buf)
        return -1;
    mblk_ctrl = (PC802_Mem_Block_t *)(cell->rx_ctrl_buf - sizeof(PC802_Mem_Block_t));
    if (1 == mblk_ctrl->pkt_type) {
        num_rx = pc802_rx_mblk_burst(pcxx_devs[dev_index].port_id, QID_DATA[cell_index], &mblk_data, 1);
        if (0 == num_rx)
            return -1;
        cell->rx_data_buf = (char *)&mblk_data[1];
    }

    if (cell->rx_data_buf) {
        mblk_data = (PC802_Mem_Block_t *)(cell->rx_data_buf - sizeof(PC802_Mem_Block_t));
        if (NULL != cell->pcxx_data_ul_handle) {
#ifdef MULTI_PC802
            cell->pcxx_data_ul_handle(cell->rx_data_buf, mblk_data->pkt_length, dev_index, cell_index );
#else
            cell->pcxx_data_ul_handle(cell->rx_data_buf, mblk_data->pkt_length);
#endif
        }
    }
    uint32_t _len = mblk_ctrl->pkt_length;
    if (cell->ctrl_cnt < 100) {
        printf("cell %d Rx-Ctrl[%2u].pkt_length = %u\n", cell_index, cell->ctrl_cnt, _len);
    }
    offset = 0;
    uint32_t subCnt = 0;
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
    cell->ctrl_cnt++;

    RTE_ASSERT(0 == _len);

    pc802_free_mem_block(mblk_ctrl);
    cell->rx_ctrl_buf = NULL;
    if (cell->rx_data_buf) {
        pc802_free_mem_block(mblk_data);
        cell->rx_data_buf = NULL;
    }

    return 0;
}

#ifndef MULTI_PC802
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset, ...)
{
    uint16_t dev_index = 0, cell_index = 0;
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
#endif
