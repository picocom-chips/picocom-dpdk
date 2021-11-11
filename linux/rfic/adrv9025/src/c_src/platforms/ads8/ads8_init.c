/**
* \file ads8_init.c
* \brief Contains ADI Transceiver Hardware Abstraction functions for hardware mode.
*        Analog Devices maintains and provides updates to this code layer for the ADS8 platform.
*        The end user should not modify this file or any code in this directory. The end user
*        may provide a similar platform layer that can be used in place of this platform layer, 
*        that uses the same function prototypes.
*/

/**
* \Page Disclaimer Legal Disclaimer
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ads8_init.h"
#include "ads8_spi.h"
#include "ads8_logging.h"
#include "ads8_timer.h"
#include "ads8_bbic_control.h"
#include "ads8_i2c.h"


static int32_t ads8_LogWriteHelper(void *devHalCfg, int32_t logLevel, const char *logMessage, ...)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    va_list args;
    va_start(args, logMessage);
    halError = ads8_LogWrite(devHalCfg, logLevel, logMessage, args);
    va_end(args);
    return halError;
}


/**
* \brief Opens all necessary files and device drivers for a specific device
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
*/
int32_t ads8_HwOpen(void *devHalCfg)
{
    adi_hal_Cfg_t *halCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    char logMessage[ADI_HAL_MAX_LOG_LINE];
    int32_t result = 0;

    logMessage[0] = 0;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->logCfg.interfaceEnabled > 0)
    {
        if (halCfg->logCfg.logFileName[0] == '\0')
        {
            halError = ads8_LogFileOpen(devHalCfg, "ads8_adihal.log");
        }
        else
        {
            halError = ads8_LogFileOpen(devHalCfg, NULL);
        }

        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
   
        result = snprintf(logMessage + strlen(logMessage), ADI_HAL_MAX_LOG_LINE, "ads8_LogFileOpen: device index %d\n", halCfg->spiCfg.chipSelectIndex);
        if (result < 0)
        {
            return (int32_t)ADI_HAL_LOGGING_FAIL;
        }
        
        halError = ads8_LogWriteHelper(devHalCfg, ADI_HAL_LOG_MSG, logMessage);
        
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
    }

    if (halCfg->spiCfg.interfaceEnabled > 0)
    {
        halError = ads8_SpiOpen(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
        
        halError = ads8_SpiInit(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
    }
    
    if (halCfg->bbicCfg.interfaceEnabled > 0)
    {
        halError = ads8_BbicOpen(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
        
        halError = ads8_BbicInit(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
    }
    
    if (halCfg->hwResetCfg.interfaceEnabled > 0)
    {
        /* ADS8 has nothing to open, as this interface is supported by the 
         * BBIC control interface */
        
        /* Verify BBIC control interface was enabled */
        if (halCfg->bbicCfg.interfaceEnabled == 0)
        {
            halError = ADI_HAL_GEN_SW;
            return halError;
        }
    }
    
    if (halCfg->i2cCfg.interfaceEnabled > 0)
    {
        halError = ads8_I2cOpen(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
        
        halError = ads8_I2cInit(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
    }
    
    if (halCfg->timerCfg.interfaceEnabled > 0)
    {
        halError = ads8_TimerOpen(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
        
        halError = ads8_TimerInit(devHalCfg);
        if (halError != (int32_t)ADI_HAL_OK)
        {
            return halError;
        }
    }
    
    /* ADS8 does not require any code to open /init timer support since using linux nanosleep function */
    
    return halError;
}

/**
* \brief Gracefully shuts down the the hardware closing any open resources
*        such as log files, I2C, SPI, GPIO drivers, timer resources, etc.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
*/
int32_t ads8_HwClose(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    halError = ads8_LogLevelSet(devHalCfg, ADI_HAL_LOG_NONE);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }

    halError = ads8_LogFileClose(devHalCfg);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }

    halError = ads8_SpiClose(devHalCfg);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }

    halError = ads8_BbicClose(devHalCfg);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }
    
    halError = ads8_I2cClose(devHalCfg);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }
    
    halError = ads8_TimerClose(devHalCfg);
    if (halError != (int32_t)ADI_HAL_OK)
    {
        return halError;
    }

    return halError;
}

/**
* \brief This function control a BBIC GPIO pin that connects to the reset pin
*        of each device.
*
*  This function is called by each device API giving access to the Reset pin
*  connected to each device.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param pinLevel The desired pin logic level 0=low, 1=high to set the GPIO pin to.
*
* \retval ADI_HAL_OK Function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR The function has been called with a null pointer
*/
int32_t ads8_HwReset(void *devHalCfg, uint8_t pinLevel)
{
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_HwResetCfg_t *hwResetCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    int32_t retVal = 0;
    uint32_t readData = 0;
    uint32_t writeData = 0;
    uint32_t pinLevelBit = 0;
    uint32_t resetPinBitPostion = 0;
    static const uint32_t FPGA_RESETPIN_REGISTER = 0x43041004;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    hwResetCfg = &halCfg->hwResetCfg;
    
    if (hwResetCfg == NULL)
    {
        return ADI_HAL_NULL_PTR;
    }
    
#ifdef __GNUC__

    if (hwResetCfg->interfaceEnabled > 0)
    {
        /* Note the pin level is inverted in the ADS8 FPGA...hence then logic inversion here */
        pinLevelBit = (pinLevel > 0) ? 0 : 1;
        
        /* hwResetCfg->resetPinIndex is the bit position in FPGA_RESETPIN_REGISTER 
         * for the reset pin of the requested device */
        switch (hwResetCfg->resetPinIndex)
        {
        case 1: /* ADRV9010: For ADS8 platform, FPGA register 0x43041004 bit 1 controls RESET pin */
        {
            resetPinBitPostion = hwResetCfg->resetPinIndex;
            break;
        }

        case 2: /* AD9528: For ADS8 platform, FPGA register 0x43041004 bit 2 controls RESET pin */
        {
            resetPinBitPostion = hwResetCfg->resetPinIndex;
            break;
        }

        default:
        {
            /* Invalid Hardware reset pin index for ADS8 Platform */
            return ADI_HAL_GPIO_FAIL;
        }
        }
        
        /* Perform read/modify/write to change the bit of interest in the FPGA
         * register that controls the reset pins to each device */
        retVal = ads8_BbicRegisterRead(devHalCfg, FPGA_RESETPIN_REGISTER, &readData);
        if (retVal > 0)
        {
            return ADI_HAL_GPIO_FAIL;
        }
        
        writeData = readData & ~(1UL << resetPinBitPostion);
        writeData |= (pinLevelBit << resetPinBitPostion);
        
        retVal = ads8_BbicRegisterWrite(devHalCfg, FPGA_RESETPIN_REGISTER, writeData);
        if (retVal > 0)
        {
            return ADI_HAL_GPIO_FAIL;
        }
    }

#endif /* __GNUC__ */

    return halError;
}

/**
* \brief This function is a helper function to fill out the members of the 
*         devHalCfg structure with driver names for this specific (ADS8) platform.
*
* This function allows keeping the platform specific knowledge of driver names
* in this layer of code.  Higher layers of code can call this to fill out the
* devHalCfg structure correctly for the ADS8 platform.
*
* Each device gets a unique instance of the devHalCfg structure describing the
* device resources for that device, such as the SPI chip select, etc.
*
* \param interfaceMask A mask that represents which platform interfaces are required by a particular device (SPI, Logging, etc)
* \param spiChipSelect The chip select index describing the particular device this structure is for (0, 1, 2 valid on ADS8)
* \param logFilename The filename of the logfile for this device.
*/
void* ads8_DevHalCfgCreate(uint32_t interfaceMask, uint8_t spiChipSelect, const char *logFilename)
{
    adi_hal_Cfg_t *halCfg = (adi_hal_Cfg_t*)calloc(1, sizeof(adi_hal_Cfg_t));
    
    if (halCfg == NULL)
    {
        return NULL;
    }

    /* Disable all interfaces, and enable only if they are needed by the specific device */
    halCfg->spiCfg.interfaceEnabled = 0;
    halCfg->logCfg.interfaceEnabled = 0;
    halCfg->bbicCfg.interfaceEnabled = 0;
    
    /* If device requires SPI interface */
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_SPI) > 0)
    {
        halCfg->spiCfg.interfaceEnabled = 1;
        
        switch (spiChipSelect)
        {
        case 0: 
        {
            strncpy(halCfg->spiCfg.spidevName, "/dev/spidev12345.0\0", ADI_HAL_STRING_LENGTH);
            halCfg->spiCfg.chipSelectIndex = spiChipSelect;
            break;
        }
        case 1:
        {
            strncpy(halCfg->spiCfg.spidevName, "/dev/spidev12345.1\0", ADI_HAL_STRING_LENGTH);
            halCfg->spiCfg.chipSelectIndex = spiChipSelect;
            break;
        }
        case 2:
        {
            strncpy(halCfg->spiCfg.spidevName, "/dev/spidev12345.2\0", ADI_HAL_STRING_LENGTH);
            halCfg->spiCfg.chipSelectIndex = spiChipSelect;
            break;
        }
        default:
        {
            free(halCfg);
            return NULL;
        }
        }
    
        /* Default SPI settings */
        halCfg->spiCfg.autoIncAddrUp = 1;
        halCfg->spiCfg.CPHA = 0;
        halCfg->spiCfg.CPOL = 0;
        halCfg->spiCfg.enSpiStreaming = 0;
        halCfg->spiCfg.fourWireMode = 1;
        halCfg->spiCfg.spiActionDisable = 0;
        halCfg->spiCfg.spiClkFreq_Hz = 25000000;
    }
    
    /* If device requires Logging interface */
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_LOG) > 0)
    {
        halCfg->logCfg.interfaceEnabled = 1;
        halCfg->logCfg.logLevel = ADI_HAL_LOG_ALL;
        strncpy(halCfg->logCfg.logFileName, logFilename, ADI_HAL_STRING_LENGTH);
        /* ensure null termination */
        halCfg->logCfg.logFileName[sizeof(halCfg->logCfg.logFileName)-1] = '\0';
    }
    
    /* If device requires FPGA register interface */
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_BBICCTRL) > 0)
    {
        halCfg->bbicCfg.interfaceEnabled = (ADI_HAL_BBIC_CORE | ADI_HAL_BBIC_RAM | ADI_HAL_BBIC_SPI);
        strncpy(halCfg->bbicCfg.coreRegsCfg.drvName, "/dev/uio0\0", ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.coreRegsCfg.mapSize = 0x1000000; /* 16MB */
        strncpy(halCfg->bbicCfg.ramCfg.drvName, "/dev/uio1\0", ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.ramCfg.mapSize = 0x10000000; /* 256MB */
        
        strncpy(halCfg->bbicCfg.spiAdvRegsCfg.drvName, "/dev/uio2\0", ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.spiAdvRegsCfg.mapSize = 0x1000; /* 16MB */
    }
    else if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_HWRESET) > 0)
    {
        halCfg->hwResetCfg.interfaceEnabled = 1;
        halCfg->bbicCfg.interfaceEnabled = ADI_HAL_BBIC_CORE | ADI_HAL_BBIC_SPI;

        strncpy(halCfg->bbicCfg.coreRegsCfg.drvName, "/dev/uio0\0", ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.coreRegsCfg.mapSize = 0x42000; /* 264kB to access hwReset TODO: include bitfields to get the correct address? */

        strncpy(halCfg->bbicCfg.spiAdvRegsCfg.drvName, "/dev/uio2\0", ADI_HAL_STRING_LENGTH);
        halCfg->bbicCfg.spiAdvRegsCfg.mapSize = 0x1000; /* 16MB */

        switch(spiChipSelect)
        {
        case 0:
            {
                halCfg->hwResetCfg.resetPinIndex = 1; /* ADRV9010 reset pin bit position in FPGA register */
                break;
            }
        case 1:
            { 
                halCfg->hwResetCfg.resetPinIndex = 2; /* AD9528 reset pin bit position in FPGA register */ 
                break;
            }
        case 2:
            {
                halCfg->hwResetCfg.resetPinIndex = 0; /* SPI2 does not need hwReset, only access to Adv Spi. A 0 value here will not get past the hwReset range checks */
                break;
            }
        default:
            free(halCfg);
            return NULL;
        }
        
    }
    
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_I2C) > 0)
    {
        /* TODO: Place holder for future support 
         * Need to update the passed parameters to include the driver location*/
        halCfg->i2cCfg.interfaceEnabled = 0;
        strncpy(halCfg->i2cCfg.drvName, "/sys/bus/i2c/devices/3-0050/eeprom", ADI_HAL_STRING_LENGTH);
    }
    
    if ((interfaceMask & (uint32_t)ADI_HAL_INTERFACE_TIMER) > 0)
    {
        halCfg->timerCfg.interfaceEnabled = 1;
        /* Currently no timer config structure for ADS8 platform */
    }
    halCfg->interfaceMask = interfaceMask;
    return halCfg;
}

