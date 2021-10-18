/*! \file */

#ifndef __PORT_SERIAL_H__
#define __PORT_SERIAL_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
int gpsGetData(int fd, uint16_t times, uint8_t * pucBuffer, uint16_t usNBytes);

#ifdef  __cplusplus
}
#endif

#endif /* __PORT_SERIAL_H__ */
