# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tests.dir/flags.make

tests/CMakeFiles/tests.dir/test_bus.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/test_bus.cpp.o: ../tests/test_bus.cpp
tests/CMakeFiles/tests.dir/test_bus.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/tests.dir/test_bus.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/test_bus.cpp.o -MF CMakeFiles/tests.dir/test_bus.cpp.o.d -o CMakeFiles/tests.dir/test_bus.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_bus.cpp

tests/CMakeFiles/tests.dir/test_bus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/test_bus.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_bus.cpp > CMakeFiles/tests.dir/test_bus.cpp.i

tests/CMakeFiles/tests.dir/test_bus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test_bus.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_bus.cpp -o CMakeFiles/tests.dir/test_bus.cpp.s

tests/CMakeFiles/tests.dir/test_cpu.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/test_cpu.cpp.o: ../tests/test_cpu.cpp
tests/CMakeFiles/tests.dir/test_cpu.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/tests.dir/test_cpu.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/test_cpu.cpp.o -MF CMakeFiles/tests.dir/test_cpu.cpp.o.d -o CMakeFiles/tests.dir/test_cpu.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_cpu.cpp

tests/CMakeFiles/tests.dir/test_cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/test_cpu.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_cpu.cpp > CMakeFiles/tests.dir/test_cpu.cpp.i

tests/CMakeFiles/tests.dir/test_cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test_cpu.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_cpu.cpp -o CMakeFiles/tests.dir/test_cpu.cpp.s

tests/CMakeFiles/tests.dir/test_memory.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/test_memory.cpp.o: ../tests/test_memory.cpp
tests/CMakeFiles/tests.dir/test_memory.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/tests.dir/test_memory.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/test_memory.cpp.o -MF CMakeFiles/tests.dir/test_memory.cpp.o.d -o CMakeFiles/tests.dir/test_memory.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_memory.cpp

tests/CMakeFiles/tests.dir/test_memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/test_memory.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_memory.cpp > CMakeFiles/tests.dir/test_memory.cpp.i

tests/CMakeFiles/tests.dir/test_memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/test_memory.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests/test_memory.cpp -o CMakeFiles/tests.dir/test_memory.cpp.s

tests/CMakeFiles/tests.dir/__/src/main.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/__/src/main.cpp.o: ../src/main.cpp
tests/CMakeFiles/tests.dir/__/src/main.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/CMakeFiles/tests.dir/__/src/main.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/__/src/main.cpp.o -MF CMakeFiles/tests.dir/__/src/main.cpp.o.d -o CMakeFiles/tests.dir/__/src/main.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/main.cpp

tests/CMakeFiles/tests.dir/__/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/__/src/main.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/main.cpp > CMakeFiles/tests.dir/__/src/main.cpp.i

tests/CMakeFiles/tests.dir/__/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/__/src/main.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/main.cpp -o CMakeFiles/tests.dir/__/src/main.cpp.s

tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o: ../src/cpu.cpp
tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o -MF CMakeFiles/tests.dir/__/src/cpu.cpp.o.d -o CMakeFiles/tests.dir/__/src/cpu.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/cpu.cpp

tests/CMakeFiles/tests.dir/__/src/cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/__/src/cpu.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/cpu.cpp > CMakeFiles/tests.dir/__/src/cpu.cpp.i

tests/CMakeFiles/tests.dir/__/src/cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/__/src/cpu.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/cpu.cpp -o CMakeFiles/tests.dir/__/src/cpu.cpp.s

tests/CMakeFiles/tests.dir/__/src/bus.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/__/src/bus.cpp.o: ../src/bus.cpp
tests/CMakeFiles/tests.dir/__/src/bus.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/CMakeFiles/tests.dir/__/src/bus.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/__/src/bus.cpp.o -MF CMakeFiles/tests.dir/__/src/bus.cpp.o.d -o CMakeFiles/tests.dir/__/src/bus.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/bus.cpp

tests/CMakeFiles/tests.dir/__/src/bus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/__/src/bus.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/bus.cpp > CMakeFiles/tests.dir/__/src/bus.cpp.i

tests/CMakeFiles/tests.dir/__/src/bus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/__/src/bus.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/bus.cpp -o CMakeFiles/tests.dir/__/src/bus.cpp.s

tests/CMakeFiles/tests.dir/__/src/memory.cpp.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/__/src/memory.cpp.o: ../src/memory.cpp
tests/CMakeFiles/tests.dir/__/src/memory.cpp.o: tests/CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tests/CMakeFiles/tests.dir/__/src/memory.cpp.o"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests.dir/__/src/memory.cpp.o -MF CMakeFiles/tests.dir/__/src/memory.cpp.o.d -o CMakeFiles/tests.dir/__/src/memory.cpp.o -c /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/memory.cpp

tests/CMakeFiles/tests.dir/__/src/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/__/src/memory.cpp.i"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/memory.cpp > CMakeFiles/tests.dir/__/src/memory.cpp.i

tests/CMakeFiles/tests.dir/__/src/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/__/src/memory.cpp.s"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/src/memory.cpp -o CMakeFiles/tests.dir/__/src/memory.cpp.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/test_bus.cpp.o" \
"CMakeFiles/tests.dir/test_cpu.cpp.o" \
"CMakeFiles/tests.dir/test_memory.cpp.o" \
"CMakeFiles/tests.dir/__/src/main.cpp.o" \
"CMakeFiles/tests.dir/__/src/cpu.cpp.o" \
"CMakeFiles/tests.dir/__/src/bus.cpp.o" \
"CMakeFiles/tests.dir/__/src/memory.cpp.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests/tests: tests/CMakeFiles/tests.dir/test_bus.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/test_cpu.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/test_memory.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/__/src/main.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/__/src/cpu.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/__/src/bus.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/__/src/memory.cpp.o
tests/tests: tests/CMakeFiles/tests.dir/build.make
tests/tests: lib/libgtest_main.a
tests/tests: lib/libgtest.a
tests/tests: tests/CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable tests"
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && /usr/bin/cmake -D TEST_TARGET=tests -D TEST_EXECUTABLE=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests/tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=tests_TESTS -D CTEST_FILE=/mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests/tests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/CMakeFiles/tests.dir/build: tests/tests
.PHONY : tests/CMakeFiles/tests.dir/build

tests/CMakeFiles/tests.dir/clean:
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tests.dir/clean

tests/CMakeFiles/tests.dir/depend:
	cd /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/tests /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests /mnt/c/Users/rudra/Desktop/EmuDev/x86_emulator/build/tests/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/tests.dir/depend

