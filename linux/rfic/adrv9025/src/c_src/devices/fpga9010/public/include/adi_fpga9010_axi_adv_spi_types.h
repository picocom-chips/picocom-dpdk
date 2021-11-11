/**
* \file adi_fpga9010.h
* \brief Contains top level fpga9010 related function prototypes for
*        adi_fpga9010.c
*
* FPGA9010 API Version: $ADI_FPGA9010_API_VERSION$
*/

/**
 * Copyright 2015 - 2020 Analog Devices Inc.
 * Released under the FPGA9010 API license, for more information
 * see the "LICENSE.pdf" file in this zip file.
 */

#ifndef _ADI_FPGA9010_AXI_ADV_SPI_TYPES_H_
#define _ADI_FPGA9010_AXI_ADV_SPI_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct adi_fpga9010_AxiAdvSpiVersion
    {
        uint8_t module_version_major;               /*!< Global Interrupt Enable. Allows passing all individually enabled interrupts to the interrupt controller. When set to: 0 = Disabled. 1 = Enabled.*/
        uint16_t module_version_minor;              /*!< Global Interrupt Enable. Allows passing all individually enabled interrupts to the interrupt controller. When set to: 0 = Disabled. 1 = Enabled.*/
    } adi_fpga9010_AxiAdvSpiVersion_t;

//    typedef struct adi_fpga9010_AxiAdvSpiDgier
//    {
//        uint8_t gie;                              /*!< Global Interrupt Enable. Allows passing all individually enabled interrupts to the interrupt controller. When set to: 0 = Disabled. 1 = Enabled.*/
//    } adi_fpga9010_AxiAdvSpiDgier_t;


    typedef struct adi_fpga9010_AxiAdvSpiIpisr
    {
        uint8_t tx_fifo_half_empty;                 /*!< Transmit FIFO Half Empty.*/
        uint8_t drr_overrun;                        /*!< Data Receive Register/FIFO Overrun.*/
        uint8_t drr_full;                           /*!< Data Receive Register/FIFO Full.*/
        uint8_t dtr_empty;                          /*!< Data Transmit Register/FIFO Empty.  */
        uint8_t modf;                               /*!<  Mode Fault Error.  */
    } adi_fpga9010_AxiAdvSpiIpisr_t;

    typedef struct adi_fpga9010_AxiAdvSpiIpier
    {
        uint8_t tx_fifo_half_empty_ien;             /*!< Transmit FIFO Half Empty IRQ Enable. 0 = Disabled. 1 = Enabled..*/
        uint8_t drr_overrun;                        /*!< Data Receive Register/FIFO Overrun IRQ Enable. 0 = Disabled. 1 = Enabled.*/
        uint8_t drr_full;                           /*!< Data Receive Register/FIFO Full IRQ Enable. 0 = Disabled. 1 = Enabled.*/
        uint8_t dtr_empty_ien;                      /*!< Data Transmit Register/FIFO Empty IRQ Enable. 0 = Disabled. 1 = Enabled.  */
        uint8_t modf_ien;                           /*!< Mode Fault Error IRQ Enable. 0 = Disabled. 1 = Enabled.  */
    } adi_fpga9010_AxiAdvSpiIpier_t;



 /**
 * \brief Data structure to hold SPI settings for all system device types
 */
    typedef struct adi_fpga9010_AxiAdvSpiSpicr
    {
        uint8_t lsbFirst;                           /*!< 1 = MSB First, 0 = LSB First Bit order for SPI transaction. Default = 0 (msbFirst*/
        uint8_t mstr_inhibit;                       /*!< This bit inhibits master transactions. This bit has no effect on slave operation. Default = 1 (Disabled)*/
        uint8_t man_ss_en;                          /*!< Manual Slave Select Assertion Enable. Default = 1 (Disabled)*/
        uint8_t rx_fifo_reset;                      /*!< RX FIFO Reset. When written to 1, this bit forces a reset of the receive FIFO to the empty condition. Default = 0 (Disabled)*/
        uint8_t tx_fifo_reset;                      /*!< TX FIFO Reset. When written to 1, this bit forces a reset of the transmit FIFO to the empty condition. Default = 0 (Disabled)*/
        uint8_t cpha;                               /*!< Clock Phase. Setting this bit defines the default clock phase. */
        uint8_t cpol;                               /*!< Clock Polarity. When set to: 0 = Active-High clock; SCK idles Low. 1 = Active-Low clock; SCK idles High. */
        uint8_t master;                             /*!< Master Mode Select. When set to: 0 = Active-High clock; SCK idles Low. 1 = Active-Low clock; SCK idles High. */
        uint8_t spe;                                /*!< 1= SPI System Enable. */
        uint8_t loop;                               /*!< 0= Normal Operation; 1=The transmitter output is internally connected to the receiver input  */
    } adi_fpga9010_AxiAdvSpiSpicr_t;

