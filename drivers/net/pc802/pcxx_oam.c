/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018-2020 Picocom Corporation
 */
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "rte_common.h"
#include <rte_debug.h>
#include <rte_memcpy.h>
#include "rte_pmd_pc802.h"
#include "pcxx_oam.h"

typedef enum {
    OamMsgType_Log = 128,       /* lower 128 reserved for driver for special handing */
    OamMsgType_Trace,
    OamMsgType_Memdump,
    OamMsgType_Num
} OamMsgType_e;


#define OAM_START_FLAG      0xd1c2b3a4
#define OAM_END_FLAG        0xa4b3c2d1
#define OAM_QUEUE_BLOCK_SIZE   (8*1024)
#define SUB_MSG_TSIZE(msg_size) (msg_size+sizeof(pcxx_oam_sub_msg_t))

typedef struct{
    uint32_t start_flag;         //0xd1c2b3a4
    uint32_t msg_type;
    uint32_t sub_msg_num;		 //Message burst
}oam_msg_head_t;

typedef struct{
    oam_msg_head_t head;
    pcxx_oam_sub_msg_t sub_msg[0];
    uint32_t end_flag;           //0xa4b3c2d1
}oam_message_t;

typedef struct{
    uint32_t start_addr;
    uint32_t total_len;
}mem_dump_req_t;

typedef struct{
    uint16_t msg_id;
    pcxx_oam_cb_fn cb_fun;
    void *cb_arg;
}sub_info_t;

typedef struct {
    uint32_t msg_type;
    pcxx_oam_cb_fn cb_fun;
    void *cb_arg;
    sub_info_t sub_list[64];
} msg_info_t;
typedef struct{
    uint16_t   dev_count;
    uint16_t   devs[PC802_INDEX_MAX];
    msg_info_t msg_list[PCXX_MSG_TYPE_MAX];
}oam_info_t;

static oam_info_t g_oam_info;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

extern int pc802_ctrl_thread_create(pthread_t *thread, const char *name, pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);
static void* oam_recv( __rte_unused void *arg  );

#if 0
static void printf_buf( const char *head, const uint8_t *buf, int size )
{
	int i = 0;
    printf( "%s(size=%d):\n", head, size);
	for ( i =0; i < size; i+=16 )
		printf( "%02d: %02x %02x %02x %02x,%02x %02x %02x %02x,%02x %02x %02x %02x,%02x %02x %02x %02x\n", i,
            buf[i+0], buf[i+1], buf[i+2], buf[i+3], buf[i+4], buf[i+5], buf[i+6], buf[i+7],
            buf[i+8], buf[i+9], buf[i+10], buf[i+11], buf[i+12], buf[i+13], buf[i+14], buf[i+15] );
}
#endif

int pcxx_oam_init(void)
{
    pthread_t tid;
    uint16_t dev_index = 0;

    g_oam_info.dev_count = pc802_get_count();
    for ( dev_index=0; dev_index<g_oam_info.dev_count; dev_index++ ) {
        g_oam_info.devs[dev_index] = pc802_get_port_id(dev_index);
        RTE_ASSERT(0 == pc802_create_tx_queue( g_oam_info.devs[dev_index], PC802_TRAFFIC_OAM, OAM_QUEUE_BLOCK_SIZE, 128, 64));
        RTE_ASSERT(0 == pc802_create_rx_queue( g_oam_info.devs[dev_index], PC802_TRAFFIC_OAM, OAM_QUEUE_BLOCK_SIZE, 128, 64));
    }

    pc802_ctrl_thread_create( &tid, "oam", NULL, oam_recv, NULL);
    return 0;
}

