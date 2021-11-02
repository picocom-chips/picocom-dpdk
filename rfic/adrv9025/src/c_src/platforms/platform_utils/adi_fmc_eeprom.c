/*
 * Functions to read I2C EEPROM info based on FMC EEPROM format
 */

#include "adi_fmc_eeprom.h"

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
#include "adi_platform_types.h"
#include "adi_fmc_fru.h"

#define DUMP_BOARD     (0x01)
#define DUMP_SUPPLY    (0x02)
#define DUMP_CONNECTOR (0x04)
#define DUMP_I2C       (0x08)

static int quiet   = 0;
static int verbose = 0;

void printf_err(const char* fmt,
    ...)
{
    va_list ap;
    va_start(ap,
             fmt);
    vfprintf(stderr,
             fmt,
             ap);
    va_end(ap);
}

void* x_calloc(size_t nmemb,
               size_t size)
{
    unsigned int* ptr;

    if ((ptr = (unsigned int *)calloc(nmemb,
                                      size)) == NULL)
    {
        printf_err("ERROR: calloc could not allocate requested memory\n");
    }

    return (void *)ptr;
}

void printf_warn(const char* fmt,
    ...)
{
    va_list ap;

    if (quiet || !verbose)
    {
        return;
    }

    va_start(ap,
             fmt);
    vprintf(fmt,
            ap);
    va_end(ap);
}

void printf_info(const char* fmt,
    ...)
{
    va_list ap;

    if (quiet)
    {
        return;
    }

    va_start(ap,
             fmt);
    vprintf(fmt,
            ap);
    va_end(ap);
}

/*
 * Read in the file of the disk, or from the EEPROM
 */
unsigned char* read_file(const char* file_name)
{
    FILE*          fp;
    unsigned char* p;
    size_t         byteRead = 1;

    if ((fp = fopen(file_name,
                    "rb")) == NULL)
    {
        printf_err("Cannot open EEPROM file '%s'\n",
                   file_name);
        return NULL;
    }

    if ((p = (unsigned char *)x_calloc(1024,
                                       1)) == NULL)
    {
        if (fclose(fp) != 0)
        {
            printf_err("Cannot close file.\n");
        }
        return NULL;
    }

    byteRead = fread(p,
                     1,
                     1024,
                     fp);

    if ((byteRead < 256) || !feof(fp))
    {
        printf("Didn't read the entire EEPROM input file %s, it's too long\n",
               file_name);
    }

    if (fclose(fp) != 0)
    {
        printf_err("Cannot close file.\n");
    }
    return p;
}

void write_FRU(struct FRU_DATA* fru,
               char*            file_name,
               bool             packed)
{
    size_t         len;
    unsigned char* buf = NULL;
    FILE*          fp;

    /* Build as ASCII output */
    buf = build_FRU_blob(fru,
                         &len,
                         packed);

    /* If it's too big, try again, with 6-bit packed */
    if (len >= 255 && !packed)
    {
        free(buf);
        buf = build_FRU_blob(fru,
                             &len,
                             1);
        if (len >= 255)
        {
            free(buf);
            printf_err("Not able to pack things into 255 char, no output\n");
            return;
        }
    }

    if (!strcmp("-",
                file_name))
    {
#ifdef __GNUC__
        ssize_t tmp;
        tmp = write(STDOUT_FILENO,
                    buf,
                    len);
        if ((size_t)tmp != len)
            printf_err("Didn't write entire file\n");
#endif
    }
    else
    {
        if ((fp = fopen(file_name,
                        "wb")) == NULL)
        {
            printf_err("Cannot open file.\n");
            free(buf);
            return;
        }

        fwrite(buf,
               1,
               len,
               fp);
        if (fclose(fp) != 0)
        {
            printf_err("Cannot close file.\n");
        }
    }
    printf_info("wrote %i bytes to %s\n",
                len,
                file_name);

    free(buf);
}

static void dump_fru_field(const char*    description,
                           size_t         offset,
                           unsigned char* field)
{
    (void)(description);
    /* does field exist, and have length? */
    if (field)
    {
        /*printf("%s\t: ", description);*/
        if (FIELD_LEN(field))
        {
            if (TYPE_CODE(field) == FRU_STRING_ASCII || offset)
            {
                printf("%s",
                       &field[offset + 1]); /*first char is a field type byte*/
            }
            else
            {
                printf("Non-ASCII\n");
            }
        }
        else
            printf("Empty Field\n");
    }
}

