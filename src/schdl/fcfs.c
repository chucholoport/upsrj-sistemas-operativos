#include <stdio.h>
#include <stdlib.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
/* Comparator para ordenar por arrival_time, desempate por id */
static int proc_cmp(const void *a, const void *b)
{
    const Process *pa = a;
    const Process *pb = b;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->id - pb->id;
}

void fcfs_schedule(Process p[], int n)
{
    if (n <= 0) return;

    qsort(p, n, sizeof(Process), proc_cmp);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        printf("Tiempo %d: Ejecutando P%d (BT=%d)\n",
               current_time, p[i].id, p[i].burst_time);

        p[i].waiting_time = current_time - p[i].arrival_time;
        current_time += p[i].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].completed = 1;

        printf("   -> P%d terminó en tiempo %d\n", p[i].id, current_time);
    }
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

    fcfs_schedule(p, n);

    print_results(p, n, "FCFS Scheduling");
    return 0;
}
#endif