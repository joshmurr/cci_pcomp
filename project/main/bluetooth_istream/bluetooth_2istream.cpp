#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main() {
    int fd1;
    char buff[0x1000];
    int rd, nbytes, tries;

    fd1=open("/dev/tty.jm_bt_3-SerialPort", O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(fd1, F_SETFL, 0);
    rd = read(fd1, buff, 100);
    cout << "Bytes received are:\n" << buff << endl;
    close(fd1);

    return 0;
}
