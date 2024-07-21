cmake_minimum_required(VERSION 3.0)
project(ModernOpenGL)

set(CMAKE_CXX_STANDARD 17)  # Set C++ standard to C++17

# Set the path to vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/jackp/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

include_directories(HeaderFiles)  # Add this line to include the HeaderFiles directory

add_executable(ModernOpenGL src/tutorial5.cpp src/shaderClass.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp)

target_link_libraries(ModernOpenGL PRIVATE glad::glad glfw)
