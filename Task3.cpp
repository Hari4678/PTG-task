#include <iostream>
#include <queue>
#include <string>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>

// Class to represent an Event
class Event {
public:
    enum EventType { Tap, Swipe };
    EventType eventType;
    int x, y;           // Coordinates
    int xEnd, yEnd;     // Ending coordinates for swipe
    std::time_t timestamp;

    Event(EventType type, int startX, int startY, int endX = 0, int endY = 0)
        : eventType(type), x(startX), y(startY), xEnd(endX), yEnd(endY) {
        timestamp = std::time(nullptr);
    }

    std::string getType() const {
        return eventType == Tap ? "Tap" : "Swipe";
    }
};

// Function to determine swipe direction
std::string getSwipeDirection(int startX, int startY, int endX, int endY) {
    int deltaX = endX - startX;
    int deltaY = endY - startY;

    if (std::abs(deltaX) > std::abs(deltaY)) {
        return deltaX > 0 ? "Right" : "Left";
    } else {
        return deltaY > 0 ? "Down" : "Up";
    }
}

// Class to handle events
class EventHandler {
    std::queue<Event> eventQueue;

public:
    void addEvent(const Event& event) {
        eventQueue.push(event);
    }

    void processEvents() {
        while (!eventQueue.empty()) {
            Event event = eventQueue.front();
            eventQueue.pop();

            std::cout << "Processing " << event.getType() 
                      << " event at (" << event.x << ", " << event.y << ")";
            if (event.eventType == Event::Swipe) {
                std::cout << " to (" << event.xEnd << ", " << event.yEnd << ")";
                std::cout << " - Direction: " 
                          << getSwipeDirection(event.x, event.y, event.xEnd, event.yEnd);
            }
            std::cout << " [Timestamp: " << std::ctime(&event.timestamp) << "]\n";
        }
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));
    EventHandler eventHandler;

    // Simulate random event generation
    std::thread eventGenerator([&]() {
        for (int i = 0; i < 10; ++i) {
            int x = std::rand() % 1000;
            int y = std::rand() % 1000;

            if (std::rand() % 2 == 0) { // Randomly choose between Tap and Swipe
                eventHandler.addEvent(Event(Event::Tap, x, y));
            } else {
                int xEnd = std::rand() % 1000;
                int yEnd = std::rand() % 1000;
                eventHandler.addEvent(Event(Event::Swipe, x, y, xEnd, yEnd));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Process events as they are generated
    std::thread eventProcessor([&]() {
        while (true) {
            eventHandler.processEvents();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    eventGenerator.join();
    eventProcessor.detach();

    std::cout << "Event handling simulation running. Press Enter to exit.\n";
    std::cin.get();
    return 0;
}

