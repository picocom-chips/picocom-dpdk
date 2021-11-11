/**
 * \file: adi_fpga9025_tx.c
 *
 * \brief Contains top level tx fpga9025 related functions
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_tx.h"
#include "adi_fpga9025_error.h"
#include "../../private/include/fpga9025_bf_dp_tollgate.h"
#include "../../private/include/fpga9025_bf_dp_tx_dma.h"
#include "../../private/include/fpga9025_bf_dp_capture_control.h"

int32_t adi_fpga9025_TxTollgateSet(adi_fpga9025_Device_t*        device,
                                   uint32_t                      txDataMoverSelMask,
                                   adi_fpga9025_TxTollgateCfg_t* tollGateCfg)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_TxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        tollGateCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         txDataMoverSelMask,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateEdgeLevelBfSet(device,
                                                               instanceAddress,
                                                               tollGateCfg->tollGateEdgeOrLvl);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to detection register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateHighRisingLowFallingBfSet(device,
                                                                          instanceAddress,
                                                                          tollGateCfg->tollGateHiRiseOrLoFall);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to polarity register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateTriggerSelectBfSet(device,
                                                                   instanceAddress,
                                                                   (uint32_t)tollGateCfg->tollGateTrigSource);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to selection register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxTollgateGet(adi_fpga9025_Device_t*        device,
                                   adi_fpga9025_TxDatamoverSel_e txDataMoverSel,
                                   adi_fpga9025_TxTollgateCfg_t* tollGateCfg)
{
    int32_t                         recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e baseAddress    = FPGA9025_BF_DP_TOLLGATE_TX_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        tollGateCfg);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9025_TX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
        break;
    case ADI_FPGA9025_TX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         txDataMoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpTollgateEdgeLevelBfGet(device,
                                                       baseAddress,
                                                       &tollGateCfg->tollGateEdgeOrLvl);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to detection register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTollgateHighRisingLowFallingBfGet(device,
                                                                  baseAddress,
                                                                  &tollGateCfg->tollGateHiRiseOrLoFall);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to polarity register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTollgateTriggerSelectBfGet(device,
                                                           baseAddress,
                                                           (uint32_t *)&tollGateCfg->tollGateTrigSource);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to selection register");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxTollgateResetSet(adi_fpga9025_Device_t* device,
                                        uint32_t               txDataMoverSelMask,
                                        uint8_t                resetVal)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_TxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateResetTollgateBfSet(device,
                                                                   instanceAddress,
                                                                   resetVal);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxTollgateResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               txDataMoverSelMask,
                                        uint8_t*               resetVal)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_TxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;
    uint8_t                         resetBitRead    = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        resetVal);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    *resetVal = 0;

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTollgateResetTollgateBfGet(device,
                                                                   instanceAddress,
                                                                   &resetBitRead);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not read from reset register");
            ADI_ERROR_RETURN(device->common.error.newAction);

            *resetVal |= (resetBitRead & 0x01) << i;
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaSet(adi_fpga9025_Device_t*   device,
                              uint32_t                 txDataMoverSelMask,
                              adi_fpga9025_TxDmaCfg_t* txDmaCfg)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;
    uint32_t                      tempWorkAround  = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        txDmaCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        /* TODO: start address could be changed at runtime by this function, and this length check is not enough to ensure RAM buffers do not overlap */
        if (txDmaCfg->length > ADI_FPGA9025_TX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "FPGA Tx DMA length too large for RAM buffer area");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTxDmaEnableEnhancedModeBfSet(device,
                                                                     instanceAddress,
                                                                     txDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaEnableSgBfSet(device,
                                                           instanceAddress,
                                                           txDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaLengthBfSet(device,
                                                         instanceAddress,
                                                         txDmaCfg->length);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSqFirstDescriptorBfSet(device,
                                                                    instanceAddress,
                                                                    txDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* todo: writing to this seems to be clearing the status register. debug later */
            //            recoveryAction = fpga9025_DpTxDmaSgLastDescriptorBfSet(device, instanceAddress, txDmaCfg->sgLastDescriptor);
            //            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9025_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
            //            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                                      instanceAddress + 0x2C,
                                                      &tempWorkAround);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             recoveryAction,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             spicrAddress,
                             "Error");
            ADI_ERROR_RETURN(device->common.error.newAction);
            tempWorkAround &= (0xFFFF0000);
            tempWorkAround |= (0x4000);
            recoveryAction = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                                       instanceAddress + 0x2C,
                                                       tempWorkAround);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             recoveryAction,
                             ADI_COMMON_ACT_ERR_CHECK_PARAM,
                             spissrAddress,
                             "Error selecting all Tokelau devices");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSimpleStartAddrBfSet(device,
                                                                  instanceAddress,
                                                                  (txDmaCfg->simpleStartAddr & 0x00000000FFFFFFFF));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSimpleStartAddrMswBfSet(device,
                                                                     instanceAddress,
                                                                     (txDmaCfg->simpleStartAddr >> 32));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaValidDataWidthStreamBfSet(device,
                                                                       instanceAddress,
                                                                       txDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaContinuousBfSet(device,
                                                             instanceAddress,
                                                             txDmaCfg->continuous);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write continuous bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaInit(adi_fpga9025_Device_t*   device,
                               uint32_t                 txDataMoverSelMask,
                               adi_fpga9025_TxDmaCfg_t* txDmaCfg)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        txDmaCfg);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTxDmaEnableEnhancedModeBfSet(device,
                                                                     instanceAddress,
                                                                     txDmaCfg->enableEnhancedMode);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableEnhancedMode bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaEnableSgBfSet(device,
                                                           instanceAddress,
                                                           txDmaCfg->enableSg);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write enableSg bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSqFirstDescriptorBfSet(device,
                                                                    instanceAddress,
                                                                    txDmaCfg->sgFirstDescriptor);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write sgFirstDescriptor bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            /* todo: writing to this seems to be clearing the status register. debug later */
            //            recoveryAction = fpga9025_DpTxDmaSgLastDescriptorBfSet(device, instanceAddress, txDmaCfg->sgLastDescriptor);
            //            ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_FPGA9025_ERR_REGISTER_IO_FAIL, recoveryAction, NULL, "Could not write sgLastDescriptor bitfield");
            //            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSimpleStartAddrBfSet(device,
                                                                  instanceAddress,
                                                                  (txDmaCfg->simpleStartAddr & 0x00000000FFFFFFFF));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaSimpleStartAddrMswBfSet(device,
                                                                     instanceAddress,
                                                                     (txDmaCfg->simpleStartAddr >> 32));
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write simpleStartAddr bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTxDmaValidDataWidthStreamBfSet(device,
                                                                       instanceAddress,
                                                                       txDmaCfg->validDataWidthStream);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write validDataWidthStream bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaGet(adi_fpga9025_Device_t*        device,
                              adi_fpga9025_TxDatamoverSel_e txDataMoverSel,
                              adi_fpga9025_TxDmaCfg_t*      txDmaCfg)
{
    int32_t                      recoveryAction   = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e baseAddress      = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                     addressReadValue = 0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        txDmaCfg);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9025_TX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_DMA_TX_0;
        break;
    case ADI_FPGA9025_TX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_DMA_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         txDataMoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpTxDmaActiveBfGet(device,
                                                 baseAddress,
                                                 &txDmaCfg->active);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read active bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaCompleteBfGet(device,
                                                   baseAddress,
                                                   &txDmaCfg->complete);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read complete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaEnableEnhancedModeBfGet(device,
                                                             baseAddress,
                                                             &txDmaCfg->enableEnhancedMode);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read enableEnhancedMode bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaEnableSgBfGet(device,
                                                   baseAddress,
                                                   &txDmaCfg->enableSg);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read enableSg bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaHaltCompleteBfGet(device,
                                                       baseAddress,
                                                       &txDmaCfg->haltComplete);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read haltComplete bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaLengthBfGet(device,
                                                 baseAddress,
                                                 &txDmaCfg->length);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read length bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaUnderflowBfGet(device,
                                                    baseAddress,
                                                    &txDmaCfg->underflow);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read underflow bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaRunStopBfGet(device,
                                                  baseAddress,
                                                  &txDmaCfg->runStop);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaContinuousBfGet(device,
                                                     baseAddress,
                                                     &txDmaCfg->continuous);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read continuous bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaSqFirstDescriptorBfGet(device,
                                                            baseAddress,
                                                            &txDmaCfg->sgFirstDescriptor);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read sgFirstDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaSgLastDescriptorBfGet(device,
                                                           baseAddress,
                                                           &txDmaCfg->sgLastDescriptor);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read sgLastDescriptor bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpTxDmaSimpleStartAddrBfGet(device,
                                                          baseAddress,
                                                          &addressReadValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read simpleStartAddr bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    txDmaCfg->simpleStartAddr = addressReadValue;

    recoveryAction = fpga9025_DpTxDmaSimpleStartAddrMswBfGet(device,
                                                             baseAddress,
                                                             &addressReadValue);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read simpleStartAddrMsw bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    txDmaCfg->simpleStartAddr |= (uint64_t)addressReadValue << 32;

    recoveryAction = fpga9025_DpTxDmaValidDataWidthStreamBfGet(device,
                                                               baseAddress,
                                                               &txDmaCfg->validDataWidthStream);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read validDataWidthStream bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxModeSet(adi_fpga9025_Device_t*         device,
                               uint32_t                       txDataMoverSelMask,
                               adi_fpga9025_TxDatamoverMode_e txMode)
{
    UNUSED_PARA(txDataMoverSelMask);
    UNUSED_PARA(txMode);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_TxModeGet(adi_fpga9025_Device_t* device,
                               uint8_t*               transmitModeMask)
{
    UNUSED_PARA(transmitModeMask);
    //TODO: implement this
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_TxTollgateTriggerSet(adi_fpga9025_Device_t*               device,
                                          uint32_t                             txDataMoverSelMask,
                                          adi_fpga9025_TxTollgateTrigSources_e triggerSelect)
{
    int32_t                         recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
    uint32_t                        i               = 0;
    adi_fpga9025_TxDatamoverSel_e   dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = adi_fpga9025_TxTollgateResetSet(device,
                                                             txDataMoverSelMask,
                                                             1);
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = fpga9025_DpTollgateTriggerSelectBfSet(device,
                                                                   instanceAddress,
                                                                   (uint32_t)triggerSelect);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write to triggerSelect bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);

            recoveryAction = adi_fpga9025_TxTollgateResetSet(device,
                                                             txDataMoverSelMask,
                                                             0);
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxTollgateTriggerGet(adi_fpga9025_Device_t*                device,
                                          adi_fpga9025_TxDatamoverSel_e         txDataMoverSel,
                                          adi_fpga9025_TxTollgateTrigSources_e* triggerSelect)
{
    int32_t                         recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTollgateChanAddr_e baseAddress    = FPGA9025_BF_DP_TOLLGATE_TX_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    ADI_NULL_PTR_RETURN(&device->common,
                        triggerSelect);

    switch (txDataMoverSel)
    {
    case ADI_FPGA9025_TX_DATAMOVER_0:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_TX_0;
        break;
    case ADI_FPGA9025_TX_DATAMOVER_1:
        baseAddress = FPGA9025_BF_DP_TOLLGATE_TX_1;
        break;
    default:
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         txDataMoverSel,
                         "Invalid datamover selected");
        ADI_ERROR_RETURN(device->common.error.newAction);
        break;
    }

    recoveryAction = fpga9025_DpTollgateTriggerSelectBfGet(device,
                                                           baseAddress,
                                                           (uint32_t *)triggerSelect);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not read triggerSelect bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxDatamoverEnableSet(adi_fpga9025_Device_t* device,
                                          uint32_t               txDataMoverSelMask)
{
    UNUSED_PARA(txDataMoverSelMask);
    //TODO: implement this using adi_fpga_txChannelSel_e
    //TxChannelSel_t will refer to all modules within a channel
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_TxDatamoverEnableGet(adi_fpga9025_Device_t* device,
                                          uint32_t*              txDataMoverSelMask)
{
    UNUSED_PARA(txDataMoverSelMask);
    //TODO: implement this using adi_fpga_txChannelSel_e
    //TxChannelSel_t will refer to all modules within a channel
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif
    return recoveryAction;
}

int32_t adi_fpga9025_TxDataChainConfigure(adi_fpga9025_Device_t*               device,
                                          uint32_t                             txDataMoverSelMask,
                                          adi_fpga9025_TxTollgateTrigSources_e triggerSelect,
                                          adi_fpga9025_TxDmaCfg_t*             txDmaCfg)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* reset capture control */
    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* set trigger */
    recoveryAction = adi_fpga9025_TxTollgateTriggerSet(device,
                                                       txDataMoverSelMask,
                                                       triggerSelect);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /*reset dmas */
    recoveryAction = adi_fpga9025_TxDmaResetSet(device,
                                                txDataMoverSelMask,
                                                1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* configure dmas */
    recoveryAction = adi_fpga9025_TxDmaSet(device,
                                           txDataMoverSelMask,
                                           txDmaCfg);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* set run_stop bit */
    recoveryAction = adi_fpga9025_TxDmaRunStopSet(device,
                                                  txDataMoverSelMask,
                                                  1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* pass token to start dma arbitration */
    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_DpCaptureControlPassTokenBfSet(device,
                                                             FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                             1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control PassToken bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxDataChainReset(adi_fpga9025_Device_t* device)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    uint8_t                       active          = 0;
    uint8_t                       haltComplete    = 0;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* reset  */
    recoveryAction = fpga9025_DpCaptureControlDatapathActiveBfSet(device,
                                                                  FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                                  0);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);
    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Error setting Capture Control Reset bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));
        active       = 0;
        haltComplete = 0;

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        recoveryAction = fpga9025_DpTxDmaActiveBfGet(device,
                                                     instanceAddress,
                                                     &active);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Error setting Capture Control Reset bitfield");
        ADI_ERROR_RETURN(device->common.error.newAction);

        recoveryAction = adi_fpga9025_TxDmaRunStopSet(device,
                                                      dataMoverSel,
                                                      0);
        ADI_ERROR_RETURN(device->common.error.newAction);

        if (active == 1)
        {
            while (haltComplete == 0)
            {
                recoveryAction = fpga9025_DpTxDmaHaltCompleteBfGet(device,
                                                                   instanceAddress,
                                                                   &haltComplete);
                ADI_ERROR_REPORT(&device->common,
                                 ADI_COMMON_ERRSRC_API,
                                 ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                                 recoveryAction,
                                 NULL,
                                 "Error setting Capture Control Reset bitfield");
                ADI_ERROR_RETURN(device->common.error.newAction);
            }
        }

        recoveryAction = adi_fpga9025_TxDmaResetSet(device,
                                                    dataMoverSel,
                                                    1);
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    recoveryAction = adi_fpga9025_TxTollgateResetSet(device,
                                                     ADI_FPGA9025_TX_DATAMOVER_ALL,
                                                     1);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxDataStart(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9025_DpCaptureControlDatapathActiveBfSet(device,
                                                                  FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                                  1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxDataStop(adi_fpga9025_Device_t* device)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    ADI_NULL_DEVICE_PTR_RETURN(device);

    recoveryAction = fpga9025_DpTxDmaRunStopBfSet(device,
                                                  FPGA9025_BF_DP_DMA_TX_0,
                                                  0);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write runStop bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    recoveryAction = fpga9025_DpCaptureControlResetBfSet(device,
                                                         FPGA9025_BF_DP_CAPTURE_CONTROL_TX,
                                                         1);
    ADI_ERROR_REPORT(&device->common,
                     ADI_COMMON_ERRSRC_API,
                     ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                     recoveryAction,
                     NULL,
                     "Could not write to DatapathActive bitfield");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaResetSet(adi_fpga9025_Device_t* device,
                                   uint32_t               txDataMoverSelMask,
                                   uint8_t                reset)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTxDmaResetBfSet(device,
                                                        instanceAddress,
                                                        reset);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write reset bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaRunStopSet(adi_fpga9025_Device_t* device,
                                     uint32_t               txDataMoverSelMask,
                                     uint8_t                runStop)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTxDmaRunStopBfSet(device,
                                                          instanceAddress,
                                                          runStop);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write runStop bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}

int32_t adi_fpga9025_TxDmaLengthSet(adi_fpga9025_Device_t* device,
                                    uint32_t               txDataMoverSelMask,
                                    uint32_t               numBytes)
{
    int32_t                       recoveryAction  = ADI_COMMON_ACT_NO_ACTION;
    fpga9025_BfDpTxDmaChanAddr_e  instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
    uint32_t                      i               = 0;
    adi_fpga9025_TxDatamoverSel_e dataMoverSel    = ADI_FPGA9025_TX_DATAMOVER_0;

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    /* Range checks */
    ADI_NULL_DEVICE_PTR_RETURN(device);

    if (txDataMoverSelMask < 1 || txDataMoverSelMask > 3)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         NULL,
                         "An invalid tx datamover selected.");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    for (i = 0; i < ADI_FPGA9025_NUM_OF_TX_DATAMOVERS; i++)
    {
        dataMoverSel = (adi_fpga9025_TxDatamoverSel_e)((uint8_t)(1 << i));

        switch (dataMoverSel)
        {
        case ADI_FPGA9025_TX_DATAMOVER_0:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_0;
            break;
        case ADI_FPGA9025_TX_DATAMOVER_1:
            instanceAddress = FPGA9025_BF_DP_DMA_TX_1;
            break;
        default:
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "Fatal API error.");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (numBytes > ADI_FPGA9025_TX_DMA_SIZE)
        {
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             ADI_COMMON_ACT_ERR_RESET_FULL,
                             NULL,
                             "FPGA Tx DMA length too large for RAM buffer area");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }

        if (((uint32_t)dataMoverSel & txDataMoverSelMask) > 0)
        {
            recoveryAction = fpga9025_DpTxDmaLengthBfSet(device,
                                                         instanceAddress,
                                                         numBytes);
            ADI_ERROR_REPORT(&device->common,
                             ADI_COMMON_ERRSRC_API,
                             ADI_FPGA9025_ERR_API_FAIL,
                             recoveryAction,
                             NULL,
                             "Could not write length bitfield");
            ADI_ERROR_RETURN(device->common.error.newAction);
        }
    }

    return recoveryAction;
}
