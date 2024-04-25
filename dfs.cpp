#include<iostream>
#include<omp.h>
#include<stack>
#include<vector>
using namespace std;

class Graph{
    private:
        int numVertices;
        vector<vector<int>> adj;
    public:
        Graph(int vertices) : numVertices(vertices), adj(numVertices){}

        void addEdge(int src, int dest){
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }

        void viewGraph(){
            cout << "Graph: "<<endl;
            for (int i=0; i<numVertices; i++){
                cout<< "Vertices"<<i<<" -> ";
                for(int neighbor : adj[i]){
                    cout<< neighbor << " ";
                }
                cout<<endl;
            }
        }

        void dfs(int startVertex){
            vector<bool> visited(numVertices, false);
            stack<int> s;
            visited[startVertex] = true;
            s.push(startVertex);

            while(!s.empty()){
                int current = s.top();
                s.pop();
                cout << current << " ";
                
                #pragma omp parallel for
                for(int neighbor : adj[current]){
                    if(!visited[neighbor]){
                        visited[neighbor] = true;
                        s.push(neighbor);
                    }
                }
            }
        }
};

int main(){

    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    Graph graph(numVertices);
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout<< "Enter the edges (source destination): \n";
    for (int i=0; i < numEdges; i++){
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    graph.viewGraph();

    int startVertex;
    cout<< "Enter the starting vertex: ";
    cin>> startVertex;

    cout<<"PARALLEL DFS: ";
    graph.dfs(startVertex);

    return 0;
}

// How to execute :
// 1. RUN THIS => g++ -Fopenmp dfs.cpp -o dfs
// 2. THEN THIS => ./dfs

// Here's a sample input :
// vertices = 6, edges = 7, edges = ["0 1", "0 2", "1 2", "1 3", "2 3", "3 4", "4 5"], starting vertex = 0