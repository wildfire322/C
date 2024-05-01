#include<stdio.h>
#include<stdlib.h>
#define inf 101

// Array to store the shortest distance from the source vertex to each vertex
int distance[1001];

// Array to store the test cases
int test[1001];

// Array to keep track of visited vertices
int visited[1001];

// Structure to represent a graph
typedef struct {
    int nv; // Number of vertices
    int ne; // Number of edges
    int e[1001][1001]; // Adjacency matrix to store edge weights
} *graph;

// Function to create a graph
graph create(int nv, int ne) {
    graph g = (graph)malloc(sizeof(graph));
    g->nv = nv;
    g->ne = ne;

    // Initialize all edge weights to infinity
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            g->e[i][j] = inf;
        }
    }
    return g;
}

// Function to find the vertex with minimum distance from the source vertex
int findmin(graph g) {
    int min = inf;
    int minindex = 0;
    for (int i = 0; i < g->nv; i++) {
        if (!visited[i] && distance[i] < min) {
            min = distance[i];
            minindex = i;
        }
    }
    return minindex;
}

// Function to perform Dijkstra's algorithm
int dijkstra(graph g) {
    int kk, z;

    // Read the test case values and initialize distance and visited arrays
    for (int i = 0; i < g->nv; i++) {
        scanf("%d", &kk);
        distance[i] = inf;
        visited[i] = 0;
        test[i] = kk - 1;
    }

    // Set the distance of the source vertex to 0 and mark it as visited
    distance[test[0]] = 0;
    visited[test[0]] = 1;

    // Update the distance array with the weights of the edges connected to the source vertex
    for (int i = 0; i < g->nv; i++) {
        if (i != test[0] && g->e[test[0]][i] != inf) {
            distance[i] = g->e[test[0]][i];
        }
    }

    // Perform Dijkstra's algorithm for the remaining vertices
    for (int i = 1; i < g->nv; i++) {
        z = findmin(g);

        // If the distance of the current vertex is not equal to the distance of the previous vertex, return 0
        if (distance[z] != distance[test[i]]) {
            return 0;
        }

        // Mark the current vertex as visited
        visited[test[i]] = 1;

        // Update the distance array with the weights of the edges connected to the current vertex
        for (int j = 0; j < g->nv; j++) {
            if (!visited[j] && g->e[test[i]][j] != inf && distance[test[i]] + g->e[test[i]][j] < distance[j]) {
                distance[j] = distance[test[i]] + g->e[test[i]][j];
            }
        }
    }
    return 1;
}

int main() {
    int m, n;

    // Read the number of vertices and edges
    scanf("%d %d", &n, &m);

    // Create a graph
    graph g = create(n, m);

    // Read the edges and their weights
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g->e[a - 1][b - 1] = c;
        g->e[b - 1][a - 1] = c;
    }

    int k, u;

    // Read the number of test cases
    scanf("%d", &k);

    // Perform Dijkstra's algorithm for each test case
    for (int i = 0; i < k; i++) {
        u = dijkstra(g);
        if (u == 1) {
            printf("Yes\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}