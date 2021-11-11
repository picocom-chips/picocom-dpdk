/**
 * \file fpga9010_bf_dp_tollgate.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_DP_TOLLGATE_H__
#define __FPGA9010_BF_DP_TOLLGATE_H__

#include "./../../private/include/fpga9010_bf_dp_tollgate_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_DpTollgateEdgeLevelBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                          uint32_t bfValue);
int32_t fpga9010_DpTollgateEdgeLevelBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                          uint32_t *bfValue);


int32_t fpga9010_DpTollgateHighRisingLowFallingBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                                     uint32_t bfValue);
int32_t fpga9010_DpTollgateHighRisingLowFallingBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                                     uint32_t *bfValue);


int32_t fpga9010_DpTollgateModuleVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                                   uint8_t *bfValue);


int32_t fpga9010_DpTollgateModuleVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                                   uint16_t *bfValue);


int32_t fpga9010_DpTollgateResetTollgateBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_DpTollgateResetTollgateBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_DpTollgateTriggerSelectBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                              uint32_t bfValue);
int32_t fpga9010_DpTollgateTriggerSelectBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTollgateChanAddr_e baseAddr, 
                                              uint32_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_DP_TOLLGATE_H__

/*  EOF: fpga9010_bf_dp_tollgate.h */

