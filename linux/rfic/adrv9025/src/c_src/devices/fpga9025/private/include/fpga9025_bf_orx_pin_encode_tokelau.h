/**
 * \file fpga9025_bf_orx_pin_encode_tokelau.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_ORX_PIN_ENCODE_TOKELAU_H__
#define __FPGA9025_BF_ORX_PIN_ENCODE_TOKELAU_H__

#include "./../../private/include/fpga9025_bf_orx_pin_encode_tokelau_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_OrxPinEncodeTokelauFastSwitchingEnableBfSet(adi_fpga9025_Device_t*                   device,
                                                             fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                             uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauFastSwitchingEnableBfGet(adi_fpga9025_Device_t*                   device,
                                                             fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                             uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode1aOrxSelectHighBfSet(adi_fpga9025_Device_t*                   device,
                                                             fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                             uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode1aOrxSelectHighBfGet(adi_fpga9025_Device_t*                   device,
                                                             fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                             uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode1aOrxSelectLowBfSet(adi_fpga9025_Device_t*                   device,
                                                            fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                            uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode1aOrxSelectLowBfGet(adi_fpga9025_Device_t*                   device,
                                                            fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                            uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode3OrxSelectBfSet(adi_fpga9025_Device_t*                   device,
                                                        fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                        uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauMode3OrxSelectBfGet(adi_fpga9025_Device_t*                   device,
                                                        fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                        uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauModeSelectBfSet(adi_fpga9025_Device_t*                   device,
                                                    fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                    uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauModeSelectBfGet(adi_fpga9025_Device_t*                   device,
                                                    fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                    uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxEnableHighTimeBfSet(adi_fpga9025_Device_t*                   device,
                                                           fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                           uint16_t                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxEnableHighTimeBfGet(adi_fpga9025_Device_t*                   device,
                                                           fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                           uint16_t*                                bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxEnableLowTimeBfSet(adi_fpga9025_Device_t*                   device,
                                                          fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                          uint16_t                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxEnableLowTimeBfGet(adi_fpga9025_Device_t*                   device,
                                                          fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                          uint16_t*                                bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxSelectSetupTimeBfSet(adi_fpga9025_Device_t*                   device,
                                                            fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                            uint16_t                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauOrxSelectSetupTimeBfGet(adi_fpga9025_Device_t*                   device,
                                                            fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                            uint16_t*                                bfValue);

int32_t fpga9025_OrxPinEncodeTokelauResetBfSet(adi_fpga9025_Device_t*                   device,
                                               fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                               uint8_t                                  bfValue);

int32_t fpga9025_OrxPinEncodeTokelauResetBfGet(adi_fpga9025_Device_t*                   device,
                                               fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                               uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauVersionMajorBfGet(adi_fpga9025_Device_t*                   device,
                                                      fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                      uint8_t*                                 bfValue);

int32_t fpga9025_OrxPinEncodeTokelauVersionMinorBfGet(adi_fpga9025_Device_t*                   device,
                                                      fpga9025_BfOrxPinEncodeTokelauChanAddr_e baseAddr,
                                                      uint16_t*                                bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_ORX_PIN_ENCODE_TOKELAU_H__

/*  EOF: fpga9025_bf_orx_pin_encode_tokelau.h */
