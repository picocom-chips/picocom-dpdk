/**
 * \file fpga9010_bf_orx_pin_encode_tokelau.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_ORX_PIN_ENCODE_TOKELAU_H__
#define __FPGA9010_BF_ORX_PIN_ENCODE_TOKELAU_H__

#include "./../../private/include/fpga9010_bf_orx_pin_encode_tokelau_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_OrxPinEncodeTokelauFastSwitchingEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauFastSwitchingEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauMode1aOrxSelectHighBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauMode1aOrxSelectHighBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauMode1aOrxSelectLowBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauMode1aOrxSelectLowBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauMode3OrxSelectBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauMode3OrxSelectBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauModeSelectBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                    uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauModeSelectBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                    uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauOrxEnableHighTimeBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                           uint16_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauOrxEnableHighTimeBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                           uint16_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauOrxEnableLowTimeBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                          uint16_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauOrxEnableLowTimeBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                          uint16_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauOrxSelectSetupTimeBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                            uint16_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauOrxSelectSetupTimeBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                            uint16_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauResetBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                               uint8_t bfValue);
int32_t fpga9010_OrxPinEncodeTokelauResetBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                               uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                      fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                      uint8_t *bfValue);


int32_t fpga9010_OrxPinEncodeTokelauVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                      fpga9010_BfOrxPinEncodeTokelauChanAddr_e baseAddr, 
                                                      uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_ORX_PIN_ENCODE_TOKELAU_H__

/*  EOF: fpga9010_bf_orx_pin_encode_tokelau.h */