void dump_BOARD(struct BOARD_INFO* fru)
{
    uint32_t i, j;
    /*time_t tmp = min2date(fru->mfg_date);*/

    if (fru == NULL)
    {
        return;
    }

    /*printf("Date of Man\t: %s", ctime(&tmp));*/
    dump_fru_field("Manufacture",
                   0,
                   fru->manufacturer);
    printf(":");
    dump_fru_field("Product Name",
                   0,
                   fru->product_name);
    printf(":");
    dump_fru_field("Serial Number",
                   0,
                   fru->serial_number);
    printf(":");
    dump_fru_field("Part Number",
                   0,
                   fru->part_number);
    /*dump_fru_field("FRU File ID", 0, fru->FRU_file_ID);*/
    printf(":");
    if (!strncasecmp((const char *)&fru->manufacturer[1],
                     "Analog Devices",
                     strlen("Analog Devices")))
    {
        for (i = 0; i < CUSTOM_FIELDS; i++)
        {
            /* These are ADI custom fields */
            if (fru->custom[i] && (fru->custom[i][0] & 0x3F))
            {
                switch (fru->custom[i][1])
                {
                case 0:
                    /*dump_fru_field("PCB Rev ", 1, fru->custom[i]);*/
                    break;
                case 1:
                    dump_fru_field("PCB ID  ",
                                   1,
                                   fru->custom[i]);
                    break;
                case 2:
                    /*dump_fru_field("BOM Rev ", 1, fru->custom[i]);*/
                    break;
                case 3:
                    /*dump_fru_field("Uses LVDS", 1, fru->custom[i]);*/
                    break;
                default:
                    /*dump_fru_field("Unknown ", 1, fru->custom[i]);*/
                    break;
                }
            }
        }
    }
    else
    {
        printf("Custom Fields:\n");
        for (i = 0; i < CUSTOM_FIELDS; i++)
        {
            if (fru->custom[i] && (fru->custom[i][0] & 0x3F))
            {
                printf("  Field %i (len=%i):",
                       i,
                       fru->custom[i][0] & 0x3F);
                for (j = 1; j <= (uint32_t)(fru->custom[i][0] & 0x3F); j++)
                    printf(" %02x",
                           fru->custom[i][j] & 0xFF);
                printf("  |");
                for (j = 1; j <= (uint32_t)(fru->custom[i][0] & 0x3F); j++)
                    printf("%c",
                           ((fru->custom[i][j] < 32) || (fru->custom[i][j] >= 127)) ? '.' : fru->custom[i][j]);
                printf("|\n");
            }
        }
    }
}

/* 
 * DC Load and DC Output Multi-record Definitions
 * Table 8 from the VITA/ANSI 57.1 Spec
 */
const char* DC_Loads[] = {
    "P1 VADJ",
    /* Load   :  0 */
    "P1 3P3V",
    /* Load   :  1 */
    "P1 12P0V",
    /* Load   :  2 */
    "P1 VIO_B_M2C",
    /* Output :  3 */
    "P1 VREF_A_M2C",
    /* Output :  4 */
    "P1 VREF_B_M2C",
    /* Output :  5 */
    "P2 VADJ",
    /* Load   :  6 */
    "P2 3P3V",
    /* Load   :  7 */
    "P2 12P0V",
    /* Load   :  8 */
    "P2 VIO_B_M2C",
    /* Load   :  9 */
    "P2 VREF_A_M2C",
    /* Load   : 10 */
    "P2 VREF_B_M2C",
    /* Load   : 11 */
};

