/**
 * \file fpga9025_bf_xilinx_jesd204c_types.h Automatically generated file with generator ver 0.0.1.0.
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

#ifndef __FPGA9025_BF_XILINX_JESD204C_TYPES_H__
#define __FPGA9025_BF_XILINX_JESD204C_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum fpga9025_BfXilinxJesd204cChanAddr
{
    FPGA9025_BF_JESD204C_DEFRAMER_0 = 0x43410000,
    FPGA9025_BF_JESD204C_DEFRAMER_1 = 0x43411000,
    FPGA9025_BF_JESD204C_DEFRAMER_2 = 0x43412000,
    FPGA9025_BF_JESD204C_FRAMER_0 = 0x43413000,
    FPGA9025_BF_JESD204C_FRAMER_1 = 0x43414000
} fpga9025_BfXilinxJesd204cChanAddr_e;

#ifdef __cplusplus
}
#endif

#endif // __FPGA9025_BF_XILINX_JESD204C_TYPES_H__

/*  EOF: fpga9025_bf_xilinx_jesd204c_types.h */
