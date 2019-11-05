#include <iostream>
#include <stdlib.h> 
#include "serial.h"

using namespace std;

int main(int argc, char *argv[]) {
    Serial arduino(argc, argv);
    int data;
    string send_string;
    char send_buf[256];
    int rc,n;

    bool init_done = false;
    bool running = false;

    if (argc==1) {
        exit(EXIT_SUCCESS);
    }

    running = arduino.setup(argc, argv);

    while(running){
        string input;
        int num;
        arduino.serialport_read_int_until('\n', data);

        if(data%64==0){
            send_buf[0] = 'b';
            arduino.serialport_write(send_buf);
            cout << "BLUE toggle" << endl;
        }
        if(data%89==0) {
            send_buf[0] = 'g';
            arduino.serialport_write(send_buf);
            cout << "GREEN toggle" << endl;
        }
        if(data%37==0) {
            send_buf[0] = 'r';
            arduino.serialport_write(send_buf);
            cout << "RED toggle" << endl;
        }

        usleep(10000);
    }

    exit(EXIT_SUCCESS);    
} 
    
