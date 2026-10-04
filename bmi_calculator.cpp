#include <cmath>
#include <iomanip>
#include <iostream>
int main() {
    double weightKg, heightM;
    std::cout << "Enter weight (kg): ";
    std::cin >> weightKg;
    std::cout << "Enter height (m): ";
    std::cin >> heightM;
    if (!std::cin || !std::isfinite(weightKg) || !std::isfinite(heightM) || weightKg <= 0 ||
        heightM <= 0) {
        std::cout << "Invalid input. Weight and height must be positive numbers." << '\n';
        return 1;
    }
    double bmi = weightKg / (heightM * heightM);
    if (!std::isfinite(bmi) || bmi <= 0) {
        std::cout << "Invalid input. BMI is outside the supported numeric range." << '\n';
        return 1;
    }
    std::cout << "Your BMI is: " << std::fixed << std::setprecision(2) << bmi << '\n';
    return 0;
}
