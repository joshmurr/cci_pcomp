#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>

#define DEBUG 1
  
int main(int argc, char *argv[])
{
  int fd, n, i;
  char buf[64] = "temp text";
  struct termios toptions;

  /* open serial port. */
  fd = open("/dev/tty.HC-05-SerialPort", O_RDWR | O_NOCTTY);
  printf("fd opened as %i\n", fd);
  
  /* wait for the Arduino to reboot */
  printf("Waiting some time for Arduino to reboot...\n");
  usleep(3500000);
  printf("Done.\n");
  
  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);

  /* Send byte to trigger Arduino to send string back */
  printf("Writing 1 byte to Arduino.\n");
  write(fd, "1", 1);

  /* Receive string from Arduino */
  printf("Reveiving from Arduino...\n");
  clock_t start, end;
  double cpu_time;
  start = clock();
  while(cpu_time < 10.0){
      n = read(fd, buf, 64);
      end = clock();
      cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  }

  if(buf[0] == 't'){
      // Failed
      fclose(fd);
  } else {

      /* insert terminating zero in the string */
      buf[n] = 0;

      printf("%i bytes read, buffer contains: %s\n", n, buf);
     
      if(DEBUG)
        {
          printf("Printing individual characters in buf as integers...\n\n");
          for(i=0; i<n; i++)
        {
          printf("Byte %i:%i, ",i+1, (int)buf[i]);
        }
          printf("\n");
        }
  }

  return 0;
}
