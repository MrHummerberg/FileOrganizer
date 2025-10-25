#pragma once

#include "FileScanner.h"
#include "Plan.h"
#include "utils/CommandLineParser.h"  // <-- THIS LINE MUST BE CORRECT
#include <filesystem>
#include <set>

/**
 * @class FileOrganizer
 * @brief The main orchestrator for the file organization and renaming process.
 *
 * This class implements the two-phase approach (Planning and Execution). It uses
 * the FileScanner, PatternMatcher, Plan, and FileOperator classes to carry out
 * its tasks. It is configured via a CommandLineArgs struct.
 */
class FileOrganizer {
public:
    /**
     * @brief Construct a new FileOrganizer object.
     *
     * @param args The parsed command-line arguments that configure the organizer's behavior.
     */
    explicit FileOrganizer(const CommandLineArgs& args);

    /**
     * @brief Organizes files in the current working directory based on hardcoded rules.
     *
     * This method executes the full workflow: scanning, planning, and (if not in dry-run mode)
     * executing the plan to move files into organized directory structures.
     */
    void organizeFiles();

    /**
     * @brief Renames files in the current working directory based on a given pattern.
     *
     * This method executes the full workflow for renaming: scanning, planning, and (if not
     * in dry-run mode) executing the plan to rename files according to the pattern.
     *
     * @param pattern The renaming pattern string with placeholders.
     */
    void renameFiles(const std::string& pattern);

private:
    CommandLineArgs args;              ///< Stores the configuration from command-line.
    std::filesystem::path workingDirectory; ///< The target directory (current path).

    /**
     * @brief Resolves a file name conflict by appending a counter.
     *
     * If a file at `filePath` already exists, this function generates a new path
     * like "filename (1).ext", "filename (2).ext", etc., until a unique path is found.
     *
     * @param filePath The desired destination path.
     * @return A unique, conflict-free file path.
     */
    std::filesystem::path resolveConflict(const std::filesystem::path& filePath);

    /**
     * @brief Generates a new filename based on a pattern and file info.
     *
     * Replaces placeholders like {name}, {ext}, {counter}, and {date} in the pattern.
     *
     * @param file The information about the original file.
     * @param pattern The user-provided pattern string.
     * @param counter The current counter value for this file.
     * @return The newly generated filename.
     */
    std::string generateNewName(const FileInfo& file, const std::string& pattern, int counter);
};
