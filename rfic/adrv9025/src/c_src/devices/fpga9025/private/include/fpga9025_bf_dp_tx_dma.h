/**
 * \file fpga9025_bf_dp_tx_dma.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_DP_TX_DMA_H__
#define __FPGA9025_BF_DP_TX_DMA_H__

#include "./../../private/include/fpga9025_bf_dp_tx_dma_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_DpTxDmaActiveBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaCompleteBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaContinuousBfSet(adi_fpga9025_Device_t*       device,
                                        fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                        uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaContinuousBfGet(adi_fpga9025_Device_t*       device,
                                        fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                        uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaEnableEnhancedModeBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaEnableEnhancedModeBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaEnableSgBfSet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaEnableSgBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaHaltCompleteBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaLengthBfSet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint32_t                     bfValue);

int32_t fpga9025_DpTxDmaLengthBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint32_t*                    bfValue);

int32_t fpga9025_DpTxDmaResetBfSet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                   uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaResetBfGet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                   uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaRunStopBfSet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                     uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaRunStopBfGet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                     uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaSgLastDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                              uint32_t                     bfValue);

int32_t fpga9025_DpTxDmaSgLastDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                              uint32_t*                    bfValue);

int32_t fpga9025_DpTxDmaSimpleStartAddrBfSet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                             uint32_t                     bfValue);

int32_t fpga9025_DpTxDmaSimpleStartAddrBfGet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                             uint32_t*                    bfValue);

int32_t fpga9025_DpTxDmaSimpleStartAddrMswBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint32_t                     bfValue);

int32_t fpga9025_DpTxDmaSimpleStartAddrMswBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint32_t*                    bfValue);

int32_t fpga9025_DpTxDmaSqFirstDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                               uint32_t                     bfValue);

int32_t fpga9025_DpTxDmaSqFirstDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                               uint32_t*                    bfValue);

int32_t fpga9025_DpTxDmaUnderflowBfGet(adi_fpga9025_Device_t*       device,
                                       fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                       uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaValidDataWidthStreamBfSet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                  uint8_t                      bfValue);

int32_t fpga9025_DpTxDmaValidDataWidthStreamBfGet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                  uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaVersionMajorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue);

int32_t fpga9025_DpTxDmaVersionMinorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint16_t*                    bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_DP_TX_DMA_H__

/*  EOF: fpga9025_bf_dp_tx_dma.h */
