/**
 * \file ads8_spi.c
 * Analog Devices ADS8 Platform + microzed hardware abstraction layer
 *
 * Copyright 2017 Analog Devices Inc.
 *
 * Support for linux layer SPI functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifdef __GNUC__
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#endif /* __GNUC__ */

#include <fcntl.h>
#include <stdio.h>
#include "ads8_spi.h"
#include "ads8_bbic_control.h"

/**
* \brief Opens/allocates any necessary resources to communicate via SPI to a 
         particular device specified in the devHalCfg structure.
*
* This function should perform any necessary steps to open the SPI master resource
* on the BBIC to enable SPI communications to a particular SPI device.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the device driver was not opened successfully
*/
int32_t ads8_SpiOpen(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_SpiCfg_t *spiCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    spiCfg = &halCfg->spiCfg;
    
    if (spiCfg == NULL)
    {
        return ADI_HAL_NULL_PTR;
    }
    
#ifdef __GNUC__
    if (spiCfg->fd <= 0)
    {
        spiCfg->fd = open(spiCfg->spidevName, O_RDWR);

        if (spiCfg->fd < 0)
        {
            return ADI_HAL_SPI_FAIL;
        }
    }
#endif /* __GNUC__ */
    return halError;
}

/**
* \brief Closes any resources open/allocated for a specific SPI device
*
* Any information needed to close the particular SPI device should be passed in
* the devHalCfg structure.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the device driver was not closed successfully
*/
int32_t ads8_SpiClose(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    
    if (halCfg->spiCfg.spiActionDisable == 0)
    {

        if (halCfg->spiCfg.fd != 0)
        {
#ifdef __GNUC__
            halError = close(halCfg->spiCfg.fd);
            if (halError < 0)
            {
                return ADI_HAL_SPI_FAIL;
            }
#endif /* __GNUC__ */

            halCfg->spiCfg.fd = 0;
        }

    }
    return halError;
}

