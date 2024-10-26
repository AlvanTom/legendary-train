#include "cpu.hpp"
#include "reg.hpp"
#include <iostream>
using namespace std;

CPU::CPU() {
    reg = Registers();
    for(int i =0; i < 16; i++){
        for(int j =0; j < 16; j++){
            opcodes[i][j] = [this, i, j](){ldTest(i,j); };
        }
    }

    for(int i =0; i < 16; i++){
        for(int j =0; j < 16; j++){
            opcodes[i][j]();
        }
    }
}

CPU::~CPU() {

}

void CPU::printReg(){
    cout << this->reg.toString() << endl;
}

// Load instructions
void CPU::ldTest(int i, int j) {
    cout << "i: " << i << ", j: " << j << endl;
}