/**
 * \brief Data structure to hold SPI settings for all system device types
 */
    typedef struct adi_fpga9010_AxiAdvSpiSpisr
    {
        uint8_t modf_flag;                     /*!< Mode Fault Error Flag.*/
        uint8_t tx_full;                       /*!< Transmit Full Flag. This bit is set high when the transmit FIFO is full.*/
        uint8_t tx_empty;                      /*!< Transmit Empty Flag. This bit is set high when the transmit FIFO is empty.*/
        uint8_t rx_full;                       /*!< Receive Full Flag. This bit is set high when the receive FIFO is full.*/
        uint8_t rx_empty;                      /*!< Receive Empty Flag. This bit is set high when the receive FIFO is empty.*/ 
    } adi_fpga9010_AxiAdvSpiSpisr_t;

    typedef struct adi_fpga9010_AxiAdvSpiFeatConfig
    {
        uint16_t clockDiv;               /*!< Advanced Feature Set Clock Divider.*/
        uint8_t threeWireTriPoint;         /*!< Advanced Feature Set Three Wire Tristate Point.*/
        uint8_t misoSampleSlip;         /*!< Advanced Feature Set MISO Sample Slip.*/
        uint8_t fourWire;               /*!< Advanced Feature Set Four Wire Mode.*/
        uint8_t lsbFirst;               /*!< Advanced Feature Set LSB First.*/
        uint8_t cpha;                   /*!< Advanced Feature Set Clock Phase.*/ 
        uint8_t cpol;                   /*!< Advanced Feature Set Clock Polarity.*/ 
        uint8_t enable;                 /*!< Advanced Feature Set Enable.*/ 
    } adi_fpga9010_AxiAdvSpiFeatConfig_t;



//    typedef struct adi_fpga9010_AxiAdvSpiSpidtr
//    {
//        uint8_t tx_data;                     /*!< Transmit Data. Data to be pushed into the TX Data FIFO.*/
//    } adi_fpga9010_AxiAdvSpiSpidtr_t;

//    typedef struct adi_fpga9010_AxiAdvSpiSpidrr
//    {
//        uint8_t rx_data;                     /*!< Transmit Data. Data to be pushed into the TX Data FIFO.*/
//    } adi_fpga9010_AxiAdvSpiSpidrr_t;


//    typedef struct adi_fpga9010_AxiAdvSpiSpissr
//    {
//        uint32_t slave_select;                     /*!< Slave Select. Active-Low, one-hot encoded slave select vector.*/
//    } adi_fpga9010_AxiAdvSpiSpissr_t;

//    typedef struct adi_fpga9010_AxiAdvSpiTxFIFOocy
//    {
//        uint8_t tx_fifo_occupancy;                     /*!< Transmit FIFO Occupancy. This field indicates the number of elements that are currently in the transmit FIFO..*/
//    } adi_fpga9010_AxiAdvSpiTxFIFOocy_t;

    typedef struct adi_fpga9010_axiAdvSpiSettings
    {
        adi_fpga9010_AxiAdvSpiVersion_t     spiModVersion;          /*!< axi_adv_spi module version */
        adi_fpga9010_AxiAdvSpiIpisr_t       spiIntStatus;           /*!< The IP Interrupt Status Register */
        adi_fpga9010_AxiAdvSpiIpier_t       spiIntEnable;           /*!<  Interrupt Enable Register */
        adi_fpga9010_AxiAdvSpiSpicr_t       spiCtrlRegSettings;     /*!< SPI settings data structure */
        adi_fpga9010_AxiAdvSpiSpisr_t       SpiStatus;              /*!< Holds settings for CLKPLL and reference clock */
        adi_fpga9010_AxiAdvSpiFeatConfig_t  advFeatSS[32];          /*!< Advanced Feature Configuration Register for Slave Select 0-31. */
    } adi_fpga9010_axiAdvSpiSettings_t;


#ifdef __cplusplus
}
#endif

#endif /* _ADI_FPGA9010_AXI_ADV_SPI_TYPES_H_ */
