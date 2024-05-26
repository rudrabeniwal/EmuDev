#ifndef BUS_HPP
#define BUS_HPP
#include <cstdint>
#include "memory.hpp"
class Bus {
public:
    Bus(Memory& mem);

    uint8_t read8(uint64_t address);
    uint32_t read32(uint64_t address);
    uint64_t read64(uint64_t address);

    void write8(uint64_t address, uint8_t data);
    void write32(uint64_t address, uint32_t data);
    void write64(uint64_t address, uint64_t data);

private:
    Memory& memory;
};
#endif // BUS_HPP