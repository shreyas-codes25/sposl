#include <stdio.h>

struct Process {
    char pname[5];
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

void roundRobin(struct Process processes[], int n, int quantum) {
    int remainingTime[n];
    int currentTime = 0;
    int completed = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].bt;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && remainingTime[i] > 0) {
                // Check if process can complete in this quantum
                if (remainingTime[i] <= quantum) {
                    currentTime += remainingTime[i];
                    processes[i].ct = currentTime;
                    processes[i].tat = processes[i].ct - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                    remainingTime[i] = 0;  // Process is completed
                    completed++;
                } else {
                    // Process still needs more time
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                }m
            }
        }
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter the name of process P%d: ", i + 1);
        scanf("%s", processes[i].pname);
        printf("Enter the Arrival Time for P%d: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("Enter the Burst Time for P%d: ", i + 1);
        scanf("%d", &processes[i].bt);
    }

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Apply Round Robin scheduling
    printf("Round Robin Scheduling\n");
    roundRobin(processes, n, quantum);

    // Output results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    int totalTAT = 0;
    int totalWT = 0;

    for (int i = 0; i < n; i++) {
        totalTAT += processes[i].tat;
        totalWT += processes[i].wt;

        printf("%s\t%d\t%d\t%d\t%d\t%d\n", processes[i].pname, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }

    double avgTAT = (double) totalTAT / n;
    double avgWT = (double) totalWT / n;

    printf("\nAverage TAT: %.2f\n", avgTAT);
    printf("Average WT: %.2f\n", avgWT);

    return 0;
}
