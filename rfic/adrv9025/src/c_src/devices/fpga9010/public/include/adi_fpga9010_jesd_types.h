/*!
* \file adi_fpga9010_jesd_types.h
* \brief Contains FPGA9010 JESD enum and struct definitions
*
* ADRV9010 API Version: $ADI_FPGA9010_API_VERSION$
*
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_JESD_TYPES_H_
#define _ADI_FPGA9010_JESD_TYPES_H_


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#define ADI_FPGA9010_NUM_LANES 8
#define ADI_FPGA9010_NUM_OF_DEFRAMERS 3
#define ADI_FPGA9010_NUM_OF_FRAMERS 2

#define ADI_FPGA9010_2P02_GHZ   2027520
#define ADI_FPGA9010_2P53_GHZ   2534400
#define ADI_FPGA9010_3_GHZ      3041280
#define ADI_FPGA9010_4P05_GHZ   4055040
#define ADI_FPGA9010_4P91_GHZ   4915200
#define ADI_FPGA9010_5_GHZ      5068800
#define ADI_FPGA9010_6P08_GHZ   6082560
#define ADI_FPGA9010_6P14_GHZ   6144000
#define ADI_FPGA9010_7_GHZ      7372800
#define ADI_FPGA9010_8_GHZ      8110080
#define ADI_FPGA9010_9P2_GHZ    9216000
#define ADI_FPGA9010_9_GHZ      9830400
#define ADI_FPGA9010_10_GHZ     10137600
#define ADI_FPGA9010_11_GHZ     11059200
#define ADI_FPGA9010_12P16_GHZ  12165120
#define ADI_FPGA9010_12P28_GHZ  12288000
#define ADI_FPGA9010_14_GHZ     14745600
#define ADI_FPGA9010_16_GHZ     16220160

#define ADI_FPGA9010_61P44_MHZ  61440
#define ADI_FPGA9010_122P88_MHZ 122880
#define ADI_FPGA9010_153P6_MHZ  153600
#define ADI_FPGA9010_184P32_MHZ 184320
#define ADI_FPGA9010_245P76_MHZ 245760
#define ADI_FPGA9010_307P2_MHZ  307200
#define ADI_FPGA9010_491P52_MHZ 491520
    
/**
* \brief Enumerated list of DRP mask values
*/
typedef enum adi_fpga9010_DrpMask
{
    ADI_FPGA9010_TXCLK25DIV_MASK        = 0xF800,
    ADI_FPGA9010_TXPHDLY_CFG1_MASK      = 0xFFFF,
    ADI_FPGA9010_TXPI_CFG3_MASK         = 0x0040,
    ADI_FPGA9010_TX_PROGDIV_CFG_MASK    = 0xFFFF,
    ADI_FPGA9010_RXCLK25DIV_MASK        = 0x00F8,
    ADI_FPGA9010_PMA_RSV1_MASK          = 0xFFFF,
    ADI_FPGA9010_RXCDR_CFG2_MASK        = 0xFFFF,
    ADI_FPGA9010_RXDFE_GC_CFG1_MASK     = 0xFFFF,
    ADI_FPGA9010_RXPI_CFG4_MASK         = 0x0200,
    ADI_FPGA9010_RXPI_CFG5_MASK         = 0x0100,
    ADI_FPGA9010_RX_EN_HI_LR_MASK       = 0x0400,
    ADI_FPGA9010_RX_WIDEMODE_CDR_MASK   = 0x0004,
    ADI_FPGA9010_RX_PROGDIV_CFG_MASK    = 0xFFFF,
    ADI_FPGA9010_QPLL_N_MASK            = 0x00FF,
    ADI_FPGA9010_QPLL_M_MASK            = 0x0F80,
    ADI_FPGA9010_QPLL_LPF_MASK          = 0x03FF,
    ADI_FPGA9010_QPLL_CFG4_MASK         = 0xFFFF,
    ADI_FPGA9010_QPLL_CP_MASK           = 0x03FF,
    ADI_FPGA9010_QPLL_FBDIV_MASK        = 0x00FF,
    ADI_FPGA9010_QPLL_LOCK_CFG_MASK     = 0xFFFF,
    ADI_FPGA9010_QPLL_LOCK_CFG_G3_MASK  = 0x03FF,
    ADI_FPGA9010_QPLL_REFCLK_DIV_MASK   = 0x0F80
} adi_fpga9010_DrpMask_e;

