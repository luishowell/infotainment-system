#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

int main(int argc, char const *argv[]){
    
    string rec = "410181076504";
    string dtc_hex = rec.substr(4, 2);
    int dtc_int = stoi(dtc_hex, nullptr, 16);

    bitset<8> dtc_bin(dtc_int);

    int number_of_dtc = dtc_int-128;

    cout<<"Received Hex: "<<"\n"; 
    cout<<rec<<"\n"<<"\n";

    // cout<<rec<<"\n";  
    // cout<<dtc_hex<<"\n";  
    // cout<<dtc_bin<<"\n"; 

    printf("Number of Diagnostic Trouble Codes: %i\n", number_of_dtc);

    if (dtc_bin[7] == 1){
        cout<<"Check engine light is on"<<"\n";
    }
    else{
        cout<<"Check engine light is off"<<"\n";
    }

    return 0;
}
