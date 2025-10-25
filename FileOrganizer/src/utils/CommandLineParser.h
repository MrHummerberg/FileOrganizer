#pragma once

#include <string>
#include <vector>

/**
 * @struct CommandLineArgs
 * @brief Holds the parsed command-line arguments.
 *
 * This structure provides a clean, typed way to access the user's
 * command-line options throughout the application.
 */
struct CommandLineArgs {
    bool dryRun = false;          ///< True if --dry-run is specified.
    bool organize = false;        ///< True if --organize is specified.
    bool rename = false;          ///< True if --rename is specified.
    std::string renamePattern;    ///< The pattern string for renaming, if applicable.
};

/**
 * @class CommandLineParser
 * @brief Parses command-line arguments into a CommandLineArgs struct.
 *
 * This class encapsulates all logic related to interpreting the command-line
 * options provided by the user. It handles flags and options and provides
 * help text.
 */
class CommandLineParser {
public:
    /**
     * @brief Parses the command-line arguments.
     *
     * @param argc The argument count from main().
     * @param argv The argument vector from main().
     * @return A CommandLineArgs struct containing the parsed options.
     */
    static CommandLineArgs parse(int argc, char* argv[]);

    /**
     * @brief Prints the usage/help information to the standard output.
     *
     * @param programName The name of the executable (e.g., argv[0]).
     */
    static void printUsage(const char* programName);

private:
    /**
     * @brief Checks if a given argument is a help flag.
     */
    static bool isHelpArgument(const std::string& arg);
};
