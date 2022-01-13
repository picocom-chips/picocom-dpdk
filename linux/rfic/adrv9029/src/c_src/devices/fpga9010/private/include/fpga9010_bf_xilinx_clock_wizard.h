/**
 * \file fpga9010_bf_xilinx_clock_wizard.h Automatically generated file with generator ver 0.0.0.1.
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

#ifndef __FPGA9010_BF_XILINX_CLOCK_WIZARD_H__
#define __FPGA9010_BF_XILINX_CLOCK_WIZARD_H__

#include "./../../private/include/fpga9010_bf_xilinx_clock_wizard_types.h"
#include "adi_fpga9010.h"

#ifdef __cplusplus
extern "C"{
#endif


int32_t fpga9010_XilinxClockWizardClkfboutFracBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint16_t bfValue);
int32_t fpga9010_XilinxClockWizardClkfboutFracBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint16_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkfboutMultBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkfboutMultBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkfboutPhaseBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkfboutPhaseBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout0DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout0DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout0DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout0DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout0FracBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint16_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout0FracBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint16_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout0PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout0PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout1DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout1DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout1DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout1DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout1PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout1PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout2DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout2DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout2DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout2DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout2PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout2PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout3DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout3DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout3DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout3DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout3PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout3PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout4DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout4DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout4DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout4DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout4PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout4PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout5DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout5DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout5DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout5DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout5PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout5PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout6DivideBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout6DivideBfGet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout6DutyBfSet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout6DutyBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardClkout6PhaseBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardClkout6PhaseBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardDivclkDivideBfSet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardDivclkDivideBfGet(adi_fpga9010_Device_t *device, 
                                                    fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                    uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardErrorStatusBfGet(adi_fpga9010_Device_t *device, 
                                                   fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                   uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardInterruptEnableBfSet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                       uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardInterruptEnableBfGet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                       uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardInterruptStatusBfSet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                       uint32_t bfValue);
int32_t fpga9010_XilinxClockWizardInterruptStatusBfGet(adi_fpga9010_Device_t *device, 
                                                       fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                       uint32_t *bfValue);


int32_t fpga9010_XilinxClockWizardLoadBfSet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                            uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardLoadBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                            uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardLockedBfGet(adi_fpga9010_Device_t *device, 
                                              fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                              uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardSaddrBfSet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                             uint8_t bfValue);
int32_t fpga9010_XilinxClockWizardSaddrBfGet(adi_fpga9010_Device_t *device, 
                                             fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                             uint8_t *bfValue);


int32_t fpga9010_XilinxClockWizardSoftwareResetBfSet(adi_fpga9010_Device_t *device, 
                                                     fpga9010_BfXilinxClockWizardChanAddr_e baseAddr, 
                                                     uint32_t bfValue);

#ifdef __cplusplus
}
#endif

#endif // __FPGA9010_BF_XILINX_CLOCK_WIZARD_H__

/*  EOF: fpga9010_bf_xilinx_clock_wizard.h */

