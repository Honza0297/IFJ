# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\danbu\CLionProjects\ifjprojektspravny

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IFJ2018.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IFJ2018.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IFJ2018.dir/flags.make

CMakeFiles/IFJ2018.dir/main.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/IFJ2018.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\main.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\main.c

CMakeFiles/IFJ2018.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\main.c > CMakeFiles\IFJ2018.dir\main.c.i

CMakeFiles/IFJ2018.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\main.c -o CMakeFiles\IFJ2018.dir\main.c.s

CMakeFiles/IFJ2018.dir/scanner.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/scanner.c.obj: ../scanner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/IFJ2018.dir/scanner.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\scanner.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\scanner.c

CMakeFiles/IFJ2018.dir/scanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/scanner.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\scanner.c > CMakeFiles\IFJ2018.dir\scanner.c.i

CMakeFiles/IFJ2018.dir/scanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/scanner.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\scanner.c -o CMakeFiles\IFJ2018.dir\scanner.c.s

CMakeFiles/IFJ2018.dir/parser_expr.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/parser_expr.c.obj: ../parser_expr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/IFJ2018.dir/parser_expr.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\parser_expr.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\parser_expr.c

CMakeFiles/IFJ2018.dir/parser_expr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/parser_expr.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\parser_expr.c > CMakeFiles\IFJ2018.dir\parser_expr.c.i

CMakeFiles/IFJ2018.dir/parser_expr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/parser_expr.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\parser_expr.c -o CMakeFiles\IFJ2018.dir\parser_expr.c.s

CMakeFiles/IFJ2018.dir/parser.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/parser.c.obj: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/IFJ2018.dir/parser.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\parser.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\parser.c

CMakeFiles/IFJ2018.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/parser.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\parser.c > CMakeFiles\IFJ2018.dir\parser.c.i

CMakeFiles/IFJ2018.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/parser.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\parser.c -o CMakeFiles\IFJ2018.dir\parser.c.s

CMakeFiles/IFJ2018.dir/symtable.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/symtable.c.obj: ../symtable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/IFJ2018.dir/symtable.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\symtable.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\symtable.c

CMakeFiles/IFJ2018.dir/symtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/symtable.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\symtable.c > CMakeFiles\IFJ2018.dir\symtable.c.i

CMakeFiles/IFJ2018.dir/symtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/symtable.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\symtable.c -o CMakeFiles\IFJ2018.dir\symtable.c.s

CMakeFiles/IFJ2018.dir/tac.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/tac.c.obj: ../tac.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/IFJ2018.dir/tac.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\tac.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\tac.c

CMakeFiles/IFJ2018.dir/tac.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/tac.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\tac.c > CMakeFiles\IFJ2018.dir\tac.c.i

CMakeFiles/IFJ2018.dir/tac.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/tac.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\tac.c -o CMakeFiles\IFJ2018.dir\tac.c.s

CMakeFiles/IFJ2018.dir/code_gen.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/code_gen.c.obj: ../code_gen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/IFJ2018.dir/code_gen.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\code_gen.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\code_gen.c

CMakeFiles/IFJ2018.dir/code_gen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/code_gen.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\code_gen.c > CMakeFiles\IFJ2018.dir\code_gen.c.i

CMakeFiles/IFJ2018.dir/code_gen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/code_gen.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\code_gen.c -o CMakeFiles\IFJ2018.dir\code_gen.c.s

CMakeFiles/IFJ2018.dir/garbage_collector.c.obj: CMakeFiles/IFJ2018.dir/flags.make
CMakeFiles/IFJ2018.dir/garbage_collector.c.obj: ../garbage_collector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/IFJ2018.dir/garbage_collector.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\IFJ2018.dir\garbage_collector.c.obj   -c C:\Users\danbu\CLionProjects\ifjprojektspravny\garbage_collector.c

CMakeFiles/IFJ2018.dir/garbage_collector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IFJ2018.dir/garbage_collector.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\danbu\CLionProjects\ifjprojektspravny\garbage_collector.c > CMakeFiles\IFJ2018.dir\garbage_collector.c.i

CMakeFiles/IFJ2018.dir/garbage_collector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IFJ2018.dir/garbage_collector.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\danbu\CLionProjects\ifjprojektspravny\garbage_collector.c -o CMakeFiles\IFJ2018.dir\garbage_collector.c.s

# Object files for target IFJ2018
IFJ2018_OBJECTS = \
"CMakeFiles/IFJ2018.dir/main.c.obj" \
"CMakeFiles/IFJ2018.dir/scanner.c.obj" \
"CMakeFiles/IFJ2018.dir/parser_expr.c.obj" \
"CMakeFiles/IFJ2018.dir/parser.c.obj" \
"CMakeFiles/IFJ2018.dir/symtable.c.obj" \
"CMakeFiles/IFJ2018.dir/tac.c.obj" \
"CMakeFiles/IFJ2018.dir/code_gen.c.obj" \
"CMakeFiles/IFJ2018.dir/garbage_collector.c.obj"

# External object files for target IFJ2018
IFJ2018_EXTERNAL_OBJECTS =

IFJ2018.exe: CMakeFiles/IFJ2018.dir/main.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/scanner.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/parser_expr.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/parser.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/symtable.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/tac.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/code_gen.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/garbage_collector.c.obj
IFJ2018.exe: CMakeFiles/IFJ2018.dir/build.make
IFJ2018.exe: CMakeFiles/IFJ2018.dir/linklibs.rsp
IFJ2018.exe: CMakeFiles/IFJ2018.dir/objects1.rsp
IFJ2018.exe: CMakeFiles/IFJ2018.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable IFJ2018.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\IFJ2018.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IFJ2018.dir/build: IFJ2018.exe

.PHONY : CMakeFiles/IFJ2018.dir/build

CMakeFiles/IFJ2018.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\IFJ2018.dir\cmake_clean.cmake
.PHONY : CMakeFiles/IFJ2018.dir/clean

CMakeFiles/IFJ2018.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\danbu\CLionProjects\ifjprojektspravny C:\Users\danbu\CLionProjects\ifjprojektspravny C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug C:\Users\danbu\CLionProjects\ifjprojektspravny\cmake-build-debug\CMakeFiles\IFJ2018.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IFJ2018.dir/depend

