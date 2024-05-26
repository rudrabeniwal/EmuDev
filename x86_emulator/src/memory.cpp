#include "memory.h"

Memory::Memory(size_t size) : data(size) {}

uint8_t Memory::read8(uint64_t address) const {
    return data.at(address);
}

uint32_t Memory::read32(uint64_t address) const {
    uint32_t value;
    std::memcpy(&value, &data.at(address), sizeof(value));
    return value;
}

uint64_t Memory::read64(uint64_t address) const {
    uint64_t value;
    std::memcpy(&value, &data.at(address), sizeof(value));
    return value;
}

void Memory::write8(uint64_t address, uint8_t data) {
    this->data.at(address) = data;
}

void Memory::write32(uint64_t address, uint32_t data) {
    std::memcpy(&this->data.at(address), &data, sizeof(data));
}

void Memory::write64(uint64_t address, uint64_t data) {
    std::memcpy(&this->data.at(address), &data, sizeof(data));
}