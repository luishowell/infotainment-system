#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <bits/stdc++.h> 
#include <algorithm>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include "obd2.hpp"
using namespace std;


obd2::obd2(string comm_port){
    serial_port = setup_obd(comm_port);

    if (serial_port == -1){
        //cout<< "Connection Error!"<<endl;
        bool fixed = false;
        for (int i=0; i<2;i++){ //tries to setup 2 more times before quitting
            cout<<"Trying again..."<<endl;
            close(serial_port);
            sleep(5);
            serial_port = setup_obd(comm_port);
            if (serial_port!=-1){
                cout<<"Connection Fixed"<<endl;
                fixed = true;
                connected = true;
                break;
            }            
        }
        if (fixed==false){
            cout<<"Could not fix connection"<<endl;
            close(serial_port);
            connected = false;
        }        
    }
    else{
        cout<<"Connection Successful"<<endl;
        connected = true;
    }        
    ifstream supported_pid_txt ("supported_pid_gen.txt");           
    string pid;
    supported_pids.clear();
    if (supported_pid_txt.is_open()){
        while ( getline (supported_pid_txt, pid) ){
            pid = pid.substr(0,2);
            supported_pids.push_back(pid);
        }
        supported_pid_txt.close();                         
    }
}

string obd2::send_cmd(string cmd, bool parse){
    if (serial_port!=-1){
        cmd = cmd + "\r";
        write(serial_port, cmd.c_str(), cmd.length());

        char read_buf [1];
        string rec = "";
        while(1){
            int num_bytes = read(serial_port,read_buf, 1);
            //cout<<"Num bytes: "<<num_bytes<<endl;
            //cout<<read_buf[0]<<endl;
            if(num_bytes>0){              
                if (read_buf[0]=='>'){                  
                    break;        
                }
                else{
                    string read_buf_str(1, read_buf[0]);
                    rec = rec+read_buf_str;
                }
            }        
            else if (num_bytes==0){
                return "TRANSMISSION_ERROR: "+rec;
            }
        }
        rec.erase(remove(rec.begin(), rec.end(), '\n'), rec.end()); //remove new line characters
        rec.erase(remove(rec.begin(), rec.end(), ' '), rec.end());  //remove spaces

        if (parse==false){
            return rec;
        }
        else {
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
                output = "OK";
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
            else if (cmd.substr(0,2)=="03"){      
                int dtc_prefix_search = rec.find("43");  
                if (dtc_prefix_search!=string::npos){
                    output = rec.substr(dtc_prefix_search);
                }
            }
            else{
                output = "PARSE_ERROR: "+rec;
            }

            return output;
        }
    }
    else{
        cout<<"Not Connected!"<<endl;
        return "";
    }
}


void obd2::scan_pids(){
    cout<<"Scanning for supported PIDs..."<<endl;
    cout<<"May take up to 5 minutes"<<endl;

    fstream pid_save_file;
    pid_save_file.open("supported_pid_gen.txt", fstream::out | fstream::trunc);    

    supported_pids.clear();
    string pid_code_hex;
    string response;
    int pid_counter = 0;
    for (int i=0; i<196; i++){
        pid_code_hex = int2hex(i);
        response = send_cmd("01"+pid_code_hex);
        //cout<<response<<endl;
        if (response.find("41")!=string::npos){
            //cout<<pid_code_hex<<" Added!"<<endl;
            pid_save_file<<pid_code_hex<<"\n";
            supported_pids.push_back(pid_code_hex);
            pid_counter++;
            //pid_save_file<<response.substr(2,2)<<"\n";
        }
    } 

    pid_save_file.close();

    if (pid_counter>0){
        cout<<"Scanning Complete"<<endl;
        cout<<pid_counter<<" PIDs supported"<<endl;
    }
    else{
        cout<<"Scanning failed"<<endl;
    }
}


void obd2::print_supported_pids(){
    ifstream supported_pid_txt ("supported_pid_gen.txt");           
    string pid;
    if (supported_pid_txt.is_open()){
        ifstream pid_desc_txt ("pid_code_list.txt");
        string line; 
        while ( getline (supported_pid_txt, pid) ){
            pid = pid.substr(0,2);
            if (pid_desc_txt.is_open()){
                while (getline(pid_desc_txt, line)){
                    if (pid==line.substr(0,2)){
                        cout<<line<<endl;
                        break;
                    }
                }
            }
        }
        supported_pid_txt.close();
        pid_desc_txt.close();                
    }
    else{
        cout<<"Supported PID file may not exist, trying running scan_pids() first"<<endl;
    }
}


