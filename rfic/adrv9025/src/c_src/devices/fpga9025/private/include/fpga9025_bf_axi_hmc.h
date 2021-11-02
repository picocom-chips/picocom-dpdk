/**
 * \file fpga9025_bf_axi_hmc.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_AXI_HMC_H__
#define __FPGA9025_BF_AXI_HMC_H__

#include "./../../private/include/fpga9025_bf_axi_hmc_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_AxiHmcAxilitePageBfSet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t                     bfValue);

int32_t fpga9025_AxiHmcAxilitePageBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc0DevRstBfGet(adi_fpga9025_Device_t*      device,
                                       fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                       uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc0FerrBfGet(adi_fpga9025_Device_t*      device,
                                     fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                     uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc0MmcmRstBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc0PhyRstBfGet(adi_fpga9025_Device_t*      device,
                                       fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                       uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc0XcvrRstBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc1DevRstBfGet(adi_fpga9025_Device_t*      device,
                                       fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                       uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc1FerrBfGet(adi_fpga9025_Device_t*      device,
                                     fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                     uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc1MmcmRstBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc1PhyRstBfGet(adi_fpga9025_Device_t*      device,
                                       fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                       uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcHmc1XcvrRstBfGet(adi_fpga9025_Device_t*      device,
                                        fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                        uint8_t*                    bfValue);

int32_t fpga9025_AxiHmcScratchBfSet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                    uint32_t                    bfValue);

int32_t fpga9025_AxiHmcScratchBfGet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                    uint32_t*                   bfValue);

int32_t fpga9025_AxiHmcTimerBfSet(adi_fpga9025_Device_t*      device,
                                  fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                  uint32_t                    bfValue);

int32_t fpga9025_AxiHmcTimerBfGet(adi_fpga9025_Device_t*      device,
                                  fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                  uint32_t*                   bfValue);

int32_t fpga9025_AxiHmcVersionBfGet(adi_fpga9025_Device_t*      device,
                                    fpga9025_BfAxiHmcChanAddr_e baseAddr,
                                    uint32_t*                   bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_AXI_HMC_H__

/*  EOF: fpga9025_bf_axi_hmc.h */
