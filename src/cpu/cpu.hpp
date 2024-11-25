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
        Reg decoder8(Uint8 i);
        Reg decoder16(Uint8 i);
        void loadr16mem(Uint8 i, MEM* mem, Uint8 value);
        Uint8 fetchr16mem(Uint8 i, MEM* mem);
        void blockZero(int byte, MEM* mem);
        void blockOne(Reg dest, Reg src, MEM* mem);
        void blockTwo(Reg op, Reg operand, MEM* mem);
};


#endif