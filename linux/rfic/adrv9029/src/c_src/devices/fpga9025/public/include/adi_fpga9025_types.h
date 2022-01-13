/*!
* \file adi_fpga9025_types.h
* \brief Contains ADRV9025 API configuration and run-time type definitions
*
* ADRV9025 API Version: 6.0.0.41
*
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9025 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9025_TYPES_H_
#define _ADI_FPGA9025_TYPES_H_

#include <stdint.h>
#include "adi_common.h"
#include "adi_fpga9025_tx_types.h"
#include "adi_fpga9025_rx_types.h"
#include "adi_fpga9025_jesd_types.h"
#include "adi_fpga9025_clk_types.h"
#include "adi_fpga9025_gpio_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ADI_FPGA9025_MIN_VERSION 0x000000
#define ADI_FPGA9025_JESD204B_DEVICEID 0xD9
#define ADI_FPGA9025_JESD204C_DEVICEID 0xDA
#define ADI_FPGA9025_JESD204H_DEVICEID 1
#define ADI_FPGA9025_RAM_ADDRESS_BOUNDARY 32
#define ADI_FPGA9025_DRP_TIMEOUT_MS 200

typedef enum adi_fpga9025_PinDir
{
    ADI_FPGA9025_PIN_DIR_IN = 0,
    ADI_FPGA9025_PIN_DIR_OUT = 1
} adi_fpga9025_PinDir_e;

typedef struct adi_fpga9025_LinkSetting
{
    uint32_t IqRate_kHz;
    uint8_t  M;
    uint8_t  L;
    uint8_t  K;
    uint8_t  Scrambling;
    uint8_t  S;
    uint8_t  Np;
    uint8_t  LinkToUse;
    uint8_t  jesd204C_en;
    uint8_t  realIf; /* ignore in tx link*/
}            adi_fpga9025_LinkSetting_t;

/**
*  \brief Data structure to hold digital clock settings
*/
typedef struct adi_fpga9025_ClockSettings
{
    adi_fpga9025_MmcmCfg_t coreMmcm;
    adi_fpga9025_QpllCfg_t qpll;
}                          adi_fpga9025_ClockSettings_t;

typedef struct adi_fpga9025_SysRefClkCfg
{
    uint32_t internalSysRefGeneratorFrequency; /*!< The number of device clock cycles to generate internal SYSREF pulse */
    uint8_t  internalSysrefEnable;             /*!< Set this to 1 to enable internal SYSREF */
    uint8_t  externalSysrefSampleEdge;         /*!< Set this to 1 to sample external SYSREF on rising edge; 0 for falling edge */
    uint8_t  externalSysrefPolarity;           /*!< Set to 1 to invert external SYSREF polarity */
}            adi_fpga9025_SysRefClkCfg_t;

/**
*  \brief Data structure to hold the Fpga Data mover transport Configuration
*/
typedef struct adi_fpga9025_TransportCfg
{
    uint16_t linkCfgF;         /*!<Identifies the number of octets per frame. Field value is actual value minus one. */
    uint8_t  linkCfgNP;        /*!<Identifies the total number of bits per sample. Field value is actual value minus one */
    uint8_t  linkCfgL;         /*!<Number of lanes. Field value is actual value minus one */
    uint8_t  linkCfgS;         /*!<Identifies the number of samples per frame. Field value is actual value minus one. */
    uint8_t  linkConfigJesdV;  /*!<Identifies thejesd version  001 - JESD204B, 010 - JESD204C*/
    uint16_t linkConfigM;      /*!<Identifies the number of converters in the link. Field value is actual value minus one. */
    uint8_t  linkConfigLinkId; /*!<This field identifies the link to which the data is extracted.*/
    uint8_t  linkConfigConvId;
    /*!This field identifies the specific converter that will be injected for this transport layer. The value here can not be greater than the Link Configuration M field value.*/
    uint8_t linkCfgDecimationFactor; /*! Decimation factor*/
}           adi_fpga9025_TransportCfg_t;

typedef enum adi_fpga9025_DrpInterface
{
    ADI_FPGA9025_PHY_CH0,
    ADI_FPGA9025_PHY_CH1,
    ADI_FPGA9025_PHY_CH2,
    ADI_FPGA9025_PHY_CH3,
    ADI_FPGA9025_PHY_CH4,
    ADI_FPGA9025_PHY_CH5,
    ADI_FPGA9025_PHY_CH6,
    ADI_FPGA9025_PHY_CH7,
    ADI_FPGA9025_PHY_QUAD0,
    ADI_FPGA9025_PHY_QUAD1
} adi_fpga9025_DrpInterface_e;

/**
* \brief The data path includes the  transport, tollgate and DMA
*/
typedef struct adi_fpga9025_DatamoverCfg
{
    /* adi_fpga9025_DmaCfg_t        dmaCfg;*/     /*!< Holds configuration for a single dma path*/
    /* adi_fpga9025_TransportCfg_t  tplCfg;*/   /*!< Holds configuration for a single transport path*/
    uint8_t placeHolder;
}           adi_fpga9025_DatamoverCfg_t;

