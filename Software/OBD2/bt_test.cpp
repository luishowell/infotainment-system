#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <algorithm>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

using namespace std;


int hex2int(string hex_string){
    return stoi(hex_string, nullptr, 16);
}


string send_cmd(string cmd, int serial_port, bool parse = false){
    cmd = cmd + "\r";
    write(serial_port, cmd.c_str(), cmd.length());

    char read_buf [1];
    string rec = "";
    while(1){
        int num_bytes = read(serial_port,read_buf, 1);
        if(num_bytes>0){              
            if (read_buf[0]=='>'){                             
                break;        
            }
            else{
                rec.append(read_buf);
            }
        }        
    }
    rec.erase(remove(rec.begin(), rec.end(), '\n'), rec.end()); //remove new line characters
    rec.erase(remove(rec.begin(), rec.end(), ' '), rec.end());  //remove spaces

    if (parse==false){
        return rec;
    }
    else if (parse==true){
        string output;

        string expected_prefix = "4"+cmd.substr(1, 3);
        int prefix_search = rec.find(expected_prefix);
        if (prefix_search!=string::npos){
            output = rec.substr(prefix_search);
        }
        else if (rec.find("OK")!=string::npos){
            output = "OK";
        }
        else if (rec.find("ELM327")!=string::npos){
            output = rec.substr(rec.find("ELM327"), 10);
        }
        else if (rec.find("BUSINIT:ERROR")!=string::npos){
            output = "BUSINIT:ERROR";
        }
        else if (rec.find("?")!=string::npos){
            output = "?";
        }
        else if (rec.find("UNABLETOCONNECT")!=string::npos){
            output = "UNABLE_TO_CONNECT";
        }
        else if (rec.find("NODATA")!=string::npos){
            output = "NO_DATA";
        }
        else{
            output = "PARSE_ERROR: "+rec;
        }

        return output;
    }
}


int setup_obd(string comm_port){
    int serial_port = open(comm_port.c_str(), O_RDWR | O_NOCTTY);
    
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    fcntl(serial_port, F_SETFL, 0);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_lflag &= !(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= !(OPOST); 

    tty.c_cc[VTIME] = 20;   
    tty.c_cc[VMIN] = 0;

    //baud rate
    cfsetispeed(&tty, B38400);
    cfsetospeed(&tty, B38400);
    
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    tcflush(serial_port, TCIOFLUSH);

    cout<<send_cmd("ATZ", serial_port, true)<<endl;   //reset
    cout<<send_cmd("ATE0", serial_port, true)<<endl;  //echo off
    cout<<send_cmd("ATL0", serial_port, true)<<endl;  //linefeed off
    cout<<send_cmd("ATSP5", serial_port, true)<<endl; //OBD2 Protocol set to KWP fast (Fiat Panda), use ATSP0 for auto

    if (send_cmd("ATFI", serial_port, true)=="BUSINIT:ERROR"){  //initalise KWP fast
        cout<<"KWP Fast Bus Initialisation Error"<<endl;

        bool fixed = false;
        for (int i=0; i<4; i++){
            cout<<"Trying again"<<endl;
            send_cmd("ATZ", serial_port, false);   //reset
            send_cmd("ATE0", serial_port, false);  //echo off
            send_cmd("ATL0", serial_port, false);  //linefeed off
            send_cmd("ATSP5", serial_port,false);

            if (send_cmd("ATFI", serial_port, true)=="OK"){
                cout<<"Bus initalised"<<endl;
                fixed == true;
                break;
            }
        }

        if (fixed==false){
            cout<<"Could not initalise bus"<<endl;
            return -1;
        }        
    }
    
    sleep(0.5);
    return serial_port;
}


int main(int argc, char const *argv[]){

    int serial_port = setup_obd("/dev/rfcomm0");

    if (serial_port == -1){
        cout<< "Connection Error!"<<endl;
        return 0;
    }
    else{
        cout<<"Connection Successful"<<endl;
    }

    cout<<send_cmd("0100", serial_port, true)<<endl;    //supported pids
    cout<<send_cmd("0101", serial_port, true)<<endl;    //number of DTC
    //cout<<send_cmd("010C", serial_port, true)<<endl;    //RPM
    //cout<<send_cmd("010D", serial_port, true)<<endl;    //vehicle speed

    string rpm_hex = send_cmd("010C", serial_port, true);
    int A = hex2int(rpm_hex.substr(4,2));
    int B = hex2int(rpm_hex.substr(6,2));
    cout<<"RPM: "<< (256*A+B)/4<<endl;
    
    string speed_hex = send_cmd("010D", serial_port, true);
    cout<<"Speed: "<<hex2int(speed_hex.substr(4))<<"Kph"<<endl;    
    
    //close(serial_port);

    cout<<"Complete"<<endl;
    return 0;
}

