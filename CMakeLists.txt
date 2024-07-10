cmake_minimum_required(VERSION 3.20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(RENDERER_ROOT_DIR "${ROOT_DIR}/renderer")
set(RENDERER_SOURCE_DIR "${RENDERER_ROOT_DIR}/src")

set(renderer_name VulanRenderer)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(EXPORT_COMPILE_COMMANDS ON)

project(${renderer_name})

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_program(GLSLC_PROGRAM glslc REQUIRED)
execute_process(COMMAND ${GLSLC_PROGRAM} ${RENDERER_ROOT_DIR}/assets/shaders/shader.vert -o ${RENDERER_ROOT_DIR}/assets/shaders/shader.vert.spv)
execute_process(COMMAND ${GLSLC_PROGRAM} ${RENDERER_ROOT_DIR}/assets/shaders/shader.frag -o ${RENDERER_ROOT_DIR}/assets/shaders/shader.frag.spv)

add_subdirectory(renderer)
