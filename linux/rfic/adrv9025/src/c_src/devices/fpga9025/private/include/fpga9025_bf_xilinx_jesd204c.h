/**
 * \file fpga9025_bf_xilinx_jesd204c.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_XILINX_JESD204C_H__
#define __FPGA9025_BF_XILINX_JESD204C_H__

#include "./../../private/include/fpga9025_bf_xilinx_jesd204c_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_XilinxJesd204cBufferLevelBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             channelId,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cBufferOverflowBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cCfgMbInEmbBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cCfgMbInEmbBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cCfgSubclassvBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cCfgSubclassvBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cCoreIsTxBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cCrcErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             channelId,
                                                  uint16_t*                           bfValue);

int32_t fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cEnableCmdInterfaceBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cEnableDataInterfaceBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cFecCorrectedErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                           uint8_t                             channelId,
                                                           uint16_t*                           bfValue);

int32_t fpga9025_XilinxJesd204cFecUncorrectedErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                             uint8_t                             channelId,
                                                             uint16_t*                           bfValue);

int32_t fpga9025_XilinxJesd204cIrqBlockSyncErrorBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqCrcErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnCrcErrorBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnCrcErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnFecErrorBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnFecErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnGlobalBfSet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnGlobalBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnLossMbLockBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnLossMbLockBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                            uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnMbErrorBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnMbErrorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnOverflowErrorBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnOverflowErrorBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnSysrefErrorBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqFecErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqLossMbLockBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqLossSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqMbErrorBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqOverflowErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqPendingBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cIrqSysrefReceivedBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cLane64b66bAlignBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cLaneEnableBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cLaneEnableBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cLaneMbAlignBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cMbLockBfGet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cMetaModeBfSet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cMetaModeBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cMulitblockAlignmentErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                                  uint8_t                             channelId,
                                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cNumberOfLanesInCoreBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cResetFixedBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cResetFixedBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cRxBufferDelayBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cRxBufferDelayBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cRxMbThBfSet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cRxMbThBfGet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cSyncHeaderAlignmentErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                                  uint8_t                             channelId,
                                                                  uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cSysrefCapturedBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cSysrefDelayBfSet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cSysrefDelayBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cTestModeBfSet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t                             bfValue);

int32_t fpga9025_XilinxJesd204cTestModeBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cVersionMajorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cVersionMinorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue);

int32_t fpga9025_XilinxJesd204cVersionRevisionBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_XILINX_JESD204C_H__

/*  EOF: fpga9025_bf_xilinx_jesd204c.h */
