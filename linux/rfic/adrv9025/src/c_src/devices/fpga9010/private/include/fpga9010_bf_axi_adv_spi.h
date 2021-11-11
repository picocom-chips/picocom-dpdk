/**
 * \file fpga9010_bf_axi_adv_spi.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_AXI_ADV_SPI_H__
#define __FPGA9010_BF_AXI_ADV_SPI_H__

#include "./../../private/include/fpga9010_bf_axi_adv_spi_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_AxiAdvSpiAdvFeat3wireTriPointBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                     uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeat3wireTriPointBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                     uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatClockDivBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint16_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatClockDivBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint16_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatCphaBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatCphaBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatCpolBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatCpolBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                            uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatEnableBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                              uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatEnableBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                              uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatFourWireBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatFourWireBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatLsbFirstBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatLsbFirstBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiAdvFeatMisoSampleSlipBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                      uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiAdvFeatMisoSampleSlipBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
uint8_t channelId,                                                      uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiCphaBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiCphaBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiCpolBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiCpolBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDrrFullBfSet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDrrFullBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDrrFullIenBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                          uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDrrFullIenBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDrrOverrunBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                          uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDrrOverrunBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDrrOverrunIenBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                             uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDrrOverrunIenBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDtrEmptyBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDtrEmptyBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiDtrEmptyIenBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiDtrEmptyIenBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiGieBfSet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                   uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiGieBfGet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                   uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiLoopBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiLoopBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiLsbFirstBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiLsbFirstBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiManSsEnBfSet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiManSsEnBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiMasterBfSet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiMasterBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiModfBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiModfFlagBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiModfIenBfSet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiModfIenBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiMstrInhibitBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiMstrInhibitBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiResetBfSet(adi_fpga9010_Device_t *device, 
                                     fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                     uint32_t bfValue);


int32_t fpga9010_AxiAdvSpiRxDataBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiRxEmptyBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiRxFifoOccupancyBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                               uint16_t *bfValue);


int32_t fpga9010_AxiAdvSpiRxFifoResetBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t bfValue);


int32_t fpga9010_AxiAdvSpiRxFullBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiSlaveSelectBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint32_t bfValue);
int32_t fpga9010_AxiAdvSpiSlaveSelectBfGet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint32_t *bfValue);


int32_t fpga9010_AxiAdvSpiSpeBfSet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                   uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiSpeBfGet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                   uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiTxDataBfSet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t bfValue);


int32_t fpga9010_AxiAdvSpiTxEmptyBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiTxFifoHalfEmptyBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                               uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiTxFifoHalfEmptyBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                               uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiTxFifoHalfEmptyIenBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                                  uint8_t bfValue);
int32_t fpga9010_AxiAdvSpiTxFifoHalfEmptyIenBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                                  uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiTxFifoOccupancyBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                               uint16_t *bfValue);


int32_t fpga9010_AxiAdvSpiTxFifoResetBfSet(adi_fpga9010_Device_t *device, 
                                           fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                           uint8_t bfValue);


int32_t fpga9010_AxiAdvSpiTxFullBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiModuleVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                                  uint8_t *bfValue);


int32_t fpga9010_AxiAdvSpiModuleVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfAxiAdvSpiChanAddr_e baseAddr, 
                                                  uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_AXI_ADV_SPI_H__

/*  EOF: fpga9010_bf_axi_adv_spi.h */

