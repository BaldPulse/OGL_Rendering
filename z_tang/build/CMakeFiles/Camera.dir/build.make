# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/zhao/Documents/cs180/Final/z_tang

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhao/Documents/cs180/Final/z_tang/build

# Include any dependencies generated for this target.
include CMakeFiles/Camera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Camera.dir/flags.make

CMakeFiles/Camera.dir/ext/glad/src/glad.c.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/ext/glad/src/glad.c.o: ../ext/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Camera.dir/ext/glad/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Camera.dir/ext/glad/src/glad.c.o   -c /home/zhao/Documents/cs180/Final/z_tang/ext/glad/src/glad.c

CMakeFiles/Camera.dir/ext/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Camera.dir/ext/glad/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/ext/glad/src/glad.c > CMakeFiles/Camera.dir/ext/glad/src/glad.c.i

CMakeFiles/Camera.dir/ext/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Camera.dir/ext/glad/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/ext/glad/src/glad.c -o CMakeFiles/Camera.dir/ext/glad/src/glad.c.s

CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o: ../ext/tiny_obj_loader/tiny_obj_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/ext/tiny_obj_loader/tiny_obj_loader.cpp

CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/ext/tiny_obj_loader/tiny_obj_loader.cpp > CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i

CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/ext/tiny_obj_loader/tiny_obj_loader.cpp -o CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s

CMakeFiles/Camera.dir/src/Application.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Application.cpp.o: ../src/Application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Camera.dir/src/Application.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Application.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Application.cpp

CMakeFiles/Camera.dir/src/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Application.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Application.cpp > CMakeFiles/Camera.dir/src/Application.cpp.i

CMakeFiles/Camera.dir/src/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Application.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Application.cpp -o CMakeFiles/Camera.dir/src/Application.cpp.s

CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o: ../src/Application_Helpers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Application_Helpers.cpp

CMakeFiles/Camera.dir/src/Application_Helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Application_Helpers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Application_Helpers.cpp > CMakeFiles/Camera.dir/src/Application_Helpers.cpp.i

CMakeFiles/Camera.dir/src/Application_Helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Application_Helpers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Application_Helpers.cpp -o CMakeFiles/Camera.dir/src/Application_Helpers.cpp.s

CMakeFiles/Camera.dir/src/Bezier.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Bezier.cpp.o: ../src/Bezier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Camera.dir/src/Bezier.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Bezier.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Bezier.cpp

CMakeFiles/Camera.dir/src/Bezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Bezier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Bezier.cpp > CMakeFiles/Camera.dir/src/Bezier.cpp.i

CMakeFiles/Camera.dir/src/Bezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Bezier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Bezier.cpp -o CMakeFiles/Camera.dir/src/Bezier.cpp.s

CMakeFiles/Camera.dir/src/Drive.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Drive.cpp.o: ../src/Drive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Camera.dir/src/Drive.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Drive.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Drive.cpp

CMakeFiles/Camera.dir/src/Drive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Drive.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Drive.cpp > CMakeFiles/Camera.dir/src/Drive.cpp.i

CMakeFiles/Camera.dir/src/Drive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Drive.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Drive.cpp -o CMakeFiles/Camera.dir/src/Drive.cpp.s

CMakeFiles/Camera.dir/src/GLSL.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/GLSL.cpp.o: ../src/GLSL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Camera.dir/src/GLSL.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/GLSL.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/GLSL.cpp

CMakeFiles/Camera.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/GLSL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/GLSL.cpp > CMakeFiles/Camera.dir/src/GLSL.cpp.i

CMakeFiles/Camera.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/GLSL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/GLSL.cpp -o CMakeFiles/Camera.dir/src/GLSL.cpp.s

CMakeFiles/Camera.dir/src/MatrixStack.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/MatrixStack.cpp.o: ../src/MatrixStack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Camera.dir/src/MatrixStack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/MatrixStack.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/MatrixStack.cpp

CMakeFiles/Camera.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/MatrixStack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/MatrixStack.cpp > CMakeFiles/Camera.dir/src/MatrixStack.cpp.i

CMakeFiles/Camera.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/MatrixStack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/MatrixStack.cpp -o CMakeFiles/Camera.dir/src/MatrixStack.cpp.s

CMakeFiles/Camera.dir/src/Program.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Program.cpp.o: ../src/Program.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Camera.dir/src/Program.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Program.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Program.cpp

CMakeFiles/Camera.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Program.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Program.cpp > CMakeFiles/Camera.dir/src/Program.cpp.i

CMakeFiles/Camera.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Program.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Program.cpp -o CMakeFiles/Camera.dir/src/Program.cpp.s

CMakeFiles/Camera.dir/src/Shape.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Shape.cpp.o: ../src/Shape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Camera.dir/src/Shape.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Shape.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Shape.cpp

CMakeFiles/Camera.dir/src/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Shape.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Shape.cpp > CMakeFiles/Camera.dir/src/Shape.cpp.i

CMakeFiles/Camera.dir/src/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Shape.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Shape.cpp -o CMakeFiles/Camera.dir/src/Shape.cpp.s

CMakeFiles/Camera.dir/src/Spline.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Spline.cpp.o: ../src/Spline.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Camera.dir/src/Spline.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Spline.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Spline.cpp

CMakeFiles/Camera.dir/src/Spline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Spline.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Spline.cpp > CMakeFiles/Camera.dir/src/Spline.cpp.i

