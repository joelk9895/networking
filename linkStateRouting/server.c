#include <stdio.h>
#include <limits.h>

#define NUM_NODES 5
#define INFINITY INT_MAX

void dijkstra(int graph[NUM_NODES][NUM_NODES], int source, int dist[NUM_NODES], int prev[NUM_NODES])
{
    int visited[NUM_NODES] = {0};
    for (int i = 0; i < NUM_NODES; i++)
    {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    dist[source] = 0;
    for (int count = 0; count < NUM_NODES - 1; count++)
    {
        int minDist = INFINITY, u = -1;
        for (int v = 0; v < NUM_NODES; v++)
        {
            if (!visited[v] && dist[v] < minDist)
            {
                minDist = dist[v];
                u = v;
            }
        }
        visited[u] = 1;
        for (int v = 0; v < NUM_NODES; v++)
        {
            if (!visited[v] && graph[u][v] != INFINITY && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
}

void printPath(int prev[NUM_NODES], int node)
{
    if (prev[node] != -1)
    {
        printPath(prev, prev[node]);
        printf(" -> ");
    }
    printf("%d", node);
}

int main()
{
    int graph[NUM_NODES][NUM_NODES] = {
        {0, 10, INFINITY, INFINITY, 5},
        {10, 0, 1, INFINITY, INFINITY},
        {INFINITY, 1, 0, 4, INFINITY},
        {INFINITY, INFINITY, 4, 0, 2},
        {5, INFINITY, INFINITY, 2, 0}};

    int source = 0;
    int dist[NUM_NODES], prev[NUM_NODES];

    dijkstra(graph, source, dist, prev);

    for (int i = 0; i < NUM_NODES; i++)
    {
        if (dist[i] == INFINITY)
            printf("No path to Node %d\n", i);
        else
        {
            printf("Shortest path to Node %d: ", i);
            printPath(prev, i);
            printf(" with distance %d\n", dist[i]);
        }
    }

    return 0;
}