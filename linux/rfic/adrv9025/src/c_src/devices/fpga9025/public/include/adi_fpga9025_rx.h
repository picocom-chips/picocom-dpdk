/**
 * \file: adi_fpga9025_rx.h
 *
 * \brief Contains top level rx fpga9025 related prototypes
 *
 * FPGA9025 API Version: 6.0.0.41
 */

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_RX_H_
#define _ADI_FPGA9025_RX_H_

#include "adi_fpga9025_rx_types.h"
#include "adi_fpga9025.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \brief    This function writes the adi_fpga9025_RxTollgateCfg_t structure to the tollgate
*           modules selected in the rxDatamoverSelMask. This function could be used as part
*           of an rx capture setup procedure if more than just the trigger select should be
*           configured.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param tollGateCfg contains the tollgate configuration setting structure
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateSet(adi_fpga9025_Device_t*        device,
                                   uint32_t                      rxDatamoverSelMask,
                                   adi_fpga9025_RxTollgateCfg_t* tollGateCfg);

/**
* \brief    Reads the configuration for a single tollgate module and populates the empty
*           adi_fpga9025_RxTollgateCfg_t structure passed in to the function.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSel an adi_fpga9025_RxDataMoverSel_e enum value selecting a single datamover
* \param tollGateCfg an empty structure that will be written with the selected tollgate's configuration values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateGet(adi_fpga9025_Device_t*        device,
                                   adi_fpga9025_RxDatamoverSel_e rxDatamoverSel,
                                   adi_fpga9025_RxTollgateCfg_t* tollGateCfg);

/**
* \brief    This function writes the reset bit to the tollgate
*           modules selected in the rxDatamoverSelMask. The reset bit is not self-clearing
*           so a full reset will require a call to this function to write a 1 then another
*           call to write a 0 for normal operation.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param resetVal the reset value (1 for reset; 0 for normal operation)
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateResetSet(adi_fpga9025_Device_t* device,
                                        uint32_t               rxDatamoverSelMask,
                                        uint8_t                resetVal);

/**
* \brief     This function reads the reset bit to the tollgate
*           modules selected in the rxDatamoverSelMask. It zeros the resetVal parameter
*           and copies each module's reset value to the bit location given by the
*           adi_fpga9025_RxDataMoverSel_e enum.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param resetVal a combination of all the selected tollgate modules' reset value
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateResetGet(adi_fpga9025_Device_t* device,
                                        uint32_t               rxDatamoverSelMask,
                                        uint16_t*              resetVal);

/**
* \brief    This function writes the trigger select to the tollgate
*           modules selected in the rxDatamoverSelMask. This function could be used as part
*           of an rx capture setup procedure. It puts the tollgate in reset, configures the
*           trigger, then releases the reset.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param triggerSelect Select from adi_fpga_TrigSources_e enum
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateTriggerSet(adi_fpga9025_Device_t*               device,
                                          uint32_t                             rxDatamoverSelMask,
                                          adi_fpga9025_RxTollgateTrigSources_e triggerSelect);

/**
* \brief    Reads the trigger bitfield for a single tollgate module and populates the empty
*           pointer passed in to the function.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSel an adi_fpga9025_RxDataMoverSel_e enum value selecting a single datamover
* \param triggerSelect pointer to an adi_fpga9025_RxTollgateTrigSources_e enum to hold the readback value
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxTollgateTriggerGet(adi_fpga9025_Device_t*                device,
                                          adi_fpga9025_RxDatamoverSel_e         rxDatamoverSel,
                                          adi_fpga9025_RxTollgateTrigSources_e* triggerSelect);

/**
* \brief    This function writes the adi_fpga9025_RxDmaCfg_t structure to the DMA
*           modules selected in the rxDatamoverSelMask. This function could be used as part
*           of an rx capture setup procedure. The LastDescriptor bitfield and RunStop bits
*           are not written during this function call.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param rxDmaCfg contains the dma configuration settings to apply to all selected DMA modules
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaSet(adi_fpga9025_Device_t*   device,
                              uint32_t                 rxDatamoverSelMask,
                              adi_fpga9025_RxDmaCfg_t* rxDmaCfg);

/**
* \brief    This function writes the static members of the adi_fpga9025_RxDmaCfg_t structure to the DMA
*           modules selected in the rxDatamoverSelMask. This function is used when the fpga
*           boots up. The DMAs are not ready for capture after this function.
*           The LastDescriptor, RunStop, and Length bitfields are not written 
*           during this function call.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param rxDmaCfg contains the dma configuration settings to apply to all selected DMA modules
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaInit(adi_fpga9025_Device_t*   device,
                               uint32_t                 rxDatamoverSelMask,
                               adi_fpga9025_RxDmaCfg_t* rxDmaCfg);

/**
* \brief    Reads the configuration for a single DMA module and populates the empty
*           adi_fpga9025_RxDmaCfg_t structure passed in to the function. This function reads
*           Read-Write & Read-Only bitfields, including status bits.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSel an adi_fpga9025_RxDataMoverSel_e enum value selecting a single datamover
* \param rxDmaCfg contains the dma configuration setting
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaGet(adi_fpga9025_Device_t*        device,
                              adi_fpga9025_RxDatamoverSel_e rxDatamoverSel,
                              adi_fpga9025_RxDmaCfg_t*      rxDmaCfg);

/**
* \brief    This function writes the reset bit to the dma
*           modules selected in the rxDatamoverSelMask. The reset bit is self-clearing
*           so there is no need to clear after setting.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param resetVal set to 1 to reset module
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaResetSet(adi_fpga9025_Device_t* device,
                                   uint32_t               rxDatamoverSelMask,
                                   uint8_t                reset);

/**
* \brief    This function writes the run-stop bit to the dma
*           modules selected in the rxDatamoverSelMask. This can be used during the middle of a transfer
*           to gracefully halt the DMA. In this case the module must be halted after halting.
*           More commonly used prior to an rx capture to start the DMAs before
*           triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param runStop set to 1 to begin transfer; 0 to halt transfer
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaRunStopSet(adi_fpga9025_Device_t* device,
                                     uint32_t               rxDataMoverSelMask,
                                     uint8_t                runStop);

/**
* \brief    This function writes the length bitfield to the dma
*           modules selected in the rxDatamoverSelMask. This should be done prior to performing a capture.
*           The length indicates the number of bytes the DMA will run for after triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param numBytes the number of bytes to transfer
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDmaLengthSet(adi_fpga9025_Device_t* device,
                                    uint32_t               rxDatamoverSelMask,
                                    uint32_t               numBytes);

/**
* \brief Unimplemented
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_RX_DATA_MOVER_ENABLE An invalid rx data mover trigger selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDatamoverEnableSet(adi_fpga9025_Device_t* device,
                                          uint32_t               rxDatamoverSelMask);

/**
* \brief    This function will configure all the selected Datachains in the rxDataMoverSelMask.
*           A Datachain consists of the Capture Control, Tollgate, & DMA modules. The tollgate trigger
*           is configured using adi_fpga9025_RxTollgateTriggerSet,
*           the DMA is reset then configured using adi_fpga9025_RxDmaSet,
*           the DMA is started by setting the run-stop bit using adi_fpga9025_RxDmaRunStopSet,
*           and finally the token passing is initiated in the Capture Control module. This function
*           is used in rx captures and is the final step before triggering.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param triggerSelect Select from adi_fpga_TrigSources_e enum
* \param rxDmaCfg contains the dma configuration settings to apply to all selected DMA modules
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDataChainConfigure(adi_fpga9025_Device_t*               device,
                                          uint32_t                             rxDataMoverSelMask,
                                          adi_fpga9025_RxTollgateTrigSources_e triggerSelect,
                                          adi_fpga9025_RxDmaCfg_t*             rxDmaCfg);

/**
* \brief    This function clears and resets all Datachains to prepare for a new capture or as part
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
int32_t adi_fpga9025_RxDataChainReset(adi_fpga9025_Device_t* device);

/**
* \brief Unimplemented
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_INV_RX_DATA_MOVER_ENABLE An invalid rx data mover trigger selected
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDatamoverEnableGet(adi_fpga9025_Device_t* device,
                                          uint32_t*              rxDatamoverSelMask);

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
int32_t adi_fpga9025_RxCaptureStart(adi_fpga9025_Device_t* device);

/**
* \brief    Called after adi_fpga9025_RxCaptureStart to block program execution until the capture completes
*           or the timeMsDelay expires. The function waits for the Active bitfield in the Capture Control
*           module to clear.
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param timeMsDelay is uint32_t type which conveys the wait time in milliseconds, i.e. 200 = 200 ms
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_DATA_RX_MOVER_WAIT_TIMEOUT Timeout occurred during Rx transaction
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxCaptureWait(adi_fpga9025_Device_t* device,
                                   uint32_t               timeMsDelay);

/**
* \brief Unimplemented
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDatamoverSel the selected datamover to read
* \param data the user provided array into which the data is placed.
* \param dataSize the size of the data array.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_DATA_RX_MOVER_WAIT_TIMEOUT Timeout occurred during Rx transaction
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxDataGet(adi_fpga9025_Device_t*        device,
                               adi_fpga9025_RxDatamoverSel_e rxDatamoverSel,
                               int32_t                       data[],
                               uint32_t*                     dataSize);

/**
* \brief Unimplemented
*
* \dep_begin
* \dep{device}
* \dep_end
*
* \param device Pointer to the FPGA9025 device data structure.
* \param rxDataMoverSelMask an or'd combination of one or more adi_fpga9025_RxDataMoverSel_e enum values
* \param numSamples the number of samples to be written from part to the memory.
*
* \retval ADI_FPGA9025_ACT_RESET_LOG Recovery action for log reset
* \retval ADI_COMMON_ACT_ERR_CHECK_PARAM Recovery action for bad parameter check
* \retval ADI_FPGA9025_ACT_DATA_RX_MOVER_WAIT_TIMEOUT Timeout occurred during Rx transaction
* \retval ADI_COMMON_ACT_NO_ACTION Function completed successfully, no action required
*
*/
int32_t adi_fpga9025_RxSamplesSet(adi_fpga9025_Device_t* device,
                                  uint32_t               rxDataMoverSelMask,
                                  uint32_t               numSamples);

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_RX_H_ */
