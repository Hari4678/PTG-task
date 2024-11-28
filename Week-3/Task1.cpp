#include <iostream>
#include <vector>
#include <string>
#include <memory>

class MenuItem {
public:
    std::string name;
    std::vector<std::shared_ptr<MenuItem>> children;

    MenuItem(const std::string& name) : name(name) {}

    void addChild(const std::shared_ptr<MenuItem>& child) {
        children.push_back(child);
    }
};

class MenuNavigator {
    std::shared_ptr<MenuItem> root;
    std::shared_ptr<MenuItem> current;
    std::vector<std::shared_ptr<MenuItem>> path;

public:
    MenuNavigator(const std::shared_ptr<MenuItem>& root) : root(root), current(root) {}

    void displayMenu() {
        std::cout << "\nCurrent Menu: " << current->name << "\n";
        std::cout << "Options:\n";
        for (size_t i = 0; i < current->children.size(); ++i) {
            std::cout << i + 1 << ". " << current->children[i]->name << "\n";
        }
        std::cout << "Actions:\n";
        std::cout << "0. Back\n";
    }

    void navigate(int option) {
        if (option == 0) { // Back
            if (!path.empty()) {
                current = path.back();
                path.pop_back();
            } else {
                std::cout << "Already at the main menu.\n";
            }
        } else if (option > 0 && option <= static_cast<int>(current->children.size())) {
            path.push_back(current);
            current = current->children[option - 1];
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    bool isAtRoot() const {
        return current == root;
    }
};

int main() {
    // Build menu structure
    auto mainMenu = std::make_shared<MenuItem>("Main Menu");

    auto settings = std::make_shared<MenuItem>("Settings");
    auto displaySettings = std::make_shared<MenuItem>("Display Settings");
    auto audioSettings = std::make_shared<MenuItem>("Audio Settings");
    settings->addChild(displaySettings);
    settings->addChild(audioSettings);

    auto media = std::make_shared<MenuItem>("Media");
    auto radio = std::make_shared<MenuItem>("Radio");
    auto bluetoothAudio = std::make_shared<MenuItem>("Bluetooth Audio");
    media->addChild(radio);
    media->addChild(bluetoothAudio);

    mainMenu->addChild(settings);
    mainMenu->addChild(media);

    // Initialize navigator
    MenuNavigator navigator(mainMenu);

    while (true) {
        navigator.displayMenu();
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        navigator.navigate(choice);

        if (navigator.isAtRoot() && choice == 0) {
            std::cout << "Exiting the menu system.\n";
            break;
        }
    }

    return 0;
}