void dump_MULTIRECORD(struct MULTIRECORD_INFO* fru)
{
    unsigned char *p, *n, *z;
    int            i;

    z = (unsigned char *)x_calloc(1,
                                  12);

    for (i = 0; i <= NUM_SUPPLIES - 1; i++)
    {
        if (!fru->supplies[i])
            continue;
        p = fru->supplies[i];
        n = p + 5;
        switch (p[0])
        {
        case 1:
            printf("DC Output\n");
            printf("  Output Number: %d (%s)\n",
                   n[0] & 0xF,
                   DC_Loads[n[0] & 0xF]);
            if (memcmp(&n[1],
                       z,
                       11))
            {
                printf("  Nominal volts:              %d (mV)\n",
                       (n[1] | (n[2] << 8)) * 10);
                printf("  Maximum negative deviation: %d (mV)\n",
                       (n[3] | (n[4] << 8)) * 10);
                printf("  Maximum positive deviation: %d (mV)\n",
                       (n[5] | (n[6] << 8)) * 10);
                printf("  Ripple and Noise pk-pk:     %d (mV)\n",
                       n[7] | (n[8] << 8));
                printf("  Minimum current draw:       %d (mA)\n",
                       n[9] | (n[10] << 8));
                printf("  Maximum current draw:       %d (mA)\n",
                       n[11] | (n[12] << 8));
            }
            else
                printf("  All Zeros\n");
            break;
        case 2:
            printf("DC Load\n");
            printf("  Output number: %d (%s)\n",
                   n[0] & 0xF,
                   DC_Loads[n[0] & 0xF]);
            printf("  Nominal volts:          %04d (mV)\n",
                   (n[1] | (n[2] << 8)) * 10);
            printf("  Minimum voltage:        %04d (mV)\n",
                   (n[3] | (n[4] << 8)) * 10);
            printf("  Maximum voltage:        %04d (mV)\n",
                   (n[5] | (n[6] << 8)) * 10);
            printf("  Ripple and Noise pk-pk: %04d (mV)\n",
                   n[7] | (n[8] << 8));
            printf("  Minimum current load:   %04d (mA)\n",
                   n[9] | (n[10] << 8));
            printf("  Maximum current load:   %04d (mA)\n",
                   n[11] | (n[12] << 8));
            break;
        }
    }
    free(z);
}

void dump_i2c(struct MULTIRECORD_INFO* fru)
{
    unsigned char *p, *n;
    unsigned int   shift;

    if (!fru->i2c_devices)
    {
        printf("No I2C information\n");
        return;
    }

    p = fru->i2c_devices;
    while (*p)
    {
        n = p;
        /* skip address for now */
        while (*p < '0')
            p++;
        /* print name */
        while (*p >= '0')
        {
            printf("%c",
                   *p);
            p++;
        }
        /* now print the address */
        printf("\t");
        while ((*n - 0x20) <= 0x0F)
        {
            printf("0x%02x|0x%02x (0b",
                   (*n - 0x20) << 4,
                   (*n - 0x20) << 3);
            for (shift = 0x08; shift > 0; shift >>= 1)
                printf("%s",
                       (((*n - 0x20) & shift) == shift) ? "1" : "0");
            printf("nnn[RW]);  ");
            n++;
        }
        printf("\n");
    }
}

void dump_FmConnector(struct MULTIRECORD_INFO* fru)
{
    unsigned char *p, *n;

    if (!fru->connector)
    {
        printf("No Connector information\n");
        return;
    }

    p = fru->connector;
    n = p + 5;

    n += 3;
    switch (n[1] >> 6)
    {
    case 0:
        printf("Single Width Card\n");
        break;
    case 1:
        printf("Double Width Card\n");
        break;
    default:
        printf("error - not the right size\n");
        break;
    }
    switch ((n[1] >> 4) & 0x3)
    {
    case 0:
        printf("P1 is LPC\n");
        break;
    case 1:
        printf("P1 is HPC\n");
        break;
    default:
        printf("P1 not legal size\n");
        break;
    }
    switch ((n[1] >> 2) & 0x3)
    {
    case 0:
        printf("P2 is LPC\n");
        break;
    case 1:
        printf("P2 is HPC\n");
        break;
    case 3:
        if (n[1] >> 6 != 0)
            printf("P2 is not populated\n");
        break;
    default:
        printf("P2 not legal size\n");
        break;
    }
    printf("P1 Bank A Signals needed %d\n",
           n[2]);
    printf("P1 Bank B Signals needed %d\n",
           n[3]);
    printf("P1 GBT Transceivers needed %d\n",
           n[6] >> 4);
    if (((n[1] >> 2) & 0x3) != 3)
    {
        printf("P2 Bank A Signals needed %d\n",
               n[4]);
        printf("P2 Bank B Signals needed %d\n",
               n[5]);
        printf("P2 GBT Transceivers needed %d\n",
               n[6] & 0xF);
    }
    printf("Max JTAG Clock %d\n",
           n[7]);
}

