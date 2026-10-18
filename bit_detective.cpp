#include <iostream>
#include <sstream>
#include <string>

int main() {
    int n;
    std::cout << "Bit Detective: enter positive integers (0 to stop)" << std::endl;

    while (true) {
        std::cout << "Enter a positive integer: ";
        std::string token;
        if (!(std::cin >> token)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        std::istringstream input(token);
        if (!(input >> n) || !(input >> std::ws).eof()) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }

        if (n == 0) {
            break;
        }
        if (n < 0) {
            std::cout << "Negative invalid, please enter a positive integer:" << std::endl;
            continue;
        }

        int original = n;
        int count = 0;

        while (n != 0) {
            n = n & (n - 1);
            count++;
        }

        std::cout << "Decimal " << original << " has " << count << " 1-bits in binary."
                  << std::endl;

        if (original > 0 && (original & (original - 1)) == 0) {
            std::cout << original << " is a power of two." << std::endl;
        } else {
            std::cout << original << " is not a power of two." << std::endl;
        }
    }

    std::cout << "Program ended." << std::endl;

    /* Thinking Questions

Question 1:
Answer:
Subtracting 1 changes the rightmost 1-bit to 0 and all the
0-bits after it to 1. The higher bits remain unchanged.
ANDing this result with n clears only the rightmost 1-bit.

Example:
    n     = 12 = 1100
    n - 1 = 11 = 1011
    AND result = 1000 = 8

Question 2:
Answer:
Yes. While n is not 0, use n % 2 to get the last binary bit.
If it is 1, increment count. Then use n = n / 2 to remove
that bit. Repeat until n becomes 0.

Question 3:
Answer:
1024 in binary is 10000000000, which contains only one 1-bit.
The clear-rightmost-1 method executes once.
The divide-by-2 method executes 11 times, once for each bit.
The first method needs fewer iterations when the number
contains few 1-bits, especially for large powers of two.

*/

    return 0;
}
