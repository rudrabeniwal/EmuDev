#include "bus.hpp"

Bus::Bus(Memory& mem) : memory(mem) {}

uint8_t Bus::read8(uint64_t address) {
    return memory.read8(address);
}

uint32_t Bus::read32(uint64_t address) {
    return memory.read32(address);
}

uint64_t Bus::read64(uint64_t address) {
    return memory.read64(address);
}

void Bus::write8(uint64_t address, uint8_t data) {
    memory.write8(address, data);
}

void Bus::write32(uint64_t address, uint32_t data) {
    memory.write32(address, data);
}

void Bus::write64(uint64_t address, uint64_t data) {
    memory.write64(address, data);
}