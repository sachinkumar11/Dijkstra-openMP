#include <stdio.h>
#include <stdlib.h>

void print_distance(int startnode, int endnode, int *distance, int *pred)
{
//    printf("\nDistance of Node %d from Node %d is: %d kms.", endnode, startnode, distance[endnode]);
    printf("\nPath is: %d", endnode);
    int i = endnode;
    while (i != startnode)
    {
        i = pred[i];
        printf(" <-- %d ", i);
    }
    printf("\n");
}
