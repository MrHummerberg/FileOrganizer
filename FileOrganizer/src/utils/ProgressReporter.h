#pragma once

#include <string>

/**
 * @class ProgressReporter
 * @brief A simple utility for reporting progress to the console.
 *
 * This class provides a clean interface for displaying progress, abstracting
 * the console output logic from the core application components.
 */
class ProgressReporter {
public:
    /**
     * @brief Reports the progress of a task.
     *
     * Prints a progress bar to the console, updating on the same line.
     *
     * @param current The number of items completed.
     * @param total The total number of items to be completed.
     * @param message An optional message to display alongside the progress bar.
     */
    static void report(int current, int total, const std::string& message = "Progress");
};
