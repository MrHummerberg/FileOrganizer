#include "FileOrganizer.h"
#include "PatternMatcher.h"
#include "FileOperator.h"
#include "utils/ProgressReporter.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace fs = std::filesystem;

FileOrganizer::FileOrganizer(const CommandLineArgs& args) 
    : args(args), workingDirectory(fs::current_path()) {
}

void FileOrganizer::organizeFiles() {
    std::cout << "Phase 1: Planning...\n";

    auto files = FileScanner::scanDirectory(workingDirectory);
    if (files.empty()) {
        std::cout << "No files found to organize in the current directory.\n";
        return;
    }
    std::cout << "Found " << files.size() << " files to process.\n";

    Plan plan;
    std::set<fs::path> plannedDirs;

    for (auto& file : files) {
        std::string targetDirName;
        if (!file.detectedDate.empty()) {
            targetDirName = file.detectedDate;
        } else {
            std::string keyword = PatternMatcher::detectKeyword(file.name);
            if (!keyword.empty()) {
                targetDirName = keyword;
            } else {
                targetDirName = PatternMatcher::getFileType(file.ext);
            }
        }
        file.targetDir = targetDirName;

        fs::path targetDirPath = workingDirectory / targetDirName;
        if (plannedDirs.find(targetDirPath) == plannedDirs.end()) {
            plan.addAction(Action(Action::CREATE_DIR, "", targetDirPath));
            plannedDirs.insert(targetDirPath);
        }

        fs::path targetFilePath = targetDirPath / file.path.filename();

        targetFilePath = resolveConflict(targetFilePath);

        plan.addAction(Action(Action::MOVE, file.path, targetFilePath));
    }

    auto summary = plan.getSummary();
    std::cout << "Plan created with " << summary["moves"] << " moves and " 
              << summary["created_dirs"] << " directories to create.\n";

    if (args.dryRun) {
        std::cout << "\n--- DRY RUN: No actual changes will be made. ---\n";
        plan.printPlan();
        return;
    }

    std::cout << "\nPhase 2: Execution...\n";
    FileOperator::executePlan(plan);
}

void FileOrganizer::renameFiles(const std::string& pattern) {
    std::cout << "Phase 1: Planning...\n";

    auto files = FileScanner::scanDirectory(workingDirectory);
    if (files.empty()) {
        std::cout << "No files found to rename in the current directory.\n";
        return;
    }
    std::cout << "Found " << files.size() << " files to process.\n";

    Plan plan;
    int counter = 1;

    for (auto& file : files) {
        std::string newName = generateNewName(file, pattern, counter);

        fs::path newFilePath = file.path.parent_path() / newName;

        newFilePath = resolveConflict(newFilePath);

        plan.addAction(Action(Action::RENAME, file.path, newFilePath));
        
        counter++;
    }

    auto summary = plan.getSummary();
    std::cout << "Plan created with " << summary["renames"] << " renames.\n";

    if (args.dryRun) {
        std::cout << "\n--- DRY RUN: No actual changes will be made. ---\n";
        plan.printPlan();
        return;
    }

    std::cout << "\nPhase 2: Execution...\n";
    FileOperator::executePlan(plan);
}

fs::path FileOrganizer::resolveConflict(const fs::path& filePath) {
    if (!fs::exists(filePath)) {
        return filePath;
    }

    fs::path stem = filePath.stem();
    fs::path ext = filePath.extension();
    fs::path parent = filePath.parent_path();

    int counter = 1;
    fs::path newPath;
    do {
        std::ostringstream oss;
        oss << stem.string() << " (" << counter << ")" << ext.string();
        newPath = parent / oss.str();
        counter++;
    } while (fs::exists(newPath));

    return newPath;
}

std::string FileOrganizer::generateNewName(const FileInfo& file, const std::string& pattern, int counter) {
    std::string result = pattern;

    size_t pos = result.find("{name}");
    while (pos != std::string::npos) {
        result.replace(pos, 6, file.name);
        pos = result.find("{name}", pos + file.name.length());
    }

    pos = result.find("{ext}");
    while (pos != std::string::npos) {
        result.replace(pos, 5, file.ext);
        pos = result.find("{ext}", pos + file.ext.length());
    }

    pos = result.find("{counter");
    while (pos != std::string::npos) {
        size_t endPos = result.find("}", pos);
        if (endPos != std::string::npos) {
            std::string counterStr = result.substr(pos, endPos - pos + 1);
            
            int padding = 0;
            size_t colonPos = counterStr.find(":");
            if (colonPos != std::string::npos) {
                try {
                    padding = std::stoi(counterStr.substr(colonPos + 1));
                } catch (const std::invalid_argument& ia) {
                    padding = 0;
                }
            }

            std::ostringstream oss;
            if (padding > 0) {
                oss << std::setw(padding) << std::setfill('0') << counter;
            } else {
                oss << counter;
            }
            
            result.replace(pos, counterStr.length(), oss.str());
            pos = result.find("{counter", pos + oss.str().length());
        } else {
            break;
        }
    }

    pos = result.find("{date}");
    while (pos != std::string::npos) {
        result.replace(pos, 6, file.detectedDate);
        pos = result.find("{date}", pos + file.detectedDate.length());
    }

    return result;
}
