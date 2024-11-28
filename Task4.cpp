#include <iostream>
#include <string>
#include <map>
#include <memory>

// Class to represent a theme
class Theme {
private:
    std::string name;
    std::string backgroundColor;
    std::string fontColor;
    int fontSize;
    std::string iconStyle;

public:
    Theme(const std::string& name, const std::string& bgColor, const std::string& fColor, int fSize, const std::string& iStyle)
        : name(name), backgroundColor(bgColor), fontColor(fColor), fontSize(fSize), iconStyle(iStyle) {}

    void applyTheme() const {
        std::cout << "\nApplying " << name << " Theme...\n";
        std::cout << "Background Color: " << backgroundColor << "\n";
        std::cout << "Font Color: " << fontColor << "\n";
        std::cout << "Font Size: " << fontSize << "\n";
        std::cout << "Icon Style: " << iconStyle << "\n";
    }

    void previewTheme() const {
        std::cout << name << " Theme: " << backgroundColor 
                  << " Background, " << fontColor << " Font, "
                  << fontSize << " pt Font Size, " << iconStyle << " Icons.\n";
    }
};

// Class to manage themes
class ThemeManager {
private:
    std::map<std::string, std::shared_ptr<Theme>> themes;
    std::shared_ptr<Theme> currentTheme;

public:
    void addTheme(const std::string& name, const std::shared_ptr<Theme>& theme) {
        themes[name] = theme;
    }

    void switchTheme(const std::string& name) {
        if (themes.find(name) != themes.end()) {
            currentTheme = themes[name];
            currentTheme->applyTheme();
        } else {
            std::cout << "Theme \"" << name << "\" not found.\n";
        }
    }

    void displayThemes() const {
        std::cout << "Available Themes:\n";
        for (const auto& pair : themes) {
            pair.second->previewTheme();
        }
    }
};

int main() {
    // Create ThemeManager
    ThemeManager themeManager;

    // Add themes
    themeManager.addTheme("Classic", std::make_shared<Theme>("Classic", "Black", "White", 12, "Minimalist"));
    themeManager.addTheme("Sport", std::make_shared<Theme>("Sport", "Red", "White", 14, "Bold"));
    themeManager.addTheme("Eco", std::make_shared<Theme>("Eco", "Green", "Brown", 12, "Nature"));

    // Main loop for theme selection
    while (true) {
        std::cout << "\n=== HMI Skin Customization ===\n";
        themeManager.displayThemes();
        std::cout << "\nEnter a theme name to apply (or type 'exit' to quit): ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            std::cout << "Exiting theme customization system.\n";
            break;
        }

        themeManager.switchTheme(input);
    }

    return 0;
}
