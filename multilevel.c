
#include <stdio.h>

int main() {

    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int PID[n], AT[n], BT[n], TYPE[n];
    int CT[n], TAT[n], WT[n], Start[n];

    printf("\nEnter Process Details\n");

    for(int i = 0; i < n; i++) {

        PID[i] = i + 1;

        printf("Process %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);

        printf("Burst Time: ");
        scanf("%d", &BT[i]);

        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &TYPE[i]);
    }

    int systemQ[n], userQ[n];
    int sysCount = 0, userCount = 0;

    for(int i = 0; i < n; i++) {

        if(TYPE[i] == 0)
            systemQ[sysCount++] = i;
        else
            userQ[userCount++] = i;
    }

    int time = 0;

    for(int i = 0; i < sysCount; i++) {

        int p = systemQ[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];

        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    for(int i = 0; i < userCount; i++) {

        int p = userQ[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];

        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }
    printf("GAANT FOR SYS Q:\n");
    for(int i = 0; i < sysCount; i++)
        printf("P%d   ",systemQ[i]+1);

    printf("\nGAANT FOR USER Q:\n");

    for(int i = 0; i < userCount; i++)
        printf("P%d   ",userQ[i]+1);

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        PID[i], AT[i], BT[i], TYPE[i],
        CT[i], TAT[i], WT[i]);
    }

    return 0;
}

