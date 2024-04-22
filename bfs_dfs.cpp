#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph
{
private:
    /* data */
    int numVertices;         // Number of vertices
    vector<vector<int>> adj; // Adjacency list
public:
    Graph(int vertices) : numVertices(vertices), adj(numVertices) {}

    void addEdge(int src, int dest)
    {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    void viewGraph()
    {
        cout << "Graph : " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            /* code */
            cout << "Vertices :" << i << " ->";
            for (int neighbour : adj[i])
            {
                /* code */
                cout << neighbour << " ";
            }
            cout << endl;
        }
    }

    void bfs(int startVertex)
    {
        vector<bool> visited(numVertices, false);

        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int current = q.front();

            q.pop();

            cout << current << " ";

#pragma omp parallel for
            for (int neighbour : adj[current])
            {
                /* code */
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }

            /* code */
        }
    }

    void dfs(int startVertex)
    {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty())
        {
            /* code */
            int current = s.top();
            s.pop();

            cout << current << " ";

#pragma omp parallel for
            for (int neighbour : adj[current])
            {
                /* code */
                if (!visited[neighbour])
                {
                    /* code */
                    visited[neighbour] = true;
                    s.push(neighbour);
                }
            }
        }
    }
};

int main()
{

    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Create a graph with the specified number of vertices
    Graph graph(numVertices);
    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";
    for (int i = 0; i < numEdges; i++)
    {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    // View the graph
    graph.viewGraph();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    cout << "Breadth First Search (BFS): ";
    graph.bfs(startVertex);
    cout << endl;

    cout << "Depth First Search (DFS): ";
    graph.dfs(startVertex);
    cout << endl;

    return 0;
    return 0;
}

// Here's a sample input :
// vertices = 6, edges = 7, edges = ["0 1", "0 2", "1 2", "1 3", "2 3", "3 4", "4 5"], starting vertex = 0