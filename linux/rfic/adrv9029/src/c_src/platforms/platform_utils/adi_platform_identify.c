#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __GNUC__
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <strings.h>
#else
#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define strncasecmp(x,y,z) _strnicmp(x,y,z)
#endif
#include <fcntl.h>
#include <string.h>
/* #define __USE_XOPEN */ /* needed for strptime */
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "adi_platform_identify.h"
#include "adi_fmc_eeprom.h"
#include "adi_fmc_fru.h"

int32_t adi_platform_Identify(uint32_t* platform)
{
    adi_hal_Err_e retVal      = ADI_HAL_OK;
    //char          bufStr[128] = {0};
    //FILE*         identityFD  = NULL;
    
#if 0
    if ((identityFD = fopen(MOTHERBOARD_NAME_PATH,
                            "r")) == NULL)
    {
        return (ADI_HAL_GEN_SW);
    }

    if (fgets(bufStr,
              64,
              identityFD) == NULL)
    {
        return (ADI_HAL_GEN_SW);
    }

    if (strstr(bufStr,
               "9025") != NULL)
    {
        *platform = (uint32_t)ADI_ADS9_PLATFORM;
    }
    else if (strstr(bufStr,
                    "9010") != NULL)
    {
        *platform = (uint32_t)ADI_ADS8_PLATFORM;
    }
    else if (strstr(bufStr,
                    "tokelau") != NULL)
    {
        *platform = (uint32_t)ADI_ADS8_PLATFORM;
    }
    else
    {
        printf("ERROR: %s:%u has failed.\n",
               __func__,
               __LINE__);
        return (ADI_HAL_GEN_SW);
    }
#else
    *platform = (uint32_t)ADI_ADS9_PLATFORM;
#endif

    return (int32_t)retVal;
}
