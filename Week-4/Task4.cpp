#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

// Define the Control struct
struct Control {
    int id;
    std::string type;  // "button" or "slider"
    std::string state; // "visible", "invisible", "disabled"

    // Comparison operator for sorting
    bool operator<(const Control& other) const {
        return id < other.id;
    }

    // Equality operator for set operations
    bool operator==(const Control& other) const {
        return id == other.id;
    }

    // Print control details
    void print() const {
        std::cout << "ID: " << id << ", Type: " << type << ", State: " << state << "\n";
    }
};

int main() {
    // Initialize two lists of controls
    std::vector<Control> controls1 = {
        {5, "button", "visible"}, {2, "slider", "invisible"},
        {7, "button", "disabled"}, {3, "slider", "visible"}};
    
    std::vector<Control> controls2 = {
        {4, "button", "visible"}, {1, "slider", "disabled"},
        {6, "button", "visible"}, {8, "slider", "invisible"}};

    // 1. Sort controls by ID
    std::sort(controls1.begin(), controls1.end());
    std::sort(controls2.begin(), controls2.end());

    std::cout << "Sorted Controls List 1:\n";
    std::for_each(controls1.begin(), controls1.end(), [](const Control& ctrl) { ctrl.print(); });

    std::cout << "\nSorted Controls List 2:\n";
    std::for_each(controls2.begin(), controls2.end(), [](const Control& ctrl) { ctrl.print(); });

    // 2. Binary Search: Find control by ID using lower_bound and upper_bound
    int searchID = 3;
    auto it = std::lower_bound(controls1.begin(), controls1.end(), Control{searchID, "", ""});

    if (it != controls1.end() && it->id == searchID) {
        std::cout << "\nControl with ID " << searchID << " found in List 1:\n";
        it->print();
    } else {
        std::cout << "\nControl with ID " << searchID << " not found in List 1.\n";
    }

    // 3. Merge two sorted lists
    std::vector<Control> mergedControls;
    std::merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
               std::back_inserter(mergedControls));

    std::cout << "\nMerged Controls List:\n";
    std::for_each(mergedControls.begin(), mergedControls.end(), [](const Control& ctrl) { ctrl.print(); });

    // 4. In-place merge (simulating two segments in a single list)
    std::vector<Control> inPlaceList = controls1;
    inPlaceList.insert(inPlaceList.end(), controls2.begin(), controls2.end());
    std::inplace_merge(inPlaceList.begin(), inPlaceList.begin() + controls1.size(), inPlaceList.end());

    std::cout << "\nIn-place Merged Controls List:\n";
    std::for_each(inPlaceList.begin(), inPlaceList.end(), [](const Control& ctrl) { ctrl.print(); });

    // 5. Set Operations: Union and Intersection
    std::vector<Control> unionControls, intersectionControls;

    std::set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
                   std::back_inserter(unionControls));
    std::set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
                          std::back_inserter(intersectionControls));

    std::cout << "\nUnion of Controls:\n";
    std::for_each(unionControls.begin(), unionControls.end(), [](const Control& ctrl) { ctrl.print(); });

    std::cout << "\nIntersection of Controls:\n";
    std::for_each(intersectionControls.begin(), intersectionControls.end(), [](const Control& ctrl) { ctrl.print(); });

    return 0;
}
