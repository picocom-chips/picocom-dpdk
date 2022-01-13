/**
 * \file fpga9010_bf_tdd_enable_ctrl.h Automatically generated file with generator ver 0.0.0.1.
 *
 * \brief Contains BitField functions to support FPGA9010 transceiver device.
 *
 * FPGA9010 BITFIELD VERSION: 0.0.0.1
 */

/**
 * Disclaimer Legal Disclaimer
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef __FPGA9010_BF_TDD_ENABLE_CTRL_H__
#define __FPGA9010_BF_TDD_ENABLE_CTRL_H__

#include "./../../private/include/fpga9010_bf_tdd_enable_ctrl_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_TddEnableCtrlEnableBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                          uint8_t bfValue);
int32_t fpga9010_TddEnableCtrlEnableBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_TddEnableCtrlEndValueBfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                            uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlEndValueBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                            uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlFramesActiveBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlFramesActiveBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlFramesInactiveBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                  uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlFramesInactiveBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                  uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlFramesOffsetBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlFramesOffsetBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlManualEnableBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint8_t bfValue);
int32_t fpga9010_TddEnableCtrlManualEnableBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_TddEnableCtrlSecEnableBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                             uint8_t bfValue);
int32_t fpga9010_TddEnableCtrlSecEnableBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_TddEnableCtrlSecEndValueBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                               uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlSecEndValueBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                               uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlSecStartValueBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                 uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlSecStartValueBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                 uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlStartValueBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                              uint32_t bfValue);
int32_t fpga9010_TddEnableCtrlStartValueBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                              uint32_t *bfValue);


int32_t fpga9010_TddEnableCtrlVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_TddEnableCtrlVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfTddEnableCtrlChanAddr_e baseAddr, 
                                                uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_TDD_ENABLE_CTRL_H__

/*  EOF: fpga9010_bf_tdd_enable_ctrl.h */

