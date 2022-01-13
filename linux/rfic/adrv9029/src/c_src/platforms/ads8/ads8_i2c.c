/**
 * \file ads8_i2c.c
 * Analog Devices ADS8 Platform + microzed hardware abstraction layer
 *
 * Copyright 2017 Analog Devices Inc.
 *
 * Support for linux layer I2C functions
 */

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#ifdef __GNUC__
#include <unistd.h>
#endif /* __GNUC__ */

#include <fcntl.h>
#include <stdio.h>
#include "ads8_i2c.h"

/**
* \brief Function to open/allocate any necessary resources for the I2C 
*        functions below.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_I2cOpen(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_I2cCfg_t *i2cCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    i2cCfg = &halCfg->i2cCfg;
    
    if (i2cCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }
    
#ifdef __GNUC__
    if (i2cCfg->fd <= 0)
    {
        i2cCfg->fd = open(i2cCfg->drvName, O_RDWR);

        if (i2cCfg->fd < 0)
        {
            return (int32_t)ADI_HAL_I2C_FAIL;
        }
    }
#endif /* __GNUC__ */
    return halError;
}

/**
* \brief Function to close/deallocate any necessary resources for the I2C 
*        functions below.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_I2cClose(void *devHalCfg)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_I2cCfg_t *i2cCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    i2cCfg = &halCfg->i2cCfg;
    
    if (i2cCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }
    
#ifdef __GNUC__
    if (i2cCfg->fd != 0)
    {
        halError = close(i2cCfg->fd);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_I2C_FAIL;
        }
        
        i2cCfg->fd = 0;
    }
#endif /* __GNUC__ */

    return halError;
}

/**
* \brief Function to init any necessary resources for the I2C 
*        functions below.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_I2cInit(void *devHalCfg)
{
    (void) (devHalCfg);
    return (int32_t)ADI_HAL_OK;
}

/**
* \brief Function to write to an I2C device from the BBIC
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Byte array of data to write to the I2C device.  First byte 
*               should be the I2C register address followed by one or more data bytes.
* \param numTxBytes Number of bytes in the txData array
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_I2cWrite(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    int retVal = 0;
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_I2cCfg_t *i2cCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    i2cCfg = &halCfg->i2cCfg;
    if (i2cCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }

    if ((numTxBytes > 0) &&
        (txData != NULL))
    {
        if (i2cCfg->fd > 0)
        {
#ifdef __GNUC__
            retVal = write(i2cCfg->fd, &txData[0], numTxBytes);
            if (retVal != (int)numTxBytes)
            {
                perror("I2C : Failed to Write to device");
                return (int32_t)ADI_HAL_I2C_FAIL;
            }
#endif
        }
        else
        {
            perror("I2C : Failed to Write to device, file descriptor invalid");
            return (int32_t)ADI_HAL_GEN_SW;
        }
    }
    
    return halError;
}

/**
* \brief Function to read from an I2C device to the BBIC
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param txData Byte array of data to write to the I2C device. Depending on the
*               I2C device, this might just be 1 byte containing the register 
*               address to read
* \param numTxBytes Number of bytes in the txData array
* \param rxData Byte array to return the read back data
* \param numRxBytes Number of bytes to read back, and size of rxData array
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_I2cRead(void *devHalCfg, const uint8_t txData[], uint32_t numTxBytes, uint8_t rxData[], uint32_t numRxBytes)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    int retVal = 0;
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_I2cCfg_t *i2cCfg = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    i2cCfg = &halCfg->i2cCfg;
    
    if (i2cCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }

    if (i2cCfg->fd > 0)
    {
        /* Write Register address */
        if ((numTxBytes > 0) && 
            (txData != NULL))
        {
#ifdef __GNUC__
            retVal = write(i2cCfg->fd, &txData[0], numTxBytes);
            if (retVal != (int)numTxBytes)
            {
                perror("I2C : Failed to Write to I2C device");
                return (int32_t)ADI_HAL_I2C_FAIL;
            }
#endif
        }

        /* Read data */
        if ((numRxBytes > 0) &&
            (rxData != NULL))
        {
#ifdef __GNUC__
            retVal = read(i2cCfg->fd, &rxData[0], numRxBytes);
            if (retVal != (int)numRxBytes)
            {
                perror("I2C : Failed to Read from I2C device");
                return (int32_t)ADI_HAL_I2C_FAIL;
            }
#endif
        }
    }
    else
    {
        perror("I2C : Failed to Write to device, file descriptor invalid");
        return (int32_t)ADI_HAL_GEN_SW;
    }
        
    
    return halError;
}
