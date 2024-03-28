#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 10 // Maximum number of cities
#define INFINITY_COST INT_MAX

int graph[MAX_N][MAX_N]; // Distance matrix
int visited[MAX_N];
int min_cost = INT_MAX;
int N; // Number of cities

void tsp(int current_city, int count, int cost) {
    if (count == N) {
        // If all cities are visited, update min_cost if this path is shorter
        min_cost = (cost + graph[current_city][0] < min_cost) ? cost + graph[current_city][0] : min_cost;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[current_city][i] != INFINITY_COST) {
            visited[i] = 1;
            tsp(i, count + 1, cost + graph[current_city][i]);
            visited[i] = 0; // Backtrack
        }
    }
}

int main() {
    printf("Enter the number of cities (maximum %d): ", MAX_N);
    scanf("%d", &N);

    if (N <= 0 || N > MAX_N) {
        printf("Invalid number of cities. Please enter a number between 1 and %d.\n", MAX_N);
        return 1;
    }

    printf("Enter the distance matrix for %d cities:\n", N);
    printf("Use %d for infinity:\n", INFINITY_COST);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == INFINITY_COST) {
                graph[i][j] = INT_MAX; // Replace INFINITY_COST with INT_MAX for calculations
            }
        }
    }

    for (int i = 0; i < N; i++) {
        visited[i] = 0;
    }
    visited[0] = 1; // Start from the first city

    tsp(0, 1, 0); // Start from the first city, with 1 city visited, and 0 cost so far

    printf("Minimum cost of TSP tour: %d\n", min_cost);

    return 0;
}
