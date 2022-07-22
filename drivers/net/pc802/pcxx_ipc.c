#include <stdint.h>

#include <rte_debug.h>

#include "rte_pmd_pc802.h"
#include "pc802_ethdev.h"
#include "pcxx_ipc.h"

/*Predefined Block num*/
#define DL_CTRL_BLOCK_NUM 4
#define UL_CTRL_BLCOK_NUM 4

#define DL_DATA_BLOCK_NUM 4
#define UL_DATA_BLCOK_NUM 4

#define DL_OAM_BLOCK_NUM 2
#define UL_OAM_BLCOK_NUM 2

#define QID_DATA    PC802_TRAFFIC_5G_EMBB_DATA
#define QID_CTRL    PC802_TRAFFIC_5G_EMBB_CTRL
#define QID_OAM     PC802_TRAFFIC_OAM

typedef enum {
    PCXX_CTRL,
    PCXX_DATA,
    PCXX_OAM,
    PCXX_INSTANCE_NUM
} PcxxInstanceType_e;

typedef enum {
    PCXX_TX_DIRECT,
    PCXX_RX_DIRECT,
    PCXX_MAX_DIRECT_NUM
} PcxxDirect_e;

static PCXX_RW_CALLBACK pccxxWriteHandle[PCXX_INSTANCE_NUM] = {}; // ul mac or phy callback
static PCXX_RW_CALLBACK pccxxReadHandle[PCXX_INSTANCE_NUM] = {}; // dl mac or phy callback

static int openCtrlState = 0;
static int openOamState = 0;
static int openDataState = 0;

