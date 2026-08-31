#include <stdio.h>

#define N 4
#define INF 999

void readCost(int cost[N][N]) {
    printf("\nEnter the cost matrix:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
}

void initialize(int cost[N][N], int dist[N][N], int nextHop[N][N]) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            dist[i][j] = cost[i][j];

            if (i == j) {
                nextHop[i][j] = i;
            }
            else if (cost[i][j] != INF) {
                nextHop[i][j] = j;
            }
            else {
                nextHop[i][j] = -1;
            }
        }
    }
}

void calculateRoutes(int dist[N][N], int nextHop[N][N]) {

    int updated;

    do {
        updated = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {

                    if (dist[i][k] != INF &&
                        dist[k][j] != INF &&
                        dist[i][j] > dist[i][k] + dist[k][j]) {

                        dist[i][j] = dist[i][k] + dist[k][j];

                        nextHop[i][j] = nextHop[i][k];

                        updated = 1;
                    }
                }
            }
        }

    } while (updated == 1);
}

void numToChar(int a) {

    if (a == 0) {
        printf("A");
    }
    else if (a == 1) {
        printf("B");
    }
    else if (a == 2) {
        printf("C");
    }
    else if (a == 3) {
        printf("D");
    }
}

void displayTables(int dist[N][N], int nextHop[N][N]) {

    printf("\nRouting Tables:\n");

    for (int i = 0; i < N; i++) {

        printf("\nRouter ");
        numToChar(i);
        printf("\n");

        printf("Destination\tCost\tNext Hop\n");

        for (int j = 0; j < N; j++) {

            numToChar(j);
            printf("\t\t");

            if (dist[i][j] == INF) {
                printf("INF\t");
            }
            else {
                printf("%d\t", dist[i][j]);
            }

            if (nextHop[i][j] == -1) {
                printf("-\n");
            }
            else {
                numToChar(nextHop[i][j]);
                printf("\n");
            }
        }
    }
}

/* Function 1: Take source and destination */
void getNodes(int *source, int *destination) {

    printf("\nEnter source node (A=0, B=1, C=2, D=3): ");
    scanf("%d", source);

    printf("Enter destination node (A=0, B=1, C=2, D=3): ");
    scanf("%d", destination);
}

/* Function 2: Calculate and print shortest path */
void printShortestPath(int source, int destination,
                       int dist[N][N], int nextHop[N][N]) {

    if (dist[source][destination] == INF) {

        printf("\nNo path exists between ");
        numToChar(source);
        printf(" and ");
        numToChar(destination);
        printf(".\n");

        return;
    }

    printf("\nShortest path length: %d\n",
           dist[source][destination]);

    printf("Shortest path: ");

    int current = source;

    numToChar(current);

    while (current != destination) {

        current = nextHop[current][destination];

        printf(" -> ");

        numToChar(current);
    }

    printf("\n");
}

int main() {

    int cost[N][N];
    int dist[N][N];
    int nextHop[N][N];

    int source;
    int destination;

    readCost(cost);

    initialize(cost, dist, nextHop);

    calculateRoutes(dist, nextHop);

    displayTables(dist, nextHop);

    getNodes(&source, &destination);

    printShortestPath(source, destination, dist, nextHop);

    return 0;
}
