cmake_minimum_required(VERSION 3.10)
project(x86_64_Emulator)
set(CMAKE_CXX_STANDARD 17)

# Add your main executable target
add_executable(x86_emulator src/main.cpp src/cpu.cpp src/bus.cpp src/memory.cpp)

# Include directories for header files
include_directories(src)

# Include Google Test for testing
add_subdirectory(googletest)

# Include source directory
add_subdirectory(src)

# Add the tests subdirectory
add_subdirectory(tests)