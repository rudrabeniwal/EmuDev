add_library(emulator
    cpu.cpp
    bus.cpp
    memory.cpp
)

target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})