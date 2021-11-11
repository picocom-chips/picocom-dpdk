/**
 * \file fpga9010_bf_jesd204_phy_tokelau_ads8.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_JESD204_PHY_TOKELAU_ADS8_H__
#define __FPGA9010_BF_JESD204_PHY_TOKELAU_ADS8_H__

#include "./../../private/include/fpga9010_bf_jesd204_phy_tokelau_ads8_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel0TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel1TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel2TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel3TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel4TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel5TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel6TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7CpllLockBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7CpllPdBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7CpllPdBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7CpllRefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7CpllRefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpResetBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpResetBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7GtpowergoodBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7GtpowergoodBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7LoopbackBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7LoopbackBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7Rx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7Rx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxBufResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxBufResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxCdrlockBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxCdrlockBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxCommaDetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxCommaDetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmEnBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmEnBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmHoldBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmHoldBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmOverrideBfSet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmOverrideBfGet(adi_fpga9010_Device_t *device, 
                                                                    fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                    uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmResetBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxDfeLpmResetBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsErrCntBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsErrCntRstBfSet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsErrCntRstBfGet(adi_fpga9010_Device_t *device, 
                                                                   fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                   uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7RxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7Tx8b10bEnableBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7Tx8b10bEnableBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxBufStatusBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxBufStatusBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxDiffControlBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxDiffControlBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPcsResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPcsResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPllClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPllClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPmaResetBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPmaResetBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPmaResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                                  fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                  uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPolarityBfSet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPolarityBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPostcursorBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPostcursorBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPowerdownBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPowerdownBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsInjErrBfSet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsInjErrBfGet(adi_fpga9010_Device_t *device, 
                                                                fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsSelBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrbsSelBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrecursorBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxPrecursorBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxRateBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxRateBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Channel7TxResetDoneBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8MmcmRefclkSelectBfSet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8MmcmRefclkSelectBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8ModuleVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8ModuleVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                              fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                              uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0LockBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0PdBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0PdBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0RefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0RefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0ResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll0ResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1LockBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1PdBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1PdBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1RefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1RefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1ResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad0Qpll1ResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpAddressBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpAddressBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpEnableBfSet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpEnableBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpErrorBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpReadDataBfGet(adi_fpga9010_Device_t *device, 
                                                            fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                            uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpReadyBfGet(adi_fpga9010_Device_t *device, 
                                                         fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                         uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpTimeoutBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint32_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpTimeoutBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint32_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataBfSet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataBfGet(adi_fpga9010_Device_t *device, 
                                                             fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                             uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataMaskBfSet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint16_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteDataMaskBfGet(adi_fpga9010_Device_t *device, 
                                                                 fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                                 uint16_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteEnableBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1DrpWriteEnableBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0LockBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0PdBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0PdBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0RefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0RefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0ResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll0ResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1LockBfGet(adi_fpga9010_Device_t *device, 
                                                          fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                          uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1PdBfSet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1PdBfGet(adi_fpga9010_Device_t *device, 
                                                        fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                        uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1RefClkSelBfSet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1RefClkSelBfGet(adi_fpga9010_Device_t *device, 
                                                               fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                               uint8_t *bfValue);


int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1ResetBfSet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t bfValue);
int32_t fpga9010_Jesd204PhyTokelauAds8Quad1Qpll1ResetBfGet(adi_fpga9010_Device_t *device, 
                                                           fpga9010_BfJesd204PhyTokelauAds8ChanAddr_e baseAddr, 
                                                           uint8_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_JESD204_PHY_TOKELAU_ADS8_H__

/*  EOF: fpga9010_bf_jesd204_phy_tokelau_ads8.h */

