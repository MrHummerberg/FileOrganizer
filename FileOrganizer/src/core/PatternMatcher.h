#pragma once

#include <string>
#include <vector>

/**
 * @class PatternMatcher
 * @brief Provides static methods to detect various patterns within filenames.
 *
 * This class is responsible for the "intelligence" of the FileOrganizer. It
 * contains hardcoded rules for detecting dates, keywords, and categorizing
 * files by their extensions. All methods are static as this class is stateless.
 */
class PatternMatcher {
public:
    /**
     * @brief Detects a date pattern within a filename.
     *
     * Searches for common date formats like YYYY-MM-DD, DD-MM-YYYY, or YYYYMMDD.
     * The search stops after the first match is found.
     *
     * @param filename The name of the file (without path or extension).
     * @return A string representing the date in "YYYY/MM" format, or an empty string if no date is found.
     */
    static std::string detectDatePattern(const std::string& filename);

    /**
     * @brief Detects specific keywords in a filename to categorize it.
     *
     * The search is case-insensitive.
     *
     * @param filename The name of the file (without path or extension).
     * @return The target directory name based on the keyword (e.g., "Wallpapers"), or an empty string if no keyword is found.
     */
    static std::string detectKeyword(const std::string& filename);

    /**
     * @brief Determines the file type category based on its extension.
     *
     * The check is case-insensitive.
     *
     * @param extension The file extension, including the dot (e.g., ".jpg").
     * @return The target directory name for the file type (e.g., "Images", "Documents").
     */
    static std::string getFileType(const std::string& extension);

private:
    /**
     * @brief Helper function to format detected date components into "YYYY/MM".
     *
     * @param year The detected year string.
     * @param month The detected month string.
     * @param day The detected day string.
     * @return A formatted date string "YYYY/MM".
     */
    static std::string formatDate(const std::string& year, const std::string& month, const std::string& day);
};