int pcxx_oam_send_msg( uint16_t dev_index, uint32_t msg_type, const pcxx_oam_sub_msg_t **sub_msg, uint32_t msg_num )
{
    char *buf = NULL;
    PC802_Mem_Block_t *mblk = NULL;
    oam_message_t *msg = NULL;
    pcxx_oam_sub_msg_t *sub = NULL;
    uint32_t len = 0;
    uint32_t i;

    if (dev_index >= g_oam_info.dev_count) {
        DBLOG("Invalid dev_index=%d!\n", dev_index);
        return -1;
    }

    pthread_mutex_lock(&lock);
    mblk = pc802_alloc_tx_mem_block( g_oam_info.devs[dev_index], PC802_TRAFFIC_OAM );
    if ( NULL==mblk ) {
        pthread_mutex_unlock(&lock);
        return -1;
    }
    buf = (char *)&mblk[1];
    msg = (oam_message_t *)buf;
    msg->head.start_flag = OAM_START_FLAG;
    msg->head.msg_type   = msg_type;
    msg->head.sub_msg_num = 0;
    len += sizeof(oam_msg_head_t);

    for ( i=0; i<msg_num; i++ ) {
        if ( SUB_MSG_TSIZE(sub_msg[i]->msg_size) > OAM_QUEUE_BLOCK_SIZE - len) {
            DBLOG( "Not enough space(%u) for sub msg(%d:%ld)\n", OAM_QUEUE_BLOCK_SIZE - len,
                   sub_msg[i]->msg_id, SUB_MSG_TSIZE(sub_msg[i]->msg_size));
            pthread_mutex_unlock(&lock);
            return -1;
        }
        sub = (pcxx_oam_sub_msg_t*)(buf+len);
        rte_memcpy( sub, sub_msg[i], SUB_MSG_TSIZE(sub_msg[i]->msg_size) );
        len += SUB_MSG_TSIZE(sub_msg[i]->msg_size);
        msg->head.sub_msg_num++;
    }
    *((uint32_t *)(buf+len)) = OAM_END_FLAG;
    len += sizeof(uint32_t);
    mblk->pkt_length = len;
    mblk->pkt_type = 2;
    mblk->eop = 1;
    //printf_buf("Send msg", (uint8_t *)buf, len);
    if ( pc802_tx_mblk_burst( g_oam_info.devs[dev_index], PC802_TRAFFIC_OAM, &mblk, 1) < 1 ) {
        DBLOG( "pc802_tx_mblk_burst(dev=%d,len=%d) err!\n", dev_index, mblk->pkt_length );
        pthread_mutex_unlock(&lock);
        return -1;
    }

    pthread_mutex_unlock(&lock);
    return 0;
}

int pcxx_oam_register(uint32_t msg_type, pcxx_oam_cb_fn cb_fun, void *arg)
{
    RTE_ASSERT( (cb_fun != NULL)&&(msg_type<PCXX_MSG_TYPE_MAX) );
    pthread_mutex_lock(&lock);
    g_oam_info.msg_list[msg_type].msg_type = msg_type;
    g_oam_info.msg_list[msg_type].cb_arg = arg;
    g_oam_info.msg_list[msg_type].cb_fun = cb_fun;
    pthread_mutex_unlock(&lock);
    return 0;
}

int pcxx_oam_unregister(uint32_t msg_type)
{
    RTE_ASSERT( msg_type<PCXX_MSG_TYPE_MAX );
    pthread_mutex_lock(&lock);
    g_oam_info.msg_list[msg_type].cb_arg = NULL;
    g_oam_info.msg_list[msg_type].cb_fun = NULL;
    g_oam_info.msg_list[msg_type].msg_type = 0;
    pthread_mutex_unlock(&lock);
    return 0;
}

int pcxx_oam_sub_msg_register(uint32_t msg_type, uint16_t sub_msg_id, pcxx_oam_cb_fn cb_fun, void *arg)
{
    uint16_t sub_index = 0;
    sub_info_t *sub_list;

    RTE_ASSERT((cb_fun != NULL) && (msg_type < PCXX_MSG_TYPE_MAX));

    pthread_mutex_lock(&lock);
    sub_list = g_oam_info.msg_list[msg_type].sub_list;
    for (sub_index = 0; sub_index < RTE_DIM(g_oam_info.msg_list[msg_type].sub_list); sub_index++)
        if ((0 == sub_list[sub_index].msg_id) && (NULL == sub_list[sub_index].cb_fun))
            break;
    if (sub_index == RTE_DIM(g_oam_info.msg_list[msg_type].sub_list)) {
        pthread_mutex_unlock(&lock);
        DBLOG("no vacancy!\n");
        return -1;
    }
    sub_list[sub_index].msg_id = sub_msg_id;
    sub_list[sub_index].cb_arg = arg;
    sub_list[sub_index].cb_fun = cb_fun;
    pthread_mutex_unlock(&lock);

    return 0;
}

