#include "FileOperator.h"
#include <filesystem>
#include <iostream>
#include <iomanip>

namespace fs = std::filesystem;

bool FileOperator::executePlan(const Plan& plan) {
    const auto& actions = plan.getActions();
    if (actions.empty()) {
        std::cout << "Nothing to do.\n";
        return true;
    }

    int successCount = 0;
    const int totalCount = static_cast<int>(actions.size());

    std::cout << "Executing plan...\n";

    for (const auto& action : actions) {
        try {
            switch (action.type) {
                case Action::MOVE:
                    // Ensure the parent directory exists before moving the file
                    fs::create_directories(action.destination.parent_path());
                    fs::rename(action.source, action.destination);
                    std::cout << "Moved:   \"" << action.source.filename().string()
                              << "\" -> \"" << action.destination.parent_path().string() << "/\"\n";
                    break;
                case Action::RENAME:
                    fs::rename(action.source, action.destination);
                    std::cout << "Renamed: \"" << action.source.filename().string()
                              << "\" -> \"" << action.destination.filename().string() << "\"\n";
                    break;
                case Action::CREATE_DIR:
                    fs::create_directories(action.destination);
                    // We don't print every directory creation to avoid clutter,
                    // as they are created implicitly during moves. This is for explicit creates.
                    // std::cout << "Created: \"" << action.destination.string() << "\"\n";
                    break;
            }
            successCount++;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

        // Update progress after each action attempt
        reportProgress(successCount, totalCount);
    }

    std::cout << "\n"; // Newline after the progress bar

    if (successCount == totalCount) {
        std::cout << "All actions completed successfully.\n";
    } else {
        std::cerr << "Some actions failed. (" << (totalCount - successCount) << " errors)\n";
    }

    return successCount == totalCount;
}

void FileOperator::reportProgress(int current, int total) {
    // Calculate percentage
    int percentage = (total > 0) ? (current * 100 / total) : 100;

    // Print progress on a single line
    std::cout << "\rProgress: " << current << "/" << total 
              << " (" << percentage << "%)          " << std::flush;
}
