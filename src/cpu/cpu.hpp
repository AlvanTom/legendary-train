#ifndef CPU_H
#define CPU_H

#include <SDL2/SDL.h>
#include "reg.hpp"

class CPU{
    private:
        Registers reg;
        std::function<void()> opcodes[16][16];
    public:
        CPU();
        ~CPU();
        void printReg();
        void ldTest(int i, int j);
};


#endif