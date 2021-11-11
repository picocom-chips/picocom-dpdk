/**
* \file ads8_bbic_control.c
* \brief Contains ADI Transceiver Hardware Abstraction functions for ADS8 interface to FPGA (BBIC) control registers.
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/

/**
* Copyright 2015 - 2020 Analog Devices Inc.
* Released under the ADRV9010 API license, for more information.
* see the "LICENSE.pdf" file in this zip file.
*/

#include <string.h>
#include <errno.h>
#include <stdio.h>

#ifdef __GNUC__
#include <unistd.h>
#include <sys/mman.h>
#endif

#include <fcntl.h>
#include "ads8_bbic_control.h"

/********************/
/* Public functions */
/********************/

/**
* \brief Function to open any necessary resources for the BBIC 
         interface functions in this file.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_NULL_PTR If devHalCfg pointer is NULL
* \retval ADI_HAL_BBICCTRL_FAIL If critical error trying to open resources
*/
int32_t ads8_BbicOpen(void *devHalCfg)
{
    adi_hal_Cfg_t *halCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;

#ifdef __GNUC__
    /* Open UIO driver to FPGA register interface */
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_CORE) > 0) && halCfg->bbicCfg.coreRegsCfg.fd <= 0)
    {
        halCfg->bbicCfg.coreRegsCfg.fd = open(halCfg->bbicCfg.coreRegsCfg.drvName, O_RDWR);

        if (halCfg->bbicCfg.coreRegsCfg.fd < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        /* offset must be page aligned */
        halCfg->bbicCfg.coreRegsCfg.mappedMemoryPtr = (uintptr_t)mmap(NULL, halCfg->bbicCfg.coreRegsCfg.mapSize, PROT_READ | PROT_WRITE, MAP_SHARED, halCfg->bbicCfg.coreRegsCfg.fd, 0);

        if ((void *)halCfg->bbicCfg.coreRegsCfg.mappedMemoryPtr == MAP_FAILED)
        {
            perror("Error mapping the file for fpga core registers.");
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
    }
    
    /* Open UIO driver to FPGA Data capture memory RAM interface */
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_RAM) > 0) && halCfg->bbicCfg.ramCfg.fd <= 0)
    {
        halCfg->bbicCfg.ramCfg.fd = open(halCfg->bbicCfg.ramCfg.drvName, O_RDWR);

        if (halCfg->bbicCfg.ramCfg.fd < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        /* offset must be page aligned */
        halCfg->bbicCfg.ramCfg.mappedMemoryPtr = (uintptr_t)mmap(NULL, halCfg->bbicCfg.ramCfg.mapSize, PROT_READ | PROT_WRITE, MAP_SHARED, halCfg->bbicCfg.ramCfg.fd, 0);

        if ((void *)halCfg->bbicCfg.ramCfg.mappedMemoryPtr == MAP_FAILED)
        {
            perror("Error mapping the file for fpga ram.");
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
    }
    
        /* Open UIO driver to FPGA Advanced SPI settings interface */
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) > 0) && halCfg->bbicCfg.spiAdvRegsCfg.fd <= 0)
    {
        halCfg->bbicCfg.spiAdvRegsCfg.fd = open(halCfg->bbicCfg.spiAdvRegsCfg.drvName, O_RDWR);

        if (halCfg->bbicCfg.spiAdvRegsCfg.fd < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        /* offset must be page aligned */
        halCfg->bbicCfg.spiAdvRegsCfg.mappedMemoryPtr = (uintptr_t)mmap(NULL, halCfg->bbicCfg.spiAdvRegsCfg.mapSize, PROT_READ | PROT_WRITE, MAP_SHARED, halCfg->bbicCfg.spiAdvRegsCfg.fd, 0);

        if ((void *)halCfg->bbicCfg.spiAdvRegsCfg.mappedMemoryPtr == MAP_FAILED)
        {
            perror("Error mapping the file for fpga spiAdvRegsCfg registers.");
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
    }
    
#endif /* __GNUC__ */
    return halError;
}

/**
* \brief Function to close any necessary resources for the BBIC 
         interface functions in this file.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_NULL_PTR If devHalCfg pointer is NULL
* \retval ADI_HAL_BBICCTRL_FAIL If critical error trying to close resources
*/
int32_t ads8_BbicClose(void *devHalCfg)
{
    adi_hal_Cfg_t *halCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }

    /* Cast void *devHalCfg structure to the specific structure for ADS8 platform */
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    
#ifdef __GNUC__
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_CORE) > 0) && halCfg->bbicCfg.coreRegsCfg.fd != 0)
    {
        halError = munmap((void *)halCfg->bbicCfg.coreRegsCfg.mappedMemoryPtr, halCfg->bbicCfg.coreRegsCfg.mapSize);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        halError = close(halCfg->bbicCfg.coreRegsCfg.fd);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
        halCfg->bbicCfg.coreRegsCfg.fd = 0;
    }
    
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_RAM) > 0) && halCfg->bbicCfg.ramCfg.fd != 0)
    {
        halError = munmap((void *)halCfg->bbicCfg.ramCfg.mappedMemoryPtr, halCfg->bbicCfg.ramCfg.mapSize);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        halError = close(halCfg->bbicCfg.ramCfg.fd);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
        halCfg->bbicCfg.ramCfg.fd = 0;
    }
    
    if (((halCfg->bbicCfg.interfaceEnabled & ADI_HAL_BBIC_SPI) > 0) && halCfg->bbicCfg.spiAdvRegsCfg.fd != 0)
    {
        halError = munmap((void *)halCfg->bbicCfg.spiAdvRegsCfg.mappedMemoryPtr, halCfg->bbicCfg.spiAdvRegsCfg.mapSize);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }

        halError = close(halCfg->bbicCfg.spiAdvRegsCfg.fd);
        if (halError < 0)
        {
            return (int32_t)ADI_HAL_BBICCTRL_FAIL;
        }
        halCfg->bbicCfg.spiAdvRegsCfg.fd = 0;
    }
