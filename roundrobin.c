#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int AT[n],BT[n],RT[n];
    int CT[n],TAT[n],WT[n];

    printf("Enter Arrival Time and Burst Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        scanf("%d %d", &AT[i], &BT[i]);
        RT[i] = BT[i];
        CT[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0;
    int completed = 0;
    int queue[100];
    int front = 0, rear = 0;
    int visited[n];

    for(int i = 0; i < n; i++)
        visited[i] = 0;

    while(completed < n) {

        for(int i = 0; i < n; i++) {
            if(AT[i] <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(front == rear) {
            time++;
            continue;
        }

        int p = queue[front++];

        if(RT[p] > tq) {

            time += tq;
            RT[p] -= tq;

            for(int i = 0; i < n; i++) {
                if(AT[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            queue[rear++] = p;
        }
        else {

            time += RT[p];
            RT[p] = 0;
            CT[p] = time;
            completed++;

            for(int i = 0; i < n; i++) {
                if(AT[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

    }
    for(int i = 0; i <rear; i++)
            printf("P%d  ",queue[i]+1);

    for(int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    return 0;
}


