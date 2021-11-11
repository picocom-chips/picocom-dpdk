/**
 * \file fpga9010_bf_dp_capture_control.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_DP_CAPTURE_CONTROL_H__
#define __FPGA9010_BF_DP_CAPTURE_CONTROL_H__

#include "./../../private/include/fpga9010_bf_dp_capture_control_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_DpCaptureControlDatapathActiveBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_DpCaptureControlDatapathActiveBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_DpCaptureControlModuleVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_DpCaptureControlModuleVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                         uint16_t *bfValue);


int32_t fpga9010_DpCaptureControlPassTokenBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                uint8_t bfValue);
int32_t fpga9010_DpCaptureControlPassTokenBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_DpCaptureControlResetBfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                            uint8_t bfValue);
int32_t fpga9010_DpCaptureControlResetBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfDpCaptureControlChanAddr_e baseAddr, 
                                            uint8_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_DP_CAPTURE_CONTROL_H__

/*  EOF: fpga9010_bf_dp_capture_control.h */

