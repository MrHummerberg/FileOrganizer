#include "ProgressReporter.h"
#include <iostream>
#include <iomanip>

void ProgressReporter::report(int current, int total, const std::string& message) {
    if (total <= 0) return;

    // Calculate percentage
    int percentage = (current * 100) / total;

    // Print progress on a single line
    std::cout << "\r" << message << ": " << current << "/" << total 
              << " (" << percentage << "%)          " << std::flush;
}
