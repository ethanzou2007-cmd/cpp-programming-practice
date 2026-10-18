#include <cstdio>

int main() {
    double price[] = {100.0, 102.5, 101.8, 103.2, 104.0, 105.5, 107.0, 106.3, 108.1, 109.5,
                      110.2, 111.0, 109.8, 108.4, 107.0, 106.5, 107.8, 109.2, 110.5, 112.0,
                      113.5, 114.8, 113.0, 111.2, 110.0, 108.5, 109.8, 111.5, 113.2, 115.0};

    const int N = sizeof(price) / sizeof(price[0]);

    double MA5[N] = {0};
    double MA10[N] = {0};
    int signal[N] = {0}; // 0 = HOLD, 1 = BUY, -1 = SELL

    for (int i = 4; i < N; i++) {
        double sum = 0.0;

        for (int j = i - 4; j <= i; j++) {
            sum += price[j];
        }

        MA5[i] = sum / 5.0;
    }

    for (int i = 9; i < N; i++) {
        double sum = 0.0;

        for (int j = i - 9; j <= i; j++) {
            sum += price[j];
        }

        MA10[i] = sum / 10.0;
    }

    for (int i = 10; i < N; i++) {
        if (MA5[i - 1] <= MA10[i - 1] && MA5[i] > MA10[i]) {
            signal[i] = 1; // BUY
        } else if (MA5[i - 1] >= MA10[i - 1] && MA5[i] < MA10[i]) {
            signal[i] = -1; // SELL
        } else {
            signal[i] = 0; // HOLD
        }
    }

    int buyCount = 0;
    int sellCount = 0;

    printf("Day\tPrice\tMA5\tMA10\tSignal\n");

    for (int i = 0; i < N; i++) {
        printf("%d\t%.2f\t", i + 1, price[i]);

        if (i >= 4)
            printf("%.2f\t", MA5[i]);
        else
            printf("---\t");

        if (i >= 9)
            printf("%.2f\t", MA10[i]);
        else
            printf("---\t");

        if (signal[i] == 1) {
            printf("BUY\n");
            buyCount++;
        } else if (signal[i] == -1) {
            printf("SELL\n");
            sellCount++;
        } else {
            printf("HOLD\n");
        }
    }

    printf("\nBUY signals: %d\n", buyCount);
    printf("SELL signals: %d\n", sellCount);

    return 0;
}
