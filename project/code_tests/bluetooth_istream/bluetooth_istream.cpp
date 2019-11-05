#include <stdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main() {
    filebuf fb;
    cout << "Connecting to Arduino via USB..." << endl;
    try{
        if(fb.open("/dev/tty.HC-05-SerialPort", ios::in|ios::out|ios::app)){
            cout << "Connection made." << endl;
            iostream is(&fb);
            char c;
            int i = 0;
            while(i < 100){
                is.get(c);
                cout << c;
                i++;
            }
        } else {
            throw "Failed to connect";    
        }
    }catch(const exception &e){
        cout << "Failed to connect.\n";
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
