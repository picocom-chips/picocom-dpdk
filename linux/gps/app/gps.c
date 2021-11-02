/*
 * This file is part of nmealib.
 *
 * Copyright (c) 2008 Timur Sinitsyn
 * Copyright (c) 2011 Ferry Huberts
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <nmea/nmea.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "portserial.h"

int main(int argc,char *argv[])
{
    nmeaINFO info;
    nmeaPARSER parser;
    nmeaPOS dpos;
    
    int ret;
    char buf_read[512];
    char tty[20]="/dev/ttyS1";
    uint8_t pucBuffer[2048];
    int fd = 0;

    fd = open(tty, O_RDWR);
    if(fd == -1)
    {
        printf("Open %s failed! Exit!\n",tty);
        exit(1);
    }
    printf("open %s successfully!\n",tty);

   ret = set_opt(fd, 115200, 8, 'N', 1);
   if (ret == -1)
   {
       printf("Set %s failed! Exit!\n",tty);
       exit(1);
   }
   printf("Set %s successfully!\n",tty);
   printf("Baud rate: 115200\n");	

   ret = gpsGetData(fd, 500, pucBuffer, 2048);
   if(ret > 0)
   {	

     printf("Read data: ret = %d, %s\n\n", ret, pucBuffer);
     printf("-------------\n");

     nmea_zero_INFO(&info);
     nmea_parser_init(&parser);

     nmea_parse(&parser, pucBuffer, ret, &info);

     nmea_info2pos(&info, &dpos);
     printf("Lat: %f, Lon: %f, Sig: %d, Fix: %d\n", dpos.lat,
            dpos.lon, info.sig, info.fix);

     nmea_parser_destroy(&parser);
   }
    
   close(fd);

   return 0;
}
