#include "../catch.hpp"
#include "../../src/main.hpp"
#include "../../src/cpu/cpu.hpp"
#include "../../src/cpu/reg.hpp"
#include "../../src/memory/mem.hpp"

TEST_CASE( "Block 1, Temp Test Reg A", "[cpu], [block1]" ) {
    MEM mem = MEM();
    REQUIRE( &mem );
    CPU myCPU = CPU(&mem);
    Registers myReg = myCPU.exposeReg();
    REQUIRE( myReg.getReg(A) == 0);
    myCPU.callInstr(0x8, 0x5);
    myCPU.callInstr(0x8, 0x5);
    myReg = myCPU.exposeReg();
    REQUIRE( myReg.getReg(A) == 0); // This will fail
}
