#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

int main() {
    // Initialize containers
    std::vector<std::string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "Odometer"};
    std::set<std::string> staticWidgets = {"Logo", "WarningLights"};

    // Print all dynamic widgets using an iterator
    std::cout << "Dynamic Widgets:\n";
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        std::cout << "- " << *it << "\n";
    }

    // Check if "WarningLights" is in the staticWidgets set
    std::string targetStaticWidget = "WarningLights";
    auto staticWidgetIt = staticWidgets.find(targetStaticWidget);

    if (staticWidgetIt != staticWidgets.end()) {
        std::cout << "\nStatic Widget \"" << targetStaticWidget << "\" found in the static set.\n";
    } else {
        std::cout << "\nStatic Widget \"" << targetStaticWidget << "\" not found in the static set.\n";
    }

    // Combine both containers into a single std::vector<std::string>
    std::vector<std::string> allWidgets;
    std::copy(dynamicWidgets.begin(), dynamicWidgets.end(), std::back_inserter(allWidgets));
    std::copy(staticWidgets.begin(), staticWidgets.end(), std::back_inserter(allWidgets));

    // Print the combined widget list
    std::cout << "\nCombined Widget List:\n";
    for (const auto& widget : allWidgets) {
        std::cout << "- " << widget << "\n";
    }

    // Use std::find to locate a specific widget in the combined container
    std::string targetWidget = "Odometer";
    auto combinedWidgetIt = std::find(allWidgets.begin(), allWidgets.end(), targetWidget);

    if (combinedWidgetIt != allWidgets.end()) {
        std::cout << "\nWidget \"" << targetWidget << "\" found in the combined list.\n";
    } else {
        std::cout << "\nWidget \"" << targetWidget << "\" not found in the combined list.\n";
    }

    return 0;
}