/**
* \brief Enumerated list of DRP mask values
*/
typedef enum adi_fpga9010_DrpAddress
{
    ADI_FPGA9010_TXCLK25DIV_ADDRESS             = 0x007A,
    ADI_FPGA9010_TXPHDLY_CFG1_ADDRESS           = 0x006F,
    ADI_FPGA9010_TXPI_CFG3_ADDRESS              = 0x009C,
    ADI_FPGA9010_TX_PROGDIV_CFG_ADDRESS         = 0x003E,
    ADI_FPGA9010_RXCLK25DIV_ADDRESS             = 0x006D,
    ADI_FPGA9010_PMA_RSV1_ADDRESS               = 0x0095,
    ADI_FPGA9010_RXCDR_CFG2_ADDRESS             = 0x0010,
    ADI_FPGA9010_RXDFE_GC_CFG1_ADDRESS          = 0x00A0,
    ADI_FPGA9010_RXPI_CFG4_ADDRESS              = 0x009D,
    ADI_FPGA9010_RXPI_CFG5_ADDRESS              = 0x009D,
    ADI_FPGA9010_RX_EN_HI_LR_ADDRESS            = 0x0052,
    ADI_FPGA9010_RX_WIDEMODE_CDR_ADDRESS        = 0x0066,
    ADI_FPGA9010_RX_PROGDIV_CFG_ADDRESS         = 0x00C6,
    ADI_FPGA9010_QPLLCLK0_N_ADDRESS             = 0x0014,
    ADI_FPGA9010_QPLLCLK0_M_ADDRESS             = 0x0018,
    ADI_FPGA9010_QPLLCLK0_LPF_ADDRESS           = 0x0019,
    ADI_FPGA9010_QPLLCLK0_CFG4_ADDRESS          = 0x0030,
    ADI_FPGA9010_QPLLCLK0_CP_ADDRESS            = 0x0016,
    ADI_FPGA9010_QPLLCLK0_FBDIV_ADDRESS         = 0x0014,
    ADI_FPGA9010_QPLLCLK0_LOCK_CFG_ADDRESS      = 0x0012,
    ADI_FPGA9010_QPLLCLK0_LOCK_CFG_G3_ADDRESS   = 0x001D,
    ADI_FPGA9010_QPLLCLK0_REFCLK_DIV_ADDRESS    = 0x0018,
    ADI_FPGA9010_QPLLCLK1_N_ADDRESS             = 0x0094,
    ADI_FPGA9010_QPLLCLK1_M_ADDRESS             = 0x0098,
    ADI_FPGA9010_QPLLCLK1_CFG4_ADDRESS          = 0x00B0,
    ADI_FPGA9010_QPLLCLK1_CP_ADDRESS            = 0x0096,
    ADI_FPGA9010_QPLLCLK1_LOCK_CFG_ADDRESS      = 0x0092,
    ADI_FPGA9010_QPLLCLK1_LOCK_CFG_G3_ADDRESS   = 0x009D,
    ADI_FPGA9010_QPLLCLK1_LPF_ADDRESS           = 0x0099
} adi_fpga9010_DrpAddress_e;

