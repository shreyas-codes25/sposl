#include <stdio.h>

struct Process {
    char pname[5];
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

void sjf(struct Process processes[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n];

    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
    }

    while (completed !=  n) {
        int minBT = 1e9;
        int minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && !isCompleted[i]) {
                if (processes[i].bt < minBT) {
                    minBT = processes[i].bt;
                    minIndex = i;
                } else if (processes[i].bt == minBT) {
                    if (processes[i].at < processes[minIndex].at) {
                        minIndex = i;
                    }
                }
            }
        }

        if (minIndex == -1) {
            currentTime++;
        } else {
            currentTime += processes[minIndex].bt;
            processes[minIndex].ct = currentTime;
            processes[minIndex].tat = processes[minIndex].ct - processes[minIndex].at;
            processes[minIndex].wt = processes[minIndex].tat - processes[minIndex].bt;
            isCompleted[minIndex] = 1;
            completed++;
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process P%d: ", i + 1);
        scanf("%s", processes[i].pname);
        printf("Enter the Arrival Time for P%d: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("Enter the Burst Time for P%d: ", i + 1);
        scanf("%d", &processes[i].bt);
    }

    printf("SJF Scheduling\n");
    sjf(processes, n);

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
