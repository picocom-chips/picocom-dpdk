/*!
* \file adi_fpga9025_rx_types.h
* \brief Contains FPGA9025 rx enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_RX_TYPES_H_
#define _ADI_FPGA9025_RX_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ADI_FPGA9025_NUM_OF_RX_DATAMOVERS 3
/* 0x2AAAAA80, 2G /3, then reduced to a 64byte boundary */
#define ADI_FPGA9025_RX_START_ADDRESS 0
#define ADI_FPGA9025_RX_DMA_SIZE 715827840

/**
* \brief Enumerated list of fpga Rx Tollgata trigger sources
*/
typedef enum adi_fpga9025_RxTollgateTrigSources
{
    ADI_FPGA9025_IMM_TRIG   = 0x1,  /*!Immediate trigger. */
    ADI_FPGA9025_EXT_TRIG   = 0x2,  /*!External Trigger external SMA. */
    ADI_FPGA9025_TDD_SM     = 0x4,  /*!TDD State Machine. */
    ADI_FPGA9025_ARM_ACK    = 0x8,  /*!GPIO. */
    ADI_FPGA9025_TX1_SOF    = 0x10, /*!TX1 Start of File Flag from transmit to indicate start of transmit tone.*/
    ADI_FPGA9025_TX2_SOF    = 0x20, /*!TX2 Start of File Flag from transmit to indicate start of transmit tone. */
    ADI_FPGA9025_TX3_SOF    = 0x40, /*!TX3 Start of File Flag from transmit to indicate start of transmit tone. */
    ADI_FPGA9025_TX4_SOF    = 0x80  /*!TX4 Start of File Flag from transmit to indicate start of transmit tone. */
} adi_fpga9025_RxTollgateTrigSources_e;

/**
*  \brief Data structure to hold the Fpga Data mover tollgate Configuration
*/
typedef struct adi_fpga9025_RxTollgateCfg
{
    uint32_t tollGateEdgeOrLvl;                                 /*!1 indicates that the trigger input is edge detected.   0 indicates that the trigger input is level sensitive. */
    uint32_t tollGateHiRiseOrLoFall;                            /*!1 indicates either high level or rising edge. 0 indicates either low level or falling edge. */
    uint8_t                              tollgateReset;         /*!Set to 1 resets the Tollgate.  Clear to 0 allows for normal operation.. */
    adi_fpga9025_RxTollgateTrigSources_e tollGateTrigSource;    /*!Selects the trigger input that is used to open the Tollgate. multiple triggers Supported */
} adi_fpga9025_RxTollgateCfg_t;

/**
*  \brief Data structure to hold the Fpga Data mover dma Configuration
*/
typedef struct adi_fpga9025_RxDmaCfg
{
    uint8_t enableEnhancedMode;     /*!When set to 1, the enhanced mode of the selected transfer is performed.  When cleared to 0, the traditional mode of the selected transfer is performed. */
    uint8_t  enableSg;              /*!When set to 1, the DMA performs a scatter-gather transfer.  When cleared to 0, the DMA performs a simple transfer. */
    uint64_t simpleStartAddr;       /*!indicates the starting address in memory where the data should be written.*/
    uint32_t length;                /*!Identifies the number of bytes to transfer in the simple mode and enhanced scatter-gather mode. */
    uint8_t  validDataWidthStream;  /*!This field indicates what the width of valid data is on the stream interface.  This field is used to pack/unpack the data from the memory.*/
    uint32_t sgFirstDescriptor;     /*!Contains the location of the first descriptor used in both scatter-gather modes. */
    uint32_t sgLastDescriptor;      /*!Contains the location of the last descriptor used in both scatter-gather modes. */
    uint8_t  runStop;               /*! When set to 1, the DMA begins the transfer.  When cleared to 0, any active transfer is gracefully halted.  When halted, the module needs to be reset after the halt completes.*/
    uint8_t active;                 /*! When this bit is 1, the DMA is actively transferring data. Read-only */
    uint8_t complete;               /*! When this bit is 1, the transfer has completed successfully.  This bit will clear when run_stop is cleared to '0'. Read-only */
    uint8_t haltComplete;           /*! When this bit is 1, the halt that was previously issued has completed.  This module must be reset after a halt completes. Read-only */
    uint8_t overflow;               /*! When this bit is 1, an overflow has occurred on the FIFO.  This is a sticky bit.  Write a 1 to this bit to clear it. Read-only */
} adi_fpga9025_RxDmaCfg_t;

/**
* \brief Enumerated list of fpga rx data movers
*/
typedef enum adi_fpga9025_RxDatamoverSel
{
    ADI_FPGA9025_RX_DATAMOVER_0     = 1,    /*!Rx Datamover 0. */
    ADI_FPGA9025_RX_DATAMOVER_1     = 2,    /*!Rx Datamover 1. */
    ADI_FPGA9025_RX_DATAMOVER_2     = 4,    /*!Rx Datamover 2. */
    ADI_FPGA9025_RX_DATAMOVER_ALL   = 7     /*!All Rx Datamovers. */
} adi_fpga9025_RxDatamoverSel_e;

#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9025_RX_TYPES_H_ */
