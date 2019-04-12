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

/**
 * @brief OBD2 vehicle communication over Bluetooth
 * 
 */

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
         * @param fast_send Appends a one to the cmd string indicting to the OBD2 chip that only one response is expected, removing the OBD2 internal delay
         * @return string The reponse from the OBD2 module
         */
        string send_cmd(string cmd, bool parse = false, bool fast_send = false);

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
         * @brief Get the description of an OBD2 PID
         * 
         * @param pid A PID e.g "0D"
         * @return string The description of the PID
         */
        string pid_desc(string pid_code);

        /**
         * @brief Sends a command and decodes the response
         * 
         * @param cmd The command to send as a hex string
         * @param fast_send Appends a one to the cmd string indicting to the OBD2 chip that only one response is expected, removing the OBD2 internal delay
         * @param option A few PIDs have multiple outputs, option selects which one will be returned
         * @return float The decoded hex response
         */
        float decoded_cmd(string cmd, bool fast_send = false, int option = 1);

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
         * @return long The int value of the hex string
         */
        long hex2int(string hex_string);

        /**
         * @brief Converts a positive integer to a hex string
         * 
         * @param int_value A positive integer value, negative values will be inverted
         * @return string A hex string representation of the integer
         */
        string int2hex(long int_value);
    
    private:

        /**
         * @brief Set the up obd object
         * 
         * @param comm_port the file address of the bluetooth module, normall "/dev/rfcomm0"
         * @return int Returns a file descriptor of serial port if successful, otherwise -1
         */
        int setup_obd(string comm_port);   
};

#endif