set(THIRD_PARITY_DIRS "${RENDERER_ROOT_DIR}/3rdparty")
set(THIRD_PARITY_INCLUDE_DIRS "${RENDERER_ROOT_DIR}/include")

add_subdirectory(3rdparty)

file(GLOB include_files "include/*.h")
file(GLOB sources_files "src/*.cpp" "src/*.h")

add_library(${renderer_name} STATIC ${sources_files})

target_include_directories(${renderer_name} PUBLIC ${RENDERER_SOURCE_DIR})

# stb_image, tiny_obj_loader
target_include_directories(${renderer_name} PUBLIC ${THIRD_PARITY_INCLUDE_DIRS})
message(${THIRD_PARITY_INCLUDE_DIRS})

# sdl2
include(3rdparty/SDL2-2.30.4/cmake/sdl2-config.cmake)
target_include_directories(${renderer_name} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${renderer_name} ${SDL2_LIBRARIES})

# vulkan
find_package(Vulkan REQUIRED)
target_include_directories(${renderer_name} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${renderer_name} Vulkan::Vulkan)

# glm
set(GLM_INCLUDE_DIRS ${THIRD_PARITY_DIRS}/glm)
target_include_directories(${renderer_name} PUBLIC ${GLM_INCLUDE_DIRS})
target_link_libraries(${renderer_name} glm)

add_subdirectory(sandbox)