float obd2::decode_response(string response, int option){
    float output;

    if (response.substr(0,2)=="41"){
        string data = response.substr(4);
        string pid = response.substr(2, 2);        

        if ((pid=="04"||pid=="11"||pid=="2C"||pid=="2E"||pid=="2F"||pid=="45"||pid=="52"||pid=="5A"||pid=="5B")&&(data.size()==1*2)){ 
            output = hex2int(data)/2.55;        
        }
        else if ((pid=="1F"||pid=="21"||pid=="31"||pid=="4D"||pid=="4E"||pid=="63")&&(data.size()==2*2)){   
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = (256*A)+B;
        }
        else if ((pid=="05"||pid=="0F"||pid=="46"||pid=="5C")&&(data.size()==1*2)){    
            output = hex2int(data)-40;
        }
        else if ((pid=="0B"||pid=="0D"||pid=="30"||pid=="33")&&(data.size()==1*2)){    
            output = hex2int(data);
        }
        else if ((pid=="06"||pid=="07"||pid=="08"||pid=="09")&&(data.size()==1*2)){
            output = (hex2int(data)/1.28)-100.0;
        }
        else if ((pid=="0A")&&(data.size()==1*2)){  
            output = hex2int(data)*3.0;
        }
        else if ((pid=="0C")&&(data.size()==2*2)){   
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = ((256*A)+B)/4.0;
        }
        else if ((pid=="5E")&&(data.size()==2*2)){   
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = ((256*A)+B)/20.0;
        }
        else if ((hex2int(pid)>=20&&hex2int(pid)<=27)&&(data.size()==2*2)){
            if (option==1){
                output = hex2int(data.substr(0, 2))/200.0;
            }
            else if (option==2){
                if (data.substr(2,2)!="FF"){
                    output = ((100.0/128.0)*hex2int(data.substr(2,2)))-100.0;
                }
                else if (data.substr(2,2)=="FF"){
                    cout<<"Sensor is not used in trim calculation"<<endl;
                    output = -999;
                }
            }
        }
        else if ((hex2int(pid)>=36&&hex2int(pid)<=43)&&(data.size()==4*2)){
            if (option==1){
                int A = hex2int(data.substr(0,2));
                int B = hex2int(data.substr(2,2));
                output = (2.0/65536.0)*((256*A)+B);            
            }
            else if (option==2){
                int C = hex2int(data.substr(4,2));
                int D = hex2int(data.substr(6,2));
                output = (8.0/65536.0)*((256*C)+D);     
            }
        }
        else if ((hex2int(pid)>=52&&hex2int(pid)<=59)&&(data.size()==4*2)){
            if (option==1){
                int A = hex2int(data.substr(0,2));
                int B = hex2int(data.substr(2,2));
                output = (2.0/65536)*((256*A)+B);            
            }
            else if (option==2){
                int C = hex2int(data.substr(4,2));
                int D = hex2int(data.substr(6,2));
                output = C+(D/256.0)-128.0;
            }
        }
        else if ((pid=="3C"||pid=="3D"||pid=="3E"||pid=="3F")&&(data.size()==2*2)){   
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = (((256*A)+B)/10.0)-40.0;
        }
        else if ((pid=="10")&&(data.size()==2*2)){   
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = ((256*A)+B)/100.0;
        }
        else if ((pid=="61"||pid=="62")&&(data.size()==1*2)){  
            output = hex2int(data)-125;
        }
        else if ((pid=="2D")&&(data.size()==1*2)){  
            output = ((100.0/128.0)*hex2int(data))-100;
        }
        else if ((pid=="22")&&(data.size()==2*2)){  
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = 0.079*((256*A)+B);
        }
        else if ((pid=="23")&&(data.size()==2*2)){  
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = 10*((256*A)+B);
        }
        else if ((pid=="44")&&(data.size()==2*2)){  
            int A = hex2int(data.substr(0,2));
            int B = hex2int(data.substr(2,2));
            output = (2.0/65536.0)*((256*A)+B);  
        }
        else{
            output = -999;
            cout<<"Decode function for this PID not yet implemented"<<endl;
        }
    }
    else{
        cout<<"Invalid Response: only decodes 01 service requests, PID may not be supported by car"<<endl;
        output = -999;
    }
    return output;
}