/**
* \brief Initializes the SPI device driver mode, bits per word, and speed
*
* Any settings needed should be passed in the devHalCfg structure
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the SPI initialization failed
*/
int32_t ads8_SpiInit(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    uint8_t spiMode = 0;
    uint32_t bitsPerWord = 0;
    uint32_t speed = 0;
    int32_t result = 0;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    
    /* Initialize SPI driver with clockrate, SPI mode, etc */
    if (halCfg->spiCfg.spiActionDisable == 0)
    {

        bitsPerWord = 8;
        speed = halCfg->spiCfg.spiClkFreq_Hz;

        /*Get Chips SPI Driver File Descriptor*/
        if (halCfg->spiCfg.fd <= 0)
        {
            return ADI_HAL_SPI_FAIL;
        }

        /*
         * spi mode
         */
        if ((halCfg->spiCfg.CPOL > 1) || (halCfg->spiCfg.CPHA > 1))
        {
            /*
            * Invalid SPI mode: CPOL and CPHA should be 1 or 0
            */
            return ADI_HAL_SPI_FAIL;
        }

        spiMode = (halCfg->spiCfg.CPOL << 1) | halCfg->spiCfg.CPHA;
        
#ifdef __GNUC__
        result = ioctl(halCfg->spiCfg.fd, SPI_IOC_WR_MODE, &spiMode);
        if (result < 0)
        {
            /*
             * Error settings requested SPI mode
             */
            return ADI_HAL_SPI_FAIL;
        }

        /*
         * bits per word
         */
        result = ioctl(halCfg->spiCfg.fd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
        if (result < 0)
        {
            /*
             * Error setting the number of Bits per SPI word
             */
            return ADI_HAL_SPI_FAIL;
        }

        /*
         * max speed hz
         */
        result = ioctl(halCfg->spiCfg.fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
        if (result < 0)
        {
            /*
             * Error Setting max SPI clock frequency for current chip select index.
             */
            return ADI_HAL_SPI_FAIL;
        }
#endif /* __GNUC__ */
    } /* If SPI hardware interface enabled */


    return halError;
}

/**
* \brief Write an array of 8-bit data to a SPI device
*
* The function will write numTxBytes number of bytes to the SPI device 
* selected in the devHalCfg structure.
*
* \dep_begin
* \dep{adi_hal_SpiCfg_t}
* \dep{adi_hal_SpiCfg_t->fd}
* \dep_end
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array txData buffer that has numTxBytes number of bytes
* \param numTxBytes The length of txData array
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not written successfully
*/
int32_t ads8_SpiWrite(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->spiCfg.spiActionDisable == 0)
    {
#ifdef __GNUC__
        int32_t result = 0;

        if (halCfg->spiCfg.fd > 0)
        {
            result = write(halCfg->spiCfg.fd, txData, numTxBytes);
            if (result <= 0)
            {
                halError = ADI_HAL_SPI_FAIL;
            }
        }
        else
        {
            /* Invalid file descriptor */
            halError = ADI_HAL_SPI_FAIL;
        }
#endif /* __GNUC__ */
    }

    return halError;
}

/**
* \brief Write an array of 8-bit data to a SPI device
*
* The function will write numTxBytes number of bytes to the SPI device
* selected in the devHalCfg structure.

* This function uses FPGA registers to manage spi transaction. It doesn't use spi device driver.
*
* \dep_begin
* \dep{adi_hal_SpiCfg_t}
* \dep{adi_hal_SpiCfg_t->fd}
* \dep_end
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array txData buffer that has numTxBytes number of bytes
* \param numTxBytes The length of txData array
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not written successfully
*/
int32_t ads8_SpiWrite_v2(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes)
{
    static const uint16_t FPGA_FIFO_SIZE = 255;
    static const uint32_t WAIT_FIFO_OCCUPANCY = 1024;
    static const uint32_t SPI_CONTROL_REGISTER     = 0x44A00060;
    static const uint32_t SPI_TXFIFO_REGISTER      = 0x44A00068;
    static const uint32_t SPI_CS_REGISTER          = 0x44A00070;
    static const uint32_t SPI_TXFIFO_OCY_REGISTER  = 0x44A00074;
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    uint32_t chipSelMask = 0xFFFFFFFF;   //one hot active low active chip select
    uint32_t i = 0;
    uint32_t readData = 0;
    uint16_t numOfChunks = 0;
    uint16_t numFifoBytes = 0;
    uint16_t remainder = 0;
    uint16_t byteCounter = 0;
    uint16_t k = 0;
    
    /* Calculate number of full FIFO transactions and remainder for last flush */
    remainder = numTxBytes % FPGA_FIFO_SIZE;
    numOfChunks = (numTxBytes - remainder) / FPGA_FIFO_SIZE;

    if(devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    
    if(halCfg->spiCfg.spiActionDisable == 0)
    {
    # ifdef __GNUC__
    
        /* This function requires access to advanced spi registers through BBIC */
        if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) == ADI_HAL_BBIC_SPI))
        {
            /* Reset Tx/Rx FIFO */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x64);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            chipSelMask = (0xFFFFFFFF & ~(1UL << halCfg->spiCfg.chipSelectIndex));

            /* Write SS register */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, chipSelMask);
            if(halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            /* Write numOfChunks full chunks and remainder */
            numFifoBytes = FPGA_FIFO_SIZE;
            for (k = 0; k < (numOfChunks + 1); k++)
            {
                /* If we're writing the remainder set numFifoBytes as remainder */
                if (k == numOfChunks)
                {
                    numFifoBytes = remainder;
                }
                
                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Write data bytes into Tx FIFO*/
                    halError = ads8_BbicRegisterWrite(devHalCfg, SPI_TXFIFO_REGISTER, (uint32_t)txData[byteCounter++]);
                    if(halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Enable SPI to start transmitting */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x06);
                if(halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }
    
                /* Wait until Tx FIFO is empty*/
                for (i = 0; i < WAIT_FIFO_OCCUPANCY; i++)
                {
                    /* Read Tx FIFO Occupancy */
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_TXFIFO_OCY_REGISTER, &readData);
                    if(halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                    
                    if (readData == 0)
                    {
                        break;
                    }
                    
                    if (i == (WAIT_FIFO_OCCUPANCY -1))
                    {
                        /* Timeout */
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Reset Tx/Rx FIFO */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x64);
                if(halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }
            }

            /* Write SS register */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, 0xFFFFFFFF);
            if(halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
    
            }
        }
        else
        {
            /* Invalid file descriptor */
            halError = (int32_t)ADI_HAL_SPI_FAIL;
            return halError;
        }

        # endif /* __GNUC__ */
    }
    
    return halError;
}

