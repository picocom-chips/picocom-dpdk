/**
 * \file adi_ad9528_types.h
 * \brief Contains enum and structure data types for all AD9528 function calls
 */
/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9025 API license, for more information
* see the "LICENSE.pdf" file in this zip file.
*/
#ifndef _ADI_AD9528_TYPES_H_
#define _ADI_AD9528_TYPES_H_

#include <stdint.h>
#include "adi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADI_AD9528_NUM_OUTPUT_CHANNELS  14
#define ADI_AD9528_NUMBER_SPI_RETRY     200
#define ADI_AD9528_PLL_DEBOUNCE_TIME_MS 50
#define ADI_AD9528_PLL_DEBOUNCE_INT_MS  10
#define ADI_AD9528_REG508_STATUS_MASK   0xEF /* Mask bit 4: Both REFA/REFB missing since this is not set in lockStatusExpectedValue */

/**
 * \brief Enum to select what source outputs from each AD9528 output channel
 */
typedef enum adi_ad9528_OutSourceSel
{
    ADI_AD9528_CHANNEL_DIV      = 0,  /*!< Channel divisor output select */
    ADI_AD9528_PLL1_OUTPUT      = 1,  /*!< VCXO output select */
    ADI_AD9528_SYSREF           = 2,  /*!< SYSREF output select */
    ADI_AD9528_INV_PLL1_OUTPUT  = 5   /*!< VCXO inverted output select */

} adi_ad9528_OutSourceSel_e;

/**
 * \brief Enum to select what output buffer standard is used for the clock 
 *  outputs
 */
typedef enum adi_ad9528_OutBufferControl
{
    ADI_AD9528_LVDS,        /*!< LVDS output buffer select */
    ADI_AD9528_LVDS_BOOST,  /*!< LVDS boost output buffer select */
    ADI_AD9528_HSTL         /*!< HSTL output buffer select */

} adi_ad9528_OutBufferControl_e;

/**
 * \brief Enum to select the clock input buffer mode
 */
typedef enum adi_ad9528_RefBuffer
{
    ADI_AD9528_DISABLED,               /*!< Disabled input buffer select */
    ADI_AD9528_SINGLE_ENDED,           /*!< Single-ended input buffer select */
    ADI_AD9528_NEG_SINGLE_ENDED,       /*!< Negative single-ended input buffer select */
    ADI_AD9528_DIFFERENTIAL            /*!< Differential input buffer select */

} adi_ad9528_RefBuffer_e;

/**
 * \brief Enum to select the SYSREF output source
 */
typedef enum adi_ad9528_SysrefSourceSelection
{
    ADI_AD9528_EXTERNAL,        /*!< External SYSREF source select */
    ADI_AD9528_EXT_RESAMPLED,   /*!< External resampled SYSREF source select */
    ADI_AD9528_INTERNAL         /*!< Internal SYSREF source select */

} adi_ad9528_SysrefSourceSelection_e;

/**
 * \brief Enum to choose the SYSREF pattern mode
 */
typedef enum adi_ad9528_SysrefPatternMode
{
    ADI_AD9528_NSHOT,       /*!< 'N' shot SYSREF pattern mode select */
    ADI_AD9528_CONTINUOUS,  /*!< Continuous SYSREF pattern mode select */
    ADI_AD9528_PRBS,        /*!< PRBS SYSREF pattern mode select */
    ADI_AD9528_STOP         /*!< Stop select */

} adi_ad9528_SysrefPatternMode_e;

/**
 * \brief Enum to select the SYSREF input pin mode
 */
typedef enum adi_ad9528_SysrefPinEdgeMode
{
    ADI_AD9528_LEVEL_ACTIVE_HIGH,   /*!< Active high level input mode select */
    ADI_AD9528_LEVEL_ACTIVE_LOW,    /*!< Active low level input mode select */
    ADI_AD9528_RISING_EDGE,         /*!< Rising edge input mode select */
    ADI_AD9528_FALLING_EDGE         /*!< Falling edge input mode select */

} adi_ad9528_SysrefPinEdgeMode_e;

