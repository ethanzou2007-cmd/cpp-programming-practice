#include <cstdint>
#include <iostream>
void printBinary(std::uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        if (value & (1 << i)) {
            std::cout << '1';
        } else {
            std::cout << '0';
        }
    }
}
std::uint8_t turnOn(std::uint8_t state, int n) {
    return static_cast<std::uint8_t>(state | (1u << n));
}
std::uint8_t turnOff(std::uint8_t state, int n) {
    return static_cast<std::uint8_t>(state & ~(1u << n));
}
std::uint8_t toggle(std::uint8_t state, int n) {
    return static_cast<std::uint8_t>(state ^ (1u << n));
}
std::uint8_t batchOn(std::uint8_t state, std::uint8_t mask) {
    return static_cast<std::uint8_t>(state | mask);
}
std::uint8_t batchOff(std::uint8_t state, std::uint8_t mask) {
    return static_cast<std::uint8_t>(state & ~mask);
}

int main() {
    std::uint8_t lights = 0;
    int choice;
    int n;
    int mask;
    std::cout << "===== Smart Street Light Controller =====" << '\n';
    std::cout << "1. Turn ON a lamp" << '\n';
    std::cout << "2. Turn OFF a lamp" << '\n';
    std::cout << "3. Toggle a lamp" << '\n';
    std::cout << "4. Batch turn ON" << '\n';
    std::cout << "5. Batch turn OFF" << '\n';
    std::cout << "6. Exit" << '\n';

    while (true) {
        std::cout << "\nCurrent state: decimal " << static_cast<int>(lights) << "   binary ";
        printBinary(lights);
        std::cout << "\nEnter operation number: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input." << '\n';
            return 1;
        }
        if (choice == 6)
            break;

        switch (choice) {
        case 1:
            std::cout << "Lamp number (0~7): ";
            if (!(std::cin >> n) || n < 0 || n > 7) {
                std::cout << "Invalid lamp number." << '\n';
                return 1;
            }
            lights = turnOn(lights, n);
            break;
        case 2:
            std::cout << "Lamp number (0~7): ";
            if (!(std::cin >> n) || n < 0 || n > 7) {
                std::cout << "Invalid lamp number." << '\n';
                return 1;
            }
            lights = turnOff(lights, n);
            break;
        case 3:
            std::cout << "Lamp number (0~7): ";
            if (!(std::cin >> n) || n < 0 || n > 7) {
                std::cout << "Invalid lamp number." << '\n';
                return 1;
            }
            lights = toggle(lights, n);
            break;
        case 4:
            std::cout << "Mask (0~255): ";
            if (!(std::cin >> mask) || mask < 0 || mask > 255) {
                std::cout << "Invalid mask." << '\n';
                return 1;
            }
            lights = batchOn(lights, static_cast<std::uint8_t>(mask));
            break;
        case 5:
            std::cout << "Mask (0~255): ";
            if (!(std::cin >> mask) || mask < 0 || mask > 255) {
                std::cout << "Invalid mask." << '\n';
                return 1;
            }
            lights = batchOff(lights, static_cast<std::uint8_t>(mask));
            break;
        default:
            std::cout << "Invalid option, please try again." << '\n';
        }
    }

    std::cout << "Final state: ";
    printBinary(lights);
    std::cout << '\n';

    return 0;
}
