/**
* \file adi_fpga9010_hal.c
* \brief Contains ADI Transceiver Hardware Abstraction functions
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/

/* Intermediate platform HAL layer maintained by Analog Devices */

#include "adi_fpga9010_user.h"
#include "adi_fpga9010_hal.h"
#include "adi_fpga9010_error.h"
#include "adi_platform.h"
#include "../../private/include/fpga9010_bf_axi_memory_pager.h"



int32_t adi_fpga9010_RegisterFieldRead(adi_fpga9010_Device_t *device, 
                                   const uint32_t addr, 
                                   uint32_t *fieldVal, 
                                   uint32_t mask, 
                                   uint8_t startBit)
{
    uint32_t rdData = 0;
    uint32_t regVal = 0;
    //uint8_t i = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    ADI_NULL_PTR_RETURN(&device->common, fieldVal);

    adi_fpga9010_RegisterRead(device, addr, &rdData);
    ADI_ERROR_RETURN(device->common.error.newAction);

    regVal = rdData;
    *fieldVal = (regVal & mask) >> startBit;

    return (device->common.error.newAction);
}



int32_t adi_fpga9010_RegisterFieldWrite(adi_fpga9010_Device_t *device, const uint32_t addr, uint32_t fieldVal, uint32_t mask, uint8_t startBit)
{
    UNUSED_PARA(startBit);
    
    uint32_t registerVal = 0;
    uint32_t newRegVal = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    adi_fpga9010_RegisterRead(device, addr, &registerVal);
    ADI_ERROR_RETURN(device->common.error.newAction);

                /* modify the register value*/
    newRegVal = (registerVal & ~mask) | fieldVal;

                /* write to the register with modified value*/
    adi_fpga9010_RegisterWrite(device, addr, newRegVal);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}

int32_t adi_fpga9010_RegisterRead(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t *data)
{
    int32_t halError = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
        ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    halError = adi_hal_BbicRegisterRead(device->common.devHalInfo, addr, data);
    ADI_ERROR_REPORT(&device->common, 2, (adi_common_ErrSources_e)halError, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "FPGA AXI Reg Read error");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}


int32_t adi_fpga9010_RegisterWrite(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t data)
{
    int32_t halError = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
        ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif

    halError = adi_hal_BbicRegisterWrite(device->common.devHalInfo, addr, data);
    ADI_ERROR_REPORT(&device->common, 2, (adi_common_ErrSources_e)halError, ADI_COMMON_ACT_ERR_RESET_FULL, NULL, "FPGA Reg write error");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return (device->common.error.newAction);
}


/**
* \brief used to page receive data from within the microzed.
* The Ads8 memory is 4GB and the microzed memory is 256Mb.
* To read all the Ads8 memory 16 pages would be necessary.
* memory reading is consecutive.
*
* each converter is assigned memory 
*
*/
int32_t adi_fpga9010_RamRead(adi_fpga9010_Device_t *device, const uint32_t ramAddress, uint32_t data[], uint32_t length)
{
    //todo add loop for length > memory page size
    uint32_t remainingLength = length;
    uint32_t endAddr = ramAddress + (length * sizeof(uint32_t));
    uint32_t currRamAddress = ramAddress;
    uint32_t currLength = 0;
    uint32_t dataOffset = 0;
    
    //ADS8 memory = 4GB divided by pagesize withb a max page size of 256MB
    // offset into a page accessed via devuio1
    uint32_t offsetAddr = ramAddress & (device->memoryPageSize - 1); /* Mask off the upper bits in the addr addressed by Page ID */
    uint64_t pageSizeMask = ~((uint64_t)(device->memoryPageSize - 1)); /* Mask off the lower bits */
    uint64_t pageId = ((uint64_t)ramAddress & pageSizeMask);
    uint64_t nextPageBoundary = pageId + device->memoryPageSize;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    if (ramAddress % sizeof(uint32_t) != 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, ramAddress, "RAM address must be word aligned");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    fpga9010_AxiMemoryPagerPageSizeBfSet(device, FPGA9010_BF_MEMORY_PAGE, (device->memoryPageSize - 1));
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    do
    {
        fpga9010_AxiMemoryPagerPageIdBfSet(device, FPGA9010_BF_MEMORY_PAGE, pageId);
        ADI_ERROR_RETURN(device->common.error.newAction);
    
        currLength = (uint32_t)((endAddr > nextPageBoundary) ? (nextPageBoundary - currRamAddress) / sizeof(uint32_t) : remainingLength); /* If we cross a page boundary, only send the difference */
        
        adi_hal_BbicRegistersRead(device->common.devHalInfo, offsetAddr, &data[dataOffset], currLength);

        ADI_ERROR_RETURN(device->common.error.newAction);
        
        remainingLength -= currLength;
        offsetAddr = 0; /* Except for the first access, every access will start at offset 0 */
        currRamAddress += currLength * sizeof(uint32_t); /* Move to where the next access will point to in RAM */
        pageId += ((uint64_t)currRamAddress & pageSizeMask); /* Move to the next page */
        dataOffset += currLength; /* Move to the next block in the data array */
        nextPageBoundary += device->memoryPageSize;
    } while (remainingLength > 0);
    
    return (device->common.error.newAction);
}


