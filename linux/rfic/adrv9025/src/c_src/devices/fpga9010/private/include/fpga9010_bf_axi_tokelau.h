/**
 * \file fpga9010_bf_axi_tokelau.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_AXI_TOKELAU_H__
#define __FPGA9010_BF_AXI_TOKELAU_H__

#include "./../../private/include/fpga9010_bf_axi_tokelau_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_AxiTokelauAd9528ResetBfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                            uint8_t bfValue);
int32_t fpga9010_AxiTokelauAd9528ResetBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                            uint8_t *bfValue);


int32_t fpga9010_AxiTokelauAdrv9010ResetBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_AxiTokelauAdrv9010ResetBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_AxiTokelauDesignIdBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt0BfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt0DetCounterBfGet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                       uint32_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt0DetEdgeLevelBfSet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                         uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpInterrupt0DetEdgeLevelBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt0DetPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpInterrupt0DetPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt1BfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt1DetCounterBfGet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                       uint32_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt1DetEdgeLevelBfSet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                         uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpInterrupt1DetEdgeLevelBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpInterrupt1DetPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpInterrupt1DetPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioEnSpi2BfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioEnSpi2BfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioEnTokJtagBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioEnTokJtagBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioEnTxToOrxBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint32_t bfValue);
int32_t fpga9010_AxiTokelauGpioEnTxToOrxBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                              uint32_t *bfValue);


int32_t fpga9010_AxiTokelauGpioInputBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                          uint32_t *bfValue);


int32_t fpga9010_AxiTokelauGpioOutputBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint32_t bfValue);
int32_t fpga9010_AxiTokelauGpioOutputBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint32_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx1ToOrx1BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx1ToOrx1BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx1ToOrx2BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx1ToOrx2BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx2ToOrx1BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx2ToOrx1BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx2ToOrx2BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx2ToOrx2BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx3ToOrx3BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx3ToOrx3BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx3ToOrx4BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx3ToOrx4BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx4ToOrx3BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx4ToOrx3BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioSelTx4ToOrx4BfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioSelTx4ToOrx4BfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp00BfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp00BfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp01BfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp01BfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp02BfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioTriggerSrcRxdp02BfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTriggerSrcTxdp00BfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioTriggerSrcTxdp00BfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTriggerSrcTxdp01BfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_AxiTokelauGpioTriggerSrcTxdp01BfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_AxiTokelauGpioTristateBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint32_t bfValue);
int32_t fpga9010_AxiTokelauGpioTristateBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint32_t *bfValue);


int32_t fpga9010_AxiTokelauResetBfSet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                      uint8_t bfValue);
int32_t fpga9010_AxiTokelauResetBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_AxiTokelauScratchPadBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint32_t bfValue);
int32_t fpga9010_AxiTokelauScratchPadBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint32_t *bfValue);


int32_t fpga9010_AxiTokelauTestInputBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                          uint8_t bfValue);
int32_t fpga9010_AxiTokelauTestInputBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_AxiTokelauTestOutputBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint8_t bfValue);
int32_t fpga9010_AxiTokelauTestOutputBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                           uint8_t *bfValue);


int32_t fpga9010_AxiTokelauTestTristateBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint8_t bfValue);
int32_t fpga9010_AxiTokelauTestTristateBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_AxiTokelauVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_AxiTokelauVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiTokelauChanAddr_e baseAddr, 
                                             uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_AXI_TOKELAU_H__

/*  EOF: fpga9010_bf_axi_tokelau.h */

