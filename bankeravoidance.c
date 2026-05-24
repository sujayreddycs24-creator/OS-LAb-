#include <stdio.h>
#include <stdbool.h>

#define P 5 // number of processes
#define R 3 // number of resources

int available[R] = {3, 3, 2};

int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[P][R];

bool bankersAlgorithm() {
    // compute need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    bool finish[P] = {false};
    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++) work[i] = available[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    if (count == P) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
        printf("\n");
        return true;
    } else {
        printf("System is NOT in a safe state.\n");
        return false;
    }
}

void processRequest(int proc, int req[R]) {
    printf("Process P%d requesting: ", proc);
    for (int j = 0; j < R; j++) printf("%d ", req[j]);
    printf("\n");

    // check if request <= need
    for (int j = 0; j < R; j++) {
        if (req[j] > need[proc][j]) {
            printf("Error: request exceeds maximum need.\n");
            return;
        }
    }

    // check if request <= available
    for (int j = 0; j < R; j++) {
        if (req[j] > available[j]) {
            printf("Resources not available. Request denied.\n");
            return;
        }
    }

    // pretend to allocate
    for (int j = 0; j < R; j++) {
        available[j] -= req[j];
        allocation[proc][j] += req[j];
        need[proc][j] -= req[j];
    }

    // check safety
    if (bankersAlgorithm()) {
        printf("Request granted.\n");
    } else {
        printf("Request would lead to unsafe state. Rolling back.\n");
        // rollback
        for (int j = 0; j < R; j++) {
            available[j] += req[j];
            allocation[proc][j] -= req[j];
            need[proc][j] += req[j];
        }
    }
}

int main() {
    // initial safety check
    if (!bankersAlgorithm()) {
        printf("Enter process number (0-%d): ", P-1);
        int proc;
        scanf("%d", &proc);

        int req[R];
        printf("Enter request vector of %d resources: ", R);
        for (int j = 0; j < R; j++) scanf("%d", &req[j]);

        processRequest(proc, req);
    }
    return 0;
}
