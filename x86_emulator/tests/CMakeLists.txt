cmake_minimum_required(VERSION 3.10)
project(x86_64_Emulator_Test)

set(CMAKE_CXX_STANDARD 17)

# Locate Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/src)

# Collect all test source files
file(GLOB TEST_SOURCES "*.cpp")

# List your specific test source files
set(TEST_SOURCES
    test_cpu.cpp
    test_memory.cpp
    test_bus.cpp
    # Add more test source files if needed
)

# Add executable for tests
add_executable(tests ${TEST_SOURCES})

# Link with Google Test libraries and your source library (emulator)
target_link_libraries(tests GTest::GTest GTest::Main emulator)

# Optionally, if you have other dependencies, link them here as well
# target_link_libraries(tests your_additional_lib)

# Add a test to the project to be run by ctest
include(GoogleTest)
gtest_discover_tests(tests)
