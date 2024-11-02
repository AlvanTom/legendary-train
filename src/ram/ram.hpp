#ifndef RAM_H
#define RAM_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class RAM {
    private: 
       vector<Uint8> mem;
public:
        RAM();
        ~RAM();
        Uint8 getByte(int addr);
        void setByte(int addr, Uint8 val);
        string toString();
};
#endif