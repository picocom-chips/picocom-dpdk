/**
 * \file fpga9025_bf_axi_adrv9025.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_AXI_ADRV9025_H__
#define __FPGA9025_BF_AXI_ADRV9025_H__

#include "./../../private/include/fpga9025_bf_axi_adrv9025_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_AxiAdrv9025Ad9528ResetBfSet(adi_fpga9025_Device_t*           device,
                                             fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                             uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025Ad9528ResetBfGet(adi_fpga9025_Device_t*           device,
                                             fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                             uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025Adrv9025ResetBfSet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025Adrv9025ResetBfGet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025DesignIdBfGet(adi_fpga9025_Device_t*           device,
                                          fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                          uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0BfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0DetCounterBfGet(adi_fpga9025_Device_t*           device,
                                                        fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                        uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0DetEdgeLevelBfSet(adi_fpga9025_Device_t*           device,
                                                          fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                          uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0DetEdgeLevelBfGet(adi_fpga9025_Device_t*           device,
                                                          fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                          uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0DetPolarityBfSet(adi_fpga9025_Device_t*           device,
                                                         fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                         uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt0DetPolarityBfGet(adi_fpga9025_Device_t*           device,
                                                         fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                         uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1BfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1DetCounterBfGet(adi_fpga9025_Device_t*           device,
                                                        fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                        uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1DetEdgeLevelBfSet(adi_fpga9025_Device_t*           device,
                                                          fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                          uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1DetEdgeLevelBfGet(adi_fpga9025_Device_t*           device,
                                                          fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                          uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1DetPolarityBfSet(adi_fpga9025_Device_t*           device,
                                                         fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                         uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpInterrupt1DetPolarityBfGet(adi_fpga9025_Device_t*           device,
                                                         fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                         uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnArmJtagBfSet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnArmJtagBfGet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnSpi2BfSet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnSpi2BfGet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnTxToOrxBfSet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint32_t                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioEnTxToOrxBfGet(adi_fpga9025_Device_t*           device,
                                               fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                               uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025GpioInputBfGet(adi_fpga9025_Device_t*           device,
                                           fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                           uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025GpioOutputBfSet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint32_t                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioOutputBfGet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx1ToOrx1BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx1ToOrx1BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx1ToOrx2BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx1ToOrx2BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx2ToOrx1BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx2ToOrx1BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx2ToOrx2BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx2ToOrx2BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx3ToOrx3BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx3ToOrx3BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx3ToOrx4BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx3ToOrx4BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx4ToOrx3BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx4ToOrx3BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx4ToOrx4BfSet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioSelTx4ToOrx4BfGet(adi_fpga9025_Device_t*           device,
                                                  fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                  uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp00BfSet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp00BfGet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp01BfSet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp01BfGet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp02BfSet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcRxdp02BfGet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcTxdp00BfSet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcTxdp00BfGet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcTxdp01BfSet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025GpioTriggerSrcTxdp01BfGet(adi_fpga9025_Device_t*           device,
                                                      fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                                      uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTristateBfSet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint32_t                         bfValue);

int32_t fpga9025_AxiAdrv9025GpioTristateBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025ResetBfSet(adi_fpga9025_Device_t*           device,
                                       fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                       uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025ResetBfGet(adi_fpga9025_Device_t*           device,
                                       fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                       uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025ScratchPadBfSet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint32_t                         bfValue);

int32_t fpga9025_AxiAdrv9025ScratchPadBfGet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint32_t*                        bfValue);

int32_t fpga9025_AxiAdrv9025TestInputBfSet(adi_fpga9025_Device_t*           device,
                                           fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                           uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025TestInputBfGet(adi_fpga9025_Device_t*           device,
                                           fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                           uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025TestOutputBfSet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025TestOutputBfGet(adi_fpga9025_Device_t*           device,
                                            fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                            uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025TestTristateBfSet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint8_t                          bfValue);

int32_t fpga9025_AxiAdrv9025TestTristateBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025VersionMajorBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint8_t*                         bfValue);

int32_t fpga9025_AxiAdrv9025VersionMinorBfGet(adi_fpga9025_Device_t*           device,
                                              fpga9025_BfAxiAdrv9025ChanAddr_e baseAddr,
                                              uint16_t*                        bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_AXI_ADRV9025_H__

/*  EOF: fpga9025_bf_axi_adrv9025.h */
