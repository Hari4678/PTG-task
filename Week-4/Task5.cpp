#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>

// Singleton: HMISystem
class HMISystem {
private:
    static HMISystem* instance; // Pointer to the singleton instance
    std::string mode; // Current mode (Day/Night)
    HMISystem() : mode("Day") {} // Private constructor

public:
    static HMISystem* getInstance() {
        if (!instance)
            instance = new HMISystem();
        return instance;
    }

    void setMode(const std::string& newMode) {
        mode = newMode;
        std::cout << "HMI mode changed to: " << mode << std::endl;
    }

    std::string getMode() const {
        return mode;
    }
};
HMISystem* HMISystem::instance = nullptr;
