//You are given:
//A graph with N vertices
//M colors
//The graph is represented as an adjacency matrix
//O(M^N)


//Determine if it is possible to color the graph such that:
//
//1. Every vertex gets exactly one color
//2. No two adjacent vertices have the same color


#include <iostream>
#include <vector>

bool isSafe(int vertex, std::vector<std::vector<int>>& graph, std::vector<int>& color, int chosenColor)
{
    for (int neighbor = 0; neighbor < graph.size(); neighbor++) //checking children of each parent basicall
    {
        if (graph[vertex][neighbor] == 1 && color[neighbor] == chosenColor)//it is 1 if connection exists; if so, ensure its different color
        {
            return false;
        }
    }

    return true; //all children checked, all valid after assigning a color to parent VERTEX
}



bool solve(int vertex, std::vector<std::vector<int>>& graph, std::vector<int> color, int colors){
    
    int n = graph.size();
    
    // base case: all vertices colored
    if (vertex == n) //
        return true;
    
    // try all colors
    //0 - no color assigned yet
    for (int c = 1; c <= colors; c++)// 1, 2, 3
    {
        if (isSafe(vertex, graph, color, c))
        {
            color[vertex] = c;     // if safe, apply the color and recruse with the next vertex parent DO

            if (solve(vertex + 1, graph, color, colors))
                return true;

            color[vertex] = 0;     // BACKTRACK
            
        } //false if any children have that chosen color already
    }
    
    
    
    
}


bool graphColoring(std::vector<std::vector<int>>& graph, int colors){
    vector<int> color(colors, 0); // 0 = unassigned

    return solve(0, graph, color, colors);
}


int main() {
    // Example graph (4 vertices)
    // 0---1
    // |  /|
    // | / |
    // 2---3

    vector<vector<int>> graph =
    {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    int colors = 3; // number of colors

    if (graphColoring(graph, colors))
        std::cout << "Coloring is possible\n";
    else
        std::cout << "Coloring is NOT possible\n";

    return EXIT_SUCCESS;
}
