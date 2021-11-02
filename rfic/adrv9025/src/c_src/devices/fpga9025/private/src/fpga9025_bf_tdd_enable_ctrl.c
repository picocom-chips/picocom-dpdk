/**
 * \file fpga9025_bf_tdd_enable_ctrl.c Automatically generated file with generator ver 0.0.1.0.
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

#include "./../../private/include/fpga9025_bf_tdd_enable_ctrl.h"
#include "./../../private/include/fpga9025_bf_hal.h"
#include "adi_common_error.h"

/**
 * \brief Enable Bit
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlEnableBfSet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                          uint8_t                            bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlEnableBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlEnableBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0xC),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Enable Bit
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlEnableBfGet(adi_fpga9025_Device_t*             device,
                                          fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                          uint8_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlEnableBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0xC),
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
 * \brief End Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlEndValueBfSet(adi_fpga9025_Device_t*             device,
                                            fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                            uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlEndValueBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlEndValueBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x8),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief End Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlEndValueBfGet(adi_fpga9025_Device_t*             device,
                                            fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                            uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlEndValueBfGet Address");
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
 * \brief Active Frames
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesActiveBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlFramesActiveBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesActiveBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x20),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Active Frames
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesActiveBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesActiveBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x20),
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
 * \brief Inactive Frames
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesInactiveBfSet(adi_fpga9025_Device_t*             device,
                                                  fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                  uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlFramesInactiveBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesInactiveBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x24),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Inactive Frames
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesInactiveBfGet(adi_fpga9025_Device_t*             device,
                                                  fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                  uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesInactiveBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x24),
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
 * \brief Frames Offset
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesOffsetBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlFramesOffsetBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesOffsetBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x1C),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Frames Offset
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlFramesOffsetBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlFramesOffsetBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x1C),
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
 * \brief Manual TDD Enable Signal
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlManualEnableBfSet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t                            bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlManualEnableBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlManualEnableBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x28),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Manual TDD Enable Signal
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlManualEnableBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlManualEnableBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x28),
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
 * \brief Secondary Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecEnableBfSet(adi_fpga9025_Device_t*             device,
                                             fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                             uint8_t                            bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlSecEnableBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecEnableBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x18),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Secondary Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecEnableBfGet(adi_fpga9025_Device_t*             device,
                                             fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                             uint8_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecEnableBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x18),
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
 * \brief Secondary End Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecEndValueBfSet(adi_fpga9025_Device_t*             device,
                                               fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                               uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlSecEndValueBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecEndValueBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x14),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Secondary End Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecEndValueBfGet(adi_fpga9025_Device_t*             device,
                                               fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                               uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecEndValueBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x14),
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
 * \brief Secondary Start Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecStartValueBfSet(adi_fpga9025_Device_t*             device,
                                                 fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                 uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlSecStartValueBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecStartValueBfSet Address");
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
 * \brief Secondary Start Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlSecStartValueBfGet(adi_fpga9025_Device_t*             device,
                                                 fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                 uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlSecStartValueBfGet Address");
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
 * \brief Start Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlStartValueBfSet(adi_fpga9025_Device_t*             device,
                                              fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                              uint32_t                           bfValue)
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
                         "Invalid fpga9025_TddEnableCtrlStartValueBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlStartValueBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x4),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Start Value
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlStartValueBfGet(adi_fpga9025_Device_t*             device,
                                              fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                              uint32_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlStartValueBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x4),
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
 * \brief Major Version
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlVersionMajorBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint8_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlVersionMajorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x0),
                                          &rxBfData[0],
                                          0xFF0000,
                                          0xD0);
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
 * \brief Minor Version
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfTddEnableCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_TddEnableCtrlVersionMinorBfGet(adi_fpga9025_Device_t*             device,
                                                fpga9025_BfTddEnableCtrlChanAddr_e baseAddr,
                                                uint16_t*                          bfValue)
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
    if ((baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_RX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX1_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX2_TO_ORX2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT1) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT2) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_EXT4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX3) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX3_TO_ORX4) &&
            (baseAddr != FPGA9025_BF_TDD_ENABLE_CONTROL_TX4_TO_ORX4))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_TddEnableCtrlVersionMinorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x0),
                                          &rxBfData[0],
                                          0xFFFF,
                                          0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfReadAssembleData(device,
                                                 &rxBfData[0x0],
                                                 0x1,
                                                 &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint16_t)data;

    return recoveryAction;
}

/*  EOF: fpga9025_bf_tdd_enable_ctrl.c */
