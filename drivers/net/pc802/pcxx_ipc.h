#ifndef __PC802_ATL_H__
#define __PC802_ATL_H__

#include <stdint.h>

#define DEV_INDEX_MAX       PC802_INDEX_MAX     /**< Max number of baseband devices */
#define CELL_NUM_PRE_DEV    2                   /**< Number of cells per baseband device */
/**< Get the total number of baseband devices that have been successfully initialised */
#define pcxxGetDevCount()   pc802_get_count()

#ifndef MULTI_PC802
typedef uint32_t (*PCXX_RW_CALLBACK)(const char* buf, uint32_t payloadSize);
#else
typedef uint32_t (*PCXX_RW_CALLBACK)(const char* buf, uint32_t payloadSize, uint16_t dev_index, uint16_t cell_index );
#endif
typedef struct {
    PCXX_RW_CALLBACK readHandle;
    PCXX_RW_CALLBACK writeHandle;
} pcxxInfo_s;

/**
* @brief Create control  queues for Tx and Rx
*
* @param[in] info Register Tx and Rx callback functions
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxCtrlOpen(const pcxxInfo_s* info, ...);
#else
int pcxxCtrlOpen(const pcxxInfo_s* info, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Close and free the control Shared memory.
*
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return	none
*/
#ifndef MULTI_PC802
void pcxxCtrlClose(void);
#else
void pcxxCtrlClose(uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Create OAM queues for Tx and Rx
*
* @param[in] info Register Tx and Rx callback functions
* @param[in] dev_index baseband device index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxOamOpen(const pcxxInfo_s* info, ...);
#else
int pcxxOamOpen(const pcxxInfo_s* info, uint16_t dev_index);
#endif

/**
* @brief Close and free the OAM Shared memory.
*
* @param[in] dev_index baseband device index
* @return	none
*/
#ifndef MULTI_PC802
void pcxxOamClose(void);
#else
void pcxxOamClose(uint16_t dev_index);
#endif

/**
* @brief Create data queues  for Rx and Tx
*
* @param[in] info Register Tx and Rx callback functions
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxDataOpen(const pcxxInfo_s* info, ...);
#else
int pcxxDataOpen(const pcxxInfo_s* info, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Close and free the data queue.
*
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return  none
*/
#ifndef MULTI_PC802
void pcxxDataClose(void);
#else
void pcxxDataClose(uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Called before sending a messages list, mainly is used to select the block .
*
* @param[in] dev_index baseband device index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxSendStart(void);
#else
int pcxxSendStart(uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Notify Rx side that new messages are arrived.
*
* @param[in] dev_index baseband device index
* @return  returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxSendEnd(void);
#else
int pcxxSendEnd(uint16_t dev_index, uint16_t cell_index );;
#endif

/**
* @brief Called before sending a Oam message, mainly is used to select the block .
*
* @param[in] dev_index baseband device index
* @return returns 0 if success, or else return error
*/
int pcxxOamSendStart(uint16_t dev_index);

/**
* @brief Notify Rx side that new message are arrived.
*
* @param[in] dev_index baseband device index
* @return  returns 0 if success, or else return error
*/
int pcxxOamSendEnd(uint16_t dev_index );

/**
* @brief Allocated one control message memory from current block in used.
*
* @param[out] buf the allocated memory address
* @param[out] availableSize the current available size in this block
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize, ...);
#else
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Update block header when the content of one control message is completed.
*
* @param[in] buf   write memory data
* @param[in] bufLen length of data written
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxCtrlSend(const char* buf, uint32_t bufLen, ...);
#else
int pcxxCtrlSend(const char* buf, uint32_t bufLen, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Checks the number of received control messages. Application thread may poll at function till it detects there is message from Tx side.
*
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return	returns 0 if handle the received messages success, or else return error
*/
#ifndef MULTI_PC802
int pcxxCtrlRecv(void);
#else
int pcxxCtrlRecv(uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Allocated one OAM message memory from current block in used.
*
* @param[out] buf the allocated memory address
* @param[out] availableSize the current available size in this block
* @param[in] dev_index baseband device index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxOamAlloc(char** buf, uint32_t* availableSize, ...);
#else
int pcxxOamAlloc(char** buf, uint32_t* availableSize, uint16_t dev_index );
#endif

/**
* @brief Update block header when the content of one OAM message is completed.
*
* @param[in] buf   write memory data
* @param[in] bufLen length of data written
* @param[in] dev_index baseband device index
* @return returns 0 if open success, or else return error
*/
#ifndef MULTI_PC802
int pcxxOamSend(const char* buf, uint32_t bufLen, ...);
#else
int pcxxOamSend(const char* buf, uint32_t bufLen, uint16_t dev_index );
#endif

/**
* @brief Checks the number of received OAM messages. Application thread may poll at function till it detects there is message from Tx side.
*
* @param[in] dev_index baseband device index
* @return	returns 0 if handle the received messages success, or else return error
*/
#ifndef MULTI_PC802
int pcxxOamRecv(void);
#else
int pcxxOamRecv(uint16_t dev_index );
#endif

/**
* @brief Allocated one data message memory from current block in used.
*
* @param[in] bufSize the alloc memory size
* @param[out] buf the available memory address
* @param[out] offset the data memory offset from first address
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if alloc success, or else return error
*/
#ifndef MULTI_PC802
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset, ...);
#else
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Update data queue context when the content of one data message is completed.
*
* @param[in] offset the offset value from first address of data queue
* @param[in] bufLen the write data length
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return returns 0 if send success, or else return error
*/
#ifndef MULTI_PC802
int pcxxDataSend(uint32_t offset, uint32_t bufLen, ...);
#else
int pcxxDataSend(uint32_t offset, uint32_t bufLen, uint16_t dev_index, uint16_t cell_index );
#endif

/**
* @brief Recv data  from queue by offset
*
* @param[in] offset offset of read data queue, data memory offset from first address
* @param[in] len read data queue length
* @param[in] dev_index baseband device index
* @param[in] cell_index baseband device cell index
* @return return pointer to the data if success, else return NULL
*/
#ifndef MULTI_PC802
void* pcxxDataRecv(uint32_t offset, uint32_t len, ...);
#else
void* pcxxDataRecv(uint32_t offset, uint32_t len, uint16_t dev_index, uint16_t cell_index );
#endif

#ifndef MULTI_PC802
int pcxxCtrlDestroy(void);
int pcxxOamDestroy(void);
int pcxxDataDestroy(void);
#else
int pcxxCtrlDestroy(uint16_t dev_index, uint16_t cell_index );
int pcxxDataDestroy(uint16_t dev_index, uint16_t cell_index );
int pcxxOamDestroy(uint16_t dev_index );
#endif

#endif

