#include <stdio.h>
#include "gps_parse.h"

uint8_t buff[2048] = {
	"$GNRMC,084257.000,A,2234.7758,N,11354.9654,E,0.032,306.43,140618,,,D*46\r\n"};


int main(void)
{
   
    GPS_Parse(buff);
}
