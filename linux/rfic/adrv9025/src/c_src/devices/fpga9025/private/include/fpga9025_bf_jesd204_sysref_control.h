/**
 * \file fpga9025_bf_jesd204_sysref_control.h Automatically generated file with generator ver 0.0.1.0.
 *
 * \brief Contains BitField functions to support FPGA9025 transceiver device.
 *
 * FPGA9025 BITFIELD VERSION: 0.0.0.1
 */

/**
 * Disclaimer Legal Disclaimer
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef __FPGA9025_BF_JESD204_SYSREF_CONTROL_H__
#define __FPGA9025_BF_JESD204_SYSREF_CONTROL_H__

#include "./../../private/include/fpga9025_bf_jesd204_sysref_control_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_Jesd204SysrefControlExtSysrefPolarityBfSet(adi_fpga9025_Device_t*                    device,
                                                            fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                            uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlExtSysrefPolarityBfGet(adi_fpga9025_Device_t*                    device,
                                                            fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                            uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlExtSysrefRequestBfSet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlExtSysrefRequestBfGet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlExtSysrefSampleEdgeBfSet(adi_fpga9025_Device_t*                    device,
                                                              fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                              uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlExtSysrefSampleEdgeBfGet(adi_fpga9025_Device_t*                    device,
                                                              fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                              uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefEnableBfSet(adi_fpga9025_Device_t*                    device,
                                                          fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                          uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefEnableBfGet(adi_fpga9025_Device_t*                    device,
                                                          fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                          uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefFreerunBfSet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefFreerunBfGet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefGenPeriodBfSet(adi_fpga9025_Device_t*                    device,
                                                             fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                             uint32_t                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefGenPeriodBfGet(adi_fpga9025_Device_t*                    device,
                                                             fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                             uint32_t*                                 bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefRequestBfSet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t                                   bfValue);

int32_t fpga9025_Jesd204SysrefControlIntSysrefRequestBfGet(adi_fpga9025_Device_t*                    device,
                                                           fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                           uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlModuleVersionMajorBfGet(adi_fpga9025_Device_t*                    device,
                                                             fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                             uint8_t*                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlModuleVersionMinorBfGet(adi_fpga9025_Device_t*                    device,
                                                             fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                             uint16_t*                                 bfValue);

int32_t fpga9025_Jesd204SysrefControlOutputEnableBfSet(adi_fpga9025_Device_t*                    device,
                                                       fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                       uint32_t                                  bfValue);

int32_t fpga9025_Jesd204SysrefControlOutputEnableBfGet(adi_fpga9025_Device_t*                    device,
                                                       fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                       uint32_t*                                 bfValue);

int32_t fpga9025_Jesd204SysrefControlSysrefReceivedBfGet(adi_fpga9025_Device_t*                    device,
                                                         fpga9025_BfJesd204SysrefControlChanAddr_e baseAddr,
                                                         uint8_t*                                  bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_JESD204_SYSREF_CONTROL_H__

/*  EOF: fpga9025_bf_jesd204_sysref_control.h */
