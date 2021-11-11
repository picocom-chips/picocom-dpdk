/**
 * \file fpga9010_bf_ads8v2.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_ADS8V2_H__
#define __FPGA9010_BF_ADS8V2_H__

#include "./../../private/include/fpga9010_bf_ads8v2_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_Ads8v2Ad9528ResetBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_Ads8v2Ad9528ResetBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_Ads8v2Adg918CtrlBfSet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                       uint8_t bfValue);
int32_t fpga9010_Ads8v2Adg918CtrlBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig0DirBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig0DirBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig0OutputSrcBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig0OutputSrcBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig1DirBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig1DirBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig1OutputSrcBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig1OutputSrcBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig2DirBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig2DirBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig2OutputSrcBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig2OutputSrcBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig3DirBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig3DirBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrig3OutputSrcBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrig3OutputSrcBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigRxdp00CtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigRxdp00CtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigRxdp01CtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigRxdp01CtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigRxdp02CtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigRxdp02CtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigTddCtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigTddCtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigTxdp00CtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigTxdp00CtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_Ads8v2ExtTrigTxdp01CtrlSrcBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_Ads8v2ExtTrigTxdp01CtrlSrcBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_Ads8v2LedBlinkDurationBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                             uint16_t bfValue);
int32_t fpga9010_Ads8v2LedBlinkDurationBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                             uint16_t *bfValue);


int32_t fpga9010_Ads8v2LedDelayToModeChangeBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint16_t bfValue);
int32_t fpga9010_Ads8v2LedDelayToModeChangeBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                                 uint16_t *bfValue);


int32_t fpga9010_Ads8v2LedMaskBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                    uint8_t bfValue);
int32_t fpga9010_Ads8v2LedMaskBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_Ads8v2LedModeBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                    uint8_t bfValue);
int32_t fpga9010_Ads8v2LedModeBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_Ads8v2LedNumBlinksBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint8_t bfValue);
int32_t fpga9010_Ads8v2LedNumBlinksBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_Ads8v2LedSwDefinedValueBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_Ads8v2LedSwDefinedValueBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_Ads8v2Pca9545ResetBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint8_t bfValue);
int32_t fpga9010_Ads8v2Pca9545ResetBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_Ads8v2VersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_Ads8v2VersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAds8v2ChanAddr_e baseAddr, 
                                         uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_ADS8V2_H__

/*  EOF: fpga9010_bf_ads8v2.h */

