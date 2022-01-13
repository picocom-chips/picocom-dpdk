/**
 * \file ads8_timer.h
 * Analog Devices ADS8 Platform + microzed hardware abstraction layer
 *
 * Copyright 2017 Analog Devices Inc.
 *
 * Support for linux layer timer functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef __ADS8_TIMER_H__
#define __ADS8_TIMER_H__

#include <stdint.h>
#include "adi_platform_types.h"


#ifdef __cplusplus
extern "C" {
#endif

int32_t ads8_TimerOpen(void *devHalCfg);
int32_t ads8_TimerClose(void *devHalCfg);
int32_t ads8_TimerInit(void *devHalCfg);
int32_t ads8_TimerWait_ms(void *devHalCfg, uint32_t time_ms);
int32_t ads8_TimerWait_us(void *devHalCfg, uint32_t time_us);

#ifdef __cplusplus
}
#endif
#endif /* __ADS8_TIMER_H__ */
