#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

int main() {
    double total = 0.0;
    int count = 0;
    std::cout << "Supermarket Checkout System\n";
    while (true) {
        std::cout << "Enter item price (0 to finish): ";
        double price = 0.0;
        std::string token;
        if (!(std::cin >> token)) {
            std::cerr << "Invalid or incomplete price input.\n";
            return 1;
        }
        std::istringstream input(token);
        if (!(input >> price) || !(input >> std::ws).eof()) {
            std::cerr << "Invalid or incomplete price input.\n";
            return 1;
        }
        if (!std::isfinite(price) || price < 0.0) {
            std::cout << "Price must be a finite non-negative number.\n";
            continue;
        }
        if (price == 0.0) {
            if (count == 0) {
                std::cout << "Must enter at least one item! Please re-enter\n";
                continue;
            }
            break;
        }
        if (!std::isfinite(total + price) || count == std::numeric_limits<int>::max()) {
            std::cerr << "Checkout total or item count is too large.\n";
            return 1;
        }
        total += price;
        ++count;
    }

    const double average = total / count;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "----------------------------\n";
    std::cout << "Number of items: " << count << '\n';
    std::cout << "Total: " << total << " yuan\n";
    std::cout << "Average price: " << average << " yuan\n";
    if (total > 200.0) {
        std::cout << "Spend over 200 yuan, get a coupon for free!\n";
    }
    std::cout << "----------------------------\n";
    return 0;
}
