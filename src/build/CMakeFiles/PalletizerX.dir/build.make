# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\run\RoboticsExp\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\run\RoboticsExp\src\build

# Include any dependencies generated for this target.
include CMakeFiles/PalletizerX.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PalletizerX.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PalletizerX.dir/flags.make

CMakeFiles/PalletizerX.dir/main.cpp.obj: CMakeFiles/PalletizerX.dir/flags.make
CMakeFiles/PalletizerX.dir/main.cpp.obj: CMakeFiles/PalletizerX.dir/includes_CXX.rsp
CMakeFiles/PalletizerX.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\run\RoboticsExp\src\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PalletizerX.dir/main.cpp.obj"
	D:\ProgramFiles\TDM-GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PalletizerX.dir\main.cpp.obj -c D:\run\RoboticsExp\src\main.cpp

CMakeFiles/PalletizerX.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PalletizerX.dir/main.cpp.i"
	D:\ProgramFiles\TDM-GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\run\RoboticsExp\src\main.cpp > CMakeFiles\PalletizerX.dir\main.cpp.i

CMakeFiles/PalletizerX.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PalletizerX.dir/main.cpp.s"
	D:\ProgramFiles\TDM-GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\run\RoboticsExp\src\main.cpp -o CMakeFiles\PalletizerX.dir\main.cpp.s

# Object files for target PalletizerX
PalletizerX_OBJECTS = \
"CMakeFiles/PalletizerX.dir/main.cpp.obj"

# External object files for target PalletizerX
PalletizerX_EXTERNAL_OBJECTS =

PalletizerX.exe: CMakeFiles/PalletizerX.dir/main.cpp.obj
PalletizerX.exe: CMakeFiles/PalletizerX.dir/build.make
PalletizerX.exe: CMakeFiles/PalletizerX.dir/linklibs.rsp
PalletizerX.exe: CMakeFiles/PalletizerX.dir/objects1.rsp
PalletizerX.exe: CMakeFiles/PalletizerX.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\run\RoboticsExp\src\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PalletizerX.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PalletizerX.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PalletizerX.dir/build: PalletizerX.exe

.PHONY : CMakeFiles/PalletizerX.dir/build

CMakeFiles/PalletizerX.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PalletizerX.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PalletizerX.dir/clean

CMakeFiles/PalletizerX.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\run\RoboticsExp\src D:\run\RoboticsExp\src D:\run\RoboticsExp\src\build D:\run\RoboticsExp\src\build D:\run\RoboticsExp\src\build\CMakeFiles\PalletizerX.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PalletizerX.dir/depend
