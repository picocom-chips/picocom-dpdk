/* ----------------------- Standard includes --------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if( tcgetattr( fd,&oldtio)  !=  0) {
	    perror("tcgetattr error");
	    return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD; 
	newtio.c_cflag &= ~CSIZE; 

	switch( nBits )
	{
	    case 7:
	        newtio.c_cflag |= CS7;
	        break;
	    case 8:
	        newtio.c_cflag |= CS8;
	        break;
	}

	switch( nEvent )
	{
	    case 'O':
	        newtio.c_cflag |= PARENB; 
	        newtio.c_cflag |= PARODD;  
	        newtio.c_iflag |= (INPCK | ISTRIP); 
	        break;
	    case 'E':
                newtio.c_iflag |= (INPCK | ISTRIP);
                newtio.c_cflag |= PARENB;
                newtio.c_cflag &= ~PARODD;
                break;
	    case 'N': 
	        newtio.c_cflag &= ~PARENB;
	        break;
	}

	switch( nSpeed )
	{
	    case 2400:
	        cfsetispeed(&newtio, B2400);
	        cfsetospeed(&newtio, B2400);
	        break;
	    case 4800:
	        cfsetispeed(&newtio, B4800);
	        cfsetospeed(&newtio, B4800);
	        break;
	    case 9600:
	        cfsetispeed(&newtio, B9600);
	        cfsetospeed(&newtio, B9600);
	        break;
	    case 115200:
	        cfsetispeed(&newtio, B115200);
	        cfsetospeed(&newtio, B115200);
	        break;
	    case 460800:
	        cfsetispeed(&newtio, B460800);
	        cfsetospeed(&newtio, B460800);
	        break;
	    default:
	        cfsetispeed(&newtio, B9600);
	        cfsetospeed(&newtio, B9600);
	        break;
	}

	if( nStop == 1){
	    newtio.c_cflag &=  ~CSTOPB; 
	}else if ( nStop == 2 ){
	    newtio.c_cflag |=  CSTOPB;
	} 
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH); 
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
	    perror("set error");
	    return -1;
	}
	return 0;
}



int _portSerialRead(int iSerialFd, uint8_t * pucBuffer, uint16_t usNBytes, uint16_t * usNBytesRead)
{
    int            bResult = 0;
    ssize_t         res;
    fd_set          rfds;
    struct timeval  tv;

    tv.tv_sec = 2;
    tv.tv_usec = 50000;
    FD_ZERO( &rfds );
    FD_SET( iSerialFd, &rfds );

    *usNBytesRead = 0;
    /* Wait until character received or timeout. Recover in case of an
     * interrupted read system call. */
    do
    {
        if( select( iSerialFd + 1, &rfds, NULL, NULL, &tv ) == -1 )
        {
            if( errno != EINTR )
            {
                bResult = -1;
            }
        }
        else if( FD_ISSET( iSerialFd, &rfds ) )
        {
            if( ( res = read( iSerialFd, pucBuffer, usNBytes ) ) == -1 )
            {
                bResult = -1;
            }
            else
            {
                *usNBytesRead = ( uint16_t ) res;
                break;
            }
        }
        else
        {
            *usNBytesRead = 0;
            break;
        }
    }
    while( bResult == 0 );
    return bResult;
}

int gpsGetData(int fd, uint16_t times, uint8_t * pucBuffer, uint16_t usNBytes)
{
  uint16_t num = 0;
  uint16_t usNBytesRead = 0;
  uint16_t left = 0;
  uint16_t res = 0;

  while(times != num)
  {

     _portSerialRead(fd, pucBuffer + left, usNBytes - left, &usNBytesRead);

    left += usNBytesRead;
    printf("num = %d left = %d usNBytesRead = %d \n", num, left, usNBytesRead);

    if(left >= usNBytes)
	    break;
     num++;

  }

   return left;
}

#if 0
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
	            printf("Read data: ret = %d, %s\n\n", ret, pucBuffer);

     	}

        close(fd);

        return 0;
}
#endif
