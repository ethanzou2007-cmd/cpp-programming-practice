#include <iostream>

int main() {
    int mood;
    char timeOfDay, weather;

    std::cout << "Mood (1 = very low, 5 = very happy): ";
    std::cin >> mood;
    std::cout << "Time of day (M = morning, A = afternoon, E = evening): ";
    std::cin >> timeOfDay;
    std::cout << "Weather (S = sunny, R = rainy): ";
    std::cin >> weather;

    if (!std::cin || mood < 1 || mood > 5 ||
        (timeOfDay != 'A' && timeOfDay != 'M' && timeOfDay != 'E') ||
        (weather != 'S' && weather != 'R')) {
        std::cout << "Invalid input." << '\n';
        return 1;
    }

    if (weather == 'R') {
        std::cout << "Recommendation: Relaxing piano music" << '\n';
    } else {
        if (mood >= 4) {
            if (timeOfDay == 'M' || timeOfDay == 'A') {
                std::cout << "Recommendation: Upbeat pop music" << '\n';
            } else {
                std::cout << "Recommendation: Smooth jazz" << '\n';
            }
        } else {
            if (timeOfDay == 'M' || timeOfDay == 'A') {
                std::cout << "Recommendation: Acoustic guitar ballads" << '\n';
            } else {
                std::cout << "Recommendation: Ambient electronic music" << '\n';
            }
        }
    }
    return 0;
}
