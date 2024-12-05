#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    bool is_completed;
} Process;

void sort_by_arrival_time(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void round_robin(Process processes[], int n, int time_quantum)
{
    int current_time = 0, completed = 0;
    int ready_queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    bool in_queue[MAX_PROCESSES] = {false};

    ready_queue[rear++] = 0;
    in_queue[0] = true;

    while (completed < n)
    {
        int idx = ready_queue[front++];

        if (processes[idx].remaining_time > time_quantum)
        {
            current_time += time_quantum;
            processes[idx].remaining_time -= time_quantum;
        }
        else
        {
            current_time += processes[idx].remaining_time;
            processes[idx].remaining_time = 0;
            processes[idx].completion_time = current_time;
            processes[idx].turn_around_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turn_around_time - processes[idx].burst_time;
            processes[idx].is_completed = true;
            completed++;
        }

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && !in_queue[i] && !processes[i].is_completed)
            {
                ready_queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        if (processes[idx].remaining_time > 0)
        {
            ready_queue[rear++] = idx;
        }
    }
}

int main()
{
    int n, time_quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = false;
    }

    sort_by_arrival_time(processes, n);
    round_robin(processes, n, time_quantum);

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurn Around\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turn_around_time,
               processes[i].waiting_time);
    }

    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        avg_turnaround_time += processes[i].turn_around_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turn Around Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}