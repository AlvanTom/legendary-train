#ifndef CPU_H
#define CPU_H

#include <SDL2/SDL.h>
#include "reg.hpp"
#include "../memory/mem.hpp"

class CPU{
    private:
        Registers reg;
        std::function<void()> opcodes[16][16];
    public:
        CPU(MEM* mem);
        ~CPU();
        void execute();
        void printReg();
        void ldTest(int i, int j);
        void callInstr(Uint8 a, Uint8 b);
        Reg decoder8(Uint8 i);
        Registers exposeReg();
        void blockOne(Reg dest, Reg src, MEM* mem);
        void blockTwo(Reg op, Reg operand, MEM* mem);
};


#endif