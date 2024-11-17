#include "cpu.hpp"
#include "reg.hpp"
#include "../memory/mem.hpp"
#include <cassert>
#include <iostream>
using namespace std;

CPU::CPU(MEM* mem) {
    reg = Registers();
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            int byte = (i << 4) + j;
            switch (byte >> 6) {
                case 0: {
                    // Block 0
                break;
                }
                case 1: {
                    Reg dest = (Reg)((byte >> 3) & 0b111);
                    Reg src = (Reg)(byte & 0b111);
                    opcodes[i][j] = [this, dest, src, mem](){blockOne(decoder8(dest), decoder8(src), mem);};
                break;
                }
                case 2:{
                    Reg op = decoder8((byte >> 3) & 0b111);
                    Reg operand = decoder8(byte & 0b111);
                    opcodes[i][j] = [this, op, operand, mem](){blockTwo(op, operand, mem);};
                break;
                }
                case 3:{
                    // Block 3
                break;
                }
                default: 
                    opcodes[i][j] = [this, i, j](){ldTest(i,j); };
            }
        }
    }
    reg.printReg();
    opcodes[0x8][0x5]();
    opcodes[0x8][0x5]();
    opcodes[0x8][0x5]();
    cout << "passed"<< endl;
    reg.printReg();
}

CPU::~CPU() {
}

void CPU::execute(){
    while(1){
        Uint16 pc = reg.getPC();
        opcodes[pc>>4 & 0b1111][pc & 0b1111];
        reg.incrementPC();
    }
}
// Testing
void CPU::ldTest(int i, int j) {
    cout << "i: " << i << ", j: " << j << endl;
}

Reg CPU::decoder8(Uint8 i){
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
    throw invalid_argument("Not a valid register");
}

// Block 1
void CPU::blockOne(Reg dest, Reg src, MEM* mem) {
    if(dest != HL && src != HL){
        reg.setReg(dest, reg.getReg(src));
        return;
    }
    if(dest == HL && src){
        cout << "IMPLEMENT HALT" << endl;
        // TODO: HALT instr
        return;
    } 
    assert((mem != nullptr));
    if (dest == HL){
        mem->setByte(dest, reg.getReg(src));
        return;
    } 
    if(src == HL) {
        reg.setReg(dest, mem->getByte(reg.getReg(src)));
        return;
    }
}

// Block 2
void CPU::blockTwo(Reg op, Reg operand, MEM* mem) {
    Uint8 regA = (Uint8) reg.getReg(A);
    Uint8 r8;
    if(operand == HL){
        r8 = (Uint8) mem->getByte(reg.getReg(HL));
    }else{
        r8 = (Uint8) reg.getReg(operand);
    }
    switch (op) {
        case 0: {
            /* ADD A, r8 */
            Uint8 addA = regA + r8;
            
            addA ? reg.setFlag(FZ, 0) : reg.setFlag(FZ, 1); // Set if result is 0
            reg.setFlag(FN, 0);
            ((addA >> 4) > 0) ? reg.setFlag(FH, 1) : reg.setFlag(FH, 0); // Set if bit 3 overflow
            (addA < regA || addA < r8) ? reg.setFlag(FC, 1) : reg.setFlag(FC, 0); // Set if bit 7 overflow
            reg.setReg(A, addA); // Store sum in reg A
            break;
        }
        case 1: {
            // ADC A,r8
            Uint8 adcA = regA + r8;
            
            adcA ? reg.setFlag(FZ, 0) : reg.setFlag(FZ, 1);
            reg.setFlag(FN, 0);
            ((adcA >> 4) > 0) ? reg.setFlag(FH, 1) : reg.setFlag(FH, 0);
            if (adcA < regA || adcA < r8) {
                reg.setFlag(FC, 1);
                adcA += 1;
            } else{
                reg.setFlag(FC, 0);
            } 
            reg.setReg(A, adcA); 
            break;
        }
        case 2: {
            // SUB A,r8
            Uint8 subA = regA - r8;
            subA ? reg.setFlag(FZ, 0) : reg.setFlag(FZ, 1);
            reg.setFlag(FN, 1);
            ((r8 & 0b1111) > (regA & 0b1111)) ? reg.setFlag(FH, 1) : reg.setFlag(FH, 0);
            (r8 > regA) ? reg.setFlag(FC, 1) : reg.setFlag(FC, 0);
            reg.setReg(A, subA);
            break;
        }
        case 3: {
            //SBC A,r8
            Uint8 carry = reg.getFlag(FC) ? 1 : 0;
            Uint8 sbcA = regA - r8 - carry;
            sbcA == 0 ? reg.setFlag(FZ, 1) : reg.setFlag(FZ, 0);
            reg.setFlag(FN, 0);
            ((r8 + carry) & 0b1111) > (regA & 0b1111) ? reg.setFlag(FH, 1) : reg.setFlag(FH, 0);
            r8 + carry > regA ? reg.setFlag(FC, 1) : reg.setFlag(FC, 0);
            reg.setReg(A, sbcA);
            break;
        }
        case 4: {
            //AND A,r8
            Uint8 andA= r8 & regA;
            reg.setFlag(FN, 0);
            reg.setFlag(FH, 1);
            reg.setFlag(FC, 0);
            andA == 0 ? reg.setFlag(FZ, 1) : reg.setFlag(FZ, 0);
            reg.setReg(A, andA);
            break;
        }
        case 5: {
            //XOR A,r8
            Uint8 xorA = r8 ^ regA;
            reg.setFlag(FN, 0);
            reg.setFlag(FH, 0);
            reg.setFlag(FC, 0);
            xorA == 0 ? reg.setFlag(FZ, 1) : reg.setFlag(FZ, 0);
            reg.setReg(A, xorA);
            break;
        }
        case 6: {
            //OR A,r8
            Uint8 orA = r8 | regA;
            reg.setFlag(FN, 0);
            reg.setFlag(FH, 0);
            reg.setFlag(FC, 0);
            orA == 0 ? reg.setFlag(FZ, 1) : reg.setFlag(FZ, 0);
            reg.setReg(A, orA);
            break;
        }
        case 7: {
            //Compare A,r8
            regA == r8 ? reg.setFlag(FZ, 1) : reg.setFlag(FZ, 0);
            reg.setFlag(FN, 1);
            (r8 & 0b1111) > (regA & 0b1111) ? reg.setFlag(FH, 1): reg.setFlag(FH, 0);
            r8 > regA ? reg.setFlag(FC, 1): reg.setFlag(FC, 0);
            break;
        }
        default: throw invalid_argument("Not a valid operand?");
    }
}
