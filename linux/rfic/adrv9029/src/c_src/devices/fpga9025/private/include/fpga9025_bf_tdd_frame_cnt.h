/**
 * \file fpga9025_bf_tdd_frame_cnt.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_TDD_FRAME_CNT_H__
#define __FPGA9025_BF_TDD_FRAME_CNT_H__

#include "./../../private/include/fpga9025_bf_tdd_frame_cnt_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_TddFrameCntEnableBfSet(adi_fpga9025_Device_t*           device,
                                        fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                        uint8_t                          bfValue);

int32_t fpga9025_TddFrameCntEnableBfGet(adi_fpga9025_Device_t*           device,
                                        fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                        uint8_t*                         bfValue);

int32_t fpga9025_TddFrameCntEndValueBfSet(adi_fpga9025_Device_t*           device,
                                          fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                          uint32_t                         bfValue);

int32_t fpga9025_TddFrameCntEndValueBfGet(adi_fpga9025_Device_t*           device,
                                          fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                          uint32_t*                        bfValue);

int32_t fpga9025_TddFrameCntLoopCountBfSet(adi_fpga9025_Device_t*           device,
                                           fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                           uint32_t                         bfValue);

int32_t fpga9025_TddFrameCntLoopCountBfGet(adi_fpga9025_Device_t*           device,
                                           fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                           uint32_t*                        bfValue);

int32_t fpga9025_TddFrameCntLoopCountEnBfSet(adi_fpga9025_Device_t*           device,
                                             fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                             uint8_t                          bfValue);

int32_t fpga9025_TddFrameCntLoopCountEnBfGet(adi_fpga9025_Device_t*           device,
                                             fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                             uint8_t*                         bfValue);

int32_t fpga9025_TddFrameCntTriggerBfSet(adi_fpga9025_Device_t*           device,
                                         fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                         uint8_t                          bfValue);

int32_t fpga9025_TddFrameCntTriggerBfGet(adi_fpga9025_Device_t*           device,
                                         fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                         uint8_t*                         bfValue);

int32_t fpga9025_TddFrameCntVersionMajorBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                              uint8_t*                         bfValue);

int32_t fpga9025_TddFrameCntVersionMinorBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfTddFrameCntChanAddr_e baseAddr,
                                              uint16_t*                        bfValue);

#ifdef __cplusplus
}
#endif

#endif /* __FPGA9025_BF_TDD_FRAME_CNT_H__ */

/*  EOF: fpga9025_bf_tdd_frame_cnt.h */