int pcxxCtrlOpen(const pcxxInfo_s* info)
{
    if (openCtrlState != 0) {
        printf("open Ctrl State = %d \n", openCtrlState);
        return -1;
    }

    if (info == NULL)
        return -1;

    pccxxReadHandle[PCXX_CTRL] = info->readHandle;
    pccxxWriteHandle[PCXX_CTRL] = info->writeHandle;

    RTE_ASSERT(0 == pc802_create_tx_queue(0, QID_CTRL, 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(0, QID_CTRL, 256*1024, 256, 128));

    openCtrlState = 1;
    return 0;
}

void pcxxCtrlClose(void)
{
}

int pcxxOamOpen(const pcxxInfo_s* info)
{
    if (openOamState != 0) {
        printf("open Oam State = %d \n", openOamState);
        return -1;
    }

    if (info == NULL)
        return -1;

    pccxxReadHandle[PCXX_OAM] = info->readHandle;
    pccxxWriteHandle[PCXX_OAM] = info->writeHandle;

    RTE_ASSERT(0 == pc802_create_tx_queue(0, QID_OAM, 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(0, QID_OAM, 256*1024, 256, 128));

    openOamState = 1;
    return 0;
}

void pcxxOamClose(void)
{
}

int pcxxDataOpen(const pcxxInfo_s* info)
{
    if (openDataState != 0) {
        printf("open Data State = %d \n", openDataState);
        return -1;
    }

    if (info == NULL)
        return -1;

    pccxxReadHandle[PCXX_DATA] = info->readHandle;
    pccxxWriteHandle[PCXX_DATA] = info->writeHandle;

    RTE_ASSERT(0 == pc802_create_tx_queue(0, QID_DATA, 256*1024, 256, 128));
    RTE_ASSERT(0 == pc802_create_rx_queue(0, QID_DATA, 256*1024, 256, 128));

    openDataState = 1;
    return 0;
}

void pcxxDataClose(void)
{
}

#define NUM_DATA_BUF    64
#define NUM_SFN_IDX 4
#define SFN_IDX_MASK    (NUM_SFN_IDX - 1)

static uint32_t sfn_idx;

static char     *ctrl_buf;
static uint32_t ctrl_length;

static char     *data_buf[NUM_SFN_IDX][NUM_DATA_BUF];
static int      data_num[NUM_SFN_IDX];
static uint32_t data_offset;
static uint32_t data_length;

static char     *rx_ctrl_buf;
static char     *rx_data_buf;

static char     *oam_buf;
static uint32_t oam_length;
static char     *rx_oam_buf;

int pcxxSendStart(void)
{
    PC802_Mem_Block_t *mblk;
    int k;
    ctrl_length = 0;
    ctrl_buf = NULL;
    for (k = 0; k < data_num[sfn_idx]; k++) {
        mblk = (PC802_Mem_Block_t *)((char *)data_buf[sfn_idx][k] - sizeof(PC802_Mem_Block_t));
        pc802_free_mem_block(mblk);
        data_buf[sfn_idx][k] = NULL;
    }
    data_num[sfn_idx] = 0;
    data_offset = 0;
    data_length = 0;
    oam_length = 0;
    oam_buf = NULL;
    return 0;
}

int pcxxSendEnd(void)
{
    PC802_Mem_Block_t *mblk_ctrl;
    PC802_Mem_Block_t *mblk_data;
    PC802_Mem_Block_t *mblk_oam;
    if (data_num[sfn_idx]) {
        mblk_data = (PC802_Mem_Block_t *)(data_buf[sfn_idx][data_num[sfn_idx] - 1] - sizeof(PC802_Mem_Block_t));
        mblk_data->pkt_length = data_length;
        mblk_data->pkt_type = 0;
        mblk_data->eop = 1;
        pc802_tx_mblk_burst(0, QID_DATA, &mblk_data, 1);
    }
    if (NULL != ctrl_buf) {
        mblk_ctrl = (PC802_Mem_Block_t *)(ctrl_buf - sizeof(PC802_Mem_Block_t));
        mblk_ctrl->pkt_length = ctrl_length;
        mblk_ctrl->pkt_type = 1 + (0 == data_offset);
        mblk_ctrl->eop = 1;
        pc802_tx_mblk_burst(0, QID_CTRL, &mblk_ctrl, 1);
        sfn_idx = (sfn_idx + 1) & SFN_IDX_MASK;
    }
    if (NULL != oam_buf) {
        mblk_oam = (PC802_Mem_Block_t *)(oam_buf - sizeof(PC802_Mem_Block_t));
        mblk_oam->pkt_length = oam_length;
        mblk_oam->pkt_type = 2;
        mblk_oam->eop = 1;
        pc802_tx_mblk_burst(0, QID_OAM, &mblk_oam, 1);
    }
    return 0;
}

int pcxxCtrlAlloc(char** buf, uint32_t* availableSize)
{
    PC802_Mem_Block_t *mblk;
    if (NULL == ctrl_buf) {
        mblk = pc802_alloc_tx_mem_block(0, QID_CTRL);
        if (NULL == mblk)
            return -1;
        ctrl_buf = (char *)&mblk[1];
    }
    if (NULL == ctrl_buf)
        return -1;
    *buf = ctrl_buf + ctrl_length;
    *availableSize = 256 * 1024 - sizeof(PC802_Mem_Block_t) - ctrl_length;
    return 0;
}

int pcxxCtrlSend(const char* buf, uint32_t bufLen)
{
    uint32_t ret;
    //RTE_ASSERT(0 == (bufLen & 3));
    if (NULL == pccxxWriteHandle[PCXX_CTRL]) {
        ctrl_length += bufLen;
        return 0;
    }
    ret = pccxxWriteHandle[PCXX_CTRL](buf, bufLen);
    if (ret)
        return -1;
    ctrl_length += bufLen;
    return 0;
}

int pcxxCtrlRecv(void)
{
    PC802_Mem_Block_t *mblk_ctrl;
    PC802_Mem_Block_t *mblk_data;
    uint16_t num_rx;
    uint32_t rLen = 0;
    uint32_t offset;
    int ret;
    static uint32_t ctrlCnt = 0;

    if (NULL == rx_ctrl_buf) {
        num_rx = pc802_rx_mblk_burst(0, QID_CTRL, &mblk_ctrl, 1);
        if (num_rx)
            rx_ctrl_buf = (char *)&mblk_ctrl[1];
    }
    if (NULL == rx_ctrl_buf)
        return -1;
    mblk_ctrl = (PC802_Mem_Block_t *)(rx_ctrl_buf - sizeof(PC802_Mem_Block_t));
    if (1 == mblk_ctrl->pkt_type) {
        num_rx = pc802_rx_mblk_burst(0, QID_DATA, &mblk_data, 1);
        if (0 == num_rx)
            return -1;
        rx_data_buf = (char *)&mblk_data[1];
    }

    if (rx_data_buf) {
        mblk_data = (PC802_Mem_Block_t *)(rx_data_buf - sizeof(PC802_Mem_Block_t));
        if (NULL != pccxxReadHandle[PCXX_DATA]) {
            pccxxReadHandle[PCXX_DATA](rx_data_buf, mblk_data->pkt_length);
        }
    }
    uint32_t _len = mblk_ctrl->pkt_length;
    if (ctrlCnt < 100) {
        printf("Rx-Ctrl[%2u].pkt_length = %u\n", ctrlCnt, _len);
    }
    offset = 0;
    uint32_t subCnt = 0;
    while (_len > 0) {
        if (NULL == pccxxReadHandle[PCXX_CTRL])
            break;
        ret = pccxxReadHandle[PCXX_CTRL](rx_ctrl_buf + offset, _len);
        if (ret < 0)
            break;
        rLen = ret;
        RTE_ASSERT(0 == (rLen & 3));
        RTE_ASSERT(rLen <= _len);
        _len -= rLen;
        offset += rLen;
        subCnt++;
        if (subCnt > 5) {
            printf("Number of Sub Ctrl msgs[%2u] = %u > 5\n", ctrlCnt, subCnt);
        }
    }
    ctrlCnt++;

    RTE_ASSERT(0 == _len);

    pc802_free_mem_block(mblk_ctrl);
    rx_ctrl_buf = NULL;
    if (rx_data_buf) {
        pc802_free_mem_block(mblk_data);
        rx_data_buf = NULL;
    }

    return 0;
}

int pcxxOamAlloc(char** buf, uint32_t* availableSize)
{
    PC802_Mem_Block_t *mblk;
    if (NULL == oam_buf) {
        mblk = pc802_alloc_tx_mem_block(0, QID_OAM);
        if (NULL == mblk)
            return -1;
        oam_buf = (char *)&mblk[1];
    }
    if (NULL == oam_buf)
        return -1;
    *buf = oam_buf + oam_length;
    *availableSize = 256 * 1024 - sizeof(PC802_Mem_Block_t) - oam_length;
    return 0;
}

int pcxxOamSend(const char* buf, uint32_t bufLen)
{
    uint32_t ret;
    RTE_ASSERT(0 == (bufLen & 3));
    if (NULL == pccxxWriteHandle[PCXX_OAM]) {
        oam_length += bufLen;
        return 0;
    }
    ret = pccxxWriteHandle[PCXX_OAM](buf, bufLen);
    if (ret)
        return -1;
    oam_length += bufLen;
    return 0;
}

int pcxxOamRecv(void)
{
    PC802_Mem_Block_t *mblk_oam;
    uint16_t num_rx;
    uint32_t rLen = 0;
    uint32_t offset;
    int ret;

    if (NULL == rx_oam_buf) {
        num_rx = pc802_rx_mblk_burst(0, QID_OAM, &mblk_oam, 1);
        if (num_rx)
            rx_oam_buf = (char *)&mblk_oam[1];
    }
    if (NULL == rx_oam_buf)
        return -1;
    mblk_oam = (PC802_Mem_Block_t *)(rx_oam_buf - sizeof(PC802_Mem_Block_t));
    uint32_t _len = mblk_oam->pkt_length;
    offset = 0;
    while (_len > 0) {
        if (NULL == pccxxReadHandle[PCXX_OAM])
            break;
        ret = pccxxReadHandle[PCXX_OAM](rx_oam_buf + offset, _len);
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

int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset)
{
    PC802_Mem_Block_t *mblk;
    if ((sizeof(PC802_Mem_Block_t) + data_offset + bufSize) > 256 * 1024)
        return -1;
    mblk = pc802_alloc_tx_mem_block(0, QID_DATA);
    if (NULL == mblk)
        return -1;
    *buf = data_buf[sfn_idx][data_num[sfn_idx]] = (char *)&mblk[1];
    *offset = data_offset;
    return 0;
}

int pcxxDataSend(uint32_t offset, uint32_t bufLen)
{
    PC802_Mem_Block_t *mblk;
    bufLen = ((bufLen + 3) >> 2) << 2;
    if ((sizeof(PC802_Mem_Block_t) + offset + bufLen ) > 256 * 1024)
        return -1;
    if (pccxxWriteHandle[PCXX_DATA]) {
        if (pccxxWriteHandle[PCXX_DATA](data_buf[sfn_idx][data_num[sfn_idx]], bufLen))
            return -2;
    }
    if (data_num[sfn_idx]){
        mblk = (PC802_Mem_Block_t *)(data_buf[sfn_idx][data_num[sfn_idx] - 1] - sizeof(PC802_Mem_Block_t));
        mblk->pkt_length = data_length;
        mblk->pkt_type = 0;
        mblk->eop = 0;
        pc802_tx_mblk_burst(0, QID_DATA, &mblk, 1);
    }
    data_offset += bufLen;
    data_length = bufLen;
    data_num[sfn_idx]++;
    return 0;
}

void* pcxxDataRecv(uint32_t offset, uint32_t len)
{
    if (NULL == rx_data_buf)
        return NULL;
    if ((sizeof(PC802_Mem_Block_t) + offset + len)  > 256 * 1024)
        return NULL;
    return (void *)(rx_data_buf + offset);
}

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

