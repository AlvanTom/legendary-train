#include "mem.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

MEM::MEM() {
    mem.assign(256*256, 0);
    // mem.reserve(255*255);
}

MEM::~MEM(){

}

Uint8 MEM::getByte(int addr){
    return mem[addr];
}

void MEM::setByte(int addr, Uint8 val){
    mem[addr] = val;
}

string MEM::toString(){
     for (size_t i = 0; i < mem.size(); ++i) {
        // Print each byte with leading zeros and fixed width of 2
        cout << hex << uppercase << setw(2) 
                  << setfill('0') << static_cast<int>(mem[i]);
        
        // Add space between elements
        if (i < mem.size() - 1) {
            cout << " ";
        }
        
        // New line after every 32 elements
        if ((i + 1) % 32 == 0 || i == mem.size() - 1) {
            cout << endl << hex << uppercase << setw(4) << setfill('0') << i << ": ";
        }
    }
    
    // Reset stream flags back to decimal
    cout << dec;
}