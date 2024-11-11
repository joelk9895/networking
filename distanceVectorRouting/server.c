#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_NODES 5
#define INFINITY INT_MAX

void printRoutingTable(int table[NUM_NODES][NUM_NODES], int node)
{
    printf("Routing table for Node %d:\n", node);
    for (int i = 0; i < NUM_NODES; i++)
    {
        if (table[node][i] == INFINITY)
            printf("To Node %d: INF\n", i);
        else
            printf("To Node %d: %d\n", i, table[node][i]);
    }
    printf("\n");
}

void updateRoutingTable(int table[NUM_NODES][NUM_NODES], int fromNode, int newTable[NUM_NODES][NUM_NODES])
{
    for (int i = 0; i < NUM_NODES; i++)
    {
        for (int j = 0; j < NUM_NODES; j++)
        {
            if (table[i][j] > newTable[i][fromNode] + newTable[fromNode][j])
            {
                table[i][j] = newTable[i][fromNode] + newTable[fromNode][j];
            }
        }
    }
}

int main()
{
    int routingTable[NUM_NODES][NUM_NODES] = {
        {0, 10, INFINITY, INFINITY, 5},
        {10, 0, 1, INFINITY, INFINITY},
        {INFINITY, 1, 0, 4, INFINITY},
        {INFINITY, INFINITY, 4, 0, 2},
        {5, INFINITY, INFINITY, 2, 0}};

    int node = 0;

    printRoutingTable(routingTable, node);

    int newTable[NUM_NODES][NUM_NODES];
    for (int i = 0; i < NUM_NODES; i++)
    {
        for (int j = 0; j < NUM_NODES; j++)
        {
            newTable[i][j] = routingTable[i][j];
        }
    }

    int neighborNode = 1;
    int neighborTable[NUM_NODES][NUM_NODES] = {
        {0, 10, INFINITY, INFINITY, 5},
        {10, 0, 1, INFINITY, INFINITY},
        {INFINITY, 1, 0, 4, INFINITY},
        {INFINITY, INFINITY, 4, 0, 2},
        {5, INFINITY, INFINITY, 2, 0}};

    updateRoutingTable(routingTable, node, neighborTable);

    printRoutingTable(routingTable, node);

    return 0;
}