float obd2::decoded_cmd(string cmd){
    return decode_response(send_cmd(cmd, true));        
}


vector<string> obd2::read_dtc(){

    string received = send_cmd("03", true);
    vector<string> dtc_codes;

    if (received.substr(0, 2)=="43"){

        string dtc_hex = received.substr(2);    

        int number_dtc_codes = dtc_hex.size()/4;

        
        string code_prefix;

        for (int i=0; i<number_dtc_codes;i++){
            string sub_string = dtc_hex.substr(i*4, 4);
            if (hex2int(sub_string)>0){
                int first_digit = hex2int(sub_string.substr(0, 1));    

                if (first_digit<=3){
                    code_prefix = "P"+to_string(first_digit);
                }
                else if ((first_digit>=4)&&(first_digit<=7)){
                    code_prefix = "C"+to_string(first_digit-4);
                }
                else if ((first_digit>=8)&&(first_digit<=11)){
                    code_prefix = "B"+to_string(first_digit-8);
                }
                else if ((first_digit>=12)&&(first_digit<=15)){
                    code_prefix = "U"+to_string(first_digit-12);
                }

                string dtc = code_prefix+sub_string.substr(1, 3);
                dtc_codes.push_back(dtc);         
            }      
        }
    }
    else{
        cout<<"Not a valid DTC response, returning empty vector"<<endl;
    }

    return dtc_codes;
}


string obd2::dtc_desc(string dtc_code){
    string line;
    string desc = "No DTC description";
    ifstream dtc_list_txt ("dtc_code_list.txt");
    if (dtc_list_txt.is_open())
    {
        while ( getline (dtc_list_txt,line) ){
            if (dtc_code == line.substr(0,5)){
                desc = line.substr(6);
                if (desc[0]==' '){
                    desc = desc.substr(1);
                }
                break;
            }       
        }
        dtc_list_txt.close();
    }   
    return desc;
}


unsigned long obd2::hex2int(string hex_string){
    try{
        return stoul(hex_string, nullptr, 16);
    }
    catch(const invalid_argument ia){
        cout<<"Invalid hex string"<<endl;
        return 0;
    }
}


string obd2::int2hex(long int_value){ 
    stringstream hex_value;
    hex_value<< setfill('0') << setw(2)<< uppercase<< hex<<int_value;
    return hex_value.str();    
}


int obd2::setup_obd(string comm_port){
    
    serial_port = open(comm_port.c_str(), O_RDWR | O_NOCTTY);
    
    tcflush(serial_port, TCIOFLUSH);
    
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

    tty.c_cc[VTIME] = 30;   
    tty.c_cc[VMIN] = 0;

    //baud rate
    cfsetispeed(&tty, B38400);
    cfsetospeed(&tty, B38400);
    
    if (tcsetattr(serial_port, TCSAFLUSH, &tty) != 0) {   //TCSANOW
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    tcflush(serial_port, TCIOFLUSH);

    if (send_cmd("ATZ", true)=="OK"){
        cout<<"Reset OK"<<endl;
    }
    else{
        cout<<"Transmission error"<<endl;
        return -1;        
    }
    if (send_cmd("ATE0", true)=="OK"){
        cout<<"Echo off OK"<<endl;
    }
    else{
        cout<<"Transmission error"<<endl;
        return -1;  
    }
    if (send_cmd("ATL0", true)=="OK"){
        cout<<"Linefeed off OK"<<endl;
    }
    else{
        cout<<"Transmission error"<<endl;
        return -1;  
    }
    if (send_cmd("ATS0", true)=="OK"){
        cout<<"Spaces off OK"<<endl;
    }
    else{
        cout<<"Transmission error"<<endl;
        return -1;  
    }
    if (send_cmd("ATSP5", true)=="OK"){
        cout<<"OBD2 Protocol set OK"<<endl;
    }
    else{
        cout<<"Transmission error"<<endl;
        return -1;  
    }

    if (send_cmd("0100", true)=="BUSINIT:ERROR"){  //initalise KWP fast
        cout<<"KWP Fast Bus Initialisation Error"<<endl;
        return -1;   
    } 

    return serial_port;
}