#ifndef SRC_SERIAL_
#define SRC_SERIAL_

#include <iostream>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

class Serial{
    // Member Function
    private:

    public:
        Serial(int argc, char* argv[]);
        void usage(void);
        bool setup(int argc, char* argv[]);
        int serialport_init(const char* serialport, int baud);
        int serialport_writebyte(uint8_t b);
        int serialport_writetwobytes(uint16_t b);
        int serialport_write(const char* str);
        int serialport_writechar(unsigned char b);
        int serialport_read_until(char until);
        int serialport_read_int_until(char until, int& data);
        int serialport_read_teapot();
        int serialport_write_teapot(uint8_t *packet);


    // Variables    
    private:
        int argc;
        int fd;
        std::string serialport;
        int baudrate;
        int serialCount;

    public:
        uint8_t buf[256];
        uint8_t teapot[14];
        bool DEBUG;
        int synced;

    private:
        char* argv[];


};


#endif
