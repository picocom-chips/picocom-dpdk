#ifndef FPGA9025_BF_HAL_H_
#define FPGA9025_BF_HAL_H_

#include <stdint.h>
#include <stddef.h>
#include "adi_common_hal.h"
#include "adi_fpga9025.h"
#include "./../../private/include/fpga9025_bf_hal_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BF_LOG_LEVEL 0xF

#define ADRV9025_BF_WRCACHE_ARRAY_SIZE 15
#define ADRV9025_BF_WRCACHE_ARRAY_TRIP_SIZE ADRV9025_BF_WRCACHE_ARRAY_SIZE -2

#define ADRV9025_BF_RDCACHE_ARRAY_SIZE 15
#define ADRV9025_BF_RDCACHE_ARRAY_TRIP_SIZE ADRV9025_BF_RDCACHE_ARRAY_SIZE -2

/* int32_t fpga9025_BfWriteCacheEn(adi_fpga9025_Device_t *device, adrv9025_Bf_WrCache_State_e wrCacheState); */
/* int32_t fpga9025_BfReadCacheEn(adi_fpga9025_Device_t *device, adrv9025_Bf_RdCache_State_e wrCacheState); */
int32_t fpga9025_BfReadCacheInit(adi_fpga9025_Device_t* device);

int32_t fpga9025_BfWriteCacheInit(adi_fpga9025_Device_t* device);

int32_t fpga9025_BfRegisterWrite(adi_fpga9025_Device_t* device,
                                 uint32_t               addr,
                                 uint32_t               regVal);

int32_t fpga9025_BfRegisterRead(adi_fpga9025_Device_t* device,
                                uint32_t               addr,
                                uint32_t*              regVal,
                                uint8_t                endOfBf);

int32_t fpga9025_BfFieldWrite(adi_fpga9025_Device_t* device,
                              uint32_t               addr,
                              uint32_t               fieldVal,
                              uint32_t               mask,
                              uint8_t                startBit);

int32_t fpga9025_BfFieldRead(adi_fpga9025_Device_t* device,
                             uint32_t               addr,
                             uint32_t*              fieldVal,
                             uint32_t               mask,
                             uint8_t                startBit);

int32_t fpga9025_BfReadAssembleData(adi_fpga9025_Device_t* device,
                                    uint32_t*              rxBfData,
                                    uint8_t                numRdBfData,
                                    uint64_t*              rdData);

int32_t fpga9025_BfWriteCacheFlush(adi_fpga9025_Device_t* device);

int32_t fpga9025_BfReadCacheFlush(adi_fpga9025_Device_t* device,
                                  uint64_t*              rdData,
                                  uint16_t*              numRxBitFields);

#ifdef __cplusplus
}
#endif

#endif /* ADRV9025_BF_HAL_H_ */
