#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int request[P][R] = {
    {0, 0, 0},
    {2, 0, 2},
    {0, 0, 0},
    {1, 0, 0},
    {0, 0, 2}
};

int available[R] = {0, 0, 0};

void detectDeadlock() {
    bool finish[P] = {false};
    int work[R];
    int safeSeq[P];
    int index = 0;

    for (int i = 0; i < R; i++) work[i] = available[i];

    bool deadlock = false;

    for (int count = 0; count < P; count++) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool possible = true;
                for (int r = 0; r < R; r++) {
                    if (request[p][r] > work[r]) {
                        possible = false;
                        break;
                    }
                
                if (possible) {
                    for (int r = 0; r < R; r++)
                        work[r] += allocation[p][r];
                    safeSeq[index++] = p;
                    finish[p] = true;
                    found = true;
                }
                }
            }
        }
        if (!found) break;
    }

    // Check if all processes finished
    bool allFinished = true;
    for (int p = 0; p < P; p++) {
        if (!finish[p]) {
            printf("Process %d is in deadlock.\n", p);
            allFinished = false;
            deadlock = true;
        }
    }

    if (!deadlock) {
        printf("No deadlock detected.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < index; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }
}

int main() {
    detectDeadlock();
    return 0;
}

