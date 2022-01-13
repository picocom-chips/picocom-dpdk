#ifndef _ADI_FMC_EEPROM_H__
#define _ADI_FMC_EEPROM_H__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char* read_file(const char* file_name);

int32_t adi_FmcEepromInfoGet(uint32_t fmcIndex,
                             char*    infoStr,
                             int32_t  infoStrSize);

int32_t adi_FmcEepromDescriptionGet(uint32_t fmcIndex,
                                    char*    descStr,
                                    int32_t  descStrSize);

int32_t adi_FmcEepromPartNumGet(uint32_t fmcIndex,
                                char*    partNumStr,
                                int32_t  partNumStrSize);

int32_t adi_FmcEepromSerialNumGet(uint32_t fmcIndex,
                                  char*    serialStr,
                                  int32_t  serialStrSize);

int32_t adi_FmcEepromNameGet(uint32_t fmcIndex,
                             char*    pcbIdStr,
                             int32_t  pcbIdStrSize);

#ifdef __cplusplus
}
#endif
#endif
