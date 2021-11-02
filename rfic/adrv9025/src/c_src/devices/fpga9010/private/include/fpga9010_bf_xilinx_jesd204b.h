/**
 * \file fpga9010_bf_xilinx_jesd204b.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_XILINX_JESD204B_H__
#define __FPGA9010_BF_XILINX_JESD204B_H__

#include "./../../private/include/fpga9010_bf_xilinx_jesd204b_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_XilinxJesd204bCfgFBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                         uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bCfgFBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bCfgKBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                         uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bCfgKBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bCfgLaneIdBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bCfgLaneIdBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bCfgSubclassvBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bCfgSubclassvBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bDisErrOnSyncBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bDisErrOnSyncBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaAdjcntBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaAdjcntBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaAdjdirBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaAdjdirBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaBidBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaBidBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaCfBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaCfBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaCsBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaCsBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaDidBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaDidBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaFBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaFchkBfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaFchkBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaHdBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaHdBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaJesdvBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                              uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaKBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaLBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaLidBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaMBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaMBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaMultiframesBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaMultiframesBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaNBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaNBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaNpBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaNpBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                           uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaPhadjBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                              uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaPhadjBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                              uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaRes1BfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaRes1BfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaRes2BfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaRes2BfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                             uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaSBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaSBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                          uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaScrBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaSubclassBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bIlaSupportEnBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bIlaSupportEnBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLaneAlignAlarmBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLanesInUseBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                               uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bLanesInUseBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane0BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane1BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane2BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane3BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane4BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane5BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane6BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkDebugStatusLane7BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrCntBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                uint32_t bfValue);
int32_t fpga9010_XilinxJesd204bLinkErrCntBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                uint32_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrCntrsEnBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bLinkErrCntrsEnBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane0BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane1BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane2BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane3BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane4BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane5BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane6BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bLinkErrorStatusLane7BfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bResetFixedBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                               uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bResetFixedBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bResetSelfClearingBfSet(adi_fpga9010_Device_t *device, 
                                                      fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                      uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bResetSelfClearingBfGet(adi_fpga9010_Device_t *device, 
                                                      fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                      uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bRxBufAdjBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                              uint16_t *bfValue);


int32_t fpga9010_XilinxJesd204bRxBufferDelayBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                  uint16_t bfValue);
int32_t fpga9010_XilinxJesd204bRxBufferDelayBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                  uint16_t *bfValue);


int32_t fpga9010_XilinxJesd204bRxBufferOvrfAlarmBfGet(adi_fpga9010_Device_t *device, 
                                                      fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                      uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bScramblingEnBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bScramblingEnBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSyncStatusBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                               uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSysrefAlwaysBfSet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bSysrefAlwaysBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSysrefCapturedBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                   uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSysrefDelayBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bSysrefDelayBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSysrefLmfcAlarmBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                    uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bSysrefRequiredOnResyncBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bSysrefRequiredOnResyncBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bTestModeBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                             uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bTestModeBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bTestModeErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxJesd204bTestModeIlaCntBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                    uint32_t bfValue);
int32_t fpga9010_XilinxJesd204bTestModeIlaCntBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxJesd204bTestModeMfCntBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                   uint32_t bfValue);
int32_t fpga9010_XilinxJesd204bTestModeMfCntBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
uint8_t channelId,                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxJesd204bVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                 fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                 uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bVersionRevisionBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                    uint8_t *bfValue);


int32_t fpga9010_XilinxJesd204bWatchdogTimerDisableBfSet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t bfValue);
int32_t fpga9010_XilinxJesd204bWatchdogTimerDisableBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfXilinxJesd204bChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_XILINX_JESD204B_H__

/*  EOF: fpga9010_bf_xilinx_jesd204b.h */

