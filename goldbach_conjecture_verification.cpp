#include <iostream>
#include <sstream>
#include <string>

int main() {
    int N;

    do {
        std::cout << "Enter an even number greater than 2: ";
        std::string token;
        if (!(std::cin >> token)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        std::istringstream input(token);
        if (!(input >> N) || !(input >> std::ws).eof()) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
    } while (N <= 2 || N % 2 != 0);

    int total = 0;

    for (int p = 2; p <= N / 2; ++p) {
        bool p_is_prime = true;
        if (p < 2) {
            p_is_prime = false;
        } else {
            for (int i = 2; i <= p / i; ++i)
                if (p % i == 0) {
                    p_is_prime = false;
                    break;
                }
        }

        if (!p_is_prime) {
            continue;
        }

        int q = N - p;
        bool q_is_prime = true;
        if (q < 2) {
            q_is_prime = false;
        } else {
            for (int i = 2; i <= q / i; ++i)
                if (q % i == 0) {
                    q_is_prime = false;
                    break;
                }
        }

        if (q_is_prime) {
            std::cout << N << " = " << p << " + " << q << std::endl;
            ++total;
        }
    }

    std::cout << "Total " << total << " representations found." << std::endl;

    /* Thinking Questions

  Question 1:
  Answer:
  If p is composite, it can be written as p = a * b,
  where a and b are integers greater than 1.
  If both factors were greater than sqrt(p), their product
  would exceed p. Therefore, at least one factor must be
  less than or equal to sqrt(p).
  Checking divisors up to sqrt(p) is enough to detect
  every composite number.

  Question 2:
  Answer:
  For N = 100, we test candidate values of p from 2 to 50
  and calculate q = 100 - p. Each prime test checks divisors
  up to the square root of the number.
  This requires roughly a few hundred remainder operations.
  The exact number depends on whether the tests stop early
  when a divisor is found or skip testing q when p is composite.


  Question 3:
  Answer:
  To check many odd numbers, use an outer loop over odd N,
  starting at 7 and increasing by 2 up to a chosen limit.
  For each N, use two nested loops to enumerate primes p
  and q, then calculate r = N - p - q.
  Check whether r is prime.
  Require p <= q <= r to avoid duplicate combinations.
  Once a valid triple is found, stop searching for that N
  and move to the next odd number.
  If no triple is found, report that N as a failure.

  */

    return 0;
}
