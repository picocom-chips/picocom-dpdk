/**
 * \file fpga9025_bf_dp_tx_dma.c Automatically generated file with generator ver 0.0.1.0.
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

#include "./../../private/include/fpga9025_bf_dp_tx_dma.h"
#include "./../../private/include/fpga9025_bf_hal.h"
#include "adi_common_error.h"

/**
 * \brief Transfer Active
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaActiveBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaActiveBfGet Address");
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
 * \brief Transfer Complete
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaCompleteBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaCompleteBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0xC),
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
 * \brief Continuous Operation
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaContinuousBfSet(adi_fpga9025_Device_t*       device,
                                        fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                        uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaContinuousBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaContinuousBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x8),
                                           (uint32_t)bfValue,
                                           0x2,
                                           0x1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Continuous Operation
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaContinuousBfGet(adi_fpga9025_Device_t*       device,
                                        fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                        uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaContinuousBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x8),
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
 * \brief Enable Enhanced Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaEnableEnhancedModeBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaEnableEnhancedModeBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaEnableEnhancedModeBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x8),
                                           (uint32_t)bfValue,
                                           0x8,
                                           0x3);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Enable Enhanced Mode
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaEnableEnhancedModeBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaEnableEnhancedModeBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x8),
                                          &rxBfData[0],
                                          0x8,
                                          0xC3);
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
 * \brief Enable Scatter Gather Transfer
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaEnableSgBfSet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaEnableSgBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaEnableSgBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x8),
                                           (uint32_t)bfValue,
                                           0x4,
                                           0x2);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Enable Scatter Gather Transfer
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaEnableSgBfGet(adi_fpga9025_Device_t*       device,
                                      fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                      uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaEnableSgBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x8),
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
 * \brief Halt Complete
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaHaltCompleteBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaHaltCompleteBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0xC),
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
 * \brief Transfer Length
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaLengthBfSet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint32_t                     bfValue)
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
                         "Invalid fpga9025_DpTxDmaLengthBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaLengthBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x18),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Transfer Length
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaLengthBfGet(adi_fpga9025_Device_t*       device,
                                    fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                    uint32_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaLengthBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x18),
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
 * \brief Reset
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaResetBfSet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                   uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaResetBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaResetBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x4),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Reset
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaResetBfGet(adi_fpga9025_Device_t*       device,
                                   fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                   uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaResetBfGet Address");
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
 * \brief Run Stop
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaRunStopBfSet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                     uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaRunStopBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaRunStopBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x8),
                                           (uint32_t)bfValue,
                                           0x1,
                                           0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Run Stop
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaRunStopBfGet(adi_fpga9025_Device_t*       device,
                                     fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                     uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaRunStopBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x8),
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
 * \brief Scatter-Gather Last Descriptor
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSgLastDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                              uint32_t                     bfValue)
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
                         "Invalid fpga9025_DpTxDmaSgLastDescriptorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSgLastDescriptorBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    recoveryAction = fpga9025_BfRegisterWrite(device,
                                              (baseAddr + 0x28),
                                              ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Scatter-Gather Last Descriptor
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSgLastDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                              fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                              uint32_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSgLastDescriptorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    recoveryAction = fpga9025_BfRegisterRead(device,
                                             (baseAddr + 0x28),
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
 * \brief Simple Transfer Start Address
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSimpleStartAddrBfSet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                             uint32_t                     bfValue)
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
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrBfSet Address");
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
 * \brief Simple Transfer Start Address
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSimpleStartAddrBfGet(adi_fpga9025_Device_t*       device,
                                             fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                             uint32_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrBfGet Address");
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
 * \brief Simple Transfer Start Address Most Significant Word
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSimpleStartAddrMswBfSet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint32_t                     bfValue)
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
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrMswBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrMswBfSet Address");
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
 * \brief Simple Transfer Start Address Most Significant Word
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSimpleStartAddrMswBfGet(adi_fpga9025_Device_t*       device,
                                                fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                uint32_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSimpleStartAddrMswBfGet Address");
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
 * \brief Scatter-Gather First Descriptor
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSqFirstDescriptorBfSet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                               uint32_t                     bfValue)
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
                         "Invalid fpga9025_DpTxDmaSqFirstDescriptorBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSqFirstDescriptorBfSet Address");
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
 * \brief Scatter-Gather First Descriptor
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaSqFirstDescriptorBfGet(adi_fpga9025_Device_t*       device,
                                               fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                               uint32_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaSqFirstDescriptorBfGet Address");
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
 * \brief Underflow
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaUnderflowBfGet(adi_fpga9025_Device_t*       device,
                                       fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                       uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaUnderflowBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0xC),
                                          &rxBfData[0],
                                          0x8,
                                          0xC3);
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
 * \brief Valid Data Width of Stream Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaValidDataWidthStreamBfSet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                  uint8_t                      bfValue)
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
                         "Invalid fpga9025_DpTxDmaValidDataWidthStreamBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_VALUE_CHECK */

#if FPGA9025_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaValidDataWidthStreamBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    recoveryAction = fpga9025_BfFieldWrite(device,
                                           (baseAddr + 0x8),
                                           (uint32_t)bfValue,
                                           0xF00,
                                           0x8);
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

/**
 * \brief Valid Data Width of Stream Interface
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaValidDataWidthStreamBfGet(adi_fpga9025_Device_t*       device,
                                                  fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                                  uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaValidDataWidthStreamBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9025_BITFIELD_ADDR_CHECK */

    recoveryAction = fpga9025_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    recoveryAction = fpga9025_BfFieldRead(device,
                                          (baseAddr + 0x8),
                                          &rxBfData[0],
                                          0xF00,
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
 * \brief Major Version
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9025 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaVersionMajorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint8_t*                     bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaVersionMajorBfGet Address");
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
 *  Parameter is of type ::fpga9025_BfDpTxDmaChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_COMMON_ACT_ERR_RESET_INTERFACE Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9025_DpTxDmaVersionMinorBfGet(adi_fpga9025_Device_t*       device,
                                          fpga9025_BfDpTxDmaChanAddr_e baseAddr,
                                          uint16_t*                    bfValue)
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
    if ((baseAddr != FPGA9025_BF_DP_DMA_TX_0) &&
            (baseAddr != FPGA9025_BF_DP_DMA_TX_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9025_DpTxDmaVersionMinorBfGet Address");
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

/*  EOF: fpga9025_bf_dp_tx_dma.c */