CMakeFiles/Camera.dir/src/Spline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Spline.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Spline.cpp -o CMakeFiles/Camera.dir/src/Spline.cpp.s

CMakeFiles/Camera.dir/src/TerrainMap.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/TerrainMap.cpp.o: ../src/TerrainMap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Camera.dir/src/TerrainMap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/TerrainMap.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/TerrainMap.cpp

CMakeFiles/Camera.dir/src/TerrainMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/TerrainMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/TerrainMap.cpp > CMakeFiles/Camera.dir/src/TerrainMap.cpp.i

CMakeFiles/Camera.dir/src/TerrainMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/TerrainMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/TerrainMap.cpp -o CMakeFiles/Camera.dir/src/TerrainMap.cpp.s

CMakeFiles/Camera.dir/src/Texture.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/Texture.cpp.o: ../src/Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Camera.dir/src/Texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/Texture.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/Texture.cpp

CMakeFiles/Camera.dir/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/Texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/Texture.cpp > CMakeFiles/Camera.dir/src/Texture.cpp.i

CMakeFiles/Camera.dir/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/Texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/Texture.cpp -o CMakeFiles/Camera.dir/src/Texture.cpp.s

CMakeFiles/Camera.dir/src/WindowManager.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/WindowManager.cpp.o: ../src/WindowManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Camera.dir/src/WindowManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/WindowManager.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/WindowManager.cpp

CMakeFiles/Camera.dir/src/WindowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/WindowManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/WindowManager.cpp > CMakeFiles/Camera.dir/src/WindowManager.cpp.i

CMakeFiles/Camera.dir/src/WindowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/WindowManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/WindowManager.cpp -o CMakeFiles/Camera.dir/src/WindowManager.cpp.s

CMakeFiles/Camera.dir/src/main.cpp.o: CMakeFiles/Camera.dir/flags.make
CMakeFiles/Camera.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Camera.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Camera.dir/src/main.cpp.o -c /home/zhao/Documents/cs180/Final/z_tang/src/main.cpp

CMakeFiles/Camera.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/cs180/Final/z_tang/src/main.cpp > CMakeFiles/Camera.dir/src/main.cpp.i

CMakeFiles/Camera.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/cs180/Final/z_tang/src/main.cpp -o CMakeFiles/Camera.dir/src/main.cpp.s

# Object files for target Camera
Camera_OBJECTS = \
"CMakeFiles/Camera.dir/ext/glad/src/glad.c.o" \
"CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o" \
"CMakeFiles/Camera.dir/src/Application.cpp.o" \
"CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o" \
"CMakeFiles/Camera.dir/src/Bezier.cpp.o" \
"CMakeFiles/Camera.dir/src/Drive.cpp.o" \
"CMakeFiles/Camera.dir/src/GLSL.cpp.o" \
"CMakeFiles/Camera.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/Camera.dir/src/Program.cpp.o" \
"CMakeFiles/Camera.dir/src/Shape.cpp.o" \
"CMakeFiles/Camera.dir/src/Spline.cpp.o" \
"CMakeFiles/Camera.dir/src/TerrainMap.cpp.o" \
"CMakeFiles/Camera.dir/src/Texture.cpp.o" \
"CMakeFiles/Camera.dir/src/WindowManager.cpp.o" \
"CMakeFiles/Camera.dir/src/main.cpp.o"

# External object files for target Camera
Camera_EXTERNAL_OBJECTS =

Camera: CMakeFiles/Camera.dir/ext/glad/src/glad.c.o
Camera: CMakeFiles/Camera.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o
Camera: CMakeFiles/Camera.dir/src/Application.cpp.o
Camera: CMakeFiles/Camera.dir/src/Application_Helpers.cpp.o
Camera: CMakeFiles/Camera.dir/src/Bezier.cpp.o
Camera: CMakeFiles/Camera.dir/src/Drive.cpp.o
Camera: CMakeFiles/Camera.dir/src/GLSL.cpp.o
Camera: CMakeFiles/Camera.dir/src/MatrixStack.cpp.o
Camera: CMakeFiles/Camera.dir/src/Program.cpp.o
Camera: CMakeFiles/Camera.dir/src/Shape.cpp.o
Camera: CMakeFiles/Camera.dir/src/Spline.cpp.o
Camera: CMakeFiles/Camera.dir/src/TerrainMap.cpp.o
Camera: CMakeFiles/Camera.dir/src/Texture.cpp.o
Camera: CMakeFiles/Camera.dir/src/WindowManager.cpp.o
Camera: CMakeFiles/Camera.dir/src/main.cpp.o
Camera: CMakeFiles/Camera.dir/build.make
Camera: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
Camera: CMakeFiles/Camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Camera.dir/build: Camera

.PHONY : CMakeFiles/Camera.dir/build

CMakeFiles/Camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Camera.dir/clean

CMakeFiles/Camera.dir/depend:
	cd /home/zhao/Documents/cs180/Final/z_tang/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhao/Documents/cs180/Final/z_tang /home/zhao/Documents/cs180/Final/z_tang /home/zhao/Documents/cs180/Final/z_tang/build /home/zhao/Documents/cs180/Final/z_tang/build /home/zhao/Documents/cs180/Final/z_tang/build/CMakeFiles/Camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Camera.dir/depend
