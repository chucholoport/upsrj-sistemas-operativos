#include <stdio.h>
#include "process.h"
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * Student implementation area
 * ============================================================ */
void rr_schedule(Process p[], int n, int quantum)
{
    if (n <= 0 || quantum <= 0) return;

    int *remaining = malloc(sizeof(int) * n);
    int *completed = malloc(sizeof(int) * n);
    if (!remaining || !completed) {
        free(remaining); free(completed);
        return;
    }

    for (int i = 0; i < n; i++) {
        remaining[i] = p[i].remaining_time;
        completed[i] = 0;
    }

    int current_time = 0;
    int done = 0;

    while (done < n) {
        int progress = 0;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && p[i].arrival_time <= current_time) {
                int run = remaining[i] < quantum ? remaining[i] : quantum;
                current_time += run;
                remaining[i] -= run;

                /* If finished, mark and compute times */
                if (remaining[i] == 0) {
                    completed[i] = 1;
                    p[i].completed = 1;
                    int completion_time = current_time;
                    p[i].turnaround_time = completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    done++;
                }
                progress = 1;
            }
        }

        if (!progress) {
            /* Advance to next arrival of any unfinished process */
            int next = -1;
            for (int i = 0; i < n; i++) {
                if (remaining[i] > 0) {
                    if (next == -1 || p[i].arrival_time < p[next].arrival_time)
                        next = i;
                }
            }
            if (next == -1) break;
            current_time = p[next].arrival_time;
        }
    }

    free(remaining);
    free(completed);
    (void)0;
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