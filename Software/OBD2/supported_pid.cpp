#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

int main(int argc, char const *argv[]){
    
    char rec[] = {'4', '1', '0', '0', 'B', 'E', '1', 'F', 'A', '8', '1', '3', '\0'};
    string rec_string = string(rec);
    string rec_pid_hex = rec_string.substr(2, 2);
    int rec_pid_int = stoi(rec_pid_hex, nullptr, 16);
    string supported_hex = rec_string.substr(4);

    long supported_int = stoul(supported_hex, nullptr, 16);
    bitset<32> supported_bin(supported_int);

    vector<string> supported_pids;

    //int j = 1;
    int j = rec_pid_int+1;
    for (int i = 31; i>-1; i--){
        if (supported_bin[i]==1){
            stringstream pid_hex;
            pid_hex<< setfill('0') << setw(2)<< hex<<j;
            supported_pids.push_back(pid_hex.str());
        }
        j++;
    }       
    
    cout<<"Received Hex: "<<"\n"; 
    // cout<<rec_pid_hex<<"\n";
    // cout<<rec_pid_int<<"\n";
    cout<<rec<<"\n"<<"\n";
    // cout<<supported_hex<<"\n";
    // cout<<supported_int<<"\n";   
    // cout<<supported_bin<<"\n"; 

    cout<<"Supported PIDs: "<<"\n"; 
    for (int i = 0; i<supported_pids.size();i++){    
        cout<<supported_pids[i]<<",";
    }

   cout<<"\n";  

   return 0;
}
