/**
 * \file fpga9010_bf_tdd_dp_ctrl.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_TDD_DP_CTRL_H__
#define __FPGA9010_BF_TDD_DP_CTRL_H__

#include "./../../private/include/fpga9010_bf_tdd_dp_ctrl_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_TddDpCtrlEnableBitBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                         uint8_t bfValue);
int32_t fpga9010_TddDpCtrlEnableBitBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_TddDpCtrlStartValueBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                          uint32_t bfValue);
int32_t fpga9010_TddDpCtrlStartValueBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                          uint32_t *bfValue);


int32_t fpga9010_TddDpCtrlVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                            uint8_t *bfValue);


int32_t fpga9010_TddDpCtrlVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                            uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_TDD_DP_CTRL_H__

/*  EOF: fpga9010_bf_tdd_dp_ctrl.h */