/**
* \brief Enumerated list of clk sources available to the Serializer/deserializer 
*/
typedef enum adi_fpga9010_LaneClkSel
{
    ADI_FPGA9010_CPLL = 0x0,
    ADI_FPGA9010_QPLLCLK0 = 0x3,
    ADI_FPGA9010_QPLLCLK1 = 0x2
} adi_fpga9010_LaneClkSel_e;
    
    /**
* \brief Enumerated list of clk sources available to the Serializer/deserializer 
*/
typedef enum adi_fpga9010_Qpll_Quad
{
    ADI_FPGA9010_QPLL_QUAD0 = 0x1,
    ADI_FPGA9010_QPLL_QUAD1 = 0x2
} adi_fpga9010_Qpll_Quad_e;

/**
* \brief Enumerated list of Gth Serializer/deserializer each is identified by a separate bit
*/
typedef enum adi_fpga9010_LaneSel
{
    ADI_FPGA9010_LANE_0 = 0x1,          /*!Gth serializer/deserializer Lane 1 */
    ADI_FPGA9010_LANE_1 = 0x2,          /*!Gth serializer/deserializer Lane 2 */
    ADI_FPGA9010_LANE_2 = 0x4,          /*!Gth serializer/deserializer Lane 3 */
    ADI_FPGA9010_LANE_3 = 0x8,          /*!Gth serializer/deserializer Lane 4 */
    ADI_FPGA9010_LANE_4 = 0x10,         /*!Gth serializer/deserializer Lane 5 */
    ADI_FPGA9010_LANE_5 = 0x20,         /*!Gth serializer/deserializer Lane 6 */
    ADI_FPGA9010_LANE_6 = 0x40,         /*!Gth serializer/deserializer Lane 7 */
    ADI_FPGA9010_LANE_7 = 0x80          /*!Gth serializer/deserializer Lane 8 */
} adi_fpga9010_LaneSel_e;

/**
*   \brief Enumerated list of JESD204C interrupts each identified by a separate bit
*/
typedef enum adi_fpga9010_Jesd204cIrq
{
    ADI_FPGA9010_GLOBAL                 = 0x1, /*!Global Interrupt Enable*/
    ADI_FPGA9010_SYSREF_RECEIVED        = 0x2, /*!Interrupt Enable SYSREF Received*/
    ADI_FPGA9010_SYSREF_ERROR           = 0X4, /*!Interrupt Enable SYSREF Error*/
    ADI_FPGA9010_LOSS_SYNC_HEADER_LOCK  = 0x10, /*!Interrupt Enable Loss of 64b66b Sync Header Lock*/
    ADI_FPGA9010_LOSS_MB_LOCK           = 0x20, /*!Interrupt Enable Loss of Multi-block Lock*/
    ADI_FPGA9010_BLOCK_SYNC_ERROR       = 0x40, /*!Interrupt Enable Block Sync Error*/
    ADI_FPGA9010_MB_ERROR               = 0x80, /*!Interrupt Enable Multi-block Error*/
    ADI_FPGA9010_CRC_ERROR              = 0x100, /*!Interrupt Enable CRC Error*/
    ADI_FPGA9010_FEC_ERROR              = 0x200, /*!Interrupt Enable FEC Error*/
    ADI_FPGA9010_OVERFLOW_ERROR         = 0x400 /*!Interrupt Enable Overflow Error*/
}adi_fpga9010_Jesd204cIrq_e;

