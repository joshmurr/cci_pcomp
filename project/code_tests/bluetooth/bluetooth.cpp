#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    filebuf fb;
    cout << "Connecting to Arduino via USB..." << endl;
    try{
        if(fb.open("/dev/tty.jm_bt_3-SerialPort", ios::in|ios::out|ios::app)){
            cout << "Connection made." << endl;
            iostream is(&fb);
            char c;
            char is_c;
            while(true){
                cout << endl;
                cin >> c;
                if(c == 'q'){
                    break;
                }
                //cout << "Sending: " << c << '\n';
                is << c << flush;
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
