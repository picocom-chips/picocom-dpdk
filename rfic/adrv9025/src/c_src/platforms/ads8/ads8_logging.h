/**
* \file ads8_logging.h
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef _ADS8_LOGGING_H_
#define _ADS8_LOGGING_H_

#include <stdio.h>
#include <stdint.h>
#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif


    /*
    * Only allow log file to have MAX_NUM_LINES to prevent it from growing too large
    * If max lines reached, start back at line 0.
    * */
#define ADS8_LOG_MAX_NUM_LINES 250000

int32_t ads8_LogFileOpen(void *devHalCfg, const char *filename);
int32_t ads8_LogFileFlush(void *devHalCfg);
int32_t ads8_LogFileClose(void *devHalCfg);
int32_t ads8_LogLevelSet(void *devHalCfg, int32_t logLevel);
int32_t ads8_LogLevelGet(void *devHalCfg, int32_t *logLevel);
int32_t ads8_LogWrite(void *devHalCfg, int32_t logLevel, const char *comment, va_list argp);


#ifdef __cplusplus
}
#endif

#endif /* _ADS8_LOGGING_H_ */