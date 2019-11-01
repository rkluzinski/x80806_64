#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "../src/cpu.h"

int main(int argc, char **argv) {
	Intel8080 cpu;
    constexpr std::size_t MEMORY_SIZE = 0x10000;
    
    try {
        loadBinary("../roms/BDOS", cpu.getMemory(), MEMORY_SIZE);
        loadBinary("../coms/HELLO.COM", cpu.getMemory() + 0x100, MEMORY_SIZE - 0x100);
        
        std::size_t cycles = cpu.execute();
        std::cout << "Cycles executed: " << cycles << std::endl;
    }
    catch (TestException &e) {
        std::cerr << "TestException: " << e.what() << std::endl;
    }
    catch (Intel8080Exception &e) {
        std::cerr << "Intel8080Exception: " << e.what() << std::endl;
        cpu.dump();
    }
	return 0;
}