int32_t ads8_DevHalCfgFree(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    
    free(devHalCfg);
    
    return halError;
}

int32_t ads8_HwVerify(void *devHalCfg)
{
	int32_t halError = (int32_t)ADI_HAL_OK;
	adi_hal_Cfg_t *halCfg = NULL;
	if (devHalCfg == NULL)
	{
		halError = (int32_t)ADI_HAL_NULL_PTR;
		return halError;
	}
    
	halCfg = (adi_hal_Cfg_t *)devHalCfg;

	/* interpret the interface mask */

	/* ADI_HAL_INTERFACE_SPI */
	if ((halCfg->interfaceMask & (uint32_t)ADI_HAL_INTERFACE_SPI) > 0)  /* Device requires spi interface */
	{
		/* throw an error if pointer is NULL */
		if (halCfg->spiCfg.fd == 0)
		{
			halError = (int32_t)ADI_HAL_SPI_FAIL;
		}
	}

	/* ADI_HAL_INTERFACE_LOG */
	if ((halCfg->interfaceMask & (uint32_t)ADI_HAL_INTERFACE_LOG) > 0)  /* Device requires logging interface */
	{
		/* throw an error if pointer is NULL */
		if (halCfg->logCfg.logfd == 0)
		{
			halError = (int32_t)ADI_HAL_LOGGING_FAIL;
		}
	}

	/* ADI_HAL_INTERFACE_BBICCTRL */
	if ((halCfg->interfaceMask & (uint32_t)ADI_HAL_INTERFACE_BBICCTRL) > 0)  /* Device requires fpga register interface */
	{
		/* throw an error if pointer is NULL */
		if (halCfg->bbicCfg.coreRegsCfg.fd == 0 ||
			halCfg->bbicCfg.ramCfg.fd == 0 ||
			halCfg->bbicCfg.spiAdvRegsCfg.fd == 0)
		{
			halError = (int32_t)ADI_HAL_BBICCTRL_FAIL;
		}
	}

	/* ADI_HAL_HWRESET */
	/* Not affected by HwClose */

	/* ADI_HAL_INTERFACE_TIMER */
	/* Not affected by HwClose */

    /* ADI_HAL_INTERFACE_I2C */
	if ((halCfg->interfaceMask & (uint32_t)ADI_HAL_INTERFACE_I2C) > 0)  /* Device requires i2c interface */
	{
		/* throw an error if pointer is NULL */
		if (halCfg->i2cCfg.fd == 0)
		{
			halError = (int32_t)ADI_HAL_I2C_FAIL;
		}
	}
	return halError;
}