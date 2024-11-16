#ifndef MEM_H
#define MEM_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class MEM {
    private: 
       vector<Uint8> mem;
public:
        MEM();
        ~MEM();
        Uint8 getByte(int addr);
        void setByte(int addr, Uint8 val);
        string toString();
};
#endif