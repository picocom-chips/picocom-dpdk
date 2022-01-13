/**
 * \file fpga9025_bf_jesd204_test_det_lat.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_JESD204_TEST_DET_LAT_H__
#define __FPGA9025_BF_JESD204_TEST_DET_LAT_H__

#include "./../../private/include/fpga9025_bf_jesd204_test_det_lat_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_Jesd204TestDetLatEnableBfSet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t                                bfValue);

int32_t fpga9025_Jesd204TestDetLatEnableBfGet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t*                               bfValue);

int32_t fpga9025_Jesd204TestDetLatLatencyBfGet(adi_fpga9025_Device_t*                 device,
                                               fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                               uint32_t*                              bfValue);

int32_t fpga9025_Jesd204TestDetLatModuleVersionMajorBfGet(adi_fpga9025_Device_t*                 device,
                                                          fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                                          uint8_t*                               bfValue);

int32_t fpga9025_Jesd204TestDetLatModuleVersionMinorBfGet(adi_fpga9025_Device_t*                 device,
                                                          fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                                          uint16_t*                              bfValue);

int32_t fpga9025_Jesd204TestDetLatRxLinkBfSet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t                                bfValue);

int32_t fpga9025_Jesd204TestDetLatRxLinkBfGet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t*                               bfValue);

int32_t fpga9025_Jesd204TestDetLatTxLinkBfSet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t                                bfValue);

int32_t fpga9025_Jesd204TestDetLatTxLinkBfGet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                              uint8_t*                               bfValue);

int32_t fpga9025_Jesd204TestDetLatValidDataWidthBfSet(adi_fpga9025_Device_t*                 device,
                                                      fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                                      uint8_t                                bfValue);

int32_t fpga9025_Jesd204TestDetLatValidDataWidthBfGet(adi_fpga9025_Device_t*                 device,
                                                      fpga9025_BfJesd204TestDetLatChanAddr_e baseAddr,
                                                      uint8_t*                               bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_JESD204_TEST_DET_LAT_H__

/*  EOF: fpga9025_bf_jesd204_test_det_lat.h */
