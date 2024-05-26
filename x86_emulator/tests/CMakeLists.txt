cmake_minimum_required(VERSION 3.10)
project(x86_64_Emulator_Test)
set(CMAKE_CXX_STANDARD 17)

# Locate Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories from src (adjust path as necessary)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Collect all test source files
file(GLOB TEST_SOURCES "*.cpp")

# Add executable for tests
add_executable(tests ${TEST_SOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/cpu.cpp ${CMAKE_SOURCE_DIR}/src/bus.cpp ${CMAKE_SOURCE_DIR}/src/memory.cpp)

# Link with Google Test libraries
target_link_libraries(tests GTest::GTest GTest::Main)

# Add a test to the project to be run by ctest
include(GoogleTest)
gtest_discover_tests(tests)