/**
 * \file fpga9025_bf_xilinx_clock_wizard.c Automatically generated file with generator ver 0.0.1.0.
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

#include "./../../private/include/fpga9025_bf_xilinx_clock_wizard.h"
#include "./../../private/include/fpga9025_bf_hal.h"
#include "adi_common_error.h"

/**
 * \brief Feedback Clock Multiplier Fractional Portion
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutFracBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint16_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 1023U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkfboutFracBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutFracBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x200),
                                           (uint32_t)bfValue,
                                           0x3FF0000,
                                           0x10);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Feedback Clock Multiplier Fractional Portion
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutFracBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint16_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutFracBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x200),
                                          &rxBfData[0],
                                          0x3FF0000,
                                          0xD0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint16_t)data;

    return recoveryAction;
}

/**
 * \brief Feedback Clock Multiplier
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutMultBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkfboutMultBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutMultBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x200),
                                           (uint32_t)bfValue,
                                           0xFF00,
                                           0x8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Feedback Clock Multiplier
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutMultBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutMultBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x200),
                                          &rxBfData[0],
                                          0xFF00,
                                          0xC8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Feedback Clock Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutPhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkfboutPhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutPhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x204),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Feedback Clock Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkfboutPhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkfboutPhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x204),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout0DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x208),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x208),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout0DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x210),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x210),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Fractional Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0FracBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint16_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 1023U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout0FracBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0FracBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x208),
                                           (uint32_t)bfValue,
                                           0x3FF00,
                                           0x8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Fractional Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0FracBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint16_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0FracBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x208),
                                          &rxBfData[0],
                                          0x3FF00,
                                          0xC8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint16_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout0PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x20C),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 0 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout0PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout0PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x20C),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout1DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x214),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x214),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout1DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x21C),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x21C),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout1PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x218),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 1 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout1PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout1PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x218),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout2DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x220),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x220),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout2DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x228),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x228),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout2PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x224),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 2 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout2PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout2PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x224),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout3DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x22C),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x22C),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout3DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x234),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x234),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout3PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x230),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 3 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout3PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout3PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x230),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout4DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x238),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x238),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout4DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x240),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x240),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout4PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x23C),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 4 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout4PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout4PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x23C),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout5DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x244),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x244),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout5DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x24C),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x24C),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout5PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x248),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 5 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout5PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout5PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x248),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6DivideBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout6DivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6DivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x250),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6DivideBfGet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6DivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x250),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6DutyBfSet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout6DutyBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6DutyBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x258),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Duty Cycle
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6DutyBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6DutyBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x258),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6PhaseBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardClkout6PhaseBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6PhaseBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x254),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Clock Output 6 Phase
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardClkout6PhaseBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardClkout6PhaseBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x254),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief DIVCLK Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardDivclkDivideBfSet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 255U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardDivclkDivideBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardDivclkDivideBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x200),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief DIVCLK Divide
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardDivclkDivideBfGet(adi_fpga9025_Device_t*                 device,
                                                    fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                    uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardDivclkDivideBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x200),
                                          &rxBfData[0],
                                          0xFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Error Status
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardErrorStatusBfGet(adi_fpga9025_Device_t*                 device,
                                                   fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                   uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardErrorStatusBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x8),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Interrupt Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardInterruptEnableBfSet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardInterruptEnableBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardInterruptEnableBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x10),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardInterruptEnableBfGet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardInterruptEnableBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x10),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Interrupt Status
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardInterruptStatusBfSet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardInterruptStatusBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardInterruptStatusBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0xC),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Status
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardInterruptStatusBfGet(adi_fpga9025_Device_t*                 device,
                                                       fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                       uint32_t*                              bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardInterruptStatusBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0xC),
                                             &rxBfData[0],
                                             0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t)data;

    return recoveryAction;
}

/**
 * \brief Load Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardLoadBfSet(adi_fpga9025_Device_t*                 device,
                                            fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                            uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 1U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardLoadBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardLoadBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x25C),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Load Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardLoadBfGet(adi_fpga9025_Device_t*                 device,
                                            fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                            uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardLoadBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x25C),
                                          &rxBfData[0],
                                          0x1,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Locked
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardLockedBfGet(adi_fpga9025_Device_t*                 device,
                                              fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                              uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardLockedBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x4),
                                          &rxBfData[0],
                                          0x1,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief SADDR
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardSaddrBfSet(adi_fpga9025_Device_t*                 device,
                                             fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                             uint8_t                                bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 1U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardSaddrBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardSaddrBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x25C),
                                           (uint32_t)bfValue,
                                           0x2,
                                           0x1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief SADDR
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardSaddrBfGet(adi_fpga9025_Device_t*                 device,
                                             fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                             uint8_t*                               bfValue)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rxBfData[8]    = {0};
    uint64_t data           = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9025_BITFIELD_NULL_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardSaddrBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x25C),
                                          &rxBfData[0],
                                          0x2,
                                          0xC1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t)data;

    return recoveryAction;
}

/**
 * \brief Software Reset
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxClockWizardChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxClockWizardSoftwareResetBfSet(adi_fpga9025_Device_t*                 device,
                                                     fpga9025_BfXilinxClockWizardChanAddr_e baseAddr,
                                                     uint32_t                               bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxClockWizardSoftwareResetBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204_CORE_CLOCK_WIZARD))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxClockWizardSoftwareResetBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x0),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/*  EOF: fpga9025_bf_xilinx_clock_wizard.c */
