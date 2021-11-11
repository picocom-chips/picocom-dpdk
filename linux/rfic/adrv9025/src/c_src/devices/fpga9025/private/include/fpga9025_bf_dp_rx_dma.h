/**
 * \file fpga9025_bf_dp_rx_dma.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_DP_RX_DMA_H__
#define __FPGA9025_BF_DP_RX_DMA_H__

#include "./../../private/include/fpga9025_bf_dp_rx_dma_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_DpRxDmaActiveBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                    uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaCompleteBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaEnableEnhancedModeBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                uint8_t                      bfValue);

int32_t fpga9025_DpRxDmaEnableEnhancedModeBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaEnableSgBfSet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                      uint8_t                      bfValue);

int32_t fpga9025_DpRxDmaEnableSgBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaHaltCompleteBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaLengthBfSet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                    uint32_t                     bfValue);

int32_t fpga9025_DpRxDmaLengthBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                    uint32_t*                    bfValue);

int32_t fpga9025_DpRxDmaOverflowBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaResetBfSet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                   uint8_t                      bfValue);

int32_t fpga9025_DpRxDmaResetBfGet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                   uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaRunStopBfSet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                     uint8_t                      bfValue);

int32_t fpga9025_DpRxDmaRunStopBfGet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                     uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaSgFirstDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                               uint32_t                     bfValue);

int32_t fpga9025_DpRxDmaSgFirstDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                               uint32_t*                    bfValue);

int32_t fpga9025_DpRxDmaSgLastDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                              uint32_t                     bfValue);

int32_t fpga9025_DpRxDmaSgLastDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                              uint32_t*                    bfValue);

int32_t fpga9025_DpRxDmaSimpleStartAddrBfSet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                             uint32_t                     bfValue);

int32_t fpga9025_DpRxDmaSimpleStartAddrBfGet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                             uint32_t*                    bfValue);

int32_t fpga9025_DpRxDmaSimpleStartAddrMswBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                uint32_t                     bfValue);

int32_t fpga9025_DpRxDmaSimpleStartAddrMswBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                uint32_t*                    bfValue);

int32_t fpga9025_DpRxDmaValidDataWidthStreamBfSet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                  uint8_t                      bfValue);

int32_t fpga9025_DpRxDmaValidDataWidthStreamBfGet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                                  uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaVersionMajorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue);

int32_t fpga9025_DpRxDmaVersionMinorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpRxDmaChanAddr_e baseAddr,
                                          uint16_t*                    bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_DP_RX_DMA_H__

/*  EOF: fpga9025_bf_dp_rx_dma.h */
