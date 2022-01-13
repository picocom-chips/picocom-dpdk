/**
 * \file fpga9025_bf_dp_tx_sof_select.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_DP_TX_SOF_SELECT_H__
#define __FPGA9025_BF_DP_TX_SOF_SELECT_H__

#include "./../../private/include/fpga9025_bf_dp_tx_sof_select_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_DpTxSofSelectDelayBfSet(adi_fpga9025_Device_t*             device,
                                         fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                         uint8_t                            bfValue);

int32_t fpga9025_DpTxSofSelectDelayBfGet(adi_fpga9025_Device_t*             device,
                                         fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                         uint8_t*                           bfValue);

int32_t fpga9025_DpTxSofSelectModuleVersionMajorBfGet(adi_fpga9025_Device_t*             device,
                                                      fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                                      uint8_t*                           bfValue);

int32_t fpga9025_DpTxSofSelectModuleVersionMinorBfGet(adi_fpga9025_Device_t*             device,
                                                      fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                                      uint16_t*                          bfValue);

int32_t fpga9025_DpTxSofSelectResetBfSet(adi_fpga9025_Device_t*             device,
                                         fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                         uint8_t                            bfValue);

int32_t fpga9025_DpTxSofSelectResetBfGet(adi_fpga9025_Device_t*             device,
                                         fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                         uint8_t*                           bfValue);

int32_t fpga9025_DpTxSofSelectSelectBfSet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                          uint8_t                            bfValue);

int32_t fpga9025_DpTxSofSelectSelectBfGet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfDpTxSofSelectChanAddr_e baseAddr,
                                          uint8_t*                           bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_DP_TX_SOF_SELECT_H__

/*  EOF: fpga9025_bf_dp_tx_sof_select.h */
