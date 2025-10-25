#pragma once

#include "Plan.h"
#include <string>

/**
 * @class FileOperator
 * @brief Executes the actions defined in a Plan.
 *
 * This class is responsible for the "Execution Phase". It takes a finalized Plan
 * and performs the file system operations (move, rename, create directory).
 * It handles errors gracefully and provides progress feedback to the user.
 * All methods are static as this class is stateless.
 */
class FileOperator {
public:
    /**
     * @brief Executes all actions within a given Plan.
     *
     * This method iterates through the actions in the plan and performs them
     * sequentially. It will create parent directories as needed before moving
     * files. It reports progress and handles any filesystem errors that occur.
     *
     * @param plan The Plan object containing all actions to be executed.
     * @return True if all actions were executed successfully, false otherwise.
     */
    static bool executePlan(const Plan& plan);

private:
    /**
     * @brief Reports the progress of the execution to the console.
     *
     * @param current The number of actions completed so far.
     * @param total The total number of actions in the plan.
     */
    static void reportProgress(int current, int total);
};
