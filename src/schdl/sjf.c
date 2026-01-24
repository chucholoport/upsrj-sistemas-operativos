#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void sjf_schedule(Process p[], int n)
{
    int current_time = 0;
    int completed = 0;

    Process ordered[n];  

    while (completed < n)
    {
        int idx = -1;
        int min_burst = 999999;

      
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed && p[i].arrival_time <= current_time)
            {
                if (p[i].burst_time < min_burst)
                {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
                else if (p[i].burst_time == min_burst)
                {
                    if (p[i].arrival_time < p[idx].arrival_time ||
                       (p[i].arrival_time == p[idx].arrival_time &&
                        p[i].id < p[idx].id))
                    {
                        idx = i;
                    }
                }
            }
        }

      
        if (idx == -1)
        {
            current_time++;
            continue;
        }

       
        p[idx].waiting_time = current_time - p[idx].arrival_time;
        p[idx].turnaround_time =
            p[idx].waiting_time + p[idx].burst_time;

        current_time += p[idx].burst_time;
        p[idx].completed = 1;

        ordered[completed] = p[idx];
        completed++;
    }

    for (int i = 0; i < n; i++)
    {
        p[i] = ordered[i];
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

    sjf_schedule(p, n);

    print_results(p, n, "SJF Scheduling");
    return 0;
}
#endif