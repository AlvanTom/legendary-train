#include "reg.hpp"

Registers::Registers() {
    for (int i = 0; i < REG_COUNT; i++) {
        setReg((Reg)i, i);
    }
}

Registers::~Registers() {}

Uint16 Registers::getReg(Reg reg) {
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

void Registers::setReg(Reg reg, Uint16 value) {
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
        if(value > 255) throw invalid_argument("value too big");
        registers[reg] = value;
    }
}
bool Registers::getFlag(Flags flag){
    return (getReg(F) >> flag) & 1;
}

void Registers::setFlag(Flags flag, bool val){
    if (val){
        setReg(F, getReg(F) | (1 << flag));
    } else {
        setReg(F, getReg(F) & ((1 << flag) ^ 0));
    }
}


void Registers::printReg(){
    cout << "A: " << hex << (uint)(getReg(A)) << endl;
    cout << "B: " << hex << (uint)(getReg(B)) << endl;
    cout << "C: " << hex << (uint)(getReg(C)) << endl;
    cout << "D: " << hex << (uint)(getReg(D)) << endl;
    cout << "E: " << hex << (uint)(getReg(E)) << endl;
    cout << "F(ZNHC): " << hex << (uint)(getReg(F) >> 4) << endl;
    cout << "H: " << hex << (uint)(getReg(H)) << endl;
    cout << "L: " << hex << (uint)(getReg(L)) << endl;
}
