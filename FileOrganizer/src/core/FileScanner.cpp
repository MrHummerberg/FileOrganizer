#include <iostream>          // <-- THIS LINE WAS ADDED
#include "FileScanner.h"
#include "PatternMatcher.h"
#include <filesystem>

namespace fs = std::filesystem;

std::vector<FileInfo> FileScanner::scanDirectory(const fs::path& directory) {
    std::vector<FileInfo> files;
    
    // Check if the directory exists and is indeed a directory
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        // In a real-world scenario, you might throw an exception or return an error
        // For this utility, we'll just return an empty vector.
        std::cerr << "Error: Directory does not exist or is not a directory: " << directory << std::endl;
        return files;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        // We only care about regular files, not subdirectories or symlinks
        if (entry.is_regular_file()) {
            FileInfo info;
            info.path = entry.path();
            info.name = entry.path().stem().string();
            info.ext = entry.path().extension().string();
            
            // Pre-detect the date pattern during the scan for efficiency
            info.detectedDate = PatternMatcher::detectDatePattern(info.name);
            
            files.push_back(std::move(info));
        }
    }
    
    return files;
}
