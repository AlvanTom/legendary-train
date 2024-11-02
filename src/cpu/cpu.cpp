#include "cpu.hpp"
#include "reg.hpp"
#include "../ram/ram.hpp"
#include <cassert>
#include <iostream>
using namespace std;

CPU::CPU(RAM* ram) {
    reg = Registers();
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            int byte = (i << 4) + j;
            if(byte >> 6 == 1){
                int dest = (byte >> 3) & 0b111;
                int src = byte & 0b111;
                cout << dest << endl;
                cout << src << endl;
                opcodes[i][j] = [this, dest, src, ram](){blockOne(dest, src, ram);};
            }else{
                opcodes[i][j] = [this, i, j](){ldTest(i,j); };
            }
        }
    }
    reg.printReg();
    opcodes[0x4][0x8]();
    cout << "passed"<< endl;
    reg.printReg();
}

CPU::~CPU() {

}

// void CPU::printReg(){
//     cout << this->reg.toString() << endl;
// }

// Load instructions
void CPU::ldTest(int i, int j) {
    cout << "i: " << i << ", j: " << j << endl;
}

//block 1
void CPU::blockOne(int dest, int src, RAM* ram) {
    if(decoder8(dest) != HL && decoder8(src) != HL){
        reg.setReg(decoder8(dest), reg.getReg(decoder8(src)));
        return;
    }
    if(decoder8(dest) == HL && decoder8(src)){
        cout << "IMPLEMENT HALT" << endl;
        // TODO: HALT instr
        return;
    } 
    assert((ram != nullptr));
    if (decoder8(dest) == HL){
        ram->setByte(decoder8(dest), reg.getReg(decoder8(src)));
        return;
    } 
    if((decoder8(src) == HL)) {
        reg.setReg(decoder8(dest), ram->getByte(reg.getReg(decoder8(src))));
        return;
    }
}

int CPU::decoder8(int i){
    switch(i){
        case(0): return B;
        case(1): return C;
        case(2): return D;
        case(3): return E;
        case(4): return H;
        case(5): return L;
        case(6): return HL;
        case(7): return A;
    }
    return -1; // error
}