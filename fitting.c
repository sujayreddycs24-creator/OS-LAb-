#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int blockOccupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (!blockOccupied[j] && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockOccupied[j] = 1;
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n", i+1);
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int blockOccupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (!blockOccupied[j] && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockOccupied[bestIdx] = 1;
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n", i+1);
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int blockOccupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (!blockOccupied[j] && blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockOccupied[worstIdx] = 1;
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d -> Not Allocated\n", i+1);
    }
}

int main() {
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426};
    int blocks = 5, processes = 4;

    int b1[MAX_BLOCKS], b2[MAX_BLOCKS], b3[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) {
        b1[i] = blockSize[i];
        b2[i] = blockSize[i];
        b3[i] = blockSize[i];
    }

    firstFit(b1, blocks, processSize, processes);
    bestFit(b2, blocks, processSize, processes);
    worstFit(b3, blocks, processSize, processes);

    return 0;
}
