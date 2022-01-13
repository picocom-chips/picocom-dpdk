/**
 * \file: adi_fpga9025_tx.h
 *
 * \brief Contains top level tx fpga9025 related prototypes
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_TX_H_
#define _ADI_FPGA9025_TX_H_

#include "adi_fpga9025_tx_types.h"
#include "adi_fpga9025_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief    This function writes the adi_fpga9025_TxTollgateCfg_t structure to the tollgate
*           modules selected in the txDataMoverSelMask. This function could be used as part
*           of a transmit setup procedure if more than just the trigger select should be
*           configured.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param tollGateCfg contains the transport configuration setting structure
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxTollgateSet(adi_fpga9025_Device_t*        device,
                                   uint32_t                      txDataMoverSelMask,
                                   adi_fpga9025_TxTollgateCfg_t* tollGateCfg);

/**
* \brief    Reads the configuration for a single tollgate module and populates the empty
*           adi_fpga9025_TxTollgateCfg_t structure passed in to the function.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSel an adi_fpga9025_TxDataMoverSel_e enum value selecting a single datamover
* \param tollGateCfg an empty structure that will be written with the selected tollgate's configuration values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_TOLLGATE_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxTollgateGet(adi_fpga9025_Device_t*        device,
                                   adi_fpga9025_TxDatamoverSel_e txDataMoverSel,
                                   adi_fpga9025_TxTollgateCfg_t* tollGateCfg);

/**
* \brief    This function writes the reset bit to the tollgate
*           modules selected in the txDatamoverSelMask. The reset bit is not self-clearing
*           so a full reset will require a call to this function to write a 1 then another
*           call to write a 0 for normal operation.
*           
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param resetVal the reset value (1 for reset; 0 for normal operation)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_TOLLGATE_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxTollgateResetSet(adi_fpga9025_Device_t* device,
                                        uint32_t               txDataMoverSelMask,
                                        uint8_t                resetVal);

/**
* \brief    This function reads the reset bit to the tollgate
*           modules selected in the txDatamoverSelMask. It zeros the resetVal parameter
*           and copies each module's reset value to the bit location given by the
*           adi_fpga9025_TxDataMoverSel_e enum.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param resetVal each corresponds to that datamover's tollgate reset bit
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_TOLLGATE_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxTollgateResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               txDataMoverSelMask,
                                        uint8_t*               resetVal);

/**
* \brief    This function writes the adi_fpga9025_TxDmaCfg_t structure to the DMA
*           modules selected in the txDatamoverSelMask. This function could be used as part
*           of an transmit setup procedure. The LastDescriptor bitfield and RunStop bits
*           are not written during this function call.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param txDmaCfg is the number of samples to transmit
* 
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_DMA_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaSet(adi_fpga9025_Device_t*   device,
                              uint32_t                 txDataMoverSelMask,
                              adi_fpga9025_TxDmaCfg_t* txDmaCfg);

/**
* \brief    Reads the configuration for a single DMA module and populates the empty
*           adi_fpga9025_TxDmaCfg_t structure passed in to the function. This function reads
*           Read-Write & Read-Only bitfields, including status bits.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSel anadi_fpga9025_TxDataMoverSel_e enum values
* \param dmaCfg Pointer to return the adi_fpga9025_TxDmaCfg_t data structure.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_DMA_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaGet(adi_fpga9025_Device_t*        device,
                              adi_fpga9025_TxDatamoverSel_e txDataMoverSel,
                              adi_fpga9025_TxDmaCfg_t*      dmaCfg);

/**
* \brief writes the  tramsmit mode for one or more  Tx data movers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param txmode can be one of adi_fpga9025_TxDatamoverMode_e
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
/* int32_t adi_fpga9025_TxModeSetup(adi_fpga9025_Device_t *device, adi_fpga_TramsmitMode_t transmitMode); */
int32_t adi_fpga9025_TxModeSet(adi_fpga9025_Device_t*         device,
                               uint32_t                       txDataMoverSelMask,
                               adi_fpga9025_TxDatamoverMode_e txmode);

/**
* \brief reads the  tramsmit mode for all Tx data movers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param transmitModeMask can be one of adi_fpga9025_TxDatamoverMode_e
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_SETUP An invalid tx datamover selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxModeGet(adi_fpga9025_Device_t* device,
                               uint8_t*               transmitModeMask);

/**
* \brief writes the trigger source for one or more Tx data movers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param triggerSelect can be a combination of adi_fpga_TrigSources_e
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_TRIGGER An invalid trigger type selected
*
*/
int32_t adi_fpga9025_TxTollgateTriggerSet(adi_fpga9025_Device_t*               device,
                                          uint32_t                             txDataMoverSelMask,
                                          adi_fpga9025_TxTollgateTrigSources_e triggerSelect);

