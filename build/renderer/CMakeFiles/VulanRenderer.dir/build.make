# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = E:\Program\CMake\bin\cmake.exe

# The command to remove a file.
RM = E:\Program\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Doc\ProjectFiles\CPP\VulkanRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Doc\ProjectFiles\CPP\VulkanRenderer\build

# Include any dependencies generated for this target.
include renderer/CMakeFiles/VulanRenderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.make

# Include the progress variables for this target.
include renderer/CMakeFiles/VulanRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include renderer/CMakeFiles/VulanRenderer.dir/flags.make

renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/buffer.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\buffer.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\buffer.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\buffer.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/buffer.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\buffer.cpp > CMakeFiles\VulanRenderer.dir\src\buffer.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/buffer.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\buffer.cpp -o CMakeFiles\VulanRenderer.dir\src\buffer.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/command_manager.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\command_manager.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\command_manager.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\command_manager.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\command_manager.cpp > CMakeFiles\VulanRenderer.dir\src\command_manager.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\command_manager.cpp -o CMakeFiles\VulanRenderer.dir\src\command_manager.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/context.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\context.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\context.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\context.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/context.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\context.cpp > CMakeFiles\VulanRenderer.dir\src\context.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/context.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\context.cpp -o CMakeFiles\VulanRenderer.dir\src\context.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/descriptor_manager.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\descriptor_manager.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\descriptor_manager.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\descriptor_manager.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\descriptor_manager.cpp > CMakeFiles\VulanRenderer.dir\src\descriptor_manager.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\descriptor_manager.cpp -o CMakeFiles\VulanRenderer.dir\src\descriptor_manager.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/huahualib.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\huahualib.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\huahualib.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\huahualib.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\huahualib.cpp > CMakeFiles\VulanRenderer.dir\src\huahualib.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\huahualib.cpp -o CMakeFiles\VulanRenderer.dir\src\huahualib.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/render_process.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\render_process.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\render_process.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\render_process.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/render_process.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\render_process.cpp > CMakeFiles\VulanRenderer.dir\src\render_process.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/render_process.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\render_process.cpp -o CMakeFiles\VulanRenderer.dir\src\render_process.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/renderer.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\renderer.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\renderer.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\renderer.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/renderer.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\renderer.cpp > CMakeFiles\VulanRenderer.dir\src\renderer.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/renderer.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\renderer.cpp -o CMakeFiles\VulanRenderer.dir\src\renderer.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/shader.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\shader.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\shader.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\shader.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/shader.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\shader.cpp > CMakeFiles\VulanRenderer.dir\src\shader.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/shader.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\shader.cpp -o CMakeFiles\VulanRenderer.dir\src\shader.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/swapchain.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\swapchain.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\swapchain.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\swapchain.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\swapchain.cpp > CMakeFiles\VulanRenderer.dir\src\swapchain.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\swapchain.cpp -o CMakeFiles\VulanRenderer.dir\src\swapchain.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/texture.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\texture.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\texture.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\texture.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/texture.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\texture.cpp > CMakeFiles\VulanRenderer.dir\src\texture.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/texture.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\texture.cpp -o CMakeFiles\VulanRenderer.dir\src\texture.cpp.s

renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/flags.make
renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/includes_CXX.rsp
renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj: E:/Doc/ProjectFiles/CPP/VulkanRenderer/renderer/src/tool.cpp
renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj: renderer/CMakeFiles/VulanRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj -MF CMakeFiles\VulanRenderer.dir\src\tool.cpp.obj.d -o CMakeFiles\VulanRenderer.dir\src\tool.cpp.obj -c E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\tool.cpp

renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulanRenderer.dir/src/tool.cpp.i"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\tool.cpp > CMakeFiles\VulanRenderer.dir\src\tool.cpp.i

renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulanRenderer.dir/src/tool.cpp.s"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && E:\Program\MSYS64\clang64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer\src\tool.cpp -o CMakeFiles\VulanRenderer.dir\src\tool.cpp.s

# Object files for target VulanRenderer
VulanRenderer_OBJECTS = \
"CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/context.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj" \
"CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj"

# External object files for target VulanRenderer
VulanRenderer_EXTERNAL_OBJECTS =

renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/buffer.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/command_manager.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/context.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/descriptor_manager.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/huahualib.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/render_process.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/renderer.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/shader.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/swapchain.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/texture.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/src/tool.cpp.obj
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/build.make
renderer/libVulanRenderer.a: renderer/CMakeFiles/VulanRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libVulanRenderer.a"
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && $(CMAKE_COMMAND) -P CMakeFiles\VulanRenderer.dir\cmake_clean_target.cmake
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\VulanRenderer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
renderer/CMakeFiles/VulanRenderer.dir/build: renderer/libVulanRenderer.a
.PHONY : renderer/CMakeFiles/VulanRenderer.dir/build

renderer/CMakeFiles/VulanRenderer.dir/clean:
	cd /d E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer && $(CMAKE_COMMAND) -P CMakeFiles\VulanRenderer.dir\cmake_clean.cmake
.PHONY : renderer/CMakeFiles/VulanRenderer.dir/clean

renderer/CMakeFiles/VulanRenderer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Doc\ProjectFiles\CPP\VulkanRenderer E:\Doc\ProjectFiles\CPP\VulkanRenderer\renderer E:\Doc\ProjectFiles\CPP\VulkanRenderer\build E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer E:\Doc\ProjectFiles\CPP\VulkanRenderer\build\renderer\CMakeFiles\VulanRenderer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : renderer/CMakeFiles/VulanRenderer.dir/depend
