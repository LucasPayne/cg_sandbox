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
CMAKE_SOURCE_DIR = /home/lucas/uni/363/ray_tracer/libraries/glm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/uni/363/ray_tracer/libraries/glm

# Include any dependencies generated for this target.
include test/perf/CMakeFiles/test-perf_matrix_div.dir/depend.make

# Include the progress variables for this target.
include test/perf/CMakeFiles/test-perf_matrix_div.dir/progress.make

# Include the compile flags for this target's objects.
include test/perf/CMakeFiles/test-perf_matrix_div.dir/flags.make

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o: test/perf/CMakeFiles/test-perf_matrix_div.dir/flags.make
test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o: test/perf/perf_matrix_div.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/uni/363/ray_tracer/libraries/glm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o"
	cd /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o -c /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf/perf_matrix_div.cpp

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.i"
	cd /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf/perf_matrix_div.cpp > CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.i

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.s"
	cd /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf/perf_matrix_div.cpp -o CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.s

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.requires:

.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.requires

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.provides: test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.requires
	$(MAKE) -f test/perf/CMakeFiles/test-perf_matrix_div.dir/build.make test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.provides.build
.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.provides

test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.provides.build: test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o


# Object files for target test-perf_matrix_div
test__perf_matrix_div_OBJECTS = \
"CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o"

# External object files for target test-perf_matrix_div
test__perf_matrix_div_EXTERNAL_OBJECTS =

test/perf/test-perf_matrix_div: test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o
test/perf/test-perf_matrix_div: test/perf/CMakeFiles/test-perf_matrix_div.dir/build.make
test/perf/test-perf_matrix_div: test/perf/CMakeFiles/test-perf_matrix_div.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/uni/363/ray_tracer/libraries/glm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-perf_matrix_div"
	cd /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-perf_matrix_div.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/perf/CMakeFiles/test-perf_matrix_div.dir/build: test/perf/test-perf_matrix_div

.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/build

test/perf/CMakeFiles/test-perf_matrix_div.dir/requires: test/perf/CMakeFiles/test-perf_matrix_div.dir/perf_matrix_div.cpp.o.requires

.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/requires

test/perf/CMakeFiles/test-perf_matrix_div.dir/clean:
	cd /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf && $(CMAKE_COMMAND) -P CMakeFiles/test-perf_matrix_div.dir/cmake_clean.cmake
.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/clean

test/perf/CMakeFiles/test-perf_matrix_div.dir/depend:
	cd /home/lucas/uni/363/ray_tracer/libraries/glm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/uni/363/ray_tracer/libraries/glm /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf /home/lucas/uni/363/ray_tracer/libraries/glm /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf /home/lucas/uni/363/ray_tracer/libraries/glm/test/perf/CMakeFiles/test-perf_matrix_div.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/perf/CMakeFiles/test-perf_matrix_div.dir/depend

