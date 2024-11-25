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
CMAKE_SOURCE_DIR = /home/rowanfoxx/Documents/github/Chemu8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rowanfoxx/Documents/github/Chemu8/build

# Include any dependencies generated for this target.
include src/emu/CMakeFiles/Emu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/emu/CMakeFiles/Emu.dir/compiler_depend.make

# Include the progress variables for this target.
include src/emu/CMakeFiles/Emu.dir/progress.make

# Include the compile flags for this target's objects.
include src/emu/CMakeFiles/Emu.dir/flags.make

src/emu/CMakeFiles/Emu.dir/cpu.cpp.o: src/emu/CMakeFiles/Emu.dir/flags.make
src/emu/CMakeFiles/Emu.dir/cpu.cpp.o: ../src/emu/cpu.cpp
src/emu/CMakeFiles/Emu.dir/cpu.cpp.o: src/emu/CMakeFiles/Emu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rowanfoxx/Documents/github/Chemu8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/emu/CMakeFiles/Emu.dir/cpu.cpp.o"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/emu/CMakeFiles/Emu.dir/cpu.cpp.o -MF CMakeFiles/Emu.dir/cpu.cpp.o.d -o CMakeFiles/Emu.dir/cpu.cpp.o -c /home/rowanfoxx/Documents/github/Chemu8/src/emu/cpu.cpp

src/emu/CMakeFiles/Emu.dir/cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emu.dir/cpu.cpp.i"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rowanfoxx/Documents/github/Chemu8/src/emu/cpu.cpp > CMakeFiles/Emu.dir/cpu.cpp.i

src/emu/CMakeFiles/Emu.dir/cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emu.dir/cpu.cpp.s"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rowanfoxx/Documents/github/Chemu8/src/emu/cpu.cpp -o CMakeFiles/Emu.dir/cpu.cpp.s

src/emu/CMakeFiles/Emu.dir/memory.cpp.o: src/emu/CMakeFiles/Emu.dir/flags.make
src/emu/CMakeFiles/Emu.dir/memory.cpp.o: ../src/emu/memory.cpp
src/emu/CMakeFiles/Emu.dir/memory.cpp.o: src/emu/CMakeFiles/Emu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rowanfoxx/Documents/github/Chemu8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/emu/CMakeFiles/Emu.dir/memory.cpp.o"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/emu/CMakeFiles/Emu.dir/memory.cpp.o -MF CMakeFiles/Emu.dir/memory.cpp.o.d -o CMakeFiles/Emu.dir/memory.cpp.o -c /home/rowanfoxx/Documents/github/Chemu8/src/emu/memory.cpp

src/emu/CMakeFiles/Emu.dir/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emu.dir/memory.cpp.i"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rowanfoxx/Documents/github/Chemu8/src/emu/memory.cpp > CMakeFiles/Emu.dir/memory.cpp.i

src/emu/CMakeFiles/Emu.dir/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emu.dir/memory.cpp.s"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rowanfoxx/Documents/github/Chemu8/src/emu/memory.cpp -o CMakeFiles/Emu.dir/memory.cpp.s

# Object files for target Emu
Emu_OBJECTS = \
"CMakeFiles/Emu.dir/cpu.cpp.o" \
"CMakeFiles/Emu.dir/memory.cpp.o"

# External object files for target Emu
Emu_EXTERNAL_OBJECTS =

src/emu/libEmu.a: src/emu/CMakeFiles/Emu.dir/cpu.cpp.o
src/emu/libEmu.a: src/emu/CMakeFiles/Emu.dir/memory.cpp.o
src/emu/libEmu.a: src/emu/CMakeFiles/Emu.dir/build.make
src/emu/libEmu.a: src/emu/CMakeFiles/Emu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rowanfoxx/Documents/github/Chemu8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libEmu.a"
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && $(CMAKE_COMMAND) -P CMakeFiles/Emu.dir/cmake_clean_target.cmake
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Emu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/emu/CMakeFiles/Emu.dir/build: src/emu/libEmu.a
.PHONY : src/emu/CMakeFiles/Emu.dir/build

src/emu/CMakeFiles/Emu.dir/clean:
	cd /home/rowanfoxx/Documents/github/Chemu8/build/src/emu && $(CMAKE_COMMAND) -P CMakeFiles/Emu.dir/cmake_clean.cmake
.PHONY : src/emu/CMakeFiles/Emu.dir/clean

src/emu/CMakeFiles/Emu.dir/depend:
	cd /home/rowanfoxx/Documents/github/Chemu8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rowanfoxx/Documents/github/Chemu8 /home/rowanfoxx/Documents/github/Chemu8/src/emu /home/rowanfoxx/Documents/github/Chemu8/build /home/rowanfoxx/Documents/github/Chemu8/build/src/emu /home/rowanfoxx/Documents/github/Chemu8/build/src/emu/CMakeFiles/Emu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/emu/CMakeFiles/Emu.dir/depend

