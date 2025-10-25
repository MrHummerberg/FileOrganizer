# FileOrganizer/src/CMakeLists.txt

# Collect all source files from src/ and its subdirectories
file(GLOB_RECURSE SOURCES 
    "*.cpp"
    "*.h"
)

# Create the main executable named 'FileOrganizer'
add_executable(FileOrganizer ${SOURCES})

# Tell the compiler to look for header files inside the 'src' directory.
# This allows you to write #include "core/..." or #include "utils/...".
target_include_directories(FileOrganizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