/**
* \brief Enumerated list of Gth Serializer/deserializer each is identified by a separate bit
*/
typedef struct adi_fpga9010_SerializerCfg
{
    uint8_t chnl;                           /*! Identifies the lane to be configured by these settings 0..7 */
    uint8_t cpllRefClkSel;                  /*! Only needed for Cpll which is not used */
    adi_fpga9010_LaneClkSel_e txPllClkSel;  /*! Selects the PLL to drive the transmitter data path. valid values from adi_fpga9010_PllClkSel_e */
    /* Rx Configs &TxConfigs */
    uint8_t rate;                           /*! Sets the final divider for the Channel receiver. The settings are: 000: Use RXOUT_DIV attributes 001: Divide by 1 010: Divide by 2 011: Divide by 4 100: Divide by 8 101: Divide by 16 110: Divide by 1 111: Divide by 1 */
    uint8_t encoder8b10bEnable;             /*! 1: enable the 8b10b encoder in the Channel 0 transmitter - this is needed for JESD204B operation. 0: bypass the 8b10b encoder - this is needed for JESD204C operation.*/
    uint8_t polarity;                       /*! When set to 1, the corresponding transmit channel is inverted. When cleared to 0, the channel is not inverted. */
    uint8_t powerDown;                      /*! 00: P0 (normal operation) 01: P0s (low recovery time power down) 10: P1 (longer recovery time; Receiver Detection still on) 11: P2 (lowest power state) Attributes can control the transition times between these power-down states. */
    /* Tx Config */
    uint8_t precursor;                      /*! Transmitter post-cursor TX pre-emphasis control */
    uint8_t postcursor;                     /*! Transmitter post-cursor TX pre-emphasis control.  */
    uint8_t diffCtrl;                       /*! Driver Swing/ Amplitude Control. */
    uint16_t txClk25Div;                    /*! RefClk / 25 - 1 written to DRP registers */
    uint16_t txPiCfg3;                      /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t txPhdlyCfg1;                   /*! JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t txProgdivCfg;                  /*! JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */

} adi_fpga9010_SerializerCfg_t;

typedef struct adi_fpga9010_DeserializerCfg
{
    uint8_t chnl;                           /*!Identifies the lane to be configured by these settings. 0..7 */
    adi_fpga9010_LaneClkSel_e rxPllClkSel;  /*! Selects the PLL to drive the receiver data path valid values from adi_fpga_qpllClkSel */
    //Rx Configs &TxConfigs;
    uint8_t rate;                           /*! This bit field sets the final divider for the Channel receiver.  valid values form adi_fpga9010_QpllFDVals_e. */
    uint8_t encoder8b10bEnable;             /*! 1: enable the 8b10b encoder in the Channel 0 transmitter - this is needed for JESD204B operation. 0: bypass the 8b10b encoder - this is needed for JESD204C operation.*/
    uint8_t polarity;                       /*! When set to 1, the corresponding transmit channel is inverted. When cleared to 0, the channel is not inverted. */
    uint8_t powerDown;                      /*! 00: P0 (normal operation) 01: P0s (low recovery time power down) 10: P1 (longer recovery time; Receiver Detection still on) 11: P2 (lowest power state) Attributes can control the transition times between these power-down states.*/
    //Rx Config
    uint8_t rxDfeLpmEn;                     /*! Controls a receive channel's rx_dfelpm_en signal. When set to 1, the LPM equalizer is enabled. When cleared to 0, the DFE equalizer is enabled.. */
    uint8_t cdrSetting;                     /*! TBD */
    uint16_t rxClk25Div;                    /*! RefClk / 25 - 1 written to DRP registers */
    uint16_t pmaRsv1;                       /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxCdrCfg2;                     /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxDfeGcCfg1;                   /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxPiCfg4;                      /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxPiCfg5;                      /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxEnHiLr;                      /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxWidemodeCdr;                 /*! JESD204B & JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
    uint16_t rxProgdivCfg;                  /*! JESD204C DRP config register. Value based on QPLL clock frequency and lane rate */
} adi_fpga9010_DeserializerCfg_t;

/**
*  \brief Enum to select desired FPGA deframer
*/
typedef enum adi_fpga9010_DeframerSel
{
    ADI_FPGA9010_DEFRAMER_0   = 1,    /*< Deframer 0 selected */
    ADI_FPGA9010_DEFRAMER_1   = 2,    /*< Deframer 1 selected */
    ADI_FPGA9010_DEFRAMER_2   = 4,    /*< Deframer 2 selected */
    ADI_FPGA9010_DEFRAMER_ALL = 7  /*< All deframers selected */
} adi_fpga9010_DeframerSel_e;

