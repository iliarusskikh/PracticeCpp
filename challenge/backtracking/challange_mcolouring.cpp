#include <iostream>
#include <vector>


using namespace std;

// Function to check if it's safe to color the current vertex
// with the given color
bool issafe(int vertex, int col, vector<int> adj[], vector<int> &color) {
    for (auto it : adj[vertex]) {
        // If adjacent vertex has the same color, not safe
        if (color[it] != -1 && col == color[it])
            return false;
    }
    return true;
}

// Recursive function to try all colorings
bool cancolor(int vertex, int m, vector<int> adj[], vector<int> &color) {
    // If all vertices are colored successfully
    if (vertex == color.size())
        return true;

    // Try all colors from 0 to m-1
    for (int i = 0; i < m; i++) {
        if (issafe(vertex, i, adj, color)) {
            color[vertex] = i;
            if (cancolor(vertex + 1, m, adj, color))
                // If the rest can be colored, return true
                return true;
            color[vertex] = -1;
        }
    }
    
    // No valid coloring found
    return false;
}

bool graphColoring(int v, vector<vector<int>> &edges, int m) {
    vector<int> adj[v];

    // Build adjacency list from edges
    for (auto it : edges) {
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }

    vector<int> color(v, -1);
    return cancolor(0, m, adj, color);
}

int main() {
    int V = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2},{0,3}, {1, 3}, {2, 3}};
    int m = 3;

    // Check if the graph can be colored with m colors
    // such that no adjacent nodes share the same color
    cout << (graphColoring(V, edges, m) ? "true" : "false") << endl;

    return 0;
}
