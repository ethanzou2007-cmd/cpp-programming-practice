#include <cstdio>
#include <iostream>

int main() {

    double temp[24] = {-2.0, -2.5, -3.0, -3.2, -3.5, -4.0, -3.8, -2.0, 1.0, 4.5, 7.0,  9.5,
                       11.0, 12.5, 13.0, 12.8, 10.0, 7.2,  5.0,  2.5,  1.0, 0.0, -1.2, -1.8};

    int n = sizeof(temp) / sizeof(temp[0]);

    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += temp[i];
    }
    double mean = sum / n;

    printf("24 hour total temperature: %.1f degrees\n", sum);
    printf("Daily mean temperature:    %.1f degrees\n\n", mean);

    double maxVal = temp[0];
    double minVal = temp[0];
    int maxHour = 0;
    int minHour = 0;

    for (int i = 0; i < n; i++) {
        if (temp[i] > maxVal) {
            maxVal = temp[i];
            maxHour = i;
        }
        if (temp[i] < minVal) {
            minVal = temp[i];
            minHour = i;
        }
    }

    printf("Maximum temperature: %.1f degrees, occurred at %d:00\n", maxVal, maxHour);
    printf("Minimum temperature: %.1f degrees, occurred at %d:00\n\n", minVal, minHour);

    int belowFreezing = 0;
    for (int i = 0; i < n; i++) {
        if (temp[i] < 0.0) {
            belowFreezing++;
        }
    }
    if (belowFreezing > 0) {
        printf("Hours below freezing: %d hours\n\n", belowFreezing);
    } else {
        printf("No freezing temperature today\n\n");
    }

    printf("Hour  Temperature  Deviation\n");
    printf("----  -----------  ---------\n");

    double dev[24];
    for (int i = 0; i < n; ++i) {
        dev[i] = temp[i] - mean;
        printf("%4d %8.1f %+8.1f\n", i, temp[i], dev[i]);
    }

    return 0;
}

/*
 * Question 1: The Dual Identity of the Array Index
 *
 * (1) Answer:
 * Besides accessing temp[i], the index i represents the hour of the day.
 * For example, i = 0 means 00:00, and i = 23 means 23:00.
 *
 * (2) Answer:
 * Change temp[24] to temp[168] and provide all 168 temperature values.
 * Update the output labels to describe one week.
 * The calculation of n, loops using i < n, and the statistical
 * calculations need no changes.
 *
 * (3) Answer:
 * Keep each temperature together with its original hour or timestamp.
 * Then sort the records by time or place each temperature back at its
 * original index. If the time information is lost, the original order
 * cannot be recovered from temperature values alone.
 *
 * Question 2: Separating vs. Merging Traversal Tasks
 *
 * (1) Answer:
 * I put maximum-finding and minimum-finding in the same loop.
 * Summation, counting hours below freezing, and displaying temperatures
 * and deviations each have separate loops. The mean is calculated
 * after summation.
 *
 * (2) Answer:
 * A single loop could add each temperature to the sum, update the
 * maximum and minimum values and their hours, and count temperatures
 * below zero.
 * The advantage is that the array is traversed only once, reducing
 * repeated access. The disadvantage is that the loop becomes more
 * complex and harder to read and debug.
 * Both approaches have O(n) time complexity. Deviations still require
 * a later loop because the final mean must be calculated first.
 *
 * (3) Answer:
 * I would prefer several small loops, each doing one task.
 * They are easier to understand, debug, and modify. For only 24
 * temperature values, the extra traversal cost is small, so
 * readability is more important.
 */
