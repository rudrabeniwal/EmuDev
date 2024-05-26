#include <gtest/gtest.h>
#include <iostream>
#include "memory.hpp"

// Define a fixture for common setup/teardown
class MemoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create memory with size 1024 bytes
        memory = std::make_unique<Memory>(1024);
    }

    std::unique_ptr<Memory> memory;
};

// Test cases for Memory operations
TEST_F(MemoryTest, Test8BitReadWrite) {
    memory->write8(100, 0x12);
    EXPECT_EQ(memory->read8(100), 0x12) << "8-bit read/write test failed";
}

TEST_F(MemoryTest, Test32BitReadWrite) {
    memory->write32(200, 0x12345678);
    EXPECT_EQ(memory->read32(200), 0x12345678) << "32-bit read/write test failed";
}

TEST_F(MemoryTest, Test64BitReadWrite) {
    memory->write64(300, 0x123456789ABCDEF0);
    EXPECT_EQ(memory->read64(300), 0x123456789ABCDEF0) << "64-bit read/write test failed";
}

// Main function to run all tests
// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
