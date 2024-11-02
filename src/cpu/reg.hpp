#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
using namespace std;

const uint REG_SIZE = 8;
const uint REG_COUNT = 8;

const uint A = 0;
const uint B = 1;
const uint C = 2;
const uint D = 3;
const uint E = 4;
const uint F = 5;
const uint H = 6;
const uint L = 7;
const uint AF = 8;
const uint BC = 9;
const uint DE = 10;
const uint HL = 11;

class Registers {
    private: 
        Uint8 registers[REG_COUNT];
        Uint16 SP;
        Uint16 PC;
    public: 
        Registers();
        ~Registers();
        Uint16 getReg(uint reg);
        void setReg(int reg, Uint16 value);
        void printReg();
};

#endif
