#include "Plan.h"
#include <iostream>
#include <iomanip>

void Plan::addAction(const Action& action) {
    actions.push_back(action);
}

const std::vector<Action>& Plan::getActions() const {
    return actions;
}

void Plan::printPlan() const {
    std::cout << "=== Plan of Actions ===\n";
    if (actions.empty()) {
        std::cout << "No actions to perform.\n";
        return;
    }

    for (const auto& action : actions) {
        switch (action.type) {
            case Action::MOVE:
                std::cout << "MOVE:   \"" << action.source.filename().string() 
                          << "\" -> \"" << action.destination.parent_path().string() << "/\"\n";
                break;
            case Action::RENAME:
                std::cout << "RENAME: \"" << action.source.filename().string() 
                          << "\" -> \"" << action.destination.filename().string() << "\"\n";
                break;
            case Action::CREATE_DIR:
                std::cout << "CREATE: \"" << action.destination.string() << "\"\n";
                break;
        }
    }
    std::cout << "========================\n";
}

std::map<std::string, int> Plan::getSummary() const {
    std::map<std::string, int> summary;
    summary["moves"] = 0;
    summary["renames"] = 0;
    summary["created_dirs"] = 0;
    
    for (const auto& action : actions) {
        switch (action.type) {
            case Action::MOVE:
                summary["moves"]++;
                break;
            case Action::RENAME:
                summary["renames"]++;
                break;
            case Action::CREATE_DIR:
                summary["created_dirs"]++;
                break;
        }
    }
    
    return summary;
}
