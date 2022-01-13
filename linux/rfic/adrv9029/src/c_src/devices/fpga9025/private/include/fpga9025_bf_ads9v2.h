/**
 * \file fpga9025_bf_ads9v2.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_ADS9V2_H__
#define __FPGA9025_BF_ADS9V2_H__

#include "./../../private/include/fpga9025_bf_ads9v2_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_Ads9v2Ad9528ResetBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2Ad9528ResetBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2Ad9576ResetBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2Ad9576ResetBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig0DirBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig0DirBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig0OutputSrcBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig0OutputSrcBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig1DirBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig1DirBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig1OutputSrcBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig1OutputSrcBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig2DirBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig2DirBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig2OutputSrcBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig2OutputSrcBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig3DirBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig3DirBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrig3OutputSrcBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrig3OutputSrcBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp00CtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp00CtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp01CtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp01CtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp02CtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigRxdp02CtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigTddCtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigTddCtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigTxdp00CtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigTxdp00CtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2ExtTrigTxdp01CtrlSrcBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t                     bfValue);

int32_t fpga9025_Ads9v2ExtTrigTxdp01CtrlSrcBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2GlobalResetBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_Ads9v2GlobalResetBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2LedBlinkDurationBfSet(adi_fpga9025_Device_t*      device,
                                             fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                             uint16_t                    bfValue);

int32_t fpga9025_Ads9v2LedBlinkDurationBfGet(adi_fpga9025_Device_t*      device,
                                             fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                             uint16_t*                   bfValue);

int32_t fpga9025_Ads9v2LedDelayToModeChangeBfSet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint16_t                    bfValue);

int32_t fpga9025_Ads9v2LedDelayToModeChangeBfGet(adi_fpga9025_Device_t*      device,
                                                 fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                                 uint16_t*                   bfValue);

int32_t fpga9025_Ads9v2LedMaskBfSet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                    uint8_t                     bfValue);

int32_t fpga9025_Ads9v2LedMaskBfGet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                    uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2LedModeBfSet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                    uint8_t                     bfValue);

int32_t fpga9025_Ads9v2LedModeBfGet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                    uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2LedNumBlinksBfSet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t                     bfValue);

int32_t fpga9025_Ads9v2LedNumBlinksBfGet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2LedSwDefinedValueBfSet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t                     bfValue);

int32_t fpga9025_Ads9v2LedSwDefinedValueBfGet(adi_fpga9025_Device_t*      device,
                                              fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                              uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2MgtRefclkSelBfSet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t                     bfValue);

int32_t fpga9025_Ads9v2MgtRefclkSelBfGet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2Pca9545ResetBfSet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t                     bfValue);

int32_t fpga9025_Ads9v2Pca9545ResetBfGet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2VersionMajorBfGet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint8_t*                    bfValue);

int32_t fpga9025_Ads9v2VersionMinorBfGet(adi_fpga9025_Device_t*      device,
                                         fpga9025_BfAds9v2ChanAddr_e baseAddr,
                                         uint16_t*                   bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_ADS9V2_H__

/*  EOF: fpga9025_bf_ads9v2.h */
