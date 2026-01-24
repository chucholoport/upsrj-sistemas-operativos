#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void rr_schedule(Process p[], int n, int quantum)
{
    int time = 0;
    int completed = 0;

    int queue[100];
    int front = 0, rear = 0;

    int in_queue[n];
    for (int i = 0; i < n; i++)
        in_queue[i] = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n) {

        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!p[i].completed &&
                    p[i].arrival_time <= time &&
                    !in_queue[i]) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        int exec_time = (p[i].remaining_time > quantum)
                        ? quantum
                        : p[i].remaining_time;

        p[i].remaining_time -= exec_time;
        time += exec_time;

        for (int j = 0; j < n; j++) {
            if (!p[j].completed &&
                p[j].arrival_time <= time &&
                !in_queue[j]) {
                queue[rear++] = j;
                in_queue[j] = 1;
            }
        }

        if (p[i].remaining_time == 0) {
            p[i].completed = 1;
            completed++;
            p[i].turnaround_time = time - p[i].arrival_time;
            p[i].waiting_time =
                p[i].turnaround_time - p[i].burst_time;
        } else {
            queue[rear++] = i;
        }
    }
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n;
    int quantum;

    printf("Número de procesos: ");
    scanf("%d", &n);

    printf("Quantum: ");
    scanf("%d", &quantum);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    rr_schedule(p, n, quantum);

    print_results(p, n, "RR Scheduling");
    return 0;
}
#endif