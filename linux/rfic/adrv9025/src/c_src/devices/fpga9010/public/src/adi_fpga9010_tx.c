/**
 * \file: adi_fpga9010_tx.c
 *
 * \brief Contains top level tx fpga9010 related functions
 *
 * FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_tx.h"
#include "adi_fpga9010_error.h"
#include "../../private/include/fpga9010_bf_dp_tollgate.h"
#include "../../private/include/fpga9010_bf_dp_tx_dma.h"
#include "../../private/include/fpga9010_bf_dp_capture_control.h"

int32_t adi_fpga9010_TxTollgateSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxTollgateCfg_t *tollGateCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_RX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, tollGateCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, txDataMoverSelMask, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateEdgeLevelBfSet(device, instanceAddress, tollGateCfg->tollGateEdgeOrLvl);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to detection register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTollgateHighRisingLowFallingBfSet(device, instanceAddress, tollGateCfg->tollGateHiRiseOrLoFall);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to polarity register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTollgateTriggerSelectBfSet(device, instanceAddress, (uint32_t)tollGateCfg->tollGateTrigSource);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to selection register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxTollgateGet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e txDataMoverSel, adi_fpga9010_TxTollgateCfg_t *tollGateCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, tollGateCfg);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9010_FRAMER_0:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
        break;
    case ADI_FPGA9010_FRAMER_1:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, txDataMoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }
    
    recoveryAction = fpga9010_DpTollgateEdgeLevelBfGet(device, baseAddress, &tollGateCfg->tollGateEdgeOrLvl);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to detection register");
    ADI_ERROR_RETURN(device->common.error.newAction);
            
    recoveryAction = fpga9010_DpTollgateHighRisingLowFallingBfGet(device, baseAddress, &tollGateCfg->tollGateHiRiseOrLoFall);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to polarity register");
    ADI_ERROR_RETURN(device->common.error.newAction);
            
    recoveryAction = fpga9010_DpTollgateTriggerSelectBfGet(device, baseAddress, (uint32_t *)&tollGateCfg->tollGateTrigSource);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxTollgateResetSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint8_t resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateResetTollgateBfSet(device, instanceAddress, resetVal);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxTollgateResetGet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint8_t *resetVal)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;
    uint8_t resetBitRead = 0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, resetVal);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetVal = 0;

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTollgateResetTollgateBfGet(device, instanceAddress, &resetBitRead);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read from reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            *resetVal |= (resetBitRead & 0x01) << i;
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDmaSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxDmaCfg_t *txDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, txDmaCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* TODO: start address could be changed at runtime by this function, and this length check is not enough to ensure RAM buffers do not overlap */
        if (txDmaCfg->length > TX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "FPGA Tx DMA length too large for RAM buffer area");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTxDmaEnableEnhancedModeBfSet(device, instanceAddress, txDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaEnableSgBfSet(device, instanceAddress, txDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaLengthBfSet(device, instanceAddress, txDmaCfg->length);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaSqFirstDescriptorBfSet(device, instanceAddress, txDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* todo: writing to this seems to be clearing the status register. debug later */
//            recoveryAction = fpga9010_DpTxDmaSgLastDescriptorBfSet(device, instanceAddress, txDmaCfg->sgLastDescriptor);
//            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
//            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaSimpleStartAddrBfSet(device, instanceAddress, txDmaCfg->simpleStartAddr);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaValidDataWidthStreamBfSet(device, instanceAddress, txDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaContinuousBfSet(device, instanceAddress, txDmaCfg->continuous);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write continuous bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9010_TxDmaInit(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxDmaCfg_t *txDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, txDmaCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTxDmaEnableEnhancedModeBfSet(device, instanceAddress, txDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaEnableSgBfSet(device, instanceAddress, txDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaSqFirstDescriptorBfSet(device, instanceAddress, txDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* todo: writing to this seems to be clearing the status register. debug later */
//            recoveryAction = fpga9010_DpTxDmaSgLastDescriptorBfSet(device, instanceAddress, txDmaCfg->sgLastDescriptor);
//            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
//            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaSimpleStartAddrBfSet(device, instanceAddress, txDmaCfg->simpleStartAddr);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9010_DpTxDmaValidDataWidthStreamBfSet(device, instanceAddress, txDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDmaGet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e txDataMoverSel, adi_fpga9010_TxDmaCfg_t *txDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e baseAddress = FPGA9010_BF_DP_DMA_TX_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, txDmaCfg);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9010_FRAMER_0:
        baseAddress = FPGA9010_BF_DP_DMA_TX_0;
        break;
    case ADI_FPGA9010_FRAMER_1:
        baseAddress = FPGA9010_BF_DP_DMA_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, txDataMoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9010_DpTxDmaActiveBfGet(device, baseAddress, &txDmaCfg->active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read active bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaCompleteBfGet(device, baseAddress, &txDmaCfg->complete);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read complete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaEnableEnhancedModeBfGet(device, baseAddress, &txDmaCfg->enableEnhancedMode);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read enableEnhancedMode bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaEnableSgBfGet(device, baseAddress, &txDmaCfg->enableSg);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read enableSg bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaHaltCompleteBfGet(device, baseAddress, &txDmaCfg->haltComplete);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read haltComplete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaLengthBfGet(device, baseAddress, &txDmaCfg->length);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read length bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaUnderflowBfGet(device, baseAddress, &txDmaCfg->underflow);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read underflow bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaRunStopBfGet(device, baseAddress, &txDmaCfg->runStop);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaContinuousBfGet(device, baseAddress, &txDmaCfg->continuous);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read continuous bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaSqFirstDescriptorBfGet(device, baseAddress, &txDmaCfg->sgFirstDescriptor);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read sgFirstDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaSgLastDescriptorBfGet(device, baseAddress, &txDmaCfg->sgLastDescriptor);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read sgLastDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaSimpleStartAddrBfGet(device, baseAddress, &txDmaCfg->simpleStartAddr);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read simpleStartAddr bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpTxDmaValidDataWidthStreamBfGet(device, baseAddress, &txDmaCfg->validDataWidthStream);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read validDataWidthStream bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxModeSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxDatamoverMode_e txMode)
{
    UNUSED_PARA(txDataMoverSelMask);
    UNUSED_PARA(txMode);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);


#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxModeGet(adi_fpga9010_Device_t *device, uint8_t *transmitModeMask)
{
    UNUSED_PARA(transmitModeMask);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);


#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxTollgateTriggerSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxTollgateTrigSources_e  triggerSelect)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            adi_fpga9010_TxTollgateResetSet(device, txDataMoverSelMask, 1);
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            fpga9010_DpTollgateTriggerSelectBfSet(device, instanceAddress, (uint32_t)triggerSelect);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to triggerSelect bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
            
            adi_fpga9010_TxTollgateResetSet(device, txDataMoverSelMask, 0);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxTollgateTriggerGet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e txDataMoverSel, adi_fpga9010_TxTollgateTrigSources_e  *triggerSelect)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTollgateChanAddr_e baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common, triggerSelect);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9010_FRAMER_0:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_0;
        break;
    case ADI_FPGA9010_FRAMER_1:
        baseAddress = FPGA9010_BF_DP_TOLLGATE_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, txDataMoverSel, "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9010_DpTollgateTriggerSelectBfGet(device, baseAddress, (uint32_t *)triggerSelect);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not read triggerSelect bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDatamoverEnableSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask)
{
    UNUSED_PARA(txDataMoverSelMask);
    //TODO: implement this using adi_fpga_txChannelSel_e
    //TxChannelSel_t will refer to all modules within a channel
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxDatamoverEnableGet(adi_fpga9010_Device_t *device, uint32_t *txDataMoverSelMask)
{
    UNUSED_PARA(txDataMoverSelMask);
    //TODO: implement this using adi_fpga_txChannelSel_e
    //TxChannelSel_t will refer to all modules within a channel
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxDataChainConfigure(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, adi_fpga9010_TxTollgateTrigSources_e  triggerSelect, adi_fpga9010_TxDmaCfg_t *txDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    /* reset capture control */
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* set trigger */
    adi_fpga9010_TxTollgateTriggerSet(device, txDataMoverSelMask, triggerSelect);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /*reset dmas */
    adi_fpga9010_TxDmaResetSet(device, txDataMoverSelMask, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* configure dmas */
    adi_fpga9010_TxDmaSet(device, txDataMoverSelMask, txDmaCfg);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* set run_stop bit */
    adi_fpga9010_TxDmaRunStopSet(device, txDataMoverSelMask, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* pass token to start dma arbitration */
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_DpCaptureControlPassTokenBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control PassToken bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDataChainReset(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint8_t active = 0;
    uint8_t haltComplete = 0;
	uint8_t i = 0;
	static const uint8_t TX_DATA_CHAIN_RESET_MAX_COUNT = 5;
    
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    /* reset  */
    recoveryAction = fpga9010_DpCaptureControlDatapathActiveBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Clear DMA 0 */
    haltComplete = 0;
    recoveryAction = fpga9010_DpTxDmaActiveBfGet(device, FPGA9010_BF_DP_DMA_TX_0, &active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_TxDmaRunStopSet(device, ADI_FPGA9010_FRAMER_0, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (active == 1)
    {
		haltComplete = 0;
		for (i = 0; i < TX_DATA_CHAIN_RESET_MAX_COUNT; i++)
        {
            recoveryAction = fpga9010_DpTxDmaHaltCompleteBfGet(device, FPGA9010_BF_DP_DMA_TX_0, &haltComplete);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
			if (haltComplete != 0)
			{
				break;
			}
        }

		if (i == TX_DATA_CHAIN_RESET_MAX_COUNT)
		{
			ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "TX0 DMA Halt failed.");
			ADI_ERROR_RETURN(device->common.error.newAction);
		}
    }
    
    adi_fpga9010_TxDmaResetSet(device, ADI_FPGA9010_FRAMER_0, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    /* Clear DMA 1 */
    haltComplete = 0;
	active = 0;
    recoveryAction = fpga9010_DpTxDmaActiveBfGet(device, FPGA9010_BF_DP_DMA_TX_1, &active);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_TxDmaRunStopSet(device, ADI_FPGA9010_FRAMER_1, 0);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    if (active == 1)
    {
		for (i = 0; i < TX_DATA_CHAIN_RESET_MAX_COUNT; i++)
        {
            recoveryAction = fpga9010_DpTxDmaHaltCompleteBfGet(device, FPGA9010_BF_DP_DMA_TX_1, &haltComplete);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Error setting Capture Control Reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
			if (haltComplete != 0)
			{
				break;
			}
        }

		if (i == TX_DATA_CHAIN_RESET_MAX_COUNT)
		{
			ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "TX1 DMA Halt failed.");
			ADI_ERROR_RETURN(device->common.error.newAction);
		}
    }
    
    adi_fpga9010_TxDmaResetSet(device, ADI_FPGA9010_FRAMER_1, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    adi_fpga9010_TxTollgateResetSet(device, ADI_FPGA9010_FRAMER_ALL, 1);
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    return recoveryAction;
}

int32_t adi_fpga9010_TxDataStart(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9010_DpCaptureControlDatapathActiveBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDataStop(adi_fpga9010_Device_t *device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9010_DpTxDmaRunStopBfSet(device, FPGA9010_BF_DP_DMA_TX_0, 0);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9010_DpCaptureControlResetBfSet(device, FPGA9010_BF_DP_CAPTURE_CONTROL_TX, 1);
    ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDataSet(adi_fpga9010_Device_t *device, adi_fpga9010_FramerSel_e txDataMoverSel, int32_t data[], uint32_t dataSize)
{
    UNUSED_PARA(txDataMoverSel);
    UNUSED_PARA(data);
    UNUSED_PARA(dataSize);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxDmaResetSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint8_t reset)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTxDmaResetBfSet(device, instanceAddress, reset);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, NULL, "Could not write reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxDmaRunStopSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint8_t runStop)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTxDmaRunStopBfSet(device, instanceAddress, runStop);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, NULL, "Could not write runStop bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_TxSamplesSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint32_t numSamples)
{
    UNUSED_PARA(txDataMoverSelMask);
    UNUSED_PARA(numSamples);
     //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9010_TxDmaLengthSet(adi_fpga9010_Device_t *device, uint32_t txDataMoverSelMask, uint32_t numBytes)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9010_BfDpTxDmaChanAddr_e instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
    uint32_t i = 0;
    adi_fpga9010_FramerSel_e dataMoverSel = ADI_FPGA9010_FRAMER_0;

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, NULL, "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9010_NUM_OF_FRAMERS; i++)
    {
        dataMoverSel = (adi_fpga9010_FramerSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9010_FRAMER_0:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9010_FRAMER_1:
            instanceAddress = FPGA9010_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (numBytes > TX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "FPGA Tx DMA length too large for RAM buffer area");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
        
        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9010_DpTxDmaLengthBfSet(device, instanceAddress, numBytes);
            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9010_ERR_API_FAIL, recoveryAction, NULL, "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return (device->common.error.newAction);
}