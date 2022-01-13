/**
 * \file fpga9025_bf_clock_freq_detect.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_CLOCK_FREQ_DETECT_H__
#define __FPGA9025_BF_CLOCK_FREQ_DETECT_H__

#include "./../../private/include/fpga9025_bf_clock_freq_detect_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_ClockFreqDetectClockFreq0BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq1BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq10BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq11BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq12BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq13BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq14BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq15BfGet(adi_fpga9025_Device_t*               device,
                                                 fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                 uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq2BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq3BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq4BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq5BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq6BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq7BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq8BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectClockFreq9BfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint32_t*                            bfValue);

int32_t fpga9025_ClockFreqDetectLocalResetBfSet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint8_t                              bfValue);

int32_t fpga9025_ClockFreqDetectLocalResetBfGet(adi_fpga9025_Device_t*               device,
                                                fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                uint8_t*                             bfValue);

int32_t fpga9025_ClockFreqDetectModuleVersionMajorBfGet(adi_fpga9025_Device_t*               device,
                                                        fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                        uint8_t*                             bfValue);

int32_t fpga9025_ClockFreqDetectModuleVersionMinorBfGet(adi_fpga9025_Device_t*               device,
                                                        fpga9025_BfClockFreqDetectChanAddr_e baseAddr,
                                                        uint16_t*                            bfValue);

#ifdef __cplusplus
}
#endif

#endif /* __FPGA9025_BF_CLOCK_FREQ_DETECT_H__ */

/*  EOF: fpga9025_bf_clock_freq_detect.h */