/**
* \brief reads the trigger source for all Tx data movers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDataMoverSel one of adi_fpga9025_TxDataMoverSel_e enum values
* \param triggerSelect can be a combination of adi_fpga_TrigSources_e
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
* \retval ADI_FPGA9025_ACT_INV_TX_DATA_MOVER_TRIGGER An invalid trigger type selected
*
*/
int32_t adi_fpga9025_TxTollgateTriggerGet(adi_fpga9025_Device_t*                device,
                                          adi_fpga9025_TxDatamoverSel_e         txDataMoverSel,
                                          adi_fpga9025_TxTollgateTrigSources_e* triggerSelect);

/**
* \brief    Writes a 1 to the Capture Control modules Datapath Active bitfield. A capture will then occur
*           based on the Tollgate trigger selections.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDataStart(adi_fpga9025_Device_t* device);

/**
* \brief Stops all enabled FPGA Tx data movers
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDataStop(adi_fpga9025_Device_t* device);

/**
* \brief    This function writes the reset bit to the dma
*           modules selected in the txDatamoverSelMask. The reset bit is self-clearing
*           so there is no need to clear after setting.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDatamoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param resetVal set to 1 to reset module
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaResetSet(adi_fpga9025_Device_t* device,
                                   uint32_t               txDataMoverSelMask,
                                   uint8_t                reset);

/**
* \brief    This function writes the run-stop bit to the dma
*           modules selected in the txDatamoverSelMask. This can be used during the middle of a transfer
*           to gracefully halt the DMA. In this case the module must be halted after halting.
*           More commonly used prior to a transmit to start the DMAs before
*           triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDatamoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param runStop set to 1 to begin transfer; 0 to halt transfer
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaRunStopSet(adi_fpga9025_Device_t* device,
                                     uint32_t               txDataMoverSelMask,
                                     uint8_t                runStop);

/**
* \brief    This function writes the length bitfield to the dma
*           modules selected in the txDatamoverSelMask. This should be done prior to performing a transmit.
*           The length indicates the number of bytes the DMA will run for after triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDatamoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param numBytes the number of bytes to transfer
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaLengthSet(adi_fpga9025_Device_t* device,
                                    uint32_t               txDataMoverSelMask,
                                    uint32_t               numBytes);

/**
* \brief    This function will configure all the selected Datachains in the txDataMoverSelMask.
*           A Datachain consists of the Capture Control, Tollgate, & DMA modules. The tollgate trigger
*           is configured using adi_fpga9025_TxTollgateTriggerSet,
*           the DMA is reset then configured using adi_fpga9025_TxDmaSet,
*           the DMA is started by setting the run-stop bit using adi_fpga9025_TxDmaRunStopSet,
*           and finally the token passing is initiated in the Capture Control module. This function
*           is used in transmit sequences and is the final step before triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDatamoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param triggerSelect Select from adi_fpga9025_TxTollgateTrigSources_e enum
* \param txDmaCfg contains the dma configuration settings to apply to all selected DMA modules
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDataChainConfigure(adi_fpga9025_Device_t*               device,
                                          uint32_t                             txDataMoverSelMask,
                                          adi_fpga9025_TxTollgateTrigSources_e triggerSelect,
                                          adi_fpga9025_TxDmaCfg_t*             txDmaCfg);

/**
* \brief    This function clears and resets all Datachains to prepare for a new transmit or as part
*           of a tear down routine. The Capture Controls are reset and deactivated, the DMAs are halted
*           and will return errors if halted ungracefully, and the Tollgates are held in reset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDataChainReset(adi_fpga9025_Device_t* device);

/**
* \brief    This function writes the static members of the adi_fpga9025_TxDmaCfg_t structure to the DMA
*           modules selected in the txDatamoverSelMask. This function is used when the fpga
*           boots up. The DMAs are not ready for transmit after this function.
*           The LastDescriptor, RunStop, and Length bitfields are not written 
*           during this function call.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param txDatamoverSelMask an or'd combination of one or more adi_fpga9025_TxDataMoverSel_e enum values
* \param txDmaCfg contains the dma configuration settings to apply to all selected DMA modules
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_TxDmaInit(adi_fpga9025_Device_t*   device,
                               uint32_t                 txDataMoverSelMask,
                               adi_fpga9025_TxDmaCfg_t* txDmaCfg);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_TX_H_ */
