#include <iostream>
#include <stdlib.h> 
#include "serial.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    int fd = 0;
    char serialport[256];
    int baudrate = B9600;  // default
    char buf[256];
    char input_buf[256];
    int input_int;
    string send_string;
    char send_buf[256];
    int rc,n;

    bool init_done = false;
    bool running = false;

    if (argc==1) {
        usage();
        exit(EXIT_SUCCESS);
    }

    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        {"help",       no_argument,       0, 'h'},
        {"port",       required_argument, 0, 'p'},
        {"baud",       required_argument, 0, 'b'},
        {"send",       required_argument, 0, 's'},
        {"receive",    no_argument,       0, 'r'},
        {"num",        required_argument, 0, 'n'},
        {"delay",      required_argument, 0, 'd'}
    };
    
    while(!init_done) {
        opt = getopt_long (argc, argv, "hp:b:s:rn:d:",
                           loptions, &option_index);
        if (opt==-1) break;
        switch (opt) {
        case '0': break;
        case 'd':
            n = strtol(optarg,NULL,10);
            usleep(n * 1000 ); // sleep milliseconds
            break;
        case 'h':
            usage();
            break;
        case 'b':
            baudrate = strtol(optarg,NULL,10);
            break;
        case 'p':
            strcpy(serialport,optarg);
            fd = serialport_init(optarg, baudrate);
            if(fd==-1) return -1;
            break;
        case 'n':
            n = strtol(optarg, NULL, 10); // convert string to number
            rc = serialport_writebyte(fd, (uint8_t)n);
            if(rc==-1) return -1;
            break;
        case 's':
            strcpy(buf,optarg);
            rc = serialport_write(fd, buf);
            if(rc==-1) return -1;
            break;
        case 'r':
            serialport_read_until(fd, buf, '\n');
            printf("read: %s\n",buf);
            break;
        }

        init_done = true;
        running = true;
    }

    while(running){
        string input;
        int num;
        if(!serialport_read_int_until(fd, input_buf, '\n', input_int)){ // If there is someting to be read

            //input = string(input_buf);
            //num = std::stoi(input);

            //int len = strlen(input_buf);
            //cout << input_buf;
            //if((int)input_buf[0] % 100 == 0) cout << "MOD" << endl;
            //for(int i=0; i<len; i++) input_buf[i] = '\0';
        }
        //cout << input_int << '\n';
        if(input_int%64==0){
            send_buf[0] = 'b';
            serialport_write(fd, send_buf);
            cout << "BLUE toggle" << endl;
        }
        if(input_int%89==0) {
            send_buf[0] = 'g';
            serialport_write(fd, send_buf);
            cout << "GREEN toggle" << endl;
        }
        if(input_int%37==0) {
            send_buf[0] = 'r';
            serialport_write(fd, send_buf);
            cout << "RED toggle" << endl;
        }
        //if(serialport_read_until(fd, input_buf, '\n')){


        /*if(cin >> send_buf){
            //cout << "Write a message to send: ";
            //cin >> send_buf;
            //cout << "Sending: " << send_buf << endl;
            rc = serialport_write(fd, send_buf);
            if (rc == -1){
                cout << "Failed to send message." << endl;
            } 
        } */


        usleep(10000);
    }

    exit(EXIT_SUCCESS);    
} // end main
    
