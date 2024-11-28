#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

// Define the Control struct
struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"

    // Helper to print control details
    void print() const {
        std::cout << "ID: " << id << ", Type: " << type << ", State: " << state << "\n";
    }
};

// Helper to generate random state
std::string generateRandomState() {
    static std::vector<std::string> states = {"visible", "invisible", "disabled"};
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, states.size() - 1);
    return states[dist(rng)];
}

int main() {
    // Initialize controls
    std::vector<Control> controls = {
        {1, "button", "visible"}, {2, "slider", "visible"},
        {3, "button", "disabled"}, {4, "slider", "visible"},
        {5, "button", "visible"}, {6, "slider", "disabled"},
        {7, "button", "invisible"}, {8, "slider", "visible"}
    };

    // Display original controls
    std::cout << "Original Controls:\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Create a backup of the control list
    std::vector<Control> backup;
    std::copy(controls.begin(), controls.end(), std::back_inserter(backup));

    // Temporarily disable all controls
    std::fill(controls.begin(), controls.end(), Control{0, "none", "disabled"});
    std::cout << "\nAfter std::fill (all disabled):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Generate random states for testing
    std::generate(controls.begin(), controls.end(), []() -> Control {
        static int id = 1;
        return Control{id++, "slider", generateRandomState()};
    });
    std::cout << "\nAfter std::generate (random states):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Change the state of all sliders to "invisible"
    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& ctrl) {
        if (ctrl.type == "slider") {
            ctrl.state = "invisible";
        }
        return ctrl;
    });
    std::cout << "\nAfter std::transform (sliders invisible):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Replace "disabled" with "enabled"
    std::replace_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "disabled"; },
        Control{0, "none", "enabled"});
    std::cout << "\nAfter std::replace (disabled to enabled):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Remove invisible controls
    auto endIt = std::remove_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "invisible"; });
    controls.erase(endIt, controls.end());
    std::cout << "\nAfter std::remove_if (invisible removed):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Reverse the order of controls
    std::reverse(controls.begin(), controls.end());
    std::cout << "\nAfter std::reverse (order reversed):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Partition controls to group visible ones together
    std::partition(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "\nAfter std::partition (visible grouped):\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    // Restore the backup
    controls = backup;
    std::cout << "\nAfter restoring backup:\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) { ctrl.print(); });

    return 0;
}
