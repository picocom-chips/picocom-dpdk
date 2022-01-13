/**
* \file ads9_bbic_control.h
* \brief Contains ADI Transceiver Hardware Abstraction functions for ADS9 interface to FPGA (BBIC) control registers.
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifndef __ADS9_BBIC_CONTROL_H__
#define __ADS9_BBIC_CONTROL_H__

#include <stdint.h>
#include "adi_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADS9_FPGA_UIO0_START_ADDRESS 0x40000000
#define ADS9_FPGA_UIO0_STOP_ADDRESS  0x5FFFFFFF
#define ADS9_FPGA_UIO2_START_ADDRESS 0x44A00000
#define ADS9_FPGA_UIO2_STOP_ADDRESS  0x44A00FFF

int32_t ads9_BbicOpen(void* devHalCfg);

int32_t ads9_BbicClose(void* devHalCfg);

int32_t ads9_BbicInit(void* devHalCfg);

int32_t ads9_BbicRegisterRead(void*     devHalCfg,
                              uint32_t  addr,
                              uint32_t* data);

int32_t ads9_BbicRegisterWrite(void*    devHalCfg,
                               uint32_t addr,
                               uint32_t data);

int32_t ads9_BbicRegistersRead(void*    devHalCfg,
                               uint32_t addr,
                               uint32_t data[],
                               uint32_t numDataWords);

int32_t ads9_BbicRegistersWrite(void*    devHalCfg,
                                uint32_t addr,
                                uint32_t data[],
                                uint32_t numDataWords);

/* Local helper functions */
/* TODO: remove these functions */
int32_t ads9_fpga_AxiReadWrite(void*     devHalCfg,
                               uint8_t   writeFlag,
                               uint32_t  addr,
                               uint32_t* data);

int32_t ads9_fpga_AxiBulkReadWrite(void*          devHalCfg,
                                   uint8_t        writeFlag,
                                   uint32_t       addr,
                                   uint32_t       data[],
                                   const uint32_t numData);

#ifdef __cplusplus
}
#endif
#endif /*__ADS9_BBIC_CONTROL_H__*/
