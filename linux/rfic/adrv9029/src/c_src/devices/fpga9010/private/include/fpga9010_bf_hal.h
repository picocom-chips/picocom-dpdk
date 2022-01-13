
#ifndef FPGA9010_BF_HAL_H_
#define FPGA9010_BF_HAL_H_

#include <stdint.h>
#include <stddef.h>
#include "adi_common_hal.h"
#include "adi_fpga9010.h"
#include "./../../private/include/fpga9010_bf_hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif



#define BF_LOG_LEVEL 0xF


#define ADRV9010_BF_WRCACHE_ARRAY_SIZE 15
#define ADRV9010_BF_WRCACHE_ARRAY_TRIP_SIZE ADRV9010_BF_WRCACHE_ARRAY_SIZE -2

#define ADRV9010_BF_RDCACHE_ARRAY_SIZE 15
#define ADRV9010_BF_RDCACHE_ARRAY_TRIP_SIZE ADRV9010_BF_RDCACHE_ARRAY_SIZE -2


//int32_t fpga9010_BfWriteCacheEn(adi_fpga9010_Device_t *device, adrv9010_Bf_WrCache_State_e wrCacheState);
//int32_t fpga9010_BfReadCacheEn(adi_fpga9010_Device_t *device, adrv9010_Bf_RdCache_State_e wrCacheState);
int32_t fpga9010_BfReadCacheInit(adi_fpga9010_Device_t *device);
int32_t fpga9010_BfWriteCacheInit(adi_fpga9010_Device_t *device);

int32_t fpga9010_BfRegisterWrite(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t regVal);
int32_t fpga9010_BfRegisterRead(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t *regVal);

int32_t fpga9010_BfFieldWrite(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t  fieldVal, uint32_t mask, uint8_t startBit);
int32_t fpga9010_BfFieldRead(adi_fpga9010_Device_t *device, uint32_t addr, uint32_t *fieldVal, uint32_t mask, uint8_t startBit);

int32_t fpga9010_BfReadAssembleData(adi_fpga9010_Device_t *device, uint32_t *rxBfData, uint8_t numRdBfData, uint64_t *rdData);
int32_t fpga9010_BfWriteCacheFlush(adi_fpga9010_Device_t *device);
int32_t fpga9010_BfReadCacheFlush(adi_fpga9010_Device_t *device, uint64_t *rdData, uint16_t *numRxBitFields);

#ifdef __cplusplus
}
#endif

#endif /* ADRV9010_BF_HAL_H_ */