/**
* \brief used to page write data within the microzed.
* The Ads8 memory is 4GB and the microzed memory is 256Mb.
* To write to all the Ads8 memory 16 pages would be necessary.
* memory reading is consecutive.
*
* each converter is assigned memory 
*
*/
int32_t adi_fpga9010_RamWrite(adi_fpga9010_Device_t *device, const uint32_t ramAddress, uint32_t data[], uint32_t length)
{
    //todo add loop for length > memory page size
    uint32_t remainingLength = length;
    uint32_t endAddr = ramAddress + (length * sizeof(uint32_t));
    uint32_t currRamAddress = ramAddress;
    uint32_t currLength = 0;
    uint32_t dataOffset = 0;
    
    //ADS8 memory = 4GB divided by pagesize withb a max page size of 256MB
    // offset into a page accessed via devuio1
    uint32_t offsetAddr = ramAddress & (device->memoryPageSize - 1); /* Mask off the upper bits in the addr addressed by Page ID */
    uint64_t pageSizeMask = ~((uint64_t)(device->memoryPageSize - 1)); /* Mask off the lower bits */
    uint64_t pageId = ((uint64_t)ramAddress & pageSizeMask);
    uint64_t nextPageBoundary = pageId + device->memoryPageSize;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9010_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common, ADI_COMMON_LOG_API);
#endif
    
    if (ramAddress % sizeof(uint32_t) != 0)
    {
        ADI_ERROR_REPORT(&device->common, ADI_COMMON_ERRSRC_API, ADI_COMMON_ERR_INV_PARAM, ADI_COMMON_ACT_ERR_CHECK_PARAM, ramAddress, "RAM address must be word aligned");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }
    
    fpga9010_AxiMemoryPagerPageSizeBfSet(device, FPGA9010_BF_MEMORY_PAGE, (device->memoryPageSize - 1));
    ADI_ERROR_RETURN(device->common.error.newAction);
    
    do
    {
        fpga9010_AxiMemoryPagerPageIdBfSet(device, FPGA9010_BF_MEMORY_PAGE, pageId);
        ADI_ERROR_RETURN(device->common.error.newAction);
    
        currLength = (uint32_t)((endAddr > nextPageBoundary) ? (nextPageBoundary - currRamAddress) / sizeof(uint32_t) : remainingLength); /* If we cross a page boundary, only send the difference */

        adi_hal_BbicRegistersWrite(device->common.devHalInfo, offsetAddr, &data[dataOffset], currLength);

        ADI_ERROR_RETURN(device->common.error.newAction);
        
        remainingLength -= currLength;
        offsetAddr = 0; /* Except for the first access, every access will start at offset 0 */
        currRamAddress += currLength * sizeof(uint32_t); /* Move to where the next access will point to in RAM */
        pageId += ((uint64_t)currRamAddress & pageSizeMask); /* Move to the next page */
        dataOffset += currLength; /* Move to the next block in the data array */
        nextPageBoundary += device->memoryPageSize;
    } while (remainingLength > 0);
    
    return (device->common.error.newAction);
}
