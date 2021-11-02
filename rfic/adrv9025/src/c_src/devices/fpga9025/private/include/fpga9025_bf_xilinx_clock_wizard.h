/**
 * \file fpga9025_bf_xilinx_clock_wizard.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_XILINX_CLOCK_WIZARD_H__
#define __FPGA9025_BF_XILINX_CLOCK_WIZARD_H__

#include "./../../private/include/fpga9025_bf_xilinx_clock_wizard_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

int32_t fpga9025_XilinxClockWizardClkfboutFracBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint16_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkfboutFracBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint16_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkfboutMultBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkfboutMultBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkfboutPhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkfboutPhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout0DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout0DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout0DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout0DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout0FracBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint16_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout0FracBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint16_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout0PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout0PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout1DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout1DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout1DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout1DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout1PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout1PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout2DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout2DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout2DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout2DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout2PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout2PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout3DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout3DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout3DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout3DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout3PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout3PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout4DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout4DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout4DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout4DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout4PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout4PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout5DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout5DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout5DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout5DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout5PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout5PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout6DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardClkout6DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout6DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout6DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardClkout6PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardClkout6PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardDivclkDivideBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardDivclkDivideBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardErrorStatusBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardInterruptEnableBfSet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardInterruptEnableBfGet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardInterruptStatusBfSet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t                               bfValue);

int32_t fpga9025_XilinxClockWizardInterruptStatusBfGet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t*                              bfValue);

int32_t fpga9025_XilinxClockWizardLoadBfSet(adi_fpga9025_Device_t*                 device,
                                            fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                            uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardLoadBfGet(adi_fpga9025_Device_t*                 device,
                                            fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                            uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardLockedBfGet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                              uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardSaddrBfSet(adi_fpga9025_Device_t*                 device,
                                             fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                             uint8_t                                bfValue);

int32_t fpga9025_XilinxClockWizardSaddrBfGet(adi_fpga9025_Device_t*                 device,
                                             fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                             uint8_t*                               bfValue);

int32_t fpga9025_XilinxClockWizardSoftwareResetBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t                               bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_XILINX_CLOCK_WIZARD_H__

/*  EOF: fpga9025_bf_xilinx_clock_wizard.h */
