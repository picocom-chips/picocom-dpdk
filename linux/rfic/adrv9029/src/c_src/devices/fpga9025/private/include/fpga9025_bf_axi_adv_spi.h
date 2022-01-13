/**
 * \file fpga9025_bf_axi_adv_spi.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_AXI_ADV_SPI_H__
#define __FPGA9025_BF_AXI_ADV_SPI_H__

#include "./../../private/include/fpga9025_bf_axi_adv_spi_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_AxiAdvSpiAdvFeat3wireTriPointBfSet(adi_fpga9025_Device_t*         device,
                                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                    uint8_t                        channelId,
                                                    uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeat3wireTriPointBfGet(adi_fpga9025_Device_t*         device,
                                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                    uint8_t                        channelId,
                                                    uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatClockDivBfSet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint16_t                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatClockDivBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint16_t*                      bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatCphaBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        channelId,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatCphaBfGet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        channelId,
                                           uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatCpolBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        channelId,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatCpolBfGet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        channelId,
                                           uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatEnableBfSet(adi_fpga9025_Device_t*         device,
                                             fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                             uint8_t                        channelId,
                                             uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatEnableBfGet(adi_fpga9025_Device_t*         device,
                                             fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                             uint8_t                        channelId,
                                             uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatFourWireBfSet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatFourWireBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatLsbFirstBfSet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatLsbFirstBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        channelId,
                                               uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatMisoSampleSlipBfSet(adi_fpga9025_Device_t*         device,
                                                     fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                     uint8_t                        channelId,
                                                     uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiAdvFeatMisoSampleSlipBfGet(adi_fpga9025_Device_t*         device,
                                                     fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                     uint8_t                        channelId,
                                                     uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiCphaBfSet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiCphaBfGet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiCpolBfSet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiCpolBfGet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDrrFullBfSet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDrrFullBfGet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDrrFullIenBfSet(adi_fpga9025_Device_t*         device,
                                          fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                          uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDrrFullIenBfGet(adi_fpga9025_Device_t*         device,
                                          fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                          uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDrrOverrunBfSet(adi_fpga9025_Device_t*         device,
                                          fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                          uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDrrOverrunBfGet(adi_fpga9025_Device_t*         device,
                                          fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                          uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDrrOverrunIenBfSet(adi_fpga9025_Device_t*         device,
                                             fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                             uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDrrOverrunIenBfGet(adi_fpga9025_Device_t*         device,
                                             fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                             uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDtrEmptyBfSet(adi_fpga9025_Device_t*         device,
                                        fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                        uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDtrEmptyBfGet(adi_fpga9025_Device_t*         device,
                                        fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                        uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiDtrEmptyIenBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiDtrEmptyIenBfGet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiGieBfSet(adi_fpga9025_Device_t*         device,
                                   fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                   uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiGieBfGet(adi_fpga9025_Device_t*         device,
                                   fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                   uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiLoopBfSet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiLoopBfGet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiLsbFirstBfSet(adi_fpga9025_Device_t*         device,
                                        fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                        uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiLsbFirstBfGet(adi_fpga9025_Device_t*         device,
                                        fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                        uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiManSsEnBfSet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiManSsEnBfGet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiMasterBfSet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiMasterBfGet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiModfBfGet(adi_fpga9025_Device_t*         device,
                                    fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                    uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiModfFlagBfGet(adi_fpga9025_Device_t*         device,
                                        fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                        uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiModfIenBfSet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiModfIenBfGet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiMstrInhibitBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiMstrInhibitBfGet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiResetBfSet(adi_fpga9025_Device_t*         device,
                                     fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                     uint32_t                       bfValue);

int32_t fpga9025_AxiAdvSpiRxDataBfGet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiRxEmptyBfGet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiRxFifoOccupancyBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint16_t*                      bfValue);

int32_t fpga9025_AxiAdvSpiRxFifoResetBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiRxFullBfGet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiSlaveSelectBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint32_t                       bfValue);

int32_t fpga9025_AxiAdvSpiSlaveSelectBfGet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint32_t*                      bfValue);

int32_t fpga9025_AxiAdvSpiSpeBfSet(adi_fpga9025_Device_t*         device,
                                   fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                   uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiSpeBfGet(adi_fpga9025_Device_t*         device,
                                   fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                   uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiTxDataBfSet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiTxEmptyBfGet(adi_fpga9025_Device_t*         device,
                                       fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                       uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoHalfEmptyBfSet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoHalfEmptyBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoHalfEmptyIenBfSet(adi_fpga9025_Device_t*         device,
                                                  fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                  uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoHalfEmptyIenBfGet(adi_fpga9025_Device_t*         device,
                                                  fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                  uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoOccupancyBfGet(adi_fpga9025_Device_t*         device,
                                               fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                               uint16_t*                      bfValue);

int32_t fpga9025_AxiAdvSpiTxFifoResetBfSet(adi_fpga9025_Device_t*         device,
                                           fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                           uint8_t                        bfValue);

int32_t fpga9025_AxiAdvSpiTxFullBfGet(adi_fpga9025_Device_t*         device,
                                      fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                      uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiModuleVersionMajorBfGet(adi_fpga9025_Device_t*         device,
                                                  fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                  uint8_t*                       bfValue);

int32_t fpga9025_AxiAdvSpiModuleVersionMinorBfGet(adi_fpga9025_Device_t*         device,
                                                  fpga9025_BfAxiAdvSpiChanAddr_e baseAddr,
                                                  uint16_t*                      bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_AXI_ADV_SPI_H__

/*  EOF: fpga9025_bf_axi_adv_spi.h */
