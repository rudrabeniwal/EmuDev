#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>

class Memory {
public:
    Memory(size_t size);

    uint8_t read8(uint64_t address) const;
    uint32_t read32(uint64_t address) const;
    uint64_t read64(uint64_t address) const;

    void write8(uint64_t address, uint8_t data);
    void write32(uint64_t address, uint32_t data);
    void write64(uint64_t address, uint64_t data);

private:
    std::vector<uint8_t> data;
};

#endif // MEMORY_H