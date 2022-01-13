/*!
* \file adi_fpga9010_types.h
* \brief Contains ADRV9010 API configuration and run-time type definitions
*
* ADRV9010 API Version: $ADI_FPGA9010_API_VERSION$
*
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_TYPES_H_
#define _ADI_FPGA9010_TYPES_H_


#include <stdint.h>
#include "adi_common.h"
#include "adi_fpga9010_tx_types.h"
#include "adi_fpga9010_rx_types.h"
#include "adi_fpga9010_jesd_types.h"
#include "adi_fpga9010_clk_types.h"
#include "adi_fpga9010_gpio_types.h"


#ifdef __cplusplus
extern "C" {
#endif

#define ADI_FPGA9010_MIN_VERSION 0x00000B
#define ADI_FPGA9010_JESD204B_DEVICEID 0xC9
#define ADI_FPGA9010_JESD204C_DEVICEID 0xCA
#define ADI_FPGA9010_DRP_TIMEOUT_MS 200

typedef enum adi_fpga9010_PinDir
{
    ADI_FPGA9010_PIN_DIR_IN = 0,
    ADI_FPGA9010_PIN_DIR_OUT = 1
} adi_fpga9010_PinDir_e;

/**
*  \brief Data structure to hold digital clock settings
*/
typedef struct adi_fpga9010_ClockSettings
{
    adi_fpga9010_MmcmCfg_t coreMmcm;
    adi_fpga9010_QpllCfg_t qpll;
} adi_fpga9010_ClockSettings_t;

typedef struct adi_fpga9010_SysRefClkCfg
{
    uint32_t    internalSysRefGeneratorFrequency;       /*!< The number of device clock cycles to generate internal SYSREF pulse */
    uint8_t     internalSysrefEnable;                   /*!< Set this to 1 to enable internal SYSREF */
    uint8_t     externalSysrefSampleEdge;               /*!< Set this to 1 to sample external SYSREF on rising edge; 0 for falling edge */
    uint8_t     externalSysrefPolarity;                 /*!< Set to 1 to invert external SYSREF polarity */
} adi_fpga9010_SysRefClkCfg_t;

typedef enum adi_fpga9010_DrpInterface
{
    ADI_FPGA9010_PHY_CH0,
    ADI_FPGA9010_PHY_CH1,
    ADI_FPGA9010_PHY_CH2,
    ADI_FPGA9010_PHY_CH3,
    ADI_FPGA9010_PHY_CH4,
    ADI_FPGA9010_PHY_CH5,
    ADI_FPGA9010_PHY_CH6,
    ADI_FPGA9010_PHY_CH7,
    ADI_FPGA9010_PHY_QUAD0,
    ADI_FPGA9010_PHY_QUAD1
} adi_fpga9010_DrpInterface_e;