/**
* \brief Write an array of 8-bit data to a SPI device
*
* The function will write numTxBytes number of bytes to the SPI device
* selected in the devHalCfg structure.
*
* This function uses FPGA registers to manage spi transaction. It doesn't use spi device driver.
* It implements the spi transfer sequence provided by XILINX DS742 document It's still under test.
*
* \dep_begin
* \dep{adi_hal_SpiCfg_t}
* \dep{adi_hal_SpiCfg_t->fd}
* \dep_end
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array txData buffer that has numTxBytes number of bytes
* \param numTxBytes The length of txData array
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not written successfully
*/
int32_t ads8_SpiWrite_v3(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes)
{
    static const uint16_t FPGA_FIFO_SIZE = 256;
    static const uint32_t WAIT_FIFO_OCCUPANCY = 1024;
    static const uint32_t SPI_CONTROL_REGISTER = 0x44A00060;
    static const uint32_t SPI_TXFIFO_REGISTER = 0x44A00068;
    static const uint32_t SPI_CS_REGISTER = 0x44A00070;
    static const uint32_t SPI_TXFIFO_OCY_REGISTER = 0x44A00074;
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    uint32_t chipSelMask = 0xFFFFFFFF;   //one hot active low active chip select
    uint32_t i = 0;
    uint32_t readData = 0;
    uint16_t numOfChunks = 0;
    uint16_t numFifoBytes = 0;
    uint16_t remainder = 0;
    uint16_t byteCounter = 0;
    uint16_t k = 0;

    /* Calculate number of full FIFO transactions and remainder for last flush */
    remainder = numTxBytes % FPGA_FIFO_SIZE;
    numOfChunks = (numTxBytes - remainder) / FPGA_FIFO_SIZE;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->spiCfg.spiActionDisable == 0)
    {
# ifdef __GNUC__

        /* This function requires access to advanced spi registers through BBIC */
        if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) == ADI_HAL_BBIC_SPI))
        {
            /* Reset Tx/Rx FIFO - Set Inhibit */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E4);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            /* Write numOfChunks full chunks and remainder */
            numFifoBytes = FPGA_FIFO_SIZE;
            for (k = 0; k < (numOfChunks + 1); k++)
            {
                /* If we're writing the remainder set numFifoBytes as remainder */
                if (k == numOfChunks)
                {
                    numFifoBytes = remainder;
                }

                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Write data bytes into Tx FIFO*/
                    halError = ads8_BbicRegisterWrite(devHalCfg, SPI_TXFIFO_REGISTER, (uint32_t)txData[byteCounter++]);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Enable SPI  - Set Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x186);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* CS low */
                chipSelMask = (0xFFFFFFFF & ~(1UL << halCfg->spiCfg.chipSelectIndex));
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, chipSelMask);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* Clear Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x86);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* Wait until Tx FIFO is empty*/
                for (i = 0; i < WAIT_FIFO_OCCUPANCY; i++)
                {
                    /* Read Tx FIFO Occupancy */
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_TXFIFO_OCY_REGISTER, &readData);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }

                    if (readData == 0)
                    {
                        break;
                    }

                    if (i == (WAIT_FIFO_OCCUPANCY - 1))
                    {
                        /* Timeout */
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Reset Tx/Rx FIFO - Set Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E6);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }
            }

            /* CS High */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, 0xFFFFFFFF);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;

            }

            /* Disable SPI - Set Inhibit */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E4);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }
        }
        else
        {
            /* Invalid file descriptor */
            halError = (int32_t)ADI_HAL_SPI_FAIL;
            return halError;
        }

# endif /* __GNUC__ */
    }

    return halError;
}

/**
* \brief Read one or more bytes from the device specified by the devHalCfg structure
*
* The function will read numTxRxBytes number of bytes from the SPI device selected in
* the devHalCfg parameter and store the resulting data sent by the device in the rxData
* data buffer.
*
* For each byte in txData written to the device, a byte is read and returned by this 
* function at the pointer provided by the rxData parameter.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array that has numTxRxBytes number of bytes
* \param rxData Pointer to byte array where read back data will be returned, that is at least numTxRxBytes in size.
* \param numTxBytes The length of txData and rxData arrays
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not read successfully
*/
int32_t ads8_SpiRead(void *devHalCfg, const uint8_t txData[], uint8_t rxData[],
                     uint32_t numTxRxBytes)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    int32_t result = 0;
    adi_hal_Cfg_t *halCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    
    if (halCfg->spiCfg.fd <= 0)
    {
        /* Invalid file descriptor */
        return ADI_HAL_SPI_FAIL;
    }

    if(halCfg->spiCfg.spiActionDisable == 0)
    {
#ifdef __GNUC__

        /*Get device's SPI Driver File Descriptor*/
        struct spi_ioc_transfer tr = { 0 };

        tr.tx_buf = (uintptr_t)&txData[0];
        tr.rx_buf = (uintptr_t)&rxData[0];
        tr.len = numTxRxBytes;
        tr.delay_usecs = 0;

        result = ioctl(halCfg->spiCfg.fd, SPI_IOC_MESSAGE(1), &tr);
        if (result <= 0)
        {
            halError = ADI_HAL_SPI_FAIL;
        }
#endif /* __GNUC__ */
    }

    return halError;
}

