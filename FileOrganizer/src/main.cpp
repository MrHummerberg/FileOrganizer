#include <iostream>
#include "core/FileOrganizer.h"
#include "utils/CommandLineParser.h" 

/**
 * @brief The main entry point for the FileOrganizer application.
 *
 * This function is responsible for:
 * 1. Parsing command-line arguments.
 * 2. Validating the provided arguments.
 * 3. Instantiating the FileOrganizer with the parsed arguments.
 * 4. Delegating the main task (organize or rename) to the FileOrganizer.
 * 5. Handling top-level errors and returning an appropriate exit code.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return int Exit code. 0 for success, 1 for error.
 */
int main(int argc, char* argv[]) {
    // Parse command-line arguments
    CommandLineArgs args = CommandLineParser::parse(argc, argv);

    // Validate arguments for the rename action
    if (args.rename && args.renamePattern.empty()) {
        std::cerr << "Error: --rename requires a pattern.\n";
        CommandLineParser::printUsage(argv[0]);
        return 1;
    }

    // Create the main organizer object
    FileOrganizer organizer(args);

    // Execute the requested action
    try {
        if (args.organize) {
            organizer.organizeFiles();
        } else if (args.rename) {
            organizer.renameFiles(args.renamePattern);
        }
    } catch (const std::exception& e) {
        // Catch any unexpected exceptions from the core logic
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
