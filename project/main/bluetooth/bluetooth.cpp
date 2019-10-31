#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    filebuf fb;
    cout << "Connecting to Arduino via USB..." << endl;
    if(fb.open("/dev/tty.HC-05-SerialPort", ios::in|ios::out|ios::app)){
        cout << "Connection made." << endl;
        iostream is(&fb);
        char c;
        while(true){
            cin >> c;
            if(c == 'q'){
                break;
            }
            cout << "Sending: " << c << '\n';
            is << c << flush;
        }
    }

    return 0;
}
