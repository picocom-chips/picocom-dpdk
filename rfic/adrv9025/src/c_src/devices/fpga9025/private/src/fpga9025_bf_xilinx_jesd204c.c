/**
 * \file fpga9025_bf_xilinx_jesd204c.c Automatically generated file with generator ver 0.0.1.0.
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

#include "./../../private/include/fpga9025_bf_xilinx_jesd204c.h"
#include "./../../private/include/fpga9025_bf_hal.h"
#include "adi_common_error.h"

/**
 * \brief Buffer Fill Level
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cBufferLevelBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             channelId,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cBufferLevelBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cBufferLevelBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x400 + channelId * 128),
                                          &rxBfData[0],
                                          0x3F,
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
 * \brief Buffer Overflow Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cBufferOverflowBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cBufferOverflowBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
                                          &rxBfData[0],
                                          0x400,
                                          0xCA);
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
 * \brief Multi-blocks in Extended Multi-blocks
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCfgMbInEmbBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cCfgMbInEmbBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCfgMbInEmbBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x30),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Multi-blocks in Extended Multi-blocks
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCfgMbInEmbBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCfgMbInEmbBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x30),
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
 * \brief Subclass Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCfgSubclassvBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cCfgSubclassvBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCfgSubclassvBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x34),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Subclass Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCfgSubclassvBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCfgSubclassvBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x34),
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
 * \brief Core is TX
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCoreIsTxBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCoreIsTxBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x4),
                                          &rxBfData[0],
                                          0x10000,
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
 * \brief CRC Error Count
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cCrcErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             channelId,
                                                  uint16_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cCrcErrorCountBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cCrcErrorCountBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x410 + channelId * 128),
                                          &rxBfData[0],
                                          0xFFFF0000,
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
 * \brief Enable Command Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cEnableCmdInterfaceBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x24),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Enable Command Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cEnableCmdInterfaceBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cEnableCmdInterfaceBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x24),
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
 * \brief Enable Data Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cEnableDataInterfaceBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cEnableDataInterfaceBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cEnableDataInterfaceBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x24),
                                           (uint32_t)bfValue,
                                           0x2,
                                           0x1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Enable Data Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cEnableDataInterfaceBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cEnableDataInterfaceBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x24),
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
 * \brief FEC Corrected Error Count
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cFecCorrectedErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                           uint8_t                             channelId,
                                                           uint16_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cFecCorrectedErrorCountBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cFecCorrectedErrorCountBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x414 + channelId * 128),
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

/**
 * \brief FEC Uncorrected Error Count
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cFecUncorrectedErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                             uint8_t                             channelId,
                                                             uint16_t*                           bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cFecUncorrectedErrorCountBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cFecUncorrectedErrorCountBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x414 + channelId * 128),
                                          &rxBfData[0],
                                          0xFFFF0000,
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
 * \brief Interrupt Status Block Sync Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqBlockSyncErrorBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqBlockSyncErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x40,
                                          0xC6);
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
 * \brief Interrupt Status CRC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqCrcErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqCrcErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x100,
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
 * \brief Interrupt Enable Block Sync Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x40,
                                           0x6);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable Block Sync Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnBlockSyncErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x40,
                                          0xC6);
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
 * \brief Interrupt Enable CRC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnCrcErrorBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnCrcErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnCrcErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x100,
                                           0x8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable CRC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnCrcErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnCrcErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x100,
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
 * \brief Interrupt Enable FEC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnFecErrorBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnFecErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnFecErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x200,
                                           0x9);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable FEC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnFecErrorBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnFecErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x200,
                                          0xC9);
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
 * \brief Global Interrupt Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnGlobalBfSet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnGlobalBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnGlobalBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Global Interrupt Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnGlobalBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnGlobalBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
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
 * \brief Interrupt Enable Loss of Multi-block Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnLossMbLockBfSet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossMbLockBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossMbLockBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x20,
                                           0x5);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable Loss of Multi-block Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnLossMbLockBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossMbLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x20,
                                          0xC5);
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
 * \brief Interrupt Enable Loss of 64b66b Sync Header Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfSet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                            uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x10,
                                           0x4);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable Loss of 64b66b Sync Header Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                            fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                            uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnLossSyncHeaderLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x10,
                                          0xC4);
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
 * \brief Interrupt Enable Multi-block Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnMbErrorBfSet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnMbErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnMbErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x80,
                                           0x7);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable Multi-block Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnMbErrorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnMbErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x80,
                                          0xC7);
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
 * \brief Interrupt Enable Overflow Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnOverflowErrorBfSet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnOverflowErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnOverflowErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x400,
                                           0xA);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable Overflow Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnOverflowErrorBfGet(adi_fpga9025_Device_t*              device,
                                                       fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                       uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnOverflowErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x400,
                                          0xCA);
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
 * \brief Interrupt Enable SYSREF Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnSysrefErrorBfSet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefErrorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefErrorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x4,
                                           0x2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable SYSREF Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
                                          &rxBfData[0],
                                          0x4,
                                          0xC2);
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
 * \brief Interrupt Enable SYSREF Received
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfSet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x64),
                                           (uint32_t)bfValue,
                                           0x2,
                                           0x1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Interrupt Enable SYSREF Received
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqEnSysrefReceivedBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x64),
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
 * \brief Interrupt Status FEC Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqFecErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqFecErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x200,
                                          0xC9);
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
 * \brief Interrupt Status Loss of Multi-block Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqLossMbLockBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqLossMbLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x20,
                                          0xC5);
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
 * \brief Interrupt Status Loss of 64b66b Sync Header Lock
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqLossSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                          fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                          uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqLossSyncHeaderLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x10,
                                          0xC4);
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
 * \brief Interrupt Status Multi-block Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqMbErrorBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqMbErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x80,
                                          0xC7);
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
 * \brief Interrupt Status Overflow Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqOverflowErrorBfGet(adi_fpga9025_Device_t*              device,
                                                     fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                     uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqOverflowErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x400,
                                          0xCA);
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
 * \brief Interrupt Pending
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqPendingBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqPendingBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
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
 * \brief Interrupt Status SYSREF Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqSysrefErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
                                          &rxBfData[0],
                                          0x4,
                                          0xC2);
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
 * \brief Interrupt Status SYSREF Received
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cIrqSysrefReceivedBfGet(adi_fpga9025_Device_t*              device,
                                                      fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                      uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cIrqSysrefReceivedBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x68),
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
 * \brief Lane Indicator 64b66b Sync Header Aligned
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cLane64b66bAlignBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cLane64b66bAlignBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x54),
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
 * \brief Lane Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cLaneEnableBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cLaneEnableBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cLaneEnableBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x40),
                                           (uint32_t)bfValue,
                                           0xFF,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Lane Enable
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cLaneEnableBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cLaneEnableBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x40),
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
 * \brief Lane Indicator Multi-block Aligned
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cLaneMbAlignBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cLaneMbAlignBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x54),
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
 * \brief Multi-block Lock Status
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cMbLockBfGet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cMbLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
                                          &rxBfData[0],
                                          0x20,
                                          0xC5);
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
 * \brief Meta Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cMetaModeBfSet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t                             bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 3U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxJesd204cMetaModeBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cMetaModeBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x38),
                                           (uint32_t)bfValue,
                                           0x3,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Meta Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cMetaModeBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cMetaModeBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x38),
                                          &rxBfData[0],
                                          0x3,
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
 * \brief Multiblock Alignment Error Count
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cMulitblockAlignmentErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                                  uint8_t                             channelId,
                                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cMulitblockAlignmentErrorCountBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cMulitblockAlignmentErrorCountBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x410 + channelId * 128),
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
 * \brief Number of Lanes in Core
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cNumberOfLanesInCoreBfGet(adi_fpga9025_Device_t*              device,
                                                        fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                        uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cNumberOfLanesInCoreBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x4),
                                          &rxBfData[0],
                                          0xF,
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
 * \brief Reset, Fixed
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cResetFixedBfSet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cResetFixedBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cResetFixedBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x20),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Reset, Fixed
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cResetFixedBfGet(adi_fpga9025_Device_t*              device,
                                               fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                               uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cResetFixedBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x20),
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
 * \brief RX Buffer Delay
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cRxBufferDelayBfSet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t                             bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 63U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxJesd204cRxBufferDelayBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cRxBufferDelayBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x44),
                                           (uint32_t)bfValue,
                                           0x3F,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief RX Buffer Delay
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cRxBufferDelayBfGet(adi_fpga9025_Device_t*              device,
                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cRxBufferDelayBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x44),
                                          &rxBfData[0],
                                          0x3F,
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
 * \brief Multi-block Lock Threshold
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cRxMbThBfSet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t                             bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 7U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxJesd204cRxMbThBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cRxMbThBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x4C),
                                           (uint32_t)bfValue,
                                           0x7,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Multi-block Lock Threshold
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cRxMbThBfGet(adi_fpga9025_Device_t*              device,
                                           fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                           uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cRxMbThBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x4C),
                                          &rxBfData[0],
                                          0x7,
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
 * \brief Sync Header Alignment Error Count
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param channelId Channel ID to be configured.
 *  Parameter is of type uint8_t
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSyncHeaderAlignmentErrorCountBfGet(adi_fpga9025_Device_t*              device,
                                                                  fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                                  uint8_t                             channelId,
                                                                  uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSyncHeaderAlignmentErrorCountBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

#if FPGA9025_CHANNELID_CHECK > 0
    /* Channel ID check */
    if (
            (channelId != 0x0) &&
            (channelId != 0x1) &&
            (channelId != 0x2) &&
            (channelId != 0x3) &&
            (channelId != 0x4) &&
            (channelId != 0x5) &&
            (channelId != 0x6) &&
            (channelId != 0x7) 
           )
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         channelId, 
                         "Invalid fpga9025_XilinxJesd204cSyncHeaderAlignmentErrorCountBfGet channelId");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x410 + channelId * 128),
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
 * \brief Sync Header Lock Status
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSyncHeaderLockBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSyncHeaderLockBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
                                          &rxBfData[0],
                                          0x10,
                                          0xC4);
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
 * \brief SYSREF Captured
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSysrefCapturedBfGet(adi_fpga9025_Device_t*              device,
                                                   fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                   uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSysrefCapturedBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
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
 * \brief SYSREF Delay
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSysrefDelayBfSet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t                             bfValue)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_BF);

