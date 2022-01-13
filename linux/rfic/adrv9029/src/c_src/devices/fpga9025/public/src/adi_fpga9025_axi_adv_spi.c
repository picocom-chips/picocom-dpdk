/*!
* \file adi_fpga9025_axi_adv_spi.c
* \brief Contains FPGA9025 AXI Advanced SPI function implementations
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_axi_adv_spi.h"
#include "adi_fpga9025_axi_adv_spi_types.h"
#include "../../private/include/fpga9025_bf_axi_adv_spi.h"

int32_t adi_fpga9025_AxiAdvSpiCfgSet(adi_fpga9025_Device_t*              device,
                                     adi_fpga9025_AxiAdvSpiFeatConfig_t* advSpiCfg,
                                     uint8_t                             slaveSelect)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t registerValue  = 0;
    /* starting address is slaveSelect0's address. Multiply parameter by 4 since it's byte-addressing and each SS gets a full register */
    uint32_t registerAddress = 0x44A00080 + (slaveSelect * 4);

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        advSpiCfg);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_HAL);
#endif

    /* Build up the registerValue */
    registerValue |= ((uint32_t)advSpiCfg->enable & 0x1) << 0;
    registerValue |= ((uint32_t)advSpiCfg->cpol & 0x1) << 1;
    registerValue |= ((uint32_t)advSpiCfg->cpha & 0x1) << 2;
    registerValue |= ((uint32_t)advSpiCfg->lsbFirst & 0x1) << 3;
    registerValue |= ((uint32_t)advSpiCfg->fourWire & 0x1) << 4;
    registerValue |= ((uint32_t)advSpiCfg->misoSampleSlip & 0x1) << 5;
    registerValue |= ((uint32_t)advSpiCfg->threeWireTriPoint & 0xFF) << 8;
    registerValue |= ((uint32_t)advSpiCfg->clockDiv & 0xFFFF) << 16;

    recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                               registerAddress,
                                               registerValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     recoveryAction,
                     ADI_COMMON_ACT_ERR_CHECK_PARAM,
                     advSpiCfg,
                     "Error configuring Advanced SPI");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return device->common.error.newAction;
}

int32_t adi_fpga9025_AxiAdvSpiChipSelectAll(adi_fpga9025_Device_t* device,
                                            uint8_t                enable)
{
    /* Manual Slave Select Assertion Enable Bit */
    static const uint32_t MAN_SS_EN = 0x00000080;

    /* Tokelau Device/s slave select indices*/
    /* TODO: This variable should be calculated at Board Discover in future */
    static const uint32_t TOK_CS = 0x00000001;

    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    /*Address of SPICR*/
    uint32_t spicrAddress = 0x44A00060;

    /*Address of SPISSR*/
    uint32_t spissrAddress = 0x44A00070;

    uint32_t spicrValue = 0;

    recoveryAction = adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                              spicrAddress,
                                              &spicrValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     recoveryAction,
                     ADI_COMMON_ACT_ERR_CHECK_PARAM,
                     spicrAddress,
                     "Error reading spicrAddress");
    ADI_ERROR_RETURN(device->common.error.newAction);

    if (enable == ADI_TRUE)
    {
        /* Select all Tokelau devices */
        recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                                   spissrAddress,
                                                   ~TOK_CS);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         recoveryAction,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         spissrAddress,
                         "Error selecting all Tokelau devices");
        ADI_ERROR_RETURN(device->common.error.newAction);

        /* Enable manual select mode */
        recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                                   spicrAddress,
                                                   (spicrValue | MAN_SS_EN));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         recoveryAction,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         spicrAddress,
                         "Error writing spicrAddress");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    else
    {
        /* Disable manual select mode */
        recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                                   spicrAddress,
                                                   (spicrValue & (~MAN_SS_EN)));
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         recoveryAction,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         spicrAddress,
                         "Error writing spicrAddress");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    return device->common.error.newAction;
}
