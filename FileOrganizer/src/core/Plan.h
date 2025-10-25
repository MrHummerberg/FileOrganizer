#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <map>

/**
 * @struct Action
 * @brief Represents a single file system operation to be performed.
 *
 * An action can be moving a file, renaming a file, or creating a directory.
 * It stores the type of operation and the necessary source and destination paths.
 */
struct Action {
    enum Type { 
        MOVE,       ///< Move a file from source to destination.
        RENAME,     ///< Rename a file from source to destination.
        CREATE_DIR  ///< Create a directory at the destination path.
    };
    
    Type type;
    std::filesystem::path source;
    std::filesystem::path destination;
    
    /**
     * @brief Construct a new Action object.
     * 
     * @param t The type of action.
     * @param src The source path (empty for CREATE_DIR).
     * @param dest The destination path.
     */
    Action(Type t, const std::filesystem::path& src, const std::filesystem::path& dest) 
        : type(t), source(src), destination(dest) {}
};

/**
 * @class Plan
 * @brief Manages a list of Actions to be executed.
 *
 * This class is the core of the "Planning Phase". It stores all the actions
 * that need to be performed, allows for adding new actions, and provides
 * utilities for displaying the plan and summarizing its contents.
 */
class Plan {
public:
    /**
     * @brief Adds an action to the plan.
     * 
     * @param action The Action object to add.
     */
    void addAction(const Action& action);
    
    /**
     * @brief Gets the list of all actions in the plan.
     * 
     * @return A const reference to the vector of actions.
     */
    const std::vector<Action>& getActions() const;
    
    /**
     * @brief Prints the entire plan to the standard output.
     * 
     * Useful for the --dry-run mode to show the user what will happen.
     */
    void printPlan() const;
    
    /**
     * @brief Generates a summary of the actions in the plan.
     * 
     * @return A map where keys are action type names ("moves", "renames", etc.)
     *         and values are the counts of those actions.
     */
    std::map<std::string, int> getSummary() const;

private:
    std::vector<Action> actions; ///< The list of actions to be executed.
};