/**
* \brief The data path includes the serializer/deserializer, framers/deframers, transport, tollgate and DMA
*/
typedef struct adi_fpga9010_DatapathCfg
{
    adi_fpga9010_SerializerCfg_t        serializerCfg[ADI_FPGA9010_NUM_LANES];   /*!< Holds configuration for the tx GTH serializer 1..8 */
    adi_fpga9010_DeserializerCfg_t      deserializerCfg[ADI_FPGA9010_NUM_LANES]; /*!< Holds configuration for the rx GTH deserializer 1..8 */
    adi_fpga9010_FramerCfg_t            framerCfg[ADI_FPGA9010_NUM_OF_FRAMERS];          /*!< Holds configuration for the tx framers 1,2 */
    adi_fpga9010_DeframerCfg_t          deframerCfg[ADI_FPGA9010_NUM_OF_DEFRAMERS];        /*!< Holds configuration for the Rx deframers 1,2,3 */
    adi_fpga9010_RxDmaCfg_t             rxDmaCfg[ADI_FPGA9010_NUM_OF_DEFRAMERS];        /*!< Holds configuration for the rx digital data paths 1..16 */
    adi_fpga9010_TxDmaCfg_t             txDmaCfg[ADI_FPGA9010_NUM_OF_FRAMERS];         /*!< Holds configuration for the tx digital data paths 1..8*/
    adi_fpga9010_RxTollgateCfg_t        rxTollgateCfg;        /*!< Holds configuration for the 16 rx tollgates all are configured identically*/
    adi_fpga9010_TxTollgateCfg_t        txTollgateCfg;        /*!< Holds configuration for the 8 tx tollgates all are configured identically*/
    uint32_t                            rxDatamoverMask;    /*! Logical or of the datamover enums to be configured */
    uint32_t                            txDatamoverMask;    /*! Logical or of the datamover enums to be configured */
    uint8_t                             syncBSel[ADI_FPGA9010_NUM_OF_DEFRAMERS + ADI_FPGA9010_NUM_OF_FRAMERS]; /*! The location in the array corresponds to sync xbar output. Values determine which input is used for that output */
    uint8_t                             syncBPolarity; /*! The polarity for the sync xbar polarity. Each bit corresponds to a single input */
    uint8_t                             pcbSerLaneSwap[ADI_FPGA9010_NUM_LANES]; /*!< Indices correspond to serializer lane numbers. Values are lane number after applying PCB swap */
    uint8_t                             pcbDesLaneSwap[ADI_FPGA9010_NUM_LANES]; /*!< Indices correspond to deserializer lane numbers. Values are lane number after applying PCB swap */
} adi_fpga9010_DatapathCfg_t;

/**
* \brief Data structure to hold ADRV9010 device instance initialization settings
*/
typedef struct adi_fpga9010_Init
{
    adi_fpga9010_ClockSettings_t   clocks;     /*!< Holds settings for CLKPLL and reference clock */
    adi_fpga9010_DatapathCfg_t     datapath;    /*!< Holds the Datapath / JESD204B/C data link and digital datapath settings */ 
    adi_fpga9010_SysRefClkCfg_t    sysref;     /*!< Holds the data for the external or internal Sysref */
} adi_fpga9010_Init_t;

typedef struct adi_fpga9010_Info
{
    uint8_t designId;                           /*!< FPGA9010 design ID read during FPGA9010_initialize */
    uint16_t versionMinor;                      /*!< FPGA9010 minor version read during FPGA9010_initialize */
    uint8_t versionMajor;                      /*!< FPGA9010 major version read during FPGA9010_initialize */
    uint32_t swTest;                            /*!< Software testmode signal */
    uint32_t tddStateMachineClk_kHz;            /*!< Frequency the TDD state machine is set to. Default is fastest lane rate / 40 */

    uint32_t linkLayerDataWidth;                /*!< 40 (bits per lane) for JESD204B; 66 for JESD204C */
    uint32_t encodingLowValue;                  /*!< 8 (from 8b10b) for JESD204B; 64 for JESD204C */
    uint32_t encodingHighValue;                 /*!< 10 (from 8b10b) for JESD204B; 66 for JESD204C */
    uint32_t dmaDataWidth;                      /*!< Num of bits per word written to RAM from DMA: 32 bits for JESD204B; 64 bits for JESD204C */
    
    adi_fpga9010_GpioModes_e gpioPinMode[ADI_FPGA9010_GPIO_PINS];   /*!< The current mode each GPIO pin is assigned */
} adi_fpga9010_Info_t;

/**
* \brief Data structure to hold FPGA9010 device instance settings
*/
typedef struct adi_fpga9010_Device
{
    adi_common_Device_t      common; /*!< Common layer structure */
    adi_fpga9010_Info_t      devStateInfo;  /*!< ADRV9010 run time state information container */
    uint32_t memoryPageSize;                /*!< The current page size used when reading/writing RAM */
} adi_fpga9010_Device_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9010_TYPES_H_ */
