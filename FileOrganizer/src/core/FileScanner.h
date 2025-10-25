#pragma once

#include <filesystem>
#include <vector>
#include <string>

/**
 * @struct FileInfo
 * @brief Holds relevant information about a single file.
 *
 * This structure is used to pass file data between the scanner, the organizer,
 * and other components. It stores the original path and extracted metadata.
 */
struct FileInfo {
    std::filesystem::path path;         ///< The full path to the file.
    std::string name;                   ///< The base name of the file (filename without extension).
    std::string ext;                    ///< The file extension, including the dot (e.g., ".txt").
    std::string detectedDate;           ///< The date string detected in the filename, if any.
    std::string targetDir;              ///< The target directory for organization, determined later.
};

/**
 * @class FileScanner
 * @brief Scans a directory and collects information about its files.
 *
 * This class is responsible for the initial phase of gathering data. It iterates
 * through all regular files in a specified directory and populates a vector
 * of FileInfo structures. It uses `std::filesystem` for efficient traversal.
 */
class FileScanner {
public:
    /**
     * @brief Scans the given directory and returns a vector of FileInfo objects.
     *
     * It iterates through the directory, ignoring subdirectories and special files.
     * For each regular file, it extracts the name and extension.
     *
     * @param directory The path to the directory to scan.
     * @return A vector of FileInfo objects, one for each file found.
     */
    static std::vector<FileInfo> scanDirectory(const std::filesystem::path& directory);
};
