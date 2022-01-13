/**
 * \file fpga9025_bf_tdd_enable_ctrl.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_TDD_ENABLE_CTRL_H__
#define __FPGA9025_BF_TDD_ENABLE_CTRL_H__

#include "./../../private/include/fpga9025_bf_tdd_enable_ctrl_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_TddEnableCtrlEnableBfSet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                          uint8_t                            bfValue);

int32_t fpga9025_TddEnableCtrlEnableBfGet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                          uint8_t*                           bfValue);

int32_t fpga9025_TddEnableCtrlEndValueBfSet(adi_fpga9025_Device_t*             device,
                                            fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                            uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlEndValueBfGet(adi_fpga9025_Device_t*             device,
                                            fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                            uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlFramesActiveBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlFramesActiveBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlFramesInactiveBfSet(adi_fpga9025_Device_t*             device,
                                                  fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                  uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlFramesInactiveBfGet(adi_fpga9025_Device_t*             device,
                                                  fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                  uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlFramesOffsetBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlFramesOffsetBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlManualEnableBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t                            bfValue);

int32_t fpga9025_TddEnableCtrlManualEnableBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t*                           bfValue);

int32_t fpga9025_TddEnableCtrlSecEnableBfSet(adi_fpga9025_Device_t*             device,
                                             fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                             uint8_t                            bfValue);

int32_t fpga9025_TddEnableCtrlSecEnableBfGet(adi_fpga9025_Device_t*             device,
                                             fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                             uint8_t*                           bfValue);

int32_t fpga9025_TddEnableCtrlSecEndValueBfSet(adi_fpga9025_Device_t*             device,
                                               fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                               uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlSecEndValueBfGet(adi_fpga9025_Device_t*             device,
                                               fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                               uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlSecStartValueBfSet(adi_fpga9025_Device_t*             device,
                                                 fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                 uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlSecStartValueBfGet(adi_fpga9025_Device_t*             device,
                                                 fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                 uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlStartValueBfSet(adi_fpga9025_Device_t*             device,
                                              fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                              uint32_t                           bfValue);

int32_t fpga9025_TddEnableCtrlStartValueBfGet(adi_fpga9025_Device_t*             device,
                                              fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                              uint32_t*                          bfValue);

int32_t fpga9025_TddEnableCtrlVersionMajorBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t*                           bfValue);

int32_t fpga9025_TddEnableCtrlVersionMinorBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint16_t*                          bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_TDD_ENABLE_CTRL_H__

/*  EOF: fpga9025_bf_tdd_enable_ctrl.h */