/**
*  \brief Enum to select desired FPGA framer
*/
typedef enum adi_fpga9010_FramerSel
{
    ADI_FPGA9010_FRAMER_0   = 1, /*< Framer 0 selected */
    ADI_FPGA9010_FRAMER_1   = 2, /*< Framer 1 selected */
    ADI_FPGA9010_FRAMER_ALL = 3  /*< All framers selected */
} adi_fpga9010_FramerSel_e;

typedef struct adi_fpga9010_DeframerCfg
{
    /* Common Data */
    uint8_t laneXbar[ADI_FPGA9010_NUM_LANES];           /*! Indices correspond to Lane XBar outputs. Values correspond to Lane XBar inputs */
    uint8_t sysRefDelay;                                /*! Add additional delay to SYSREF re-alignment of LMFC counter 1111 = 15 core_clk cycles */
    uint8_t subclassV;                                  /*! JESD204b sublcass: Subclass 2 = 0x10 Subclass 1 = 0x01 Subclass 0 = 0x00. JESD204c subclass: 0 = Subclass 0; 1 = Subclass 1 */
    uint8_t lanesInUse;                                 /*! Each bit corresponds to a single lane, when set to 1 lane is active. Due to Lane XBars will always fill from bit 0 */
    
    /* JESD204B */
    uint8_t bankId[ADI_FPGA9010_NUM_LANES];             /*! JESD204b Configuration Bank ID extension to Device ID. Read only, captured by ILA sequence */
    uint8_t cfgLaneId[ADI_FPGA9010_NUM_LANES];          /*! Read only, captured by ILA sequence  */
    uint8_t scramblingEn;                               /*! Set to 1 to enable scrambling. Clear to disable */
    uint16_t cfgF;                                      /*! Octets per frame. Register programmed with value - 1 */
    uint8_t cfgK;                                       /*! Frames per multiframe. Register programmed with value - 1 */
    uint8_t ilaNp[ADI_FPGA9010_NUM_LANES];              /*! N' (Totals bits per Sample) */
    uint8_t ilaN[ADI_FPGA9010_NUM_LANES];               /*! N Converter Resolution */
    uint8_t ilaS[ADI_FPGA9010_NUM_LANES];               /*! Number of samples per converter per frame. Read only, captured by ILA sequence. Register programmed with value - 1 */
    uint8_t ilaM[ADI_FPGA9010_NUM_LANES];               /*! Number of converters per device. Read only, captured by ILA sequence. Register programmed with value - 1 */
    uint16_t rxBufferDly;                               /*! Used with RX Buffer Adjust to minimize latency */
    uint16_t rxBufferAdj[ADI_FPGA9010_NUM_LANES];       /*! Used with RX Buffer Delay to minimize latency. Read only, captured by ILA sequence  */
    uint8_t errReportingDisable;                        /*! Disable Error Reporting Using SYNC Interface */
    uint8_t ilaSupportEn;                               /*! ILA Support Enable */
    uint8_t sysRefAlways;                               /*! SYSREF Always 1 = Core re-aligns LMFC counter on all SYSREF events */
    uint8_t sysRefRequiredOnResync;                     /*! 1 = A SYSREF event is required following a Link Re-Sync event */
    
    /* JESD204C */
    uint8_t enableCmdInterface;                         /*! 1 = Enables AXI4-Stream Cmd interface; 0 = Cmd words will be zeroed */
    uint8_t enableDataInterface;                        /*! 1 = Enables AXI4-Stream Data interface; 0 = Link will be transmitting scrambled zeros */
    uint8_t cfgE;                                       /*! CTRL_MB_IN_EMB- Number of multi-blocks in an extended multi-block. Programmed with actual value (0 is invalid) */
    uint8_t ctrlMetaMode;                               /*! 0 = Cmd; 1 = CRC; 2 = FEC [TBD] */
    uint8_t ctrlRxBufAdv;                               /*! Advance the release of the receiver buffer by N 64-bit words */
    uint8_t ctrlRxMBlockTh;                             /*! MB lock threshold */
    uint16_t ctrlIrq;                                   /*! Bit mask to enable/disable individual interrupts. Bit 0 is Global Interrupt Enable */
    
} adi_fpga9010_DeframerCfg_t;