/**
* \brief Read the FMC EEPROM on the daughtercard to identify a list of daughtercard information
* 
* Print the FMC Manufacturer, Product Name, Serial number, Part number, and PCB ID in a ; separated list.
* 
* \param fmcIndex Index used if the FMC carrier card has more than one daughter
*                 card FMC connector to specify which FMC daughtercard to read
* \param infoStr Character array that is used to return the daughtercard's product name
* \param infoStrSize Size of infoStr character array in bytes
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_GEN_SW If error reading EEPROM on daughtercard
*/
int32_t adi_FmcEepromInfoGet(uint32_t fmcIndex,
                             char*    infoStr,
                             int32_t  infoStrSize)
{
    (void)(fmcIndex);
    adi_hal_Err_e    retVal         = ADI_HAL_OK;
    const char*      input_file     = "/sys/bus/i2c/devices/3-0050/eeprom";
    uint8_t*         raw_input_data = NULL;
    uint32_t         i;
    struct FRU_DATA* fru           = NULL;
    char             tmp_str1[128] = {0};

    if ((raw_input_data = read_file(input_file)) != NULL)
    {
        fru = parse_FRU(raw_input_data);
        free(raw_input_data);

        /* The parse_FRU() will return a null pointer for fru if an error occurred during reading the EEPROM, so verify a non-NULL pointer */
        if (fru == NULL)
        {
            snprintf(infoStr,
                     infoStrSize,
                     "%s",
                     "ERROR: EEPROM not found or blank.");
            retVal = ADI_HAL_GEN_SW;
        }
        else
        {
            snprintf(infoStr,
                     infoStrSize,
                     "%s%s%s%s%s%s%s%s",
                     "Manufacturer:",
                     (fru->Board_Area->manufacturer + 1),
                     ";Product Name:",
                     (fru->Board_Area->product_name + 1),
                     ";Serial Number:",
                     (fru->Board_Area->serial_number + 1),
                     ";Part Number:",
                     (fru->Board_Area->part_number + 1));

            if (!strncasecmp((const char *)&fru->Board_Area->manufacturer[1],
                             "Analog Devices",
                             strlen("Analog Devices")))
            {
                for (i = 0; i < CUSTOM_FIELDS; i++)
                {
                    /* These are ADI custom fields */
                    if (fru->Board_Area->custom[i] && (fru->Board_Area->custom[i][0] & 0x3F))
                    {
                        switch (fru->Board_Area->custom[i][1])
                        {
                        case 0:
                            //dump_fru_field("PCB Rev ", 1, fru->custom[i]);
                            break;
                        case 1:

                            sprintf(tmp_str1,
                                    "%s",
                                    fru->Board_Area->custom[i]);
                            strncat(infoStr,
                                    ";PCB ID:",
                                    (infoStrSize - 1));
                            strncat(infoStr,
                                    &tmp_str1[2],
                                    (infoStrSize - 1));
                            break;
                        case 2:
                            sprintf(tmp_str1,
                                    "%s",
                                    fru->Board_Area->custom[i]);
                            strncat(infoStr,
                                    ";BOM REV:",
                                    (infoStrSize - 1));
                            strncat(infoStr,
                                    &tmp_str1[2],
                                    (infoStrSize - 1));
                            break;
                        case 3:
                            //dump_fru_field("Uses LVDS", 1, fru->custom[i]);
                            break;
                        default:
                            //dump_fru_field("Unknown ", 1, fru->custom[i]);
                            break;
                        }
                    }
                }
            }

            free_FRU(fru);
        } /* if fru is a valid pointer */
    }     /* if EEPROM file was readable, will still read even if daughter is not plugged on. */
    else
    {
        snprintf(infoStr,
                 infoStrSize,
                 "%s",
                 "ERROR: EEPROM not found or blank.");
        retVal = ADI_HAL_GEN_SW;
    }

    return (int32_t)retVal;
}

