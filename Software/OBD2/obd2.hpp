#ifndef OBD2_H
#define OBD2_H

#include <string>
#include <vector>
using namespace std;

class obd2{
    public:

        int serial_port;
        bool connected = false;
        vector<string> supported_pids;

        obd2(string comm_port);

        string send_cmd(string cmd, bool parse = false);
        void scan_pids();
        void print_supported_pids();
        float decode_response(string response, int option = 1);
        float decoded_cmd(string cmd);
        vector<string> read_dtc();
        string dtc_desc(string dtc_code);
    
    private:

        int hex2int(string hex_string);
        string int2hex(int int_value);
        int setup_obd(string comm_port);   

};

#endif