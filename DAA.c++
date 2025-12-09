#include <iostream>
#include <algorithm>
using namespace std;

#define INF 999999
#define MAX 100

//  Edge structure for Kruskal 
struct Edge {
    int u, v, w;
};

//  DSU (Disjoint Set Union) for Kruskal 
int parent[MAX];
int rnk[MAX];

void makeSet(int n) {
    for(int i=0; i<n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int findSet(int x) {
    if(parent[x] != x)
        parent[x] = findSet(parent[x]);
    return parent[x];
}

void unionSet(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if(x != y) {
        if(rnk[x] < rnk[y]) swap(x, y);
        parent[y] = x;
        if(rnk[x] == rnk[y]) rnk[x]++;
    }
}

//PRIM'S ALGORITHM (Adjacency Matrix)

void primMST(int n, int graph[MAX][MAX]) {
    int key[MAX];        // store minimum weight to connect
    bool inMST[MAX];     // track included nodes
    int parentNode[MAX]; // store MST edges

    for(int i=0; i<n; i++) {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0; // start from node 0
    parentNode[0] = -1;

    for(int i=0; i<n-1; i++) {
        int minKey = INF, u = -1;

        // Pick the smallest key vertex not in MST
        for(int v=0; v<n; v++) {
            if(!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        // Update adjacent nodes
        for(int v=0; v<n; v++) {
            if(graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parentNode[v] = u;
            }
        }
    }

    cout << "\nPrim's MST:\n";
    for(int i=1; i<n; i++) {
        cout << parentNode[i] << " - " << i 
             << "  weight=" << graph[i][parentNode[i]] << endl;
    }
}

//KRUSKAL'S ALGORITHM (Edge List)

void kruskalMST(Edge edges[], int E, int n) {
    sort(edges, edges + E, [](Edge a, Edge b){
        return a.w < b.w;
    });

    makeSet(n);

    cout << "\nKruskal's MST:\n";
    int count = 0;

    for(int i=0; i<E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if(findSet(u) != findSet(v)) {
            cout << u << " - " << v << "  weight=" << edges[i].w << endl;
            unionSet(u, v);
            count++;
            if(count == n-1) break;
        }
    }
}

//MAIN

int main() {
    int n = 5;

    // Simple adjacency matrix (0 means no edge)
    int graph[MAX][MAX] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 0},
        {0, 5, 7, 0, 0}
    };

    // Edge list for Kruskal
    Edge edges[MAX] = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}
    };
    int E = 6;

    primMST(n, graph);
    kruskalMST(edges, E, n);

    return 0;
}