/**
* \brief Read the FMC EEPROM on the daughtercard to identify the daughtercard's description/product name
*
* \param fmcIndex Index used if the FMC carrier card has more than one daughter
*                 card FMC connector to specify which FMC daughtercard to read
* \param descStr Character array that is used to return the daughtercard's product name
* \param descStrSize Size of descStr character array in bytes
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_GEN_SW If error reading EEPROM on daughtercard
*/
int32_t adi_FmcEepromDescriptionGet(uint32_t fmcIndex,
                                    char*    descStr,
                                    int32_t  descStrSize)
{
    (void)(fmcIndex);
    adi_hal_Err_e    retVal         = ADI_HAL_OK;
    const char*      input_file     = "/sys/bus/i2c/devices/3-0050/eeprom";
    uint8_t*         raw_input_data = NULL;
    struct FRU_DATA* fru            = NULL;

    if ((raw_input_data = read_file(input_file)) != NULL)
    {
        fru = parse_FRU(raw_input_data);
        free(raw_input_data);

        /* The parse_FRU() will return a null pointer for fru if an error occurred during reading the EEPROM, so verify a non-NULL pointer */
        if (fru == NULL)
        {
            snprintf(descStr,
                     descStrSize,
                     "%s",
                     "ERROR: EEPROM not found or blank.");
            retVal = ADI_HAL_GEN_SW;
        }
        else
        {
            snprintf(descStr,
                     descStrSize,
                     "%s",
                     (fru->Board_Area->product_name + 1));

            free_FRU(fru);
        } /* if fru is a valid pointer */
    }     /* if EEPROM file was readable, will still read even if daughter is not plugged on. */
    else
    {
        snprintf(descStr,
                 descStrSize,
                 "%s",
                 "ERROR: EEPROM not found or blank.");
        retVal = ADI_HAL_GEN_SW;
    }

    return (int32_t)retVal;
}

/**
* \brief Read the FMC EEPROM on the daughtercard to identify the daughtercard's part number
*
* \param fmcIndex Index used if the FMC carrier card has more than one daughter
*                 card FMC connector to specify which FMC daughtercard to read
* \param partNumStr Character array that is used to return the part number
* \param partNumStrSize Size of partNumStr character array in bytes
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_GEN_SW If error reading EEPROM on daughtercard
*/
int32_t adi_FmcEepromPartNumGet(uint32_t fmcIndex,
                                char*    partNumStr,
                                int32_t  partNumStrSize)
{
    (void)(fmcIndex);
    adi_hal_Err_e    retVal         = ADI_HAL_OK;
    const char*      input_file     = "/sys/bus/i2c/devices/3-0050/eeprom";
    uint8_t*         raw_input_data = NULL;
    struct FRU_DATA* fru            = NULL;

    if (input_file == NULL)
    {
        snprintf(partNumStr,
                 partNumStrSize,
                 "%s",
                 "ERROR: EEPROM not found or blank.");
        retVal = ADI_HAL_GEN_SW;
    }
    else
    {
        if ((raw_input_data = read_file(input_file)) != NULL)
        {
            fru = parse_FRU(raw_input_data);
            free(raw_input_data);

            /* The parse_FRU() will return a null pointer for fru if an error occurred during reading the EEPROM, so verify a non-NULL pointer */
            if (fru == NULL)
            {
                snprintf(partNumStr,
                         partNumStrSize,
                         "%s",
                         "ERROR: EEPROM not found or blank.");
                retVal = ADI_HAL_GEN_SW;
            }
            else
            {
                snprintf(partNumStr,
                         partNumStrSize,
                         "%s",
                         (fru->Board_Area->part_number + 1));

                free_FRU(fru);
            } /* if fru is a valid pointer */
        }     /* if EEPROM file was readable, will still read even if daughter is not plugged on. */
        else
        {
            snprintf(partNumStr,
                     partNumStrSize,
                     "%s",
                     "ERROR: EEPROM not found or blank.");
            retVal = ADI_HAL_GEN_SW;
        }
    }

    return (int32_t)retVal;
}

