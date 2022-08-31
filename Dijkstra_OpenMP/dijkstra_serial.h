#include <stdio.h>
#include <stdlib.h>

void serial_dijkstra(int **G, int n, int startnode, int endnode, int verbose)
{
    // Initializing and allocation of memory for the variables
    int **cost, *distance, *pred, *visited;
    int count, mindistance, nextnode, i, j;

    cost = (int **)malloc(n * sizeof(int *));
    distance = (int *)malloc(n * sizeof(int));
    pred = (int *)malloc(n * sizeof(int));
    visited = (int *)malloc(n * sizeof(int));

    // Initializing cost matrix
    for (i = 0; i < n; i++) {
        cost[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            if (G[i][j] == INF) cost[i][j] = INF;
            else cost[i][j] = G[i][j];
        }
    }

    // Initialize pred[], distance[] and visited[]
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;    // Distance from startnode to startnode is 0
    visited[startnode] = 1;     // startnode is visited
    count = 1;                  // count number of nodes

    // Find shortest path for all nodes
    while (count < n - 1)
    {
        // Pick the minimum distance node from all the nodes not yet
        // processed. mindistance is always equal to startnode in first iteration
        mindistance = INF;
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        // Mark the picked node as processed
        visited[nextnode] = 1;

        // update distance[i] only if it is not in visited and there is an edge
        // from nextnode to i and total weight of path from startnode to i is
        // smaller than current value of distance[i]
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    // Print the shortest distance from startnode to endnode
    if (verbose)
        print_distance(startnode, endnode, distance, pred);
}