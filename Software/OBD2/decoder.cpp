#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <algorithm>

using namespace std;


int hex2int(string hex_string){
    return stoi(hex_string, nullptr, 16);
}


float decode_response(string response, int option = 1){
    string data = response.substr(4);
    string pid = response.substr(2, 2);
    float output;

    if (pid=="04"||pid=="11"||pid=="2C"||pid=="2E"||pid=="2F"||pid=="45"||pid=="52"||pid=="5A"||pid=="5B"){ 
        output = hex2int(data)/2.55;        
    }
    else if (pid=="1F"||pid=="21"||pid=="31"||pid=="4D"||pid=="4E"||pid=="63"){   
        int A = hex2int(data.substr(0,2));
        int B = hex2int(data.substr(2,2));
        output = (256*A)+B;
    }
    else if (pid=="05"||pid=="0F"||pid=="46"||pid=="5C"){    
        output = hex2int(data)-40;
    }
    else if (pid=="0B"||pid=="0D"||pid=="30"||pid=="33"){    
        output = hex2int(data);
    }
    else if (pid=="06"||pid=="07"||pid=="08"||pid=="09"){
        output = (hex2int(data)/1.28)-100.0;
    }
    else if (pid=="0A"){  
        output = hex2int(data)*3.0;
    }
    else if (pid=="0C"){   
        int A = hex2int(data.substr(0,2));
        int B = hex2int(data.substr(2,2));
        output = ((256*A)+B)/4.0;
    }
    else if (pid=="5E"){   
        int A = hex2int(data.substr(0,2));
        int B = hex2int(data.substr(2,2));
        output = ((256*A)+B)/20.0;
    }
    else if (hex2int(pid)>=20&&hex2int(pid)<=27){
        if (option==1){
            output = hex2int(data.substr(0, 2))/200.0;
        }
        else if (option==2){
            if (data.substr(2,2)!="FF"){
                output = ((100.0/128.0)*hex2int(data.substr(2,2)))-100.0;
            }
            else if (data.substr(2,2)!="FF"){
                output = 999;
            }
        }
    }
    else if (hex2int(pid)>=36&&hex2int(pid)<=43){
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
    else if (hex2int(pid)>=52&&hex2int(pid)<=59){
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
    else if (pid=="3C"||pid=="3D"||pid=="3E"||pid=="3F"){   
        int A = hex2int(data.substr(0,2));
        int B = hex2int(data.substr(2,2));
        output = (((256*A)+B)/10.0)-40.0;
    }
    else if (pid=="10"){   
        int A = hex2int(data.substr(0,2));
        int B = hex2int(data.substr(2,2));
        output = ((256*A)+B)/100.0;
    }
    else if (pid=="61"||pid=="62"){  
        output = hex2int(data)-125;
    }
    else if (pid=="2D"){  
        output = ((100.0/128.0)*hex2int(data))-100;
    }
    else{
        output = -999;
    }
    return output;
}


int main(int argc, char const *argv[])
{
    cout<<decode_response("410C1AF8")<<endl;    //rpm
    return 0;
}