#endif /* __GNUC__ */

    return halError;
}

/**
* \brief Function to initialize any necessary resources for the BBIC 
         interface functions in this file.
*
* \param devHalCfg Pointer to device instance specific platform settings
*
* \retval ADI_HAL_OK Function completed successfully
*/
int32_t ads8_BbicInit(void *devHalCfg)
{
    (void)(devHalCfg);
    /* ADI ADS8 platform does not require any BBIC register/control init */
    return (int32_t)ADI_HAL_OK;
}

/**
 * \brief Function to read a single BBIC control register
 *
 * \param devHalCfg Pointer to device instance specific platform settings
 * \param addr 32bit address of BBIC register to read
 * \param data 32bit Pointer to store return value representing the data of the register at the specified address
 *
 * \retval ADI_HAL_OK Function completed successfully
 * \retval ADI_HAL_NULL_PTR devHalCfg pointer is NULL or data pointer is NULL
 */
int32_t ads8_BbicRegisterRead(void *devHalCfg, uint32_t addr, uint32_t *data)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    static const uint8_t READ_REG = 0;
   
    if ((devHalCfg == NULL) || (data == NULL))
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }

    halError = ads8_fpga_AxiReadWrite(devHalCfg, READ_REG, addr, data);

    return halError;
}

/**
 * \brief Function to write a single BBIC control register
 *
 * \param devHalCfg Pointer to device instance specific platform settings
 * \param addr 32bit address of BBIC register to write
 * \param data 32bit data to write to the register at the specified address
 *
 * \retval ADI_HAL_OK Function completed successfully
 * \retval ADI_HAL_NULL_PTR devHalCfg pointer is NULL
 */
int32_t ads8_BbicRegisterWrite(void *devHalCfg, uint32_t addr, uint32_t data)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    static const uint8_t WRITE_REG = 1;
   
    if (devHalCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }

    halError = ads8_fpga_AxiReadWrite(devHalCfg, WRITE_REG, addr, &data);

    return halError;
}

/**
 * \brief Function to read multiple consecutive BBIC control registers starting at a specified register address.
 *
 * \param devHalCfg Pointer to device instance specific platform settings
 * \param addr 32bit address of BBIC register to start reading from
 * \param data 32bit Pointer to store return array representing the data starting at the specified register address
               and ending at (addr + numDataWords -1)
 * \param numDataWords Number of elements in the data array
 *
 * \retval ADI_HAL_OK Function completed successfully
 * \retval ADI_HAL_NULL_PTR devHalCfg pointer is NULL
 */
int32_t ads8_BbicRegistersRead(void *devHalCfg, uint32_t addr, uint32_t data[], uint32_t numDataWords)
{
    int32_t halError = (int32_t)ADI_HAL_OK;
    static const uint8_t READ_REG = 0;

    if (devHalCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }
    
    halError = ads8_fpga_AxiBulkReadWrite(devHalCfg, READ_REG, addr, data, numDataWords);

    return halError;
}

/**
 * \brief Function to write multiple consecutive BBIC control registers starting at a specified register address.
 *
 * \param devHalCfg Pointer to device instance specific platform settings
 * \param addr 32bit address of BBIC register to start writing to
 * \param data 32bit Pointer to array representing the data to write starting at the specified register address
               and ending at (addr + numDataWords -1)
 * \param numDataWords Number of elements in the data array
 *
 * \retval ADI_HAL_OK Function completed successfully
 * \retval ADI_HAL_NULL_PTR devHalCfg pointer is NULL
 */
