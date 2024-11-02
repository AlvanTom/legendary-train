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
        void blockOne(int dest, int src, RAM* ram);
        int decoder8(int i);
};


#endif