/**
* \brief Read the FMC EEPROM on the daughtercard to identify the PCB Serial Number
*
* \param fmcIndex Index used if the FMC carrier card has more than one daughter
*                 card FMC connector to specify which FMC daughtercard to read
* \param serialStr Character array that is used to return the PCB Serial Number
* \param serialStrSize Size of serialStr character array in bytes
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_GEN_SW If error reading EEPROM on daughtercard
*/
int32_t adi_FmcEepromSerialNumGet(uint32_t fmcIndex,
                                  char*    serialStr,
                                  int32_t  serialStrSize)
{
    (void)(fmcIndex);
    adi_hal_Err_e    retVal         = ADI_HAL_OK;
    const char*      input_file     = "/sys/bus/i2c/devices/3-0050/eeprom";
    uint8_t*         raw_input_data = NULL;
    struct FRU_DATA* fru            = NULL;

    if (input_file == NULL)
    {
        snprintf(serialStr,
                 serialStrSize,
                 "%s",
                 "ERROR: EEPROM not found or blank.");
        retVal = ADI_HAL_GEN_SW;
    }
    else
    {
        if ((raw_input_data = read_file(input_file)) != NULL)
        {
            fru = parse_FRU(raw_input_data);
            free(raw_input_data);

            /* The parse_FRU() will return a null pointer for fru if an error occurred during reading the EEPROM, so verify a non-NULL pointer */
            if (fru == NULL)
            {
                snprintf(serialStr,
                         serialStrSize,
                         "%s",
                         "ERROR: EEPROM not found or blank.");
                retVal = ADI_HAL_GEN_SW;
            }
            else
            {
                snprintf(serialStr,
                         serialStrSize,
                         "%s",
                         (fru->Board_Area->serial_number + 1));

                free_FRU(fru);
            } /* if fru is a valid pointer */
        }     /* if EEPROM file was readable, will still read even if daughter is not plugged on. */
        else
        {
            snprintf(serialStr,
                     serialStrSize,
                     "%s",
                     "ERROR: EEPROM not found or blank.");
            retVal = ADI_HAL_GEN_SW;
        }
    }
    return (int32_t)retVal;
}

/**
* \brief Read the FMC EEPROM on the daughtercard to identify the PCB name
*
* \param fmcIndex Index used if the FMC carrier card has more than one daughter
*                 card FMC connector to specify which FMC daughtercard to read
* \param pcbIdStr Character array that is used to return the PCB name
* \param pcbIdStrSize Size of pcbIdStr character array in bytes
*
* \retval ADI_HAL_OK Function completed successfully
* \retval ADI_HAL_GEN_SW If error reading EEPROM on daughtercard
*/
int32_t adi_FmcEepromNameGet(uint32_t fmcIndex,
                             char*    pcbIdStr,
                             int32_t  pcbIdStrSize)
{
    (void)(fmcIndex);
    adi_hal_Err_e    retVal         = ADI_HAL_OK;
    const char*      input_file     = "/sys/bus/i2c/devices/3-0050/eeprom";
    int              i              = 0;
    unsigned char*   raw_input_data = NULL;
    struct FRU_DATA* fru            = NULL;

    if (input_file == NULL)
    {
        snprintf(pcbIdStr,
                 pcbIdStrSize,
                 "%s",
                 "ERROR: EEPROM not found or blank.");
        retVal = ADI_HAL_GEN_SW;
    }
    else
    {
        if ((raw_input_data = read_file(input_file)) != NULL)
        {
            fru = parse_FRU(raw_input_data);
            free(raw_input_data);

            if (fru == NULL)
            {
                snprintf(pcbIdStr,
                         pcbIdStrSize,
                         "%s",
                         "ERROR: EEPROM not found or blank.");
                retVal = ADI_HAL_GEN_SW;
            }
            else
            {
                if (!strncasecmp((const char *)&fru->Board_Area->manufacturer[1],
                                 "Analog Devices",
                                 strlen("Analog Devices")))
                {
                    for (i = 0; i < CUSTOM_FIELDS; i++)
                    {
                        /* These are ADI custom fields */
                        if (fru->Board_Area->custom[i] && (fru->Board_Area->custom[i][0] & 0x3F))
                        {
                            switch (fru->Board_Area->custom[i][1])
                            {
                            case 1:
                                snprintf(pcbIdStr,
                                         pcbIdStrSize,
                                         "%s",
                                         (fru->Board_Area->custom[i] + 2));
                                break;

                            default:
                                break;
                            }
                        }
                    }
                }

                free_FRU(fru);
            }
        }
        else
        {
            snprintf(pcbIdStr,
                     pcbIdStrSize,
                     "%s",
                     "ERROR: EEPROM not found or blank.");
            retVal = ADI_HAL_GEN_SW;
        }
    }

    return (int32_t)retVal;
}
