#include "main.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
using namespace std;

int main () {
    RAM ram = RAM();
    CPU myCPU = CPU(&ram);
    return 0; 
}