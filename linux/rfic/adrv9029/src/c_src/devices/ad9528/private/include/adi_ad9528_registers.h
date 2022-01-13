/**
* \file adi_ad9528_registers.h
* \brief Contains register map definition for the AD9528 clock chip
*/
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef _ADI_AD9528_REGISTERS_H_
#define _ADI_AD9528_REGISTERS_H_

#include "adi_common_error_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* AD9528 SPI Address defines */
#define AD9528_ADDR_ADI_SPI_CONFIG_A        0x000
#define AD9528_ADDR_ADI_SPI_CONFIG_B        0x001
#define AD9528_ADDR_IO_UPDATE               0x00F

#define AD9528_ADDR_REF_A_DIVIDER_LSB       0x100
#define AD9528_ADDR_REF_A_DIVIDER_MSB       0x101
#define AD9528_ADDR_REF_B_DIVIDER_LSB       0x102
#define AD9528_ADDR_REF_B_DIVIDER_MSB       0x103
#define AD9528_ADDR_PLL1_N_DIV_LSB          0x104
#define AD9528_ADDR_PLL1_N_DIV_MSB          0x105
#define AD9528_ADDR_PLL1_CHARGEPUMP         0x106
#define AD9528_ADDR_PLL1_CP_CTRL2           0x107
#define AD9528_ADDR_INPUT_RECEIVERS1        0x108
#define AD9528_ADDR_INPUT_RECEIVERS2        0x109
#define AD9528_ADDR_INPUT_RECEIVERS3        0x10A
#define AD9528_ADDR_PLL1_FASTLOCK           0x10B

#define AD9528_ADDR_PLL2_CHARGEPUMP         0x200
#define AD9528_ADDR_PLL2_N_DIV              0x201
#define AD9528_ADDR_PLL2_CTRL               0x202
#define AD9528_ADDR_PLL2_VCO_CTRL           0x203
#define AD9528_ADDR_PLL2_VCO_DIV            0x204
#define AD9528_ADDR_PLL2_LF_CTRL1           0x205
#define AD9528_ADDR_PLL2_LF_CTRL2           0x206
#define AD9528_ADDR_PLL2_RDIV               0x207
#define AD9528_ADDR_PLL2_REPLICA_CHDIV      0x208
#define AD9528_ADDR_PLL2_REPLICA_DIV_PHASE  0x209

#define AD9528_ADDR_CH_OUT0_CTRL1           0x300
#define AD9528_ADDR_CH_OUT0_CTRL2           0x301
#define AD9528_ADDR_CH_OUT0_CHDIV           0x302
#define AD9528_ADDR_OUTPUT_SYNC             0x32A
#define AD9528_ADDR_MASK_SYNC1              0x32B
#define AD9528_ADDR_MASK_SYNC2              0x32C
#define AD9528_ADDR_EN_OUTPUT_PATH_SEL1     0x32D
#define AD9528_ADDR_EN_OUTPUT_PATH_SEL2     0x32E

#define AD9528_ADDR_SYSERF_DIV_LSB          0x400
#define AD9528_ADDR_SYSERF_DIV_MSB          0x401
#define AD9528_ADDR_SYSREF_CTRL3            0x402
#define AD9528_ADDR_SYSREF_CTRL4            0x403
#define AD9528_ADDR_SYSREF_CTRL5            0x404

#define AD9528_ADDR_POWERDOWN_CTRL          0x500
#define AD9528_ADDR_CH_POWERDOWN1           0x501
#define AD9528_ADDR_CH_POWERDOWN2           0x502
#define AD9528_ADDR_LDO_ENABLES1            0x503
#define AD9528_ADDR_LDO_ENABLES2            0x504
#define AD9528_ADDR_STATUS0_CTRL            0x505
#define AD9528_ADDR_STATUS1_CTRL            0x506
#define AD9528_ADDR_STATUS_OE               0x507
#define AD9528_ADDR_STATUS_READBACK0        0x508
#define AD9528_ADDR_STATUS_READBACK1        0x509

#ifdef __cplusplus
}
#endif

#endif /*_ADI_AD9528_REGISTERS_H_*/
