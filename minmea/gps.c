#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "portserial.h"
#include "gps_parse.h"

int main(int argc,char *argv[])
{
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

	GPS_Parse(pucBuffer);
   }
    
   close(fd);

   return 0;
}