int32_t ads8_BbicRegistersWrite(void *devHalCfg, uint32_t addr, uint32_t data[], uint32_t numDataWords)
{
    static const uint8_t WRITE_REG = 1;
    
    return ads8_fpga_AxiBulkReadWrite(devHalCfg, WRITE_REG, addr, data, numDataWords);
}

/*********************/
/* Private functions */
/*********************/

/**
* \brief Writes and reads to the BBIC (FPGA) AXI memory mapped registers.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \param writeFlag (Hi)tells the function to write the data to address addr
* \Param writeFlag 1 = write, 0 = read.
* \param data the data to write to address addr.
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_GEN_SW If addr is out of valid range
* \retval ADI_HAL_BBICCTRL_FAIL If critical error during read or write operation
*/
int32_t ads8_fpga_AxiReadWrite(void *devHalCfg, uint8_t writeFlag, uint32_t addr, uint32_t *data)
{
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_fpga_AxiCfg_t *axiCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    uint32_t offsetAddr = 0;
    void *ptr = NULL;
    
    if (devHalCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }
     
    halCfg = (adi_hal_Cfg_t *)devHalCfg;

    if ((addr >= ADS8_FPGA_UIO0_START_ADDRESS) &&
        (addr <= ADS8_FPGA_UIO0_STOP_ADDRESS))
    {
        offsetAddr = addr - ADS8_FPGA_UIO0_START_ADDRESS;
        axiCfg =  &halCfg->bbicCfg.coreRegsCfg;
    }
    else if ((addr >= ADS8_FPGA_UIO2_START_ADDRESS) &&
             (addr <= ADS8_FPGA_UIO2_STOP_ADDRESS))
    {
        offsetAddr = addr - ADS8_FPGA_UIO2_START_ADDRESS;
        axiCfg =  &halCfg->bbicCfg.spiAdvRegsCfg;
    }
    else 
    {
        /* The offset parameter is the actual fpga memory address. Range check to make sure it's valid */
        halError = (int32_t)ADI_HAL_GEN_SW;
        return halError;
    }

#ifdef __GNUC__

    if (axiCfg == NULL)
    {
        return (int32_t)ADI_HAL_NULL_PTR;
    }
    
    ptr = (void *)axiCfg->mappedMemoryPtr;
    
    /* If UIO driver file not open */
    if (ptr == MAP_FAILED || ptr == NULL)
    {
        return (int32_t)ADI_HAL_BBICCTRL_FAIL;
    }

    if (writeFlag)
    {
        *((uint32_t *)((uintptr_t)ptr + offsetAddr)) = *data;
    }
    else
    {
        *data = *((uint32_t*)((uintptr_t)ptr + offsetAddr));
    }

#endif /* __GNUC__ */

    return halError;
}

/**
* \brief Writes and reads to the BBIC (FPGA) AXI memory mapped registers.
*
* \param devHalCfg Pointer to device instance specific platform settings
* \Param writeFlag 1 = write, 0 = read.
* \param addr the addrers to write the data to.
* \param data the data to write to address addr.
*
* \retval ADI_HAL_OK function completed successfully, no action required
* \retval ADI_HAL_NULL_PTR the function has been called with a null pointer
* \retval ADI_HAL_BBICCTRL_FAIL If critcal error during read or write transaction
*/
int32_t ads8_fpga_AxiBulkReadWrite(void *devHalCfg, uint8_t writeFlag, uint32_t addr, uint32_t data[], const uint32_t numData)
{
    adi_hal_Cfg_t *halCfg = NULL;
    adi_hal_fpga_AxiCfg_t *ramCfg = NULL;
    int32_t halError = (int32_t)ADI_HAL_OK;
    /* uint32_t offsetAddr = 0; */
    void *ptr = NULL;
    
    if (devHalCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    halCfg = (adi_hal_Cfg_t *)devHalCfg;
    ramCfg = &halCfg->bbicCfg.ramCfg;

    if (ramCfg == NULL)
    {
        halError = (int32_t)ADI_HAL_NULL_PTR;
        return halError;
    }
    
    if (addr + numData > ramCfg->mapSize)
    {
        halError = (int32_t)ADI_HAL_BBICCTRL_FAIL;
        return halError;
    }

#ifdef __GNUC__
    
    ptr = (void *)ramCfg->mappedMemoryPtr;
    
    /* If UIO driver file not open */
    if (ptr == MAP_FAILED || ptr == NULL)
    {
        return (int32_t)ADI_HAL_BBICCTRL_FAIL;
    }

    if (writeFlag)
    {
        memcpy((void *)((uintptr_t)ptr + addr), data, numData * sizeof(uint32_t));
    }
    else
    {
        memcpy(data, (void *)((uintptr_t)ptr + addr), numData * sizeof(uint32_t));
    }

#endif /* __GNUC__ */
    
    return halError;
}
