#include <iostream>

int main() {
    int solutionCount = 0;
    std::cout << "All solutions to the Hundred Monks and Buns problem:" << std::endl;
    std::cout << "Senior\tMiddle\tJunior" << std::endl;
    std::cout << "----------------------------" << std::endl;

    for (int a = 0; a <= 33; ++a) {
        for (int b = 0; b <= 50; ++b) {
            int c = 100 - a - b;
            if (c >= 0 && c % 3 == 0 && 9 * a + 6 * b + c == 300) {
                std::cout << a << "\t" << b << "\t" << c << std::endl;
                solutionCount++;
            }
        }
    }

    std::cout << "----------------------------" << std::endl;
    std::cout << "Total " << solutionCount << " solutions found." << std::endl;

    /* Thinking Questions

Question 1:
Answer:
Yes, the program may still produce output if it only checks the
total number of buns. However, c = 100 - a + b does not guarantee
a + b + c = 100, so some printed results may be invalid.
Every candidate must satisfy all the original conditions.
A result being printed does not mean it is correct.

Question 2:
Answer:
Yes, provided that all conditions are checked, including c >= 0.
Searching from 0 to 100 still includes every valid solution,
but it also checks many impossible combinations.
The number of candidate pairs increases from 34 * 51 = 1734
to 101 * 101 = 10201, which is about 5.9 times as many.

Question 3:
Answer:
Use three nested loops to enumerate a, b, and d.
Calculate c = 100 - a - b - d instead of using a fourth loop.
Since there are 100 buns, a <= 33, b <= 50, and d <= 20,
because these monks eat 3, 2, and 5 buns each.
For each candidate, check that c >= 0 and that the total
number of buns eaten is exactly 100.
The loop bounds can be reduced further using the remaining
number of monks and buns after each choice.

*/

    return 0;
}
