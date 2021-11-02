/**
 * \file fpga9010_bf_dp_rx_dma.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_DP_RX_DMA_H__
#define __FPGA9010_BF_DP_RX_DMA_H__

#include "./../../private/include/fpga9010_bf_dp_rx_dma_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_DpRxDmaActiveBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_DpRxDmaCompleteBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_DpRxDmaEnableEnhancedModeBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                                uint8_t bfValue);
int32_t fpga9010_DpRxDmaEnableEnhancedModeBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_DpRxDmaEnableSgBfSet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                      uint8_t bfValue);
int32_t fpga9010_DpRxDmaEnableSgBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_DpRxDmaHaltCompleteBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_DpRxDmaLengthBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                    uint32_t bfValue);
int32_t fpga9010_DpRxDmaLengthBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                    uint32_t *bfValue);


int32_t fpga9010_DpRxDmaOverflowBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_DpRxDmaResetBfSet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                   uint8_t bfValue);
int32_t fpga9010_DpRxDmaResetBfGet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                   uint8_t *bfValue);


int32_t fpga9010_DpRxDmaRunStopBfSet(adi_fpga9010_Device_t *device, 
                                     fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                     uint8_t bfValue);
int32_t fpga9010_DpRxDmaRunStopBfGet(adi_fpga9010_Device_t *device, 
                                     fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                     uint8_t *bfValue);


int32_t fpga9010_DpRxDmaSgFirstDescriptorBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                               uint32_t bfValue);
int32_t fpga9010_DpRxDmaSgFirstDescriptorBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                               uint32_t *bfValue);


int32_t fpga9010_DpRxDmaSgLastDescriptorBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                              uint32_t bfValue);
int32_t fpga9010_DpRxDmaSgLastDescriptorBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                              uint32_t *bfValue);


int32_t fpga9010_DpRxDmaSimpleStartAddrBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                             uint32_t bfValue);
int32_t fpga9010_DpRxDmaSimpleStartAddrBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                             uint32_t *bfValue);


int32_t fpga9010_DpRxDmaValidDataWidthStreamBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                                  uint8_t bfValue);
int32_t fpga9010_DpRxDmaValidDataWidthStreamBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                                  uint8_t *bfValue);


int32_t fpga9010_DpRxDmaVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_DpRxDmaVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpRxDmaChanAddr_e baseAddr, 
                                          uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_DP_RX_DMA_H__

/*  EOF: fpga9010_bf_dp_rx_dma.h */

