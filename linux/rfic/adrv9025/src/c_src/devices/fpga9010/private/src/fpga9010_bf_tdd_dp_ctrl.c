/**
 * \file fpga9010_bf_tdd_dp_ctrl.c Automatically generated file with generator ver 0.0.0.1.
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

#include "./../../private/include/fpga9010_bf_tdd_dp_ctrl.h"
#include "./../../private/include/fpga9010_bf_hal.h"
#include "adi_common_error.h"

/**
 * \brief Enable Bit for the Datapath Control Module
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlEnableBitBfSet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                          uint8_t bfValue)
{
    

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 1U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9010_TddDpCtrlEnableBitBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_VALUE_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlEnableBitBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Field */
    fpga9010_BfFieldWrite(device, (baseAddr + 0x8), (uint32_t)bfValue, 0x1, 0x0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return(device->common.error.newAction);
}

/**
 * \brief Enable Bit for the Datapath Control Module
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlEnableBitBfGet(adi_fpga9010_Device_t *device, 
                                         fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                          uint8_t *bfValue)
{
    
    uint32_t rxBfData[8] = { 0 };
    uint64_t data = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9010_BITFIELD_NULL_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlEnableBitBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    fpga9010_BfFieldRead(device, (baseAddr + 0x8), &rxBfData[0], 0x1, 0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfReadAssembleData(device, &rxBfData[0x0], 0x1, &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t) data;

    return(device->common.error.newAction);
}
/**
 * \brief Start Value for Datapath Control Module
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlStartValueBfSet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                           uint32_t bfValue)
{
    

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_VALUE_CHECK > 0
    /* Range check */
    if ((bfValue < 0) ||
        (bfValue > 4294967295U))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM, 
                         bfValue,
                         "Invalid fpga9010_TddDpCtrlStartValueBfSet parameter");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_VALUE_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlStartValueBfSet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfWriteCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Write to Single Register */
    fpga9010_BfRegisterWrite(device, (baseAddr + 0x4), ((uint32_t)bfValue));
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfWriteCacheFlush(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return(device->common.error.newAction);
}

/**
 * \brief Start Value for Datapath Control Module
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint32_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlStartValueBfGet(adi_fpga9010_Device_t *device, 
                                          fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                           uint32_t *bfValue)
{
    
    uint32_t rxBfData[8] = { 0 };
    uint64_t data = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9010_BITFIELD_NULL_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlStartValueBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read to Single Register */
    fpga9010_BfRegisterRead(device, (baseAddr + 0x4), &rxBfData[0]);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfReadAssembleData(device, &rxBfData[0x0], 0x1, &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint32_t) data;

    return(device->common.error.newAction);
}

/**
 * \brief Major Version
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint8_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlVersionMajorBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                             uint8_t *bfValue)
{
    
    uint32_t rxBfData[8] = { 0 };
    uint64_t data = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9010_BITFIELD_NULL_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlVersionMajorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    fpga9010_BfFieldRead(device, (baseAddr + 0x0), &rxBfData[0], 0xFF0000, 0xD0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfReadAssembleData(device, &rxBfData[0x0], 0x1, &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint8_t) data;

    return(device->common.error.newAction);
}

/**
 * \brief Minor Version
 * 
 * \dep_begin
 * \dep{device->common.devHalInfo}
 * \dep_end
 * 
 * \param device Pointer to the FPGA9010 device data structure.
 * \param baseAddr Base Address of instance to be configured.
 *  Parameter is of type ::fpga9010_BfTddDpCtrlChanAddr_e.
 * \param bfValue Data to be configured. Parameter is of type uint16_t.
 * 
 * \retval ADI_COMMON_ACT_WARN_RESET_LOG Recovery action for log reset.
 * \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check.
 * \retval ADI_FPGA9010_ACT_ERR_RESET_SPI Recovery action for SPI reset required.
 * \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required.
 * 
 */
int32_t fpga9010_TddDpCtrlVersionMinorBfGet(adi_fpga9010_Device_t *device, 
                                            fpga9010_BfTddDpCtrlChanAddr_e baseAddr, 
                                             uint16_t *bfValue)
{
    
    uint32_t rxBfData[8] = { 0 };
    uint64_t data = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_BF);

#if FPGA9010_BITFIELD_NULL_CHECK > 0
    /* NULL check */
    ADI_NULL_PTR_RETURN(&device->common, bfValue);
#endif /* FPGA9010_BITFIELD_NULL_CHECK */

#if FPGA9010_BITFIELD_ADDR_CHECK > 0
    /* Base Address check */
    if ((baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_1) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_0) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_RX_DP_2) &&
            (baseAddr != FPGA9010_BF_TDD_DATAPATH_CONTROL_TX_DP_1))
    {
        ADI_ERROR_REPORT(&device->common, 
                         ADI_COMMON_ERRSRC_DEVICEBF, 
                         ADI_COMMON_ERR_INV_PARAM, 
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         baseAddr, 
                         "Invalid fpga9010_TddDpCtrlVersionMinorBfGet Address");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
#endif /* FPGA9010_BITFIELD_ADDR_CHECK */ 

    fpga9010_BfReadCacheInit(device);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* Read Field */
    fpga9010_BfFieldRead(device, (baseAddr + 0x0), &rxBfData[0], 0xFFFF, 0xC0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    fpga9010_BfReadAssembleData(device, &rxBfData[0x0], 0x1, &data);
    ADI_ERROR_RETURN(device->common.error.newAction);

    *bfValue = (uint16_t) data;

    return(device->common.error.newAction);
}

/*  EOF: fpga9010_bf_tdd_dp_ctrl.c */

