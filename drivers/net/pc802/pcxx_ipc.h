#ifndef __PC802_ATL_H__
#define __PC802_ATL_H__

#include <stdint.h>

typedef uint32_t (*PCXX_RW_CALLBACK)(const char* buf, uint32_t payloadSize);

typedef struct {
    PCXX_RW_CALLBACK readHandle;
    PCXX_RW_CALLBACK writeHandle;
} pcxxInfo_s;

/**
* @brief Create control  queues for Tx and Rx
*
* @param[in] info Register Tx and Rx callback functions
* @return returns 0 if open success, or else return error
*/
int pcxxCtrlOpen(const pcxxInfo_s* info);

/**
* @brief Close and free the control Shared memory.
*
* @param	none 
* @return	none
*/
void pcxxCtrlClose(void);

/**
* @brief Create OAM queues for Tx and Rx
*
* @param[in] info Register Tx and Rx callback functions
* @return returns 0 if open success, or else return error
*/
int pcxxOamOpen(const pcxxInfo_s* info);

/**
* @brief Close and free the OAM Shared memory.
*
* @param	none 
* @return	none
*/
void pcxxOamClose(void);

/**
* @brief Create data queues  for Rx and Tx
*
* @param[in] info Register Tx and Rx callback functions
* @return returns 0 if open success, or else return error 
*/
int pcxxDataOpen(const pcxxInfo_s* info);

/**
* @brief Close and free the data queue.
*
* @param	 none
* @return  none
*/
void pcxxDataClose(void);

/**
* @brief Called before sending a messages list, mainly is used to select the block .
*
* @param none
* @return returns 0 if open success, or else return error
*/
int pcxxSendStart(void);

/**
* @brief Notify Rx side that new messages are arrived.
*
* @param 	none
* @return  returns 0 if open success, or else return error
*/
int pcxxSendEnd(void);

/**
* @brief Allocated one control message memory from current block in used.
*
* @param[out] buf the allocated memory address
* @param[out] availableSize the current available size in this block
* @return returns 0 if open success, or else return error
*/
int pcxxCtrlAlloc(char** buf, uint32_t* availableSize);

/**
* @brief Update block header when the content of one control message is completed.
*
* @param[in] buf   write memory data
* @param[in] bufLen length of data written  
* @return returns 0 if open success, or else return error
*/
int pcxxCtrlSend(const char* buf, uint32_t bufLen);

/**
* @brief Checks the number of received control messages. Application thread may poll at function till it detects there is message from Tx side.
*
* @param	none
* @return	returns 0 if handle the received messages success, or else return error  
*/
int pcxxCtrlRecv(void);

/**
* @brief Allocated one OAM message memory from current block in used.
*
* @param[out] buf the allocated memory address
* @param[out] availableSize the current available size in this block
* @return returns 0 if open success, or else return error
*/
int pcxxOamAlloc(char** buf, uint32_t* availableSize);

/**
* @brief Update block header when the content of one OAM message is completed.
*
* @param[in] buf   write memory data
* @param[in] bufLen length of data written  
* @return returns 0 if open success, or else return error
*/
int pcxxOamSend(const char* buf, uint32_t bufLen);

/**
* @brief Checks the number of received OAM messages. Application thread may poll at function till it detects there is message from Tx side.
*
* @param	none
* @return	returns 0 if handle the received messages success, or else return error  
*/
int pcxxOamRecv(void);

/**
* @brief Allocated one data message memory from current block in used.
*
* @param[in] bufSize the alloc memory size
* @param[out] buf the available memory address
* @param[out] offset the data memory offset from first address
* @return returns 0 if alloc success, or else return error 
*/
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset);

/**
* @brief Update data queue context when the content of one data message is completed.
*
* @param[in] offset the offset value from first address of data queue
* @param[in] bufLen the write data length
* @return returns 0 if send success, or else return error 
*/
int pcxxDataSend(uint32_t offset, uint32_t bufLen);

/**
* @brief Recv data  from queue by offset
*
* @param[in] offset offset of read data queue, data memory offset from first address
* @param[in] len read data queue length
* @return return pointer to the data if success, else return NULL
*/
void* pcxxDataRecv(uint32_t offset, uint32_t len);

int pcxxCtrlDestroy(void);
int pcxxOamDestroy(void);
int pcxxDataDestroy(void);

#endif