/**
* \brief Read one or more bytes from the device specified by the devHalCfg structure
*
* The function will read numTxRxBytes number of bytes from the SPI device selected in
* the devHalCfg parameter and store the resulting data sent by the device in the rxData
* data buffer.
*
* For each byte in txData written to the device, a byte is read and returned by this
* function at the pointer provided by the rxData parameter.
*
* This function uses FPGA registers to manage spi transaction. It doesn't use spi device driver.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array that has numTxRxBytes number of bytes
* \param rxData Pointer to byte array where read back data will be returned, that is at least numTxRxBytes in size.
* \param numTxBytes The length of txData and rxData arrays
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not read successfully
*/
int32_t ads8_SpiRead_v2(void *devHalCfg, const uint8_t txData[], uint8_t rxData[], uint32_t numTxRxBytes)
{
    static const uint16_t FPGA_FIFO_SIZE = 255;
    static const uint32_t WAIT_FIFO_OCCUPANCY = 1024;
    static const uint32_t SPI_CONTROL_REGISTER = 0x44A00060;
    static const uint32_t SPI_TXFIFO_REGISTER = 0x44A00068;
    static const uint32_t SPI_RXFIFO_REGISTER = 0x44A0006C;
    static const uint32_t SPI_CS_REGISTER = 0x44A00070;
    static const uint32_t SPI_TXFIFO_OCY_REGISTER = 0x44A00074;
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    uint32_t chipSelMask = 0xFFFFFFFF;   //one hot active low active chip select
    uint32_t i = 0;
    uint32_t readData = 0;
    uint16_t numOfChunks = 0;
    uint16_t numFifoBytes = 0;
    uint16_t remainder = 0;
    uint16_t txByteCounter = 0;
    uint16_t rxByteCounter = 0;
    uint16_t k = 0;

    /* Calculate number of full FIFO transactions and remainder for last flush */
    remainder = numTxRxBytes % FPGA_FIFO_SIZE;
    numOfChunks = (numTxRxBytes - remainder) / FPGA_FIFO_SIZE;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->spiCfg.spiActionDisable == 0)
    {
# ifdef __GNUC__

        /* This function requires access to advanced spi registers through BBIC */
        if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) == ADI_HAL_BBIC_SPI))
        {
            /* Reset Tx/Rx FIFO */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x64);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            chipSelMask = (0xFFFFFFFF & ~(1UL << halCfg->spiCfg.chipSelectIndex));

            /* Write SS register */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, chipSelMask);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            /* Write numOfChunks full chunks and remainder */
            numFifoBytes = FPGA_FIFO_SIZE;
            for (k = 0; k < (numOfChunks + 1); k++)
            {
                /* If we're writing the remainder set numFifoBytes as remainder */
                if (k == numOfChunks)
                {
                    numFifoBytes = remainder;
                }

                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Write data bytes into Tx FIFO*/
                    halError = ads8_BbicRegisterWrite(devHalCfg, SPI_TXFIFO_REGISTER, (uint32_t)txData[txByteCounter++]);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Enable SPI to start transmitting */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x06);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* Wait until Tx FIFO is empty*/
                for (i = 0; i < WAIT_FIFO_OCCUPANCY; i++)
                {
                    /* Read Tx FIFO Occupancy */
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_TXFIFO_OCY_REGISTER, &readData);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }

                    if (readData == 0)
                    {
                        break;
                    }

                    if (i == (WAIT_FIFO_OCCUPANCY - 1))
                    {
                        /* Timeout */
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Read data bytes from Rx FIFO*/
                    uint32_t dataTmp = 0;
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_RXFIFO_REGISTER, &dataTmp);
                    rxData[rxByteCounter++] = (uint8_t)(dataTmp & 0x000000FF);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x64);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }
            }

            /* Write SS register */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, 0xFFFFFFFF);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;

            }
        }
        else
        {
            /* Invalid file descriptor */
            halError = (int32_t)ADI_HAL_SPI_FAIL;
            return halError;
        }

# endif /* __GNUC__ */
    }

    return halError;
}

/**
* \brief Read one or more bytes from the device specified by the devHalCfg structure
*
* The function will read numTxRxBytes number of bytes from the SPI device selected in
* the devHalCfg parameter and store the resulting data sent by the device in the rxData
* data buffer.
*
* For each byte in txData written to the device, a byte is read and returned by this
* function at the pointer provided by the rxData parameter.
*
* This function uses FPGA registers to manage spi transaction. It doesn't use spi device driver.
* It implements the spi transfer sequence provided by XILINX DS742 document It's still under test.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Pointer to byte array that has numTxRxBytes number of bytes
* \param rxData Pointer to byte array where read back data will be returned, that is at least numTxRxBytes in size.
* \param numTxBytes The length of txData and rxData arrays
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_SPI_FAIL the data was not read successfully
*/

