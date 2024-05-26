cmake_minimum_required(VERSION 3.10)
project(x86_64_Emulator)

set(CMAKE_CXX_STANDARD 17)

# Add your main executable target
add_executable(x86_emulator
    src/main.cpp
    src/cpu.cpp
    src/bus.cpp
    src/memory.cpp
    # Add all necessary header files here as well
    src/cpu.hpp
    src/bus.hpp
    src/memory.hpp
)

# Optionally, link with additional libraries if needed
# target_link_libraries(x86_emulator your_additional_library)

# Include Google Test for testing
add_subdirectory(googletest)

# Add the tests subdirectory
add_subdirectory(tests)
