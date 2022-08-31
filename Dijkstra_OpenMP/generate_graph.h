#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define RAND_NUM 200
#define INF 99999

int **generate_graph(int n, int m, int verbose)
{
    int i, j, **graph;

    if (m > (n * (n - 1) / 2))
    {
        if (verbose)
            printf("\n--- [GRAPH GENERATOR] Number of edges is greater than the number of possible edges!\n");
        exit(0);
    }

    graph = (int **)malloc(n * sizeof(int *));

    if (graph == NULL)
    {
        if (verbose)
            printf("\n--- [GRAPH GENERATOR] Error allocating memory!\n");
        exit(-1);
    }

    if (verbose)
        printf("\n--- [GRAPH GENERATOR] Generating graph...\n");
    
    srand(time(NULL));

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for private(i)
        for (i = 0; i < n; i++)
            graph[i] = (int *)malloc(n * sizeof(int));


        #pragma omp for private(i, j)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (i == j)
                    graph[i][j] = 0;
                else
                    graph[i][j] = INF;
                // graph[i][j] = 0;

        #pragma omp for private(i, j)
        for (i = 0; i < m; i++)
        {
            int a = rand() % n;
            int b = rand() % n;

            if (a != b)
            {
                int weight = rand() % 150;
                graph[a][b] = weight;
                graph[b][a] = weight;
            }
        }
    }
    double end = omp_get_wtime();

    if (verbose)
        printf("--- [GRAPH GENERATOR] Graph generated in %.2f seconds\n", end - start);
    return graph;
}