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
CMAKE_SOURCE_DIR = /home/zong/projects/ChatServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zong/projects/ChatServer/build

# Include any dependencies generated for this target.
include src/server/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/server.dir/flags.make

src/server/CMakeFiles/server.dir/chatserver.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/chatserver.cpp.o: ../src/server/chatserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/CMakeFiles/server.dir/chatserver.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/chatserver.cpp.o -c /home/zong/projects/ChatServer/src/server/chatserver.cpp

src/server/CMakeFiles/server.dir/chatserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/chatserver.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/chatserver.cpp > CMakeFiles/server.dir/chatserver.cpp.i

src/server/CMakeFiles/server.dir/chatserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/chatserver.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/chatserver.cpp -o CMakeFiles/server.dir/chatserver.cpp.s

src/server/CMakeFiles/server.dir/main.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/main.cpp.o: ../src/server/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/server/CMakeFiles/server.dir/main.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/main.cpp.o -c /home/zong/projects/ChatServer/src/server/main.cpp

src/server/CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/main.cpp > CMakeFiles/server.dir/main.cpp.i

src/server/CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/main.cpp -o CMakeFiles/server.dir/main.cpp.s

src/server/CMakeFiles/server.dir/service.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/service.cpp.o: ../src/server/service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/server/CMakeFiles/server.dir/service.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/service.cpp.o -c /home/zong/projects/ChatServer/src/server/service.cpp

src/server/CMakeFiles/server.dir/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/service.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/service.cpp > CMakeFiles/server.dir/service.cpp.i

src/server/CMakeFiles/server.dir/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/service.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/service.cpp -o CMakeFiles/server.dir/service.cpp.s

src/server/CMakeFiles/server.dir/db/db.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/db/db.cpp.o: ../src/server/db/db.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/server/CMakeFiles/server.dir/db/db.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/db/db.cpp.o -c /home/zong/projects/ChatServer/src/server/db/db.cpp

src/server/CMakeFiles/server.dir/db/db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/db/db.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/db/db.cpp > CMakeFiles/server.dir/db/db.cpp.i

src/server/CMakeFiles/server.dir/db/db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/db/db.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/db/db.cpp -o CMakeFiles/server.dir/db/db.cpp.s

src/server/CMakeFiles/server.dir/model/friendmodel.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/model/friendmodel.cpp.o: ../src/server/model/friendmodel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/server/CMakeFiles/server.dir/model/friendmodel.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/model/friendmodel.cpp.o -c /home/zong/projects/ChatServer/src/server/model/friendmodel.cpp

src/server/CMakeFiles/server.dir/model/friendmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/model/friendmodel.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/model/friendmodel.cpp > CMakeFiles/server.dir/model/friendmodel.cpp.i

src/server/CMakeFiles/server.dir/model/friendmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/model/friendmodel.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/model/friendmodel.cpp -o CMakeFiles/server.dir/model/friendmodel.cpp.s

src/server/CMakeFiles/server.dir/model/groupmodel.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/model/groupmodel.cpp.o: ../src/server/model/groupmodel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/server/CMakeFiles/server.dir/model/groupmodel.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/model/groupmodel.cpp.o -c /home/zong/projects/ChatServer/src/server/model/groupmodel.cpp

src/server/CMakeFiles/server.dir/model/groupmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/model/groupmodel.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/model/groupmodel.cpp > CMakeFiles/server.dir/model/groupmodel.cpp.i

src/server/CMakeFiles/server.dir/model/groupmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/model/groupmodel.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/model/groupmodel.cpp -o CMakeFiles/server.dir/model/groupmodel.cpp.s

src/server/CMakeFiles/server.dir/model/msgmodel.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/model/msgmodel.cpp.o: ../src/server/model/msgmodel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/server/CMakeFiles/server.dir/model/msgmodel.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/model/msgmodel.cpp.o -c /home/zong/projects/ChatServer/src/server/model/msgmodel.cpp

src/server/CMakeFiles/server.dir/model/msgmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/model/msgmodel.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/model/msgmodel.cpp > CMakeFiles/server.dir/model/msgmodel.cpp.i

src/server/CMakeFiles/server.dir/model/msgmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/model/msgmodel.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/model/msgmodel.cpp -o CMakeFiles/server.dir/model/msgmodel.cpp.s

src/server/CMakeFiles/server.dir/model/usermodel.cpp.o: src/server/CMakeFiles/server.dir/flags.make
src/server/CMakeFiles/server.dir/model/usermodel.cpp.o: ../src/server/model/usermodel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/server/CMakeFiles/server.dir/model/usermodel.cpp.o"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/model/usermodel.cpp.o -c /home/zong/projects/ChatServer/src/server/model/usermodel.cpp

src/server/CMakeFiles/server.dir/model/usermodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/model/usermodel.cpp.i"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zong/projects/ChatServer/src/server/model/usermodel.cpp > CMakeFiles/server.dir/model/usermodel.cpp.i

src/server/CMakeFiles/server.dir/model/usermodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/model/usermodel.cpp.s"
	cd /home/zong/projects/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zong/projects/ChatServer/src/server/model/usermodel.cpp -o CMakeFiles/server.dir/model/usermodel.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/chatserver.cpp.o" \
"CMakeFiles/server.dir/main.cpp.o" \
"CMakeFiles/server.dir/service.cpp.o" \
"CMakeFiles/server.dir/db/db.cpp.o" \
"CMakeFiles/server.dir/model/friendmodel.cpp.o" \
"CMakeFiles/server.dir/model/groupmodel.cpp.o" \
"CMakeFiles/server.dir/model/msgmodel.cpp.o" \
"CMakeFiles/server.dir/model/usermodel.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

../bin/server: src/server/CMakeFiles/server.dir/chatserver.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/main.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/service.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/db/db.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/model/friendmodel.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/model/groupmodel.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/model/msgmodel.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/model/usermodel.cpp.o
../bin/server: src/server/CMakeFiles/server.dir/build.make
../bin/server: src/server/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zong/projects/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ../../../bin/server"
	cd /home/zong/projects/ChatServer/build/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/CMakeFiles/server.dir/build: ../bin/server

.PHONY : src/server/CMakeFiles/server.dir/build

src/server/CMakeFiles/server.dir/clean:
	cd /home/zong/projects/ChatServer/build/src/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/server.dir/clean

src/server/CMakeFiles/server.dir/depend:
	cd /home/zong/projects/ChatServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zong/projects/ChatServer /home/zong/projects/ChatServer/src/server /home/zong/projects/ChatServer/build /home/zong/projects/ChatServer/build/src/server /home/zong/projects/ChatServer/build/src/server/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/server.dir/depend

