#include <stdio.h>
#include "process.h"
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * Student implementation area
 * ============================================================ */
void sjf_schedule(Process p[], int n)
{
    if (n <= 0) return;

    /* We'll build an execution order in `order[]` */
    Process *order = malloc(sizeof(Process) * n);
    int placed = 0;
    int current_time = 0;
    int taken[n];
    for (int i = 0; i < n; i++) taken[i] = 0;

    while (placed < n) {
        /* Find all available processes */
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (taken[i]) continue;
            if (p[i].arrival_time <= current_time) {
                if (best == -1 || p[i].burst_time < p[best].burst_time ||
                    (p[i].burst_time == p[best].burst_time && p[i].id < p[best].id)) {
                    best = i;
                }
            }
        }

        if (best == -1) {
            /* No process available yet: advance time to next arrival */
            int next = -1;
            for (int i = 0; i < n; i++) {
                if (!taken[i]) {
                    if (next == -1 || p[i].arrival_time < p[next].arrival_time)
                        next = i;
                }
            }
            if (next == -1) break;
            current_time = p[next].arrival_time;
            continue;
        }

        /* Schedule `best` to completion */
        order[placed++] = p[best];
        taken[best] = 1;

        if (current_time < order[placed-1].arrival_time)
            current_time = order[placed-1].arrival_time;

        int wt = current_time - order[placed-1].arrival_time;
        current_time += order[placed-1].burst_time;
        int tat = wt + order[placed-1].burst_time;

        /* Update fields in the copied struct */
        order[placed-1].waiting_time = wt;
        order[placed-1].turnaround_time = tat;
        order[placed-1].completed = 1;
    }

    /* Copy execution order back into p[] */
    for (int i = 0; i < n; i++) {
        p[i] = order[i];
    }

    (void)0;

    free(order);
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    sjf_schedule(p, n);

    print_results(p, n, "SJF Scheduling");
    return 0;
}
#endif