#include <iostream>
#include "memory.h"

void test_memory_operations() {
    // Create memory with size 1024 bytes
    Memory memory(1024);

    // Test write and read 8-bit
    memory.write8(100, 0x12);
    if (memory.read8(100) != 0x12) {
        std::cerr << "Test failed: Expected 0x12, but got " << std::hex << static_cast<int>(memory.read8(100)) << std::endl;
    } else {
        std::cout << "Test passed: 8-bit read/write" << std::endl;
    }

    // Test write and read 32-bit
    memory.write32(200, 0x12345678);
    if (memory.read32(200) != 0x12345678) {
        std::cerr << "Test failed: Expected 0x12345678, but got " << std::hex << memory.read32(200) << std::endl;
    } else {
        std::cout << "Test passed: 32-bit read/write" << std::endl;
    }

    // Test write and read 64-bit
    memory.write64(300, 0x123456789ABCDEF0);
    if (memory.read64(300) != 0x123456789ABCDEF0) {
        std::cerr << "Test failed: Expected 0x123456789ABCDEF0, but got " << std::hex << memory.read64(300) << std::endl;
    } else {
        std::cout << "Test passed: 64-bit read/write" << std::endl;
    }
}

int main() {
    test_memory_operations();
    return 0;
}