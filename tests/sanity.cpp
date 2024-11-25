#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/main.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/memory/mem.hpp"

TEST_CASE( "Memory and CPU are initialized", "[sanity], [setup]" ) {
    MEM mem = MEM();
    REQUIRE( &mem );
    CPU myCPU = CPU(&mem);
    REQUIRE( &myCPU );
}
