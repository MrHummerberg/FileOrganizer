# FileOrganizer/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(FileOrganizer VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard for the entire project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the source code subdirectory to the build
add_subdirectory(src)
