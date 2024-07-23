cmake_minimum_required(VERSION 3.0)
project(ModernOpenGL)

set(CMAKE_CXX_STANDARD 17)

# Set the path to vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/jackp/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Debug print of the source directory
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/HeaderFiles)
include_directories(${PROJECT_SOURCE_DIR}/libs/stb)

add_executable(ModernOpenGL src/tutorial6.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp src/shaderClass.cpp src/stb.cpp)

target_link_libraries(ModernOpenGL PRIVATE glad::glad glfw)
