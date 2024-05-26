enable_testing()

add_executable(test_cpu test_cpu.cpp)
target_link_libraries(test_cpu emulator)
add_test(NAME test_cpu COMMAND test_cpu)

add_executable(test_memory test_memory.cpp)
target_link_libraries(test_memory emulator)
add_test(NAME test_memory COMMAND test_memory)

add_executable(test_bus test_bus.cpp)
target_link_libraries(test_bus emulator)
add_test(NAME test_bus COMMAND test_bus)