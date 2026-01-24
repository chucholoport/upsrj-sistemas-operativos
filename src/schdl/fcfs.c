#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void fcfs_schedule(Process p[], int n)
{
    int current_time = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].arrival_time < p[i].arrival_time ||
               (p[j].arrival_time == p[i].arrival_time &&
                p[j].id < p[i].id))
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    /* Calcular tiempos en orden FCFS */
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;

        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;

        current_time += p[i].burst_time;
        p[i].completed = 1;
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