/**
 * \brief Enum to select the SYSREF output number of pulses for NSHOT mode
 */
typedef enum adi_ad9528_SysrefNshotMode
{
    ADI_AD9528_ONE_PULSE = 0,          /*!< Single (1) pulse NSHOT mode select */
    ADI_AD9528_TWO_PULSES = 2,         /*!< Two (2) pulse NSHOT mode select */
    ADI_AD9528_FOUR_PULSES = 3,        /*!< Four (4) pulse NSHOT mode select */
    ADI_AD9528_SIX_PULSES = 4,         /*!< Six (6) pulse NSHOT mode select */
    ADI_AD9528_EIGHT_PULSES = 5        /*!< Eight (8) pulse NSHOT mode select */

} adi_ad9528_SysrefNshotMode_e;

/**
 * \brief Enum to select how a SYSREF is requested
 */
typedef enum adi_ad9528_SysrefRequestMethod
{
    ADI_AD9528_SPI,     /*!< SPI mode request for SYSREF */
    ADI_AD9528_PIN      /*!< Pin mode request for SYSREF */

} adi_ad9528_SysrefRequestMethod_e;

/**
* \brief Structure for use in adi_ad9528_InitStructConfig function
*/
typedef struct adi_ad9528_ClockFrequencySettings
{
    uint32_t vcxoFrequency_Hz;
    uint32_t refAFrequency_Hz;
    uint32_t outputClock_Hz[ADI_AD9528_NUM_OUTPUT_CHANNELS];
    adi_ad9528_OutSourceSel_e outSource[ADI_AD9528_NUM_OUTPUT_CHANNELS];

} adi_ad9528_ClockFrequencySettings_t;

/**
 * \brief Structure to hold AD9528 PLL1 settings
 */
typedef struct adi_ad9528_Pll1Settings
{
    uint32_t refA_Frequency_Hz;
    uint16_t refA_Divider;
    adi_ad9528_RefBuffer_e refA_bufferCtrl;

    uint32_t refB_Frequency_Hz;
    uint16_t refB_Divider;
    adi_ad9528_RefBuffer_e refB_bufferCtrl;

    uint32_t vcxo_Frequency_Hz;
    adi_ad9528_RefBuffer_e vcxoBufferCtrl;

    uint16_t nDividerPll1;

} adi_ad9528_Pll1Settings_t;

/**
 * \brief Data structure to hold SPI settings for all system device types
 */
typedef struct adi_ad9528_SpiSettings
{
    uint8_t msbFirst;               /*!< 1 = MSBFirst, 0 = LSBFirst */
    uint8_t autoIncAddrUp;          /*!< Not implemented. For SPI Streaming, set address increment direction. 1= next addr = addr+1, 0:addr = addr-1 */
    uint8_t fourWireMode;           /*!< 1: Use 4-wire SPI, 0: 3-wire SPI (SDIO pin is bidirectional). NOTE: ADI's FPGA platform always uses 4-wire mode. */

} adi_ad9528_SpiSettings_t;

/**
 * \brief Structure to hold AD9528 PLL2 settings
 */
typedef struct adi_ad9528_Pll2Settings
{
    uint8_t rfDivider;      /*!< VCO divider: Valid range (3,4,5) */
    uint16_t n2Divider;     /*!< PLL2 N2 Divider */
    uint8_t r1Divider;      /*! PLL2 R1 Divider */
    uint8_t totalNdiv;      /*!< NDiv = 4*Bdiv + Adiv //Bdiv valid range (3 to 63), Adiv valid range (0-3) */

} adi_ad9528_Pll2Settings_t;

/**
 * \brief Structure to hold AD9528 Output Clock settings
 */
