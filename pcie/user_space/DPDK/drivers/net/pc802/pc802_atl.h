#ifndef __PC802_ATL_H__
#define __PC802_ATL_H__

#include <stdint.h>

typedef uint32_t (*PCXX_RW_CALLBACK)(const char* buf, uint32_t payloadSize);

typedef struct {
    PCXX_RW_CALLBACK readHandle;
    PCXX_RW_CALLBACK writeHandle;
} pcxxInfo_s;

int pcxxCtrlOpen(const pcxxInfo_s* info);
void pcxxCtrlClose(void);

int pcxxDataOpen(const pcxxInfo_s* info);
void pcxxDataClose(void);

int pcxxSendStart(void);
int pcxxSendEnd(void);

int pcxxCtrlAlloc(char** buf, uint32_t* availableSize);
int pcxxCtrlSend(const char* buf, uint32_t bufLen);
int pcxxCtrlRecv(void);
int pcxxDataAlloc(uint32_t bufSize, char** buf, uint32_t* offset);
int pcxxDataSend(uint32_t offset, uint32_t bufLen);
void* pcxxDataRecv(uint32_t offset, uint32_t len);
int pcxxCtrlDestroy(void);
int pcxxDataDestroy(void);

#endif

