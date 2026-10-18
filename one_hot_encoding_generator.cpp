#include <cstdio>
#include <iostream>

int main() {
    // Total number of categories (constant)
    const int C = 5;

    // 12 sample category labels
    int labels[] = {2, 0, 4, 1, 3, 2, 0, 4, 3, 1, 0, 2};

    // Automatically compute the number of labels
    int N = sizeof(labels) / sizeof(labels[0]);

    // ========== Part 1: Generate and Print One Hot Encodings ==========
    printf("=== One Hot Encoding Output ===\n");

    for (int i = 0; i < N; ++i) {
        if (labels[i] < 0 || labels[i] >= C) {
            std::cerr << "Invalid category label.\n";
            return 1;
        }
        int onehot[C] = {0};
        onehot[labels[i]] = 1;
        printf("Label %d -> [", labels[i]);
        for (int j = 0; j < C; ++j) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", onehot[j]);
        }
        printf("]\n");
    }

    // ========== Part 2: Count How Many Times Each Category Appears ==========
    printf("\n=== Category Frequency Count ===\n");
    int counts[C] = {0};
    for (int i = 0; i < N; ++i) {
        counts[labels[i]]++;
    }
    for (int i = 0; i < C; ++i) {
        printf("%d:%dtimes\n", i, counts[i]);
    }

    return 0;
}
