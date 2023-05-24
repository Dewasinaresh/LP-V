/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
void bfs(std::vector<std::vector<int>>& graph, int source) {
    int numVertices = graph.size();
    std::vector<bool> visited(numVertices, false);
    std::queue<int> q;

    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        std::cout << currentVertex << " ";

        #pragma omp parallel for
        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                #pragma omp critical
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
}
int main()
{
    int numVertices, numEdges;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;
    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, 0));

    std::cout << "Enter the edges: " << std::endl;
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // assuming an undirected graph
    }

    int source;
    std::cout << "Enter the source node: ";
    std::cin >> source;

    std::cout << "BFS Traversal: ";
    bfs(graph, source);
    std::cout << std::endl;

    
    return 0;
}
