#include "reg.hpp"

Registers::Registers() {
    for (int i = 0; i < REG_COUNT; i++) {
        setReg(i, i);
    }
}

Registers::~Registers() {}

Uint16 Registers::getReg(uint reg) {
    if(reg > HL) throw std::invalid_argument("not a register");
    if(reg >= AF) {
        switch(reg) {
            case AF: 
                return (registers[A] << REG_SIZE) | registers[F];
            break;
            case BC: 
                return (registers[B] << REG_SIZE) | registers[C];
            break;
            case DE: 
                return (registers[D] << REG_SIZE) | registers[E];
            break;
            case HL: 
                return (registers[H] << REG_SIZE) | registers[L];
            break;
        }
    } else {
        return registers[reg];
    }
}

void Registers::setReg(int reg, Uint16 value) {
    if(reg > HL) throw std::invalid_argument("not a register");
    if(reg >= AF) {
        switch(reg) {
            case AF: 
                registers[A] = value >> REG_SIZE;
                registers[F] = value; 
            break;
            case BC: 
                registers[B] = value >> REG_SIZE;
                registers[C] = value; 
            break;
            case DE: 
                registers[D] = value >> REG_SIZE;
                registers[E] = value; 
            break;
            case HL: 
                registers[H] = value >> REG_SIZE;
                registers[L] = value; 
            break;
        }
    } else {
        if(value > 255) throw std::invalid_argument("value too big");
        registers[reg] = value;
    }
}

void Registers::printReg(){
    cout << "A: " << (uint)(getReg(A)) << endl;
    cout << "B: " << (uint)(getReg(B)) << endl;
    cout << "C: " << (uint)(getReg(C)) << endl;
    cout << "D: " << (uint)(getReg(D)) << endl;
    cout << "E: " << (uint)(getReg(E)) << endl;
    cout << "F: " << (uint)(getReg(F))<< endl;
    cout << "H: " << (uint)(getReg(H)) << endl;
    cout << "L: " << (uint)(getReg(L)) << endl;
    cout << "AF: " << (uint)(getReg(AF)) << endl;
    cout << "BC: " << (uint)(getReg(BC)) << endl;
    cout << "DE: " << (uint)(getReg(DE)) << endl;
    cout << "HL: " << (uint)(getReg(HL)) << endl;
}