typedef struct adi_fpga9010_FramerCfg
{
    /* Common data */
    uint8_t laneXbar[ADI_FPGA9010_NUM_LANES];           /*! Indices correspond to Lane XBar outputs. Values correspond to Lane XBar inputs */
    uint8_t sysRefDelay;                                /*! Add additional delay to SYSREF re-alignment of LMFC counter 1111 = 15 core_clk cycles */
    uint8_t subclassV;                                  /*! JESD204b sublcass: Subclass 2 = 0x10 Subclass 1 = 0x01 Subclass 0 = 0x00. JESD204c subclass: 0 = Subclass 0; 1 = Subclass 1 */
    uint8_t lanesInUse;                                 /*! Each bit corresponds to a single lane, when set to 1 lane is active. Due to Lane XBars will always fill from bit 0 */
    
    /* JESD204B */
    uint8_t deviceId;                                   /*! JESD204b Configuration Device ID.  Sets value for all lanes */
    uint8_t bankId;                                     /*! JESD204b Configuration Bank ID extension to Device ID. Sets value for all lanes */
    uint8_t scramblingEn;                               /*! Set to 1 to enable scrambling. Clear to disable */
    uint16_t ilaMultiFrames;                            /*! Multiframes in the Transmitted ILAS. Register programmed with value - 1 */
    uint16_t cfgF;                                      /*! Octets per frame. Register programmed with value - 1 */
    uint8_t cfgK;                                       /*! Frames per multiframe. Register programmed with value - 1 */
    uint8_t ilaM;                                       /*! Number of converters per device. Sets value for all lanes. Register programmed with value - 1 */
    uint8_t ilaN;                                       /*! Converter resolution.  Sets value for all lanes. Register programmed with value - 1 */
    uint8_t ilaCs;                                      /*! Control bits per sample.  Sets value for all lanes */
    uint8_t ilaNp;                                      /*! Total bits per sampele.  Sets value for all lanes. Register programmed with value - 1 */
    uint8_t ilaS;                                       /*! Samples per converter per frame.  Sets value for all lanes. Register programmed with value - 1 */
    uint8_t ilaCf;                                      /*! Control words per frame.  Sets value for all lanes */
    uint8_t ilaHd;                                      /*! High density format.  Sets value for all lanes */
    uint8_t ilaSupportEn;                               /*! ILA Support Enable */
    uint8_t sysRefAlways;                               /*! SYSREF Always 1 = Core re-aligns LMFC counter on all SYSREF events */
    uint8_t sysRefRequiredOnResync;                     /*! 1 = A SYSREF event is required following a Link Re-Sync event */
    
    /* JESD204C */
    uint8_t enableCmdInterface;                         /*! 1 = Enables AXI4-Stream Cmd interface; 0 = Cmd words will be zeroed */
    uint8_t enableDataInterface;                        /*! 1 = Enables AXI4-Stream Data interface; 0 = Link will be transmitting scrambled zeros */
    uint8_t cfgE;                                       /*! CTRL_MB_IN_EMB- Number of multi-blocks in an extended multi-block. Programmed with actual value (0 is invalid) */
    uint8_t ctrlMetaMode;                               /*! 0 = Cmd; 1 = CRC; 2 = FEC [TBD] */
    uint16_t ctrlIrq;                                   /*! Bit mask to enable/disable individual interrupts. Bit 0 is Global Interrupt Enable */
    
} adi_fpga9010_FramerCfg_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ADI_FPGA9010_JESD_TYPES_H_ */
