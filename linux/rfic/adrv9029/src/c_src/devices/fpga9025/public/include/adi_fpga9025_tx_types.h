/*!
* \file adi_adrv9025_tx_types.h
* \brief Contains FPGA9025 tx enum and struct definitions
*
* ADRV9025 API Version: 6.0.0.41
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_TX_TYPES_H_
#define _ADI_FPGA9025_TX_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ADI_FPGA9025_NUM_OF_TX_DATAMOVERS 2
#define ADI_FPGA9025_TX_START_ADDRESS 0x100000000
#define ADI_FPGA9025_TX_DMA_SIZE 0x40000000

typedef enum adi_fpga9025_TxDatamoverMode
{
    ADI_FPGA9025_TXMODE_SNGL = 0,
    ADI_FPGA9025_TXMODE_CONT = 1
} adi_fpga9025_TxDatamoverMode_e;

/**
* \brief Enumerated list of fpga Tx Tollgata trigger sources
*/
typedef enum adi_fpga9025_TxTollgateTrigSources
{
    ADI_FPGA9025_TX_IMM_TRIG    = 0x1,  /*!Immediate trigger. */
    ADI_FPGA9025_TX_EXT_TRIG    = 0x2,  /*!External Trigger external SMA. */
    ADI_FPGA9025_TX_TDD_SM      = 0x4,  /*!TDD State Machine. */
    ADI_FPGA9025_TX_ARM_ACK     = 0x8   /*!GPIO. */
} adi_fpga9025_TxTollgateTrigSources_e;

/**
*  \brief Data structure to hold the Fpga Data mover tollgate Configuration
*/
typedef struct adi_fpga9025_TxTollgateCfg
{
    uint32_t tollGateEdgeOrLvl;         /*!1 indicates that the trigger input is edge detected.   0 indicates that the trigger input is level sensitive. */
    uint32_t tollGateHiRiseOrLoFall;    /*!1 indicates either high level or rising edge. 0 indicates either low level or falling edge. */
    uint8_t                              tollgateReset;      /*!Set to 1 resets the Tollgate.  Clear to 0 allows for normal operation.. */
    adi_fpga9025_TxTollgateTrigSources_e tollGateTrigSource; /*!Selects the trigger input that is used to open the Tollgate. multiple triggers Supported */
} adi_fpga9025_TxTollgateCfg_t;

/**
*  \brief Data structure to hold the Fpga Data mover dma Configuration
*/
typedef struct adi_fpga9025_TxDmaCfg
{
    uint8_t enableEnhancedMode;    /*!When set to 1, the enhanced mode of the selected transfer is performed.  When cleared to 0, the traditional mode of the selected transfer is performed. */
    uint8_t  enableSg;             /*!When set to 1, the DMA performs a scatter-gather transfer.  When cleared to 0, the DMA performs a simple transfer. */
    uint64_t simpleStartAddr;      /*!indicates the starting address in memory where the data should be written.*/
    uint32_t length;               /*!Identifies the number of bytes to transfer in the simple mode and enhanced scatter-gather mode. */
    uint8_t  validDataWidthStream; /*!This field indicates what the width of valid data is on the stream interface.  This field is used to pack/unpack the data from the memory.*/
    uint32_t sgFirstDescriptor;    /*!Contains the location of the first descriptor used in both scatter-gather modes. */
    uint32_t sgLastDescriptor;     /*!Contains the location of the last descriptor used in both scatter-gather modes. */
    uint8_t  runStop;              /*! When set to 1, the DMA begins the transfer.  When cleared to 0, any active transfer is gracefully halted.  When halted, the module needs to be reset after the halt completes.*/
    uint8_t continuous;            /*! When set to 1, the DMA will restart the transfer.  When cleared to 0, the DMA performs one transfer and stops.*/
    uint8_t active;                /*! When this bit is 1, the DMA is actively transferring data. Read-only */
    uint8_t complete;              /*! When this bit is 1, the transfer has completed successfully.  This bit will clear when run_stop is cleared to '0'. Read-only */
    uint8_t haltComplete;          /*! When this bit is 1, the halt that was previously issued has completed.  This module must be reset after a halt completes. Read-only */
    uint8_t underflow;             /*! When this bit is 1, an overflow has occurred on the FIFO.  This is a sticky bit.  Write a 1 to this bit to clear it. Read-only */
} adi_fpga9025_TxDmaCfg_t;

/**
* \brief Enumerated list of fpga tx data movers
*/
typedef enum adi_fpga9025_TxDatamoverSel
{
    ADI_FPGA9025_TX_DATAMOVER_0 = 1,    /*!Tx Datamover 0. */
    ADI_FPGA9025_TX_DATAMOVER_1 = 2,    /*!Tx Datamover 1. */
    ADI_FPGA9025_TX_DATAMOVER_ALL = 3   /*!All Rx Datamovers. */
} adi_fpga9025_TxDatamoverSel_e;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_TX_TYPES_H_ */
