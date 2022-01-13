/**
* \file adi_fpga9025_hal.c
* \brief Contains ADI Transceiver Hardware Abstraction functions
*        Analog Devices maintains and provides updates to this code layer.
*        The end user should not modify this file or any code in this directory.
*/

/* Intermediate platform HAL layer maintained by Analog Devices */

#include "adi_fpga9025_user.h"
#include "adi_fpga9025_hal.h"
#include "adi_fpga9025_error.h"
#include "adi_platform.h"

#include "../../private/include/fpga9025_bf_axi_hmc.h"

int32_t adi_fpga9025_RegisterFieldRead(adi_fpga9025_Device_t* device,
                                       const uint32_t         addr,
                                       uint32_t*              fieldVal,
                                       uint32_t               mask,
                                       uint8_t                startBit)
{
    int32_t  recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    uint32_t rdData         = 0;
    uint32_t regVal         = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    ADI_NULL_PTR_RETURN(&device->common,
                        fieldVal);

    recoveryAction = adi_fpga9025_RegisterRead(device,
                                               addr,
                                               &rdData);
    ADI_ERROR_RETURN(device->common.error.newAction);

    regVal    = rdData;
    *fieldVal = (regVal & mask) >> startBit;

    return recoveryAction;
}

int32_t adi_fpga9025_RegisterFieldWrite(adi_fpga9025_Device_t* device,
                                        const uint32_t         addr,
                                        uint32_t               fieldVal,
                                        uint32_t               mask,
                                        uint8_t                startBit)
{
    UNUSED_PARA(startBit);
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint32_t registerVal = 0;
    uint32_t newRegVal   = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    recoveryAction = adi_fpga9025_RegisterRead(device,
                                               addr,
                                               &registerVal);
    ADI_ERROR_RETURN(device->common.error.newAction);

    /* modify the register value*/
    newRegVal = (registerVal & ~mask) | fieldVal;

    /* write to the register with modified value*/
    recoveryAction = adi_fpga9025_RegisterWrite(device,
                                                addr,
                                                newRegVal);
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RegisterRead(adi_fpga9025_Device_t* device,
                                  uint32_t               addr,
                                  uint32_t*              data)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t halError       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    halError = adi_hal_BbicRegisterRead(device->common.devHalInfo,
                                        addr,
                                        data);
    ADI_ERROR_REPORT(&device->common,
                     2,
                     (adi_common_ErrSources_e)halError,
                     ADI_COMMON_ACT_ERR_RESET_FULL,
                     NULL,
                     "FPGA AXI Reg Read error");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RegisterWrite(adi_fpga9025_Device_t* device,
                                   uint32_t               addr,
                                   uint32_t               data)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;
    int32_t halError       = 0;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    halError = adi_hal_BbicRegisterWrite(device->common.devHalInfo,
                                         addr,
                                         data);
    ADI_ERROR_REPORT(&device->common,
                     2,
                     (adi_common_ErrSources_e)halError,
                     ADI_COMMON_ACT_ERR_RESET_FULL,
                     NULL,
                     "FPGA Reg write error");
    ADI_ERROR_RETURN(device->common.error.newAction);

    return recoveryAction;
}

int32_t adi_fpga9025_RamRead(adi_fpga9025_Device_t* device,
                             const uint64_t         ramAddress,
                             uint32_t               data[],
                             uint32_t               length)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint32_t remainingLength = length;
    uint64_t endAddr         = ramAddress + (length * sizeof(uint32_t));
    uint64_t currRamAddress  = ramAddress;
    uint32_t currLength      = 0;
    uint32_t dataOffset      = 0;

    /* HMC = 8GB divided by pagesize withb a max page size of 1GB */
    /* offset into a page accessed via devuio1 */
    uint32_t offsetAddr       = ramAddress & (device->memoryPageSize - 1); /* Mask off the upper bits in the addr */
    uint8_t  pageId           = (uint8_t)(ramAddress / device->memoryPageSize);
    uint64_t nextPageBoundary = (uint64_t)(pageId + 1) * device->memoryPageSize;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (ramAddress % ADI_FPGA9025_RAM_ADDRESS_BOUNDARY != 0)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         ramAddress,
                         "RAM address must be on a 128 byte boundary");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    do
    {
        recoveryAction = fpga9025_AxiHmcAxilitePageBfSet(device,
                                                         FPGA9025_BF_AXI_HMC,
                                                         pageId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Could not write to HMC page");
        ADI_ERROR_RETURN(device->common.error.newAction);

        currLength = (uint32_t)((endAddr > nextPageBoundary) ? (nextPageBoundary - currRamAddress) / sizeof(uint32_t) : remainingLength);
        /* If we cross a page boundary, only send the difference */

        recoveryAction = adi_hal_BbicRegistersRead(device->common.devHalInfo,
                                                   offsetAddr,
                                                   &data[dataOffset],
                                                   currLength);
        ADI_ERROR_REPORT(&device->common,
                         device->common.error.errSource,
                         device->common.error.errCode,
                         recoveryAction,
                         device->common.error.varName,
                         device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);

        remainingLength -= currLength;
        offsetAddr = 0;
        /* The first access could be in the middle of a page. However, each subsequent pages will be offset 0 from the start of that page */
        currRamAddress += currLength * sizeof(uint32_t); /* Move to where the next access will point to in RAM */
        pageId++;                                        /* Move to the next page */
        dataOffset += currLength;                        /* Move to the next block in the data array */
        nextPageBoundary += device->memoryPageSize;
    }
    while (remainingLength > 0);

    return recoveryAction;
}

