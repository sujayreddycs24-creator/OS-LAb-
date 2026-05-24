#include<stdio.h>
#define MAX_TASK 20
#define MAX_TIME 20

typedef struct{
    int ci;
    int pi;
    int id;
    int next_arrival;
    int remaining_time;

} Task;

void sortByPeriod(Task t[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (t[i].Pi > t[j].Pi) {
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    Task t[MAX_TASKS];
    int gantt[MAX_TIME];

    printf("Enter number of tasks: ");
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        printf("Execution Time (Ci): ");
        scanf("%d", &t[i].Ci);
        printf("Period (Pi): ");
        scanf("%d", &t[i].Pi);

        t[i].id = i + 1;
        t[i].next_arrival = 0;
        t[i].remaining_time = 0;
    }
    for (int i = 0; i < MAX_TIME; i++)
        gantt[i] = -1;


    sortByPeriod(t, n);


    for (int time = 0; time < MAX_TIME; time++) {


        for (int i = 0; i < n; i++) {
            if (time == t[i].next_arrival) {
                t[i].remaining_time = t[i].Ci;
                t[i].next_arrival += t[i].Pi;
            }
        }


        int current = -1;
        for (int i = 0; i < n; i++) {
            if (t[i].remaining_time > 0) {
                current = i;
                break;
            }
        }


        if (current != -1) {
            gantt[time] = t[current].id;
            t[current].remaining_time--;
        } else {
            gantt[time] = -1;
        }
    }


    printf("\n\n--- Gantt Chart ---\n\n");

    printf("|");

    for (int i = 1; i < MAX_TIME; i++) {
        if (gantt[i] != gantt[i - 1]) {
            if (gantt[i - 1] == -1)
                printf(" Idle |");
            else
                printf(" T%d |", gantt[i - 1]);
        }
    }


    if (gantt[MAX_TIME - 1] == -1)
        printf(" Idle |");
    else
        printf(" T%d |", gantt[MAX_TIME - 1]);


    printf("\n0");
    for (int i = 1; i < MAX_TIME; i++) {
        if (gantt[i] != gantt[i - 1]) {
            printf("%6d", i);
        }
    }
    printf("%6d\n", MAX_TIME);

    return 0;
}