int pcxx_oam_sub_msg_unregister( uint32_t msg_type, uint16_t sub_msg_id )
{
    uint16_t sub_index = 0;
    sub_info_t *sub_list;

    RTE_ASSERT( msg_type<PCXX_MSG_TYPE_MAX );
    pthread_mutex_lock(&lock);
    sub_list = g_oam_info.msg_list[msg_type].sub_list;
    for (sub_index = 0; sub_index < RTE_DIM(g_oam_info.msg_list[msg_type].sub_list); sub_index++)
        if (sub_msg_id == sub_list[sub_index].msg_id)
            break;
    if (sub_index < RTE_DIM(g_oam_info.msg_list[msg_type].sub_list)) {
        sub_list[sub_index].msg_id = 0;
        sub_list[sub_index].cb_arg = NULL;
        sub_list[sub_index].cb_fun = NULL;
    }
    pthread_mutex_unlock(&lock);
    return 0;
}

static sub_info_t *get_sub_index(sub_info_t sub_list[], uint16_t msg_id)
{
    uint16_t sub_index = 0;
    for (sub_index = 0; sub_index < RTE_DIM(g_oam_info.msg_list[0].sub_list); sub_index++)
        if ((msg_id == sub_list[sub_index].msg_id) && (NULL != sub_list[sub_index].cb_fun))
            return &sub_list[sub_index];
    return NULL;
}

static uint32_t process_oam_msg(uint16_t dev_index, const oam_message_t *msg, uint32_t len)
{
    const pcxx_oam_sub_msg_t *cur = NULL;
    const pcxx_oam_sub_msg_t *sub[32] = {NULL};
    uint32_t sub_num = 0;
    uint32_t i = 0;
    msg_info_t *msg_info = NULL;
    sub_info_t *sub_info = NULL;

    if (OAM_START_FLAG != msg->head.start_flag || len < sizeof(oam_message_t)){
        DBLOG("Invalid msg(start_flag=%u,len=%u)!\n", msg->head.start_flag, len );
        return -EINVAL;;
    }
    if (msg->head.msg_type >= PCXX_MSG_TYPE_MAX) {
         DBLOG("Invalid msg_type=%u!\n", msg->head.msg_type );
        return -EINVAL;;
    }

    pthread_mutex_lock(&lock);
    msg_info = &g_oam_info.msg_list[msg->head.msg_type];
    len -= sizeof(oam_msg_head_t);
    cur = msg->sub_msg;
    for (i = 0; (i < msg->head.sub_msg_num) && (len > sizeof(pcxx_oam_sub_msg_t)); i++) {
        if (len < SUB_MSG_TSIZE(cur->msg_size))
            break;

        sub_info = get_sub_index( msg_info->sub_list, cur->msg_id);
        if (NULL != sub_info){
            sub_info->cb_fun(sub_info->cb_arg, dev_index, msg->head.msg_type, &cur, 1);
        }
        else
            sub[sub_num++] = cur;
        len -= SUB_MSG_TSIZE(cur->msg_size);
        cur = (const pcxx_oam_sub_msg_t *)((const char *)cur + SUB_MSG_TSIZE(cur->msg_size));
    }

    if ((sub_num > 0) && (NULL != msg_info->cb_fun))
        msg_info->cb_fun(msg_info->cb_arg, dev_index, msg->head.msg_type, sub, sub_num);
    pthread_mutex_unlock(&lock);

    if (OAM_END_FLAG != *((const uint32_t *)cur)){
        DBLOG("Dev %d oam msg %u end flag(%u) invalid!\n", dev_index, msg->head.msg_type, *((const uint32_t *)cur));
        return -EINVAL;
    }
    return 0;
}

static void *oam_recv( __rte_unused void *arg)
{
    uint16_t dev_index;
    PC802_Mem_Block_t *mblk = NULL;
    uint16_t num_rx;
    int num = 0;

    sleep(5);
    while (1) {
        num = 0;
        for (dev_index = 0; dev_index < g_oam_info.dev_count; dev_index++) {
            num_rx = pc802_rx_mblk_burst(g_oam_info.devs[dev_index], PC802_TRAFFIC_OAM, &mblk, 1);
            if (0 == num_rx)
                continue;
            num += num_rx;
            //printf_buf("Recv msg",  (uint8_t *)&mblk[1], mblk->pkt_length);
            switch (mblk->pkt_type) {
            case OamMsgType_Log:
            case OamMsgType_Trace:
                break;
            case OamMsgType_Memdump:
                break;
            default:
                process_oam_msg(dev_index, (oam_message_t *)&mblk[1], mblk->pkt_length);
                break;
            }
            pc802_free_mem_block(mblk);
        }
        if (0 == num)
            usleep(5000);
    }
    return NULL;
}
