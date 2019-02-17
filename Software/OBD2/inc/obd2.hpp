/**
* @file obd2.hpp
* @brief The class obd2 provides methods for communicating with an OBD2 vhicle over Bluetooth.
*
* @author Luis Howell
*
*/

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

        /**
         * @brief obd2 object constructor
         * 
         * @param comm_port The device location of the bluetooth serial port, often /dev/rfcomm0
         */
        obd2(string comm_port);


        /**
         * @brief Send a command to the OBD2 module
         * 
         * @param cmd The command to send in the format of a hex string
         * @param parse A bool flag which sets whether the response should be parsed to remove all non-data in the response e.g spaces, new lines
         * @return string The reponse from the OBD2 module
         */
        string send_cmd(string cmd, bool parse = false);

        /**
         * @brief Scans the OBD2 PIDs supported by the vehcile
         * 
         * Stores the supported PIDs as a vector of strings in supported_pids 
         * 
         */
        void scan_pids();

        /**
         * @brief Prints the supported PIDs and their descriptions
         * 
         * scan_pids() must have been ran at least once
         */
        void print_supported_pids();

        /**
         * @brief Decodes the Hex responses from the OBD2 module
         * 
         * @param response The hex response 
         * @param option A few PIDs have multiple outputs, option selects which one will be returned
         * @return float The decoded value
         */
        float decode_response(string response, int option = 1);

        /**
         * @brief Sends a command and decodes the response
         * 
         * @param cmd The command to send as a hex string
         * @return float The decoded hex response
         */
        float decoded_cmd(string cmd);

        /**
         * @brief Reads the currently stored diagnostic trouble codes (DTC)
         * 
         * @return vector<string> A vector of strings containing the DTCs
         */
        vector<string> read_dtc();

        /**
         * @brief Reads the DTC description
         * 
         * @param dtc_code A DTC code
         * @return string The desctiption of the DTC code
         */
        string dtc_desc(string dtc_code);

        /**
         * @brief Converts a hex string to an integer
         * 
         * @param hex_string A hex string
         * @return unsigned long The int value of the hex string
         */
        unsigned long hex2int(string hex_string);

        /**
         * @brief Converts an integer to a hex string
         * 
         * @param int_value An integer value
         * @return string A hex string representation of the integer
         */
        string int2hex(long int_value);
    
    private:

        int setup_obd(string comm_port);   

};

#endif