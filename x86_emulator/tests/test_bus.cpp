#include <iostream>
#include "bus.h"
#include "memory.h"

void test_bus_operations() {
    // Create memory with size 1024 bytes
    Memory memory(1024);
    
    // Create bus
    Bus bus(memory);

    // Test write and read 8-bit
    bus.write8(100, 0x12);
    if (bus.read8(100) != 0x12) {
        std::cerr << "Test failed: Expected 0x12, but got " << std::hex << static_cast<int>(bus.read8(100)) << std::endl;
    } else {
        std::cout << "Test passed: 8-bit read/write" << std::endl;
    }

    // Test write and read 32-bit
    bus.write32(200, 0x12345678);
    if (bus.read32(200) != 0x12345678) {
        std::cerr << "Test failed: Expected 0x12345678, but got " << std::hex << bus.read32(200) << std::endl;
    } else {
        std::cout << "Test passed: 32-bit read/write" << std::endl;
    }

    // Test write and read 64-bit
    bus.write64(300, 0x123456789ABCDEF0);
    if (bus.read64(300) != 0x123456789ABCDEF0) {
        std::cerr << "Test failed: Expected 0x123456789ABCDEF0, but got " << std::hex << bus.read64(300) << std::endl;
    } else {
        std::cout << "Test passed: 64-bit read/write" << std::endl;
    }
}

int main() {
    test_bus_operations();
    return 0;
}