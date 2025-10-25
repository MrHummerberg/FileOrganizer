#include "CommandLineParser.h"
#include <iostream>
#include <algorithm>

CommandLineArgs CommandLineParser::parse(int argc, char* argv[]) {
    CommandLineArgs args;
    std::vector<std::string> arguments(argv + 1, argv + argc);

    // Check for help flag first
    if (std::any_of(arguments.begin(), arguments.end(), isHelpArgument)) {
        printUsage(argv[0]);
        exit(0); // Exit after printing help
    }

    for (size_t i = 0; i < arguments.size(); ++i) {
        const std::string& arg = arguments[i];

        if (arg == "--dry-run" || arg == "-n") {
            args.dryRun = true;
        } else if (arg == "--organize" || arg == "-o") {
            args.organize = true;
        } else if (arg == "--rename" || arg == "-r") {
            args.rename = true;
            // The next argument should be the pattern
            if (i + 1 < arguments.size()) {
                args.renamePattern = arguments[++i];
            }
        }
    }

    // Default action is organize if no action is specified
    if (!args.organize && !args.rename) {
        args.organize = true;
    }
    
    return args;
}

void CommandLineParser::printUsage(const char* programName) {
    std::cout << "FileOrganizer - High-Performance File Organization Utility\n\n";
    std::cout << "Usage: " << programName << " [options]\n\n";
    std::cout << "Options:\n";
    std::cout << "  --organize, -o        Organize files based on patterns (default action)\n";
    std::cout << "  --rename, -r PATTERN  Rename files based on pattern\n";
    std::cout << "  --dry-run, -n         Show what would be done without making changes\n";
    std::cout << "  --help, -h            Show this help message\n\n";
    std::cout << "Pattern placeholders for --rename:\n";
    std::cout << "  {name}      Original filename without extension\n";
    std::cout << "  {ext}       Original file extension\n";
    std::cout << "  {counter}   Incrementing number (optional padding: {counter:3})\n";
    std::cout << "  {date}      Detected date from filename\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " --organize\n";
    std::cout << "  " << programName << " --rename \"vacation-{counter:03}.{ext}\"\n";
    std::cout << "  " << programName << " --organize --dry-run\n";
}

bool CommandLineParser::isHelpArgument(const std::string& arg) {
    return arg == "--help" || arg == "-h";
}