/**
* \brief The data path includes the serializer/deserializer, framers/deframers, transport, tollgate and DMA
*/
typedef struct adi_fpga9025_DatapathCfg
{
    adi_fpga9025_SerializerCfg_t   serializerCfg[ADI_FPGA9025_NUM_LANES];          /*!< Holds configuration for the tx GTH serializer 1..8 */
    adi_fpga9025_DeserializerCfg_t deserializerCfg[ADI_FPGA9025_NUM_LANES];        /*!< Holds configuration for the rx GTH deserializer 1..8 */
    adi_fpga9025_FramerCfg_t       framerCfg[ADI_FPGA9025_NUM_OF_TX_DATAMOVERS];   /*!< Holds configuration for the tx framers 1,2 */
    adi_fpga9025_DeframerCfg_t     deframerCfg[ADI_FPGA9025_NUM_OF_RX_DATAMOVERS]; /*!< Holds configuration for the Rx deframers 1,2,3 */
    adi_fpga9025_RxDmaCfg_t        rxDmaCfg[ADI_FPGA9025_NUM_OF_RX_DATAMOVERS];    /*!< Holds configuration for the rx digital data paths 1..16 */
    adi_fpga9025_TxDmaCfg_t        txDmaCfg[ADI_FPGA9025_NUM_OF_TX_DATAMOVERS];    /*!< Holds configuration for the tx digital data paths 1..8*/
    adi_fpga9025_RxTollgateCfg_t   rxTollgateCfg;
    /*!< Holds configuration for the 16 rx tollgates all are configured identically*/
    adi_fpga9025_TxTollgateCfg_t txTollgateCfg;
    /*!< Holds configuration for the 8 tx tollgates all are configured identically*/
    uint32_t rxDatamoverMask; /*! Logical or of the datamover enums to be configured */
    uint32_t txDatamoverMask; /*! Logical or of the datamover enums to be configured */
    uint8_t  syncBSel[ADI_FPGA9025_NUM_OF_RX_DATAMOVERS + ADI_FPGA9025_NUM_OF_TX_DATAMOVERS];
    /*! The location in the array corresponds to sync xbar output. Values determine which input is used for that output */
    uint8_t syncBPolarity;                           /*! The polarity for the sync xbar polarity. Each bit corresponds to a single input */
    uint8_t pcbSerLaneSwap[ADI_FPGA9025_NUM_LANES];  /*!< Indices correspond to serializer lane numbers. Values are lane number after applying PCB swap */
    uint8_t pcbDesLaneSwap[ADI_FPGA9025_NUM_LANES];  /*!< Indices correspond to deserializer lane numbers. Values are lane number after applying PCB swap */
    uint8_t desLanePnInvert[ADI_FPGA9025_NUM_LANES]; /*!< Indices correspond to serializer lane numbers. Values are lane number after applying PCB swap */
    uint8_t serLanePnInvert[ADI_FPGA9025_NUM_LANES]; /*!< Indices correspond to deserializer lane numbers. Values are lane number after applying PCB swap */
}           adi_fpga9025_DatapathCfg_t;

/**
* \brief Data structure to hold ADRV9025 device instance initialization settings
*/
typedef struct adi_fpga9025_Init
{
    adi_fpga9025_ClockSettings_t clocks;   /*!< Holds settings for CLKPLL and reference clock */
    adi_fpga9025_DatapathCfg_t   datapath; /*!< Holds the Datapath / JESD204B/C data link and digital datapath settings */
    adi_fpga9025_SysRefClkCfg_t  sysref;   /*!< Holds the data for the external or internal Sysref */
}                                adi_fpga9025_Init_t;

typedef struct adi_fpga9025_Info
{
    uint8_t  designId;               /*!< FPGA9025 design ID read during FPGA9025_initialize */
    uint16_t versionMinor;           /*!< FPGA9025 minor version read during FPGA9025_initialize */
    uint8_t  versionMajor;           /*!< FPGA9025 major version read during FPGA9025_initialize */
    uint32_t swTest;                 /*!< Software testmode signal */
    uint32_t tddStateMachineClk_kHz; /*!< Frequency the TDD state machine is set to. Default is fastest lane rate / 40 */

    uint32_t linkLayerDataWidth; /*!< 40 (bits per lane) for JESD204B; 66 for JESD204C */
    uint32_t encodingLowValue;   /*!< 8 (from 8b10b) for JESD204B; 64 for JESD204C */
    uint32_t encodingHighValue;  /*!< 10 (from 8b10b) for JESD204B; 66 for JESD204C */
    uint32_t dmaDataWidth;       /*!< Num of bits per word written to RAM from DMA: 32 bits for JESD204B; 64 bits for JESD204C */

    adi_fpga9025_GpioModes_e gpioPinMode[ADI_FPGA9025_GPIO_PINS]; /*!< The current mode each GPIO pin is assigned */
}                            adi_fpga9025_Info_t;

/**
* \brief Data structure to hold FPGA9025 device instance settings
*/
typedef struct adi_fpga9025_Device
{
    adi_common_Device_t common;         /*!< Common layer structure */
    adi_fpga9025_Info_t devStateInfo;   /*!< ADRV9025 run time state information container */
    uint32_t            memoryPageSize; /*!< The current page size used when reading/writing RAM */
}                       adi_fpga9025_Device_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9025_TYPES_H_ */
