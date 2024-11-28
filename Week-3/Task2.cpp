#include <iostream>
#include <iomanip>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <ctime>

// Class to store vehicle data
class VehicleData {
public:
    int speed;          // in km/h
    int fuelLevel;      // in percentage
    int engineTemp;     // in °C

    VehicleData() : speed(0), fuelLevel(100), engineTemp(80) {}

    void updateData() {
        // Randomly update the parameters
        speed = rand() % 181; // Speed between 0 and 180 km/h
        fuelLevel = std::max(0, fuelLevel - rand() % 5); // Decrease fuel slightly
        engineTemp = 70 + rand() % 41; // Temperature between 70 and 110 °C
    }
};

// Class to display vehicle data
class Display {
public:
    void showData(const VehicleData& data) {
        std::cout << "\033[2J\033[1;1H"; // Clear console and move to top
        std::cout << "=== Instrument Cluster ===\n";
        std::cout << "Speed: " << data.speed << " km/h\n";
        std::cout << "Fuel: " << data.fuelLevel << "%\n";
        std::cout << "Engine Temp: " << data.engineTemp << " °C\n";

        // Warnings
        if (data.engineTemp > 100) {
            std::cout << "WARNING: Engine temperature exceeds safe limit!\n";
        }
        if (data.fuelLevel < 10) {
            std::cout << "WARNING: Low fuel level!\n";
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    VehicleData vehicleData;
    Display display;
    std::atomic<bool> running(true);

    // Thread to update vehicle data
    std::thread dataUpdater([&]() {
        while (running) {
            vehicleData.updateData();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    // Main thread to display data
    while (true) {
        display.showData(vehicleData);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Stop simulation on user input
        if (std::cin.peek() != EOF) {
            running = false;
            break;
        }
    }

    dataUpdater.join(); // Wait for the updater thread to finish
    return 0;
}
