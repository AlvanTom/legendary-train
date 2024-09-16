#include <SDL2/SDL.h>
#include <stdexcept>
#include "reg.hpp"


class Registers {
    private:
        Uint8 registers[8]; 
    public:
        Uint16 getReg(uint reg){
            if(reg > HL) throw std::invalid_argument("not a register");
            if(reg >= AF) {
                switch(reg) {
                    case AF: 
                        return (registers[A] << 8) | registers[F];
                    break;
                    case BC: 
                        return (registers[B] << 8) | registers[C];
                    break;
                    case DE: 
                        return (registers[D] << 8) | registers[E];
                    break;
                    case HL: 
                        return (registers[H] << 8) | registers[L];
                    break;
                }
            } else {
                return registers[reg];
            }
        }

        void setReg(int reg, Uint16 value) {
            if(reg > HL) throw std::invalid_argument("not a register");
            if(reg >= AF) {
                switch(reg) {
                    case AF: 
                        registers[A] = value >> 8;
                        registers[F] = value; 
                    break;
                    case BC: 
                        registers[B] = value >> 8;
                        registers[C] = value; 
                    break;
                    case DE: 
                        registers[D] = value >> 8;
                        registers[E] = value; 
                    break;
                    case HL: 
                        registers[H] = value >> 8;
                        registers[L] = value; 
                    break;
                }
            } else {
                if(value > 255) throw std::invalid_argument("value too big");
                registers[reg] = value;
            }
        }
};
