/**
 * \file fpga9010_bf_jesd204b_sync_xbar.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_JESD204B_SYNC_XBAR_H__
#define __FPGA9010_BF_JESD204B_SYNC_XBAR_H__

#include "./../../private/include/fpga9010_bf_jesd204b_sync_xbar_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_Jesd204bSyncXbarModuleVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarModuleVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                         uint16_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncInPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncInPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut0SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut0SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut1SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut1SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut2SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut2SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut3SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut3SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut4SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut4SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut5SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut5SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut6SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut6SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_Jesd204bSyncXbarSyncOut7SelectBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_Jesd204bSyncXbarSyncOut7SelectBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfJesd204bSyncXbarChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_JESD204B_SYNC_XBAR_H__

/*  EOF: fpga9010_bf_jesd204b_sync_xbar.h */

