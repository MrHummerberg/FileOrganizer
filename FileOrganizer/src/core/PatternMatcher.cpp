#include "PatternMatcher.h"
#include <regex>
#include <algorithm>
#include <sstream>
#include <iomanip>

std::string PatternMatcher::detectDatePattern(const std::string& filename) {
    // YYYY-MM-DD or YYYY_MM_DD pattern
    std::regex datePattern1(R"((\d{4})[-_](\d{1,2})[-_](\d{1,2}))");
    // DD-MM-YYYY or DD_MM_YYYY pattern
    std::regex datePattern2(R"((\d{1,2})[-_](\d{1,2})[-_](\d{4}))");
    // YYYYMMDD pattern
    std::regex datePattern3(R"((\d{4})(\d{2})(\d{2}))");
    
    std::smatch match;

    // Check for YYYY-MM-DD or YYYY_MM_DD first
    if (std::regex_search(filename, match, datePattern1)) {
        return formatDate(match[1].str(), match[2].str(), match[3].str());
    }
    
    // Check for DD-MM-YYYY or DD_MM_YYYY
    if (std::regex_search(filename, match, datePattern2)) {
        return formatDate(match[3].str(), match[2].str(), match[1].str());
    }
    
    // Check for YYYYMMDD
    if (std::regex_search(filename, match, datePattern3)) {
        return formatDate(match[1].str(), match[2].str(), match[3].str());
    }
    
    return "";
}

std::string PatternMatcher::detectKeyword(const std::string& filename) {
    std::string lowerFilename = filename;
    std::transform(lowerFilename.begin(), lowerFilename.end(), lowerFilename.begin(), ::tolower);
    
    if (lowerFilename.find("wallpaper") != std::string::npos || 
        lowerFilename.find("wallpapers") != std::string::npos) {
        return "Wallpapers";
    }
    
    if (lowerFilename.find("screenshot") != std::string::npos || 
        lowerFilename.find("snap") != std::string::npos) {
        return "Screenshots";
    }
    
    return "";
}

std::string PatternMatcher::getFileType(const std::string& extension) {
    std::string lowerExt = extension;
    std::transform(lowerExt.begin(), lowerExt.end(), lowerExt.begin(), ::tolower);
    
    // Document types
    if (lowerExt == ".pdf" || lowerExt == ".docx" || lowerExt == ".doc" || 
        lowerExt == ".txt" || lowerExt == ".rtf" || lowerExt == ".odt") {
        return "Documents";
    }
    
    // Image types
    if (lowerExt == ".jpg" || lowerExt == ".jpeg" || lowerExt == ".png" || 
        lowerExt == ".gif" || lowerExt == ".bmp" || lowerExt == ".tiff" || 
        lowerExt == ".webp") {
        return "Images";
    }
    
    // Video types
    if (lowerExt == ".mp4" || lowerExt == ".avi" || lowerExt == ".mkv" || 
        lowerExt == ".mov" || lowerExt == ".wmv" || lowerExt == ".flv" || 
        lowerExt == ".webm") {
        return "Videos";
    }
    
    // Audio types
    if (lowerExt == ".mp3" || lowerExt == ".wav" || lowerExt == ".flac" || 
        lowerExt == ".aac" || lowerExt == ".ogg" || lowerExt == ".wma") {
        return "Audio";
    }
    
    // Archive types
    if (lowerExt == ".zip" || lowerExt == ".rar" || lowerExt == ".7z" || 
        lowerExt == ".tar" || lowerExt == ".gz") {
        return "Archives";
    }
    
    // Code types
    if (lowerExt == ".cpp" || lowerExt == ".h" || lowerExt == ".hpp" || lowerExt == ".java" || 
        lowerExt == ".py" || lowerExt == ".js" || lowerExt == ".html" || 
        lowerExt == ".css") {
        return "Code";
    }
    
    return "Others";
}

std::string PatternMatcher::formatDate(const std::string& year, const std::string& month, const std::string& day) {
    // We only need YYYY/MM for the directory structure
    std::ostringstream oss;
    oss << year << "/" << std::setw(2) << std::setfill('0') << month;
    return oss.str();
}