#if FPGA9025_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 15U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9025_XilinxJesd204cSysrefDelayBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSysrefDelayBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x50),
                                           (uint32_t)bfValue,
                                           0xF0000,
                                           0x10);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief SYSREF Delay
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSysrefDelayBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSysrefDelayBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x50),
                                          &rxBfData[0],
                                          0xF0000,
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
 * \brief SYSREF Error
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cSysrefErrorBfGet(adi_fpga9025_Device_t*              device,
                                                fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cSysrefErrorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x60),
                                          &rxBfData[0],
                                          0x4,
                                          0xC2);
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
 * \brief Test Mode Select
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cTestModeBfSet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t                             bfValue)
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
                         "Invalid fpga9025_XilinxJesd204cTestModeBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cTestModeBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x48),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Test Mode Select
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cTestModeBfGet(adi_fpga9025_Device_t*              device,
                                             fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                             uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cTestModeBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x48),
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
 * \brief Version Major
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cVersionMajorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cVersionMajorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x0),
                                          &rxBfData[0],
                                          0xFF000000,
                                          0xD8);
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
 * \brief Version Minor
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cVersionMinorBfGet(adi_fpga9025_Device_t*              device,
                                                 fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                 uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cVersionMinorBfGet Address");
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
 * \brief Revision
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfXilinxJesd204cChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_XilinxJesd204cVersionRevisionBfGet(adi_fpga9025_Device_t*              device,
                                                    fpga9025_BfXilinxJesd204cChanAddr_e baseAddr,
                                                    uint8_t*                            bfValue)
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
    if ((baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_1) &&
            (baseAddr != FPGA9025_BF_JESD204C_DEFRAMER_2) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_0) &&
            (baseAddr != FPGA9025_BF_JESD204C_FRAMER_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_XilinxJesd204cVersionRevisionBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x0),
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

/*  EOF: fpga9025_bf_xilinx_jesd204c.c */