typedef struct adi_ad9528_OutputSettings
{
    uint16_t outPowerDown;                                                          /*!< bit per output, if 1 power down that output */
    adi_ad9528_OutSourceSel_e outSource[ADI_AD9528_NUM_OUTPUT_CHANNELS];            /*!< CHANNEL_DIV, PLL1_OUTPUT, SYSREF, INV_PLL1_OUTPUT */
    adi_ad9528_OutBufferControl_e outBufferCtrl[ADI_AD9528_NUM_OUTPUT_CHANNELS];    /*!< LVDS, LVDS_BOOST, HSTL */
    uint8_t outAnalogDelay[ADI_AD9528_NUM_OUTPUT_CHANNELS];                         /*!< bit[4] enables fine analog delay & adds 600ps delay. bits[3:0] are find delay steps, 31 ps each */
    uint8_t outDigitalDelay[ADI_AD9528_NUM_OUTPUT_CHANNELS];                        /*!< 6 bits, 1/2 clock resolution @ channel div input frequency */
    uint16_t outChannelDiv[ADI_AD9528_NUM_OUTPUT_CHANNELS];                          /*!< 8 bit channel divider. Valid values 1-256. Register written with (value - 1)  */
    uint32_t outFrequency_Hz[ADI_AD9528_NUM_OUTPUT_CHANNELS];                       /*!< output clock frequency per clock output */

} adi_ad9528_OutputSettings_t;

/**
* \brief Structure to hold AD9528 SYSREF output settings
*/
typedef struct adi_ad9528_SysrefSettings
{
    adi_ad9528_SysrefRequestMethod_e sysrefRequestMethod;
    adi_ad9528_SysrefSourceSelection_e sysrefSource;
    adi_ad9528_SysrefPinEdgeMode_e sysrefPinEdgeMode;
    adi_ad9528_RefBuffer_e sysrefPinBufferMode;
    adi_ad9528_SysrefPatternMode_e sysrefPatternMode;
    adi_ad9528_SysrefNshotMode_e sysrefNshotMode;
    uint16_t sysrefDivide;

} adi_ad9528_SysrefSettings_t;

/**
 * \brief Structure to hold AD9528 run time state information
 */
typedef struct adi_ad9528_Info
{
    /* uint8_t pllLocked;*/
    /* uint8_t programmed;*/
    uint8_t initialized;
    uint8_t swModeEnabled;
    uint32_t deviceRevision;
    uint32_t deviceId;
    adi_ad9528_SysrefPatternMode_e sysrefPatternMode;
    uint8_t sysrefCtrlReg403Init; /*!< Initialize sets this to value that SPI reg x403 was initialized to for SYSREF Control, later used by SysrefRequest() */

} adi_ad9528_Info_t;

/**
* \brief Structure to hold AD9528 init settings
*/
typedef struct adi_ad9528_Init
{
    adi_ad9528_SpiSettings_t    spiSettings;
    adi_ad9528_Pll1Settings_t   pll1Settings;
    adi_ad9528_Pll2Settings_t   pll2Settings;
    adi_ad9528_OutputSettings_t outputSettings;
    adi_ad9528_SysrefSettings_t sysrefSettings;
    uint32_t                    pllLockTimeout_ms; /*!<If non-zero, adi_ad9528_Initialize will block waiting for PLLs to lock or timeout occurs. If set to zero, PLL lock status is not checked. */
    uint32_t                    deviceId;

} adi_ad9528_Init_t;

/**
 * \brief Structure to hold AD9528 device settings
 */
typedef struct adi_ad9528_Device
{
    adi_common_Device_t      common; /*!< Common layer structure */ 
    adi_ad9528_Info_t       devStateInfo;   /*!< AD9528 run time state information */
    uint8_t lockStatusExpectedValue;        /*!< Stored during initialization based on config and used to determine correct PLLs are locked */
} adi_ad9528_Device_t;

#ifdef __cplusplus
}
#endif

#endif /* _ADI_AD9528_TYPES_H_ */
