#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
using namespace std;

const uint REG_SIZE = 8;
const uint REG_COUNT = 8;

enum Flags {
    FZ = 7,
    FN = 6,
    FH = 5,
    FC = 4
};
enum Reg {
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L,
    AF,
    BC,
    DE,
    HL
};

class Registers {
    private: 
        Uint8 registers[REG_COUNT];
        Uint16 SP;
        Uint16 PC;
    public: 
        Registers();
        ~Registers();
        Uint16 getReg(Reg reg);
        void setReg(Reg reg, Uint16 value);
        Uint16 HLD();
        Uint16 HLI();
        Uint16 getSP();
        void setSP(Uint16 value);
        Uint16 getPC();
        void setPC(Uint16 value);
        void incrementPC();
        bool getFlag(Flags flag);
        void setFlag(Flags flag, bool value);
        void printReg();
};

#endif
