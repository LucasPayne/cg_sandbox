# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/computer_graphics/cg_sandbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/computer_graphics/cg_sandbox/build

# Utility rule file for docs.

# Include the progress variables for this target.
include dependencies/glfw/docs/CMakeFiles/docs.dir/progress.make

dependencies/glfw/docs/CMakeFiles/docs:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/lucas/computer_graphics/cg_sandbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating HTML documentation"
	cd /home/lucas/computer_graphics/cg_sandbox/build/dependencies/glfw/docs && /usr/bin/doxygen

docs: dependencies/glfw/docs/CMakeFiles/docs
docs: dependencies/glfw/docs/CMakeFiles/docs.dir/build.make

.PHONY : docs

# Rule to build all files generated by this target.
dependencies/glfw/docs/CMakeFiles/docs.dir/build: docs

.PHONY : dependencies/glfw/docs/CMakeFiles/docs.dir/build

dependencies/glfw/docs/CMakeFiles/docs.dir/clean:
	cd /home/lucas/computer_graphics/cg_sandbox/build/dependencies/glfw/docs && $(CMAKE_COMMAND) -P CMakeFiles/docs.dir/cmake_clean.cmake
.PHONY : dependencies/glfw/docs/CMakeFiles/docs.dir/clean

dependencies/glfw/docs/CMakeFiles/docs.dir/depend:
	cd /home/lucas/computer_graphics/cg_sandbox/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/computer_graphics/cg_sandbox /home/lucas/computer_graphics/cg_sandbox/dependencies/glfw/docs /home/lucas/computer_graphics/cg_sandbox/build /home/lucas/computer_graphics/cg_sandbox/build/dependencies/glfw/docs /home/lucas/computer_graphics/cg_sandbox/build/dependencies/glfw/docs/CMakeFiles/docs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies/glfw/docs/CMakeFiles/docs.dir/depend

