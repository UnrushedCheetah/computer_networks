#include <stdio.h>

#define N 4
#define INF 999

void readCost (int cost[N][N]) {
    printf("\nEnter the cost matrix: \n");

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
}

void initialize(int cost[N][N], int dist[N][N], int nextHop[N][N]) {

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            dist[i][j] = cost[i][j];

            if(i == j) {
                nextHop[i][j] = i;
            }
            else if(cost[i][j] != INF) {
                nextHop[i][j] = j;
            }
            else {
                nextHop[i][j] = -1;
            }
        }
    }
}

void calculateRoutes (int dist[N][N], int nextHop[N][N]) {
    int updated;

    do {
        updated = 0;

        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                for(int k=0; k<N; k++) {
                    
                    if(dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                        
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];

                        updated = 1;
                    }
                }
            }
        }
    } while(updated == 0);
}

void numToChar(int a) {
    if(a == 0){
        printf("A\t\t");
    }
    else if (a == 1) {
        printf("B\t\t");
    }
    else if (a == 2) {
        printf("C\t\t");
    }
    else if (a == 3) {
        printf("D\t\t");
    }
}

void displayTables(int dist[N][N], int nextHop[N][N]) {
    
    printf("\nRouting Tables: \n");

    for(int i=0; i<N; i++) {

        printf("\nRouter ");
        numToChar(i);
        printf("\n");

        printf("Destination\tCost\tNext Hop\n");

        for (int j = 0; j < N; j++) {

            numToChar(j);

            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);

            if (nextHop[i][j] == -1)
                printf("-\n");
            else
                numToChar(nextHop[i][j]);
                printf("\n");
        }
    }
}

int main () {

    int cost[N][N], dist[N][N], nextHop[N][N];

    readCost(cost);
    initialize(cost, dist, nextHop);
    calculateRoutes(dist, nextHop);
    displayTables(dist, nextHop);


return 0;
}