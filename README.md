# FileOrganizer

A high-performance, intelligent command-line file organization and renaming utility written in modern C++.

## Features

*   **Intelligent Organization:** Automatically organizes files into structured directories based on date patterns, keywords, or file type.
*   **Bulk Renaming:** Renames batches of files using customizable patterns with placeholders.
*   **Safe by Default:** Includes a `--dry-run` mode to preview actions before making changes.
*   **Conflict Resolution:** Automatically handles filename conflicts by appending a counter.
*   **Two-Phase Execution:** A robust planning phase followed by an execution phase for safety and efficiency.

## Building from Source

This project uses CMake and requires a C++17 compliant compiler.

```bash
# Clone the repository
git clone https://github.com/MrHummerberg/FileOrganizer.git
cd FileOrganizer

# Create a build directory
mkdir build && cd build

# Configure and build the project
cmake ..
cmake --build .
