#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// Define the Control struct
struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"

    // Helper for printing
    void print() const {
        std::cout << "ID: " << id << ", Type: " << type << ", State: " << state << "\n";
    }
};

int main() {
    // Initialize the container with sample controls
    std::vector<Control> controls = {
        {1, "button", "visible"}, {2, "button", "invisible"},
        {3, "button", "disabled"}, {4, "button", "visible"},
        {5, "button", "visible"},  {6, "slider", "visible"},
        {7, "slider", "disabled"}, {8, "slider", "visible"},
        {9, "slider", "invisible"},{10, "slider", "disabled"}
    };

    std::cout << "=== All Controls ===\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        ctrl.print();
    });

    // Find a control with a specific ID
    int targetId = 3;
    auto controlWithId = std::find_if(controls.begin(), controls.end(),
        [targetId](const Control& ctrl) { return ctrl.id == targetId; });

    if (controlWithId != controls.end()) {
        std::cout << "\nControl with ID " << targetId << ":\n";
        controlWithId->print();
    } else {
        std::cout << "\nControl with ID " << targetId << " not found.\n";
    }

    // Find the first invisible control
    auto invisibleControl = std::find_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "invisible"; });

    if (invisibleControl != controls.end()) {
        std::cout << "\nFirst invisible control:\n";
        invisibleControl->print();
    } else {
        std::cout << "\nNo invisible controls found.\n";
    }

    // Check for consecutive controls with the same state
    auto consecutiveSameState = std::adjacent_find(controls.begin(), controls.end(),
        [](const Control& a, const Control& b) { return a.state == b.state; });

    if (consecutiveSameState != controls.end() && consecutiveSameState + 1 != controls.end()) {
        std::cout << "\nConsecutive controls with the same state:\n";
        consecutiveSameState->print();
        (consecutiveSameState + 1)->print();
    } else {
        std::cout << "\nNo consecutive controls with the same state found.\n";
    }

    // Count the number of visible controls
    int visibleCount = std::count_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "visible"; });

    std::cout << "\nNumber of visible controls: " << visibleCount << "\n";

    // Count sliders that are disabled
    int disabledSliders = std::count_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.type == "slider" && ctrl.state == "disabled"; });

    std::cout << "Number of disabled sliders: " << disabledSliders << "\n";

    // Compare two subranges of controls to check if they are identical
    if (controls.size() >= 4) {
        bool areEqual = std::equal(controls.begin(), controls.begin() + 2, controls.begin() + 2, controls.begin() + 4);
        std::cout << "\nSubranges (first 2 and next 2 controls) are "
                  << (areEqual ? "identical.\n" : "not identical.\n");
    } else {
        std::cout << "\nNot enough controls to compare subranges.\n";
    }

    return 0;
}
