# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Kaio\Documents\rpgh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Kaio\Documents\rpgh\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rpg2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rpg2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rpg2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rpg2.dir/flags.make

CMakeFiles/rpg2.dir/main.c.obj: CMakeFiles/rpg2.dir/flags.make
CMakeFiles/rpg2.dir/main.c.obj: ../main.c
CMakeFiles/rpg2.dir/main.c.obj: CMakeFiles/rpg2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Kaio\Documents\rpgh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rpg2.dir/main.c.obj"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg2.dir/main.c.obj -MF CMakeFiles\rpg2.dir\main.c.obj.d -o CMakeFiles\rpg2.dir\main.c.obj -c C:\Users\Kaio\Documents\rpgh\main.c

CMakeFiles/rpg2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rpg2.dir/main.c.i"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Kaio\Documents\rpgh\main.c > CMakeFiles\rpg2.dir\main.c.i

CMakeFiles/rpg2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rpg2.dir/main.c.s"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Kaio\Documents\rpgh\main.c -o CMakeFiles\rpg2.dir\main.c.s

CMakeFiles/rpg2.dir/src/mesa.c.obj: CMakeFiles/rpg2.dir/flags.make
CMakeFiles/rpg2.dir/src/mesa.c.obj: ../src/mesa.c
CMakeFiles/rpg2.dir/src/mesa.c.obj: CMakeFiles/rpg2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Kaio\Documents\rpgh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/rpg2.dir/src/mesa.c.obj"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg2.dir/src/mesa.c.obj -MF CMakeFiles\rpg2.dir\src\mesa.c.obj.d -o CMakeFiles\rpg2.dir\src\mesa.c.obj -c C:\Users\Kaio\Documents\rpgh\src\mesa.c

CMakeFiles/rpg2.dir/src/mesa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rpg2.dir/src/mesa.c.i"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Kaio\Documents\rpgh\src\mesa.c > CMakeFiles\rpg2.dir\src\mesa.c.i

CMakeFiles/rpg2.dir/src/mesa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rpg2.dir/src/mesa.c.s"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Kaio\Documents\rpgh\src\mesa.c -o CMakeFiles\rpg2.dir\src\mesa.c.s

CMakeFiles/rpg2.dir/src/section.c.obj: CMakeFiles/rpg2.dir/flags.make
CMakeFiles/rpg2.dir/src/section.c.obj: ../src/section.c
CMakeFiles/rpg2.dir/src/section.c.obj: CMakeFiles/rpg2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Kaio\Documents\rpgh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/rpg2.dir/src/section.c.obj"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg2.dir/src/section.c.obj -MF CMakeFiles\rpg2.dir\src\section.c.obj.d -o CMakeFiles\rpg2.dir\src\section.c.obj -c C:\Users\Kaio\Documents\rpgh\src\section.c

CMakeFiles/rpg2.dir/src/section.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rpg2.dir/src/section.c.i"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Kaio\Documents\rpgh\src\section.c > CMakeFiles\rpg2.dir\src\section.c.i

CMakeFiles/rpg2.dir/src/section.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rpg2.dir/src/section.c.s"
	C:\Users\Kaio\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\222.4345.21\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Kaio\Documents\rpgh\src\section.c -o CMakeFiles\rpg2.dir\src\section.c.s

# Object files for target rpg2
rpg2_OBJECTS = \
"CMakeFiles/rpg2.dir/main.c.obj" \
"CMakeFiles/rpg2.dir/src/mesa.c.obj" \
"CMakeFiles/rpg2.dir/src/section.c.obj"

# External object files for target rpg2
rpg2_EXTERNAL_OBJECTS =

rpg2.exe: CMakeFiles/rpg2.dir/main.c.obj
rpg2.exe: CMakeFiles/rpg2.dir/src/mesa.c.obj
rpg2.exe: CMakeFiles/rpg2.dir/src/section.c.obj
rpg2.exe: CMakeFiles/rpg2.dir/build.make
rpg2.exe: CMakeFiles/rpg2.dir/linklibs.rsp
rpg2.exe: CMakeFiles/rpg2.dir/objects1.rsp
rpg2.exe: CMakeFiles/rpg2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Kaio\Documents\rpgh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable rpg2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\rpg2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rpg2.dir/build: rpg2.exe
.PHONY : CMakeFiles/rpg2.dir/build

CMakeFiles/rpg2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\rpg2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/rpg2.dir/clean

CMakeFiles/rpg2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Kaio\Documents\rpgh C:\Users\Kaio\Documents\rpgh C:\Users\Kaio\Documents\rpgh\cmake-build-debug C:\Users\Kaio\Documents\rpgh\cmake-build-debug C:\Users\Kaio\Documents\rpgh\cmake-build-debug\CMakeFiles\rpg2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rpg2.dir/depend
