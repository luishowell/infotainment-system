#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std;

int main(int argc, char const *argv[]){
    
    string rec = "41003000210010";
    string dtc_hex = rec.substr(2);    

    int number_dtc_codes = dtc_hex.size()/4;

    vector<string> dtc_codes;
    string code_prefix;

    for (int i=0; i<number_dtc_codes;i++){
        string sub_string = dtc_hex.substr(i*4, 4);
        if (stoi(sub_string, nullptr, 16)>0){
            int first_digit = stoi(sub_string.substr(0, 1), nullptr, 16);    

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
    
    cout<<"Received Hex: "<<"\n"; 
    cout<<rec<<"\n"<<"\n";

    cout<<"Trouble Codes:"<<"\n"; 
    // for (int i = 0; i<dtc_codes.size();i++){    
    //     cout<<dtc_codes[i]<<",";
    // }
    // cout<<"\n";  

    for (int i = 0; i<dtc_codes.size();i++){    
        string line;
        ifstream dtc_list_txt ("dtc_code_list.txt");
        if (dtc_list_txt.is_open())
        {
            while ( getline (dtc_list_txt,line) ){
                if (dtc_codes[i] == line.substr(0,5)){
                    cout << line << '\n';
                    break;
                }       
            }
            dtc_list_txt.close();
        }
    }

    return 0;
}
