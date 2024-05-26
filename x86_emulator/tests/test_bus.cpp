#include <gtest/gtest.h>
#include <iostream>
#include "bus.hpp"
#include "../src/memory.hpp"

// Define a fixture for common setup/teardown
class BusTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create memory with size 1024 bytes
        memory = std::make_shared<Memory>(1024);
        // Create bus
        bus = std::make_unique<Bus>(*memory);
    }

    std::shared_ptr<Memory> memory;
    std::unique_ptr<Bus> bus;
};

// Test cases for Bus operations
TEST_F(BusTest, Test8BitReadWrite) {
    bus->write8(100, 0x12);
    EXPECT_EQ(bus->read8(100), 0x12) << "8-bit read/write test failed";
}

TEST_F(BusTest, Test32BitReadWrite) {
    bus->write32(200, 0x12345678);
    EXPECT_EQ(bus->read32(200), 0x12345678) << "32-bit read/write test failed";
}

TEST_F(BusTest, Test64BitReadWrite) {
    bus->write64(300, 0x123456789ABCDEF0);
    EXPECT_EQ(bus->read64(300), 0x123456789ABCDEF0) << "64-bit read/write test failed";
}

// // Main function to run all tests
// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
