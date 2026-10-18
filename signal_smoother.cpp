#include <cstdio>
#include <iostream>

int main() {

    double raw[] = {35.2, 36.1, 34.8, 89.3, 35.5, 36.0, 34.9, 35.8, 36.3, 35.0};

    int n = sizeof(raw) / sizeof(raw[0]);
    double smooth[10] = {0.0};

    smooth[0] = raw[0];
    smooth[n - 1] = raw[n - 1];

    for (int i = 1; i < n - 1; ++i) {
        smooth[i] = (raw[i - 1] + raw[i] + raw[i + 1]) / 3.0;
    }

    printf("Index   Original   Smoothed\n");
    printf("-----   --------   --------\n");
    for (int i = 0; i < n; ++i) {
        printf("%4d %8.1f %8.1f\n", i, raw[i], smooth[i]);
    }
    return 0;
}

/*
 * Question 1: The Dilemma of Boundary Handling
 *
 * (1) Answer:
 * Copying the original boundary values is a simple and reasonable choice,
 * but those values are not smoothed like the middle elements.
 * This may cause an unnatural jump near either end, especially if
 * a boundary value contains noise.
 *
 * (2) Answer:
 * One alternative is to use a smaller window at the boundaries.
 * Average the first two values for the first element, and average
 * the last two values for the last element.
 *
 * (3) Answer:
 * The two boundary elements occupy 2 / 1,000,000 = 0.000002,
 * or 0.0002% of the dataset.
 * Their effect on overall statistics is usually very small.
 * However, the strategy still matters if endpoint accuracy is important.
 *
 * Question 2: The Trade-off of Window Size
 *
 * (1) Answer:
 * A width-5 window averages more neighboring values, so it usually
 * reduces random noise more strongly and produces a smoother curve.
 * However, it also reduces sharp peaks and blurs rapid changes.
 *
 * (2) Answer:
 * A bigger window is not always better.
 * If humidity drops rapidly, a large window may spread the drop
 * across several points and make it appear slower and less severe.
 * This could make the real event harder to detect.
 *
 * (3) Answer:
 * Choose the window size based on the sampling interval, noise level.
 * Weather data may need smoothing that preserves important changes.
 * Stock analysis may use different windows for short-term and
 * long-term trends. Anomaly detection needs a window that reduces
 * noise without hiding brief anomalies.
 */
