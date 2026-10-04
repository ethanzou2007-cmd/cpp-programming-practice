#include <iostream>

int main() {
    int moisture, days;
    std::cout << "Soil moisture (0-100): ";
    std::cin >> moisture;
    std::cout << "Days since last watering: ";
    std::cin >> days;

    if (!std::cin || moisture < 0 || moisture > 100 || days < 0) {
        std::cout << "Invalid input." << '\n';
        return 1;
    }
    if (moisture < 20) {
        std::cout << "Water immediately!" << '\n';
    } else if (days > 5) {
        std::cout << "Time to water your plant." << '\n';
    } else if (moisture >= 80) {
        std::cout << "Soil is too wet. Check drainage." << '\n';
    } else {
        std::cout << "Your plant is happy!" << '\n';
    }
    return 0;
}
