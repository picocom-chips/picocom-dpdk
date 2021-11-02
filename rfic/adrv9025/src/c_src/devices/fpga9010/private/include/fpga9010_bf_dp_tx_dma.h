/**
 * \file fpga9010_bf_dp_tx_dma.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_DP_TX_DMA_H__
#define __FPGA9010_BF_DP_TX_DMA_H__

#include "./../../private/include/fpga9010_bf_dp_tx_dma_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_DpTxDmaActiveBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                    uint8_t *bfValue);


int32_t fpga9010_DpTxDmaCompleteBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_DpTxDmaContinuousBfSet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                        uint8_t bfValue);
int32_t fpga9010_DpTxDmaContinuousBfGet(adi_fpga9010_Device_t *device, 
                                        fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                        uint8_t *bfValue);


int32_t fpga9010_DpTxDmaEnableEnhancedModeBfSet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                                uint8_t bfValue);
int32_t fpga9010_DpTxDmaEnableEnhancedModeBfGet(adi_fpga9010_Device_t *device, 
                                                fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                                uint8_t *bfValue);


int32_t fpga9010_DpTxDmaEnableSgBfSet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                      uint8_t bfValue);
int32_t fpga9010_DpTxDmaEnableSgBfGet(adi_fpga9010_Device_t *device, 
                                      fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                      uint8_t *bfValue);


int32_t fpga9010_DpTxDmaHaltCompleteBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_DpTxDmaLengthBfSet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                    uint32_t bfValue);
int32_t fpga9010_DpTxDmaLengthBfGet(adi_fpga9010_Device_t *device, 
                                    fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                    uint32_t *bfValue);


int32_t fpga9010_DpTxDmaResetBfSet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                   uint8_t bfValue);
int32_t fpga9010_DpTxDmaResetBfGet(adi_fpga9010_Device_t *device, 
                                   fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                   uint8_t *bfValue);


int32_t fpga9010_DpTxDmaRunStopBfSet(adi_fpga9010_Device_t *device, 
                                     fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                     uint8_t bfValue);
int32_t fpga9010_DpTxDmaRunStopBfGet(adi_fpga9010_Device_t *device, 
                                     fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                     uint8_t *bfValue);


int32_t fpga9010_DpTxDmaSgLastDescriptorBfSet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                              uint32_t bfValue);
int32_t fpga9010_DpTxDmaSgLastDescriptorBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                              uint32_t *bfValue);


int32_t fpga9010_DpTxDmaSimpleStartAddrBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                             uint32_t bfValue);
int32_t fpga9010_DpTxDmaSimpleStartAddrBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                             uint32_t *bfValue);


int32_t fpga9010_DpTxDmaSqFirstDescriptorBfSet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                               uint32_t bfValue);
int32_t fpga9010_DpTxDmaSqFirstDescriptorBfGet(adi_fpga9010_Device_t *device, 
                                               fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                               uint32_t *bfValue);


int32_t fpga9010_DpTxDmaUnderflowBfGet(adi_fpga9010_Device_t *device, 
                                       fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                       uint8_t *bfValue);


int32_t fpga9010_DpTxDmaValidDataWidthStreamBfSet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                                  uint8_t bfValue);
int32_t fpga9010_DpTxDmaValidDataWidthStreamBfGet(adi_fpga9010_Device_t *device, 
                                                  fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                                  uint8_t *bfValue);


int32_t fpga9010_DpTxDmaVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                          uint8_t *bfValue);


int32_t fpga9010_DpTxDmaVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfDpTxDmaChanAddr_e baseAddr, 
                                          uint16_t *bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_DP_TX_DMA_H__

/*  EOF: fpga9010_bf_dp_tx_dma.h */

