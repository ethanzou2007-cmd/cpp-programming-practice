#include <iostream>

int main() {
    const int LIVING = 1;
    const int BEDROOM = 2;
    const int KITCHEN = 4;
    const int BATHROOM = 8;

    int status;
    std::cout << "Room status (0-15): ";
    std::cin >> status;

    if (!std::cin || status < 0 || status > 15) {
        std::cout << "Invalid status value." << '\n';
        return 1;
    }

    if (status & KITCHEN) {
        std::cout << "turn on the kitchen fan" << '\n';
    } else if (status & BATHROOM) {
        std::cout << "turn on the bathroom heater" << '\n';
    } else if (status & LIVING) {
        std::cout << "turn on the living room air conditioner and set the lights to bright" << '\n';
    } else if (status & BEDROOM) {
        std::cout << "turn on the bedroom air conditioner but dim the lights" << '\n';
    } else {
        std::cout << "All rooms empty. Entering standby mode." << '\n';
    }
    return 0;
}