int32_t adi_fpga9025_RamWrite(adi_fpga9025_Device_t* device,
                              const uint64_t         ramAddress,
                              uint32_t               data[],
                              uint32_t               length)
{
    int32_t recoveryAction = ADI_COMMON_ACT_NO_ACTION;

    uint32_t remainingLength = length;
    uint64_t endAddr         = ramAddress + (length * sizeof(uint32_t));
    uint64_t currRamAddress  = ramAddress;
    uint32_t currLength      = 0;
    uint32_t dataOffset      = 0;

    /* HMC = 8GB divided by pagesize withb a max page size of 1GB */
    /* offset into a page accessed via devuio1 */
    uint32_t offsetAddr       = ramAddress & (device->memoryPageSize - 1); /* Mask off the upper bits in the addr */
    uint8_t  pageId           = (uint8_t)(ramAddress / device->memoryPageSize);
    uint64_t nextPageBoundary = (uint64_t)(pageId + 1) * device->memoryPageSize;

    ADI_NULL_DEVICE_PTR_RETURN(device);

#if ADI_FPGA9025_VERBOSE > 0
    ADI_FUNCTION_ENTRY_LOG(&device->common,
                           ADI_COMMON_LOG_API);
#endif

    if (ramAddress % ADI_FPGA9025_RAM_ADDRESS_BOUNDARY != 0)
    {
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_COMMON_ERR_INV_PARAM,
                         ADI_COMMON_ACT_ERR_CHECK_PARAM,
                         ramAddress,
                         "RAM address must be on a 128 byte boundary");
        ADI_ERROR_RETURN(device->common.error.newAction);
    }

    do
    {
        recoveryAction = fpga9025_AxiHmcAxilitePageBfSet(device,
                                                         FPGA9025_BF_AXI_HMC,
                                                         pageId);
        ADI_ERROR_REPORT(&device->common,
                         ADI_COMMON_ERRSRC_API,
                         ADI_FPGA9025_ERR_REGISTER_IO_FAIL,
                         recoveryAction,
                         NULL,
                         "Could not write to HMC page");
        ADI_ERROR_RETURN(device->common.error.newAction);

        currLength = (uint32_t)((endAddr > nextPageBoundary) ? (nextPageBoundary - currRamAddress) / sizeof(uint32_t) : remainingLength);
        /* If we cross a page boundary, only send the difference */

        recoveryAction = adi_hal_BbicRegistersWrite(device->common.devHalInfo,
                                                    offsetAddr,
                                                    &data[dataOffset],
                                                    currLength);
        ADI_ERROR_REPORT(&device->common,
                         device->common.error.errSource,
                         device->common.error.errCode,
                         recoveryAction,
                         device->common.error.varName,
                         device->common.error.errormessage);
        ADI_ERROR_RETURN(device->common.error.newAction);

        remainingLength -= currLength;
        offsetAddr = 0;
        /* The first access could be in the middle of a page. However, each subsequent pages will be offset 0 from the start of that page */
        currRamAddress += currLength * sizeof(uint32_t); /* Move to where the next access will point to in RAM */
        pageId ++;                                       /* Move to the next page */
        dataOffset += currLength;                        /* Move to the next block in the data array */
        nextPageBoundary += device->memoryPageSize;
    }
    while (remainingLength > 0);

    return recoveryAction;
}