int32_t ads8_SpiRead_v3(void *devHalCfg, const uint8_t txData[], uint8_t rxData[],
    uint32_t numTxRxBytes)
{
    static const uint16_t FPGA_FIFO_SIZE = 256;
    static const uint32_t WAIT_FIFO_OCCUPANCY = 1024;
    static const uint32_t SPI_CONTROL_REGISTER = 0x44A00060;
    static const uint32_t SPI_TXFIFO_REGISTER = 0x44A00068;
    static const uint32_t SPI_RXFIFO_REGISTER = 0x44A0006C;
    static const uint32_t SPI_CS_REGISTER = 0x44A00070;
    static const uint32_t SPI_TXFIFO_OCY_REGISTER = 0x44A00074;
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    uint32_t chipSelMask = 0xFFFFFFFF;   //one hot active low active chip select
    uint32_t i = 0;
    uint32_t readData = 0;
    uint16_t numOfChunks = 0;
    uint16_t numFifoBytes = 0;
    uint16_t remainder = 0;
    uint16_t txByteCounter = 0;
    uint16_t rxByteCounter = 0;
    uint16_t k = 0;

    /* Calculate number of full FIFO transactions and remainder for last flush */
    remainder = numTxRxBytes % FPGA_FIFO_SIZE;
    numOfChunks = (numTxRxBytes - remainder) / FPGA_FIFO_SIZE;

    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if (halCfg->spiCfg.spiActionDisable == 0)
    {
# ifdef __GNUC__

        /* This function requires access to advanced spi registers through BBIC */
        if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) == ADI_HAL_BBIC_SPI))
        {
            /* Reset Tx/Rx FIFO - Set Inhibit */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E4);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }

            /* Write numOfChunks full chunks and remainder */
            numFifoBytes = FPGA_FIFO_SIZE;
            for (k = 0; k < (numOfChunks + 1); k++)
            {
                /* If we're writing the remainder set numFifoBytes as remainder */
                if (k == numOfChunks)
                {
                    numFifoBytes = remainder;
                }

                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Write data bytes into Tx FIFO*/
                    halError = ads8_BbicRegisterWrite(devHalCfg, SPI_TXFIFO_REGISTER, (uint32_t)txData[txByteCounter++]);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Enable SPI  - Set Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x186);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* CS low */
                chipSelMask = (0xFFFFFFFF & ~(1UL << halCfg->spiCfg.chipSelectIndex));
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, chipSelMask);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* Clear Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x86);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }

                /* Wait until Tx FIFO is empty*/
                for (i = 0; i < WAIT_FIFO_OCCUPANCY; i++)
                {
                    /* Read Tx FIFO Occupancy */
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_TXFIFO_OCY_REGISTER, &readData);
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }

                    if (readData == 0)
                    {
                        break;
                    }

                    if (i == (WAIT_FIFO_OCCUPANCY - 1))
                    {
                        /* Timeout */
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                for (i = 0; i < numFifoBytes; i++)
                {
                    /* Read data bytes from Rx FIFO*/
                    uint32_t dataTmp = 0;
                    halError = ads8_BbicRegisterRead(devHalCfg, SPI_RXFIFO_REGISTER, &dataTmp);
                    rxData[rxByteCounter++] = dataTmp & 0xFF;
                    if (halError != (int32_t)ADI_HAL_OK)
                    {
                        halError = (int32_t)ADI_HAL_SPI_FAIL;
                        return halError;
                    }
                }

                /* Reset Tx/Rx FIFO - Set Inhibit */
                halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E6);
                if (halError != (int32_t)ADI_HAL_OK)
                {
                    halError = (int32_t)ADI_HAL_SPI_FAIL;
                    return halError;
                }
            }

            /* CS High */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CS_REGISTER, 0xFFFFFFFF);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;

            }

            /* Disable SPI - Set Inhibit */
            halError = ads8_BbicRegisterWrite(devHalCfg, SPI_CONTROL_REGISTER, 0x1E4);
            if (halError != (int32_t)ADI_HAL_OK)
            {
                halError = (int32_t)ADI_HAL_SPI_FAIL;
                return halError;
            }
        }
        else
        {
            /* Invalid file descriptor */
            halError = (int32_t)ADI_HAL_SPI_FAIL;
            return halError;
        }

# endif /* __GNUC__ */
    }

    return halError;
}