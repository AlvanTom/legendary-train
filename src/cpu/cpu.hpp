#ifndef CPU_H
#define CPU_H

#include <SDL2/SDL.h>
#include "reg.hpp"
#include "../ram/ram.hpp"

class CPU{
    private:
        Registers reg;
        std::function<void()> opcodes[16][16];
    public:
        CPU(RAM* ram);
        ~CPU();
        void printReg();
        void ldTest(int i, int j);
        Reg decoder8(Uint8 i);
        void blockOne(Reg dest, Reg src, RAM* ram);
        void blockTwo(Reg op, Reg operand, RAM* ram);
};


#endif