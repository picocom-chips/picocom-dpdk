/**
 * \file fpga9025_bf_jesd204_phy_ads9.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_JESD204_PHY_ADS9_H__
#define __FPGA9025_BF_JESD204_PHY_ADS9_H__

#include "./../../private/include/fpga9025_bf_jesd204_phy_ads9_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_Jesd204PhyAds9Channel0CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel0TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel1TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel2TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel3TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel4TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel5TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel6TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7CpllLockBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7CpllPdBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7CpllPdBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7CpllRefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7CpllRefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpResetBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpResetBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7GtpowergoodBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7GtpowergoodBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7LoopbackBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7LoopbackBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7Rx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7Rx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxBufResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxBufResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCdrHoldBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCdrHoldBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCdrlockBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCdrlockBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCommaDetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxCommaDetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmEnBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmEnBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmHoldBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmHoldBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmOverrideBfSet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmOverrideBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                             uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmResetBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxDfeLpmResetBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxGearboxSlipBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxGearboxSlipBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPrbsErrCntBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPrbsErrCntRstBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPrbsErrCntRstBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7RxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7Tx8b10bEnableBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7Tx8b10bEnableBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxBufStatusBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxBufStatusBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxDiffControlBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxDiffControlBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxOutClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxOutClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPcsResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPcsResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPllClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPllClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPmaResetBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPmaResetBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPmaResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                           uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPolarityBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPolarityBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPostcursorBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPostcursorBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPowerdownBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPowerdownBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrbsInjErrBfSet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrbsInjErrBfGet(adi_fpga9025_Device_t*              device,
                                                         fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                         uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrbsSelBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrbsSelBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrecursorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxPrecursorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxRateBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxRateBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Channel7TxResetDoneBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9MmcmRefclkSelectBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9MmcmRefclkSelectBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9ModuleVersionMajorBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9ModuleVersionMinorBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                       uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0LockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0PdBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0PdBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0RefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0RefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0ResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll0ResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1LockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1PdBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1PdBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1RefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1RefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1ResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad0Qpll1ResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpAddressBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpAddressBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpEnableBfSet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpEnableBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpReadDataBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                     uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpReadyBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpTimeoutBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint32_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpTimeoutBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint32_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteDataBfSet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteDataBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                      uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteDataMaskBfSet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint16_t                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteDataMaskBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                          uint16_t*                           bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteEnableBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1DrpWriteEnableBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0LockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0PdBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0PdBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0RefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0RefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0ResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll0ResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1LockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1PdBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1PdBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1RefClkSelBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1RefClkSelBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1ResetBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_Jesd204PhyAds9Quad1Qpll1ResetBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfJesd204PhyAds9ChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_JESD204_PHY_ADS9_H__

/*  EOF: fpga9025_bf_jesd204_phy_ads9.h */
