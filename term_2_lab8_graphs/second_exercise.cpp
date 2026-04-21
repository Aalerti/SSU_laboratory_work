#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


map<int, vector<int>> init_graphs_on_adj_array() {
    int n,m;
    cout << "Enter number of Vertices: ";
    cin >> n;

    map<int, vector<int>> graph;

    cout << "Enter vertices:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        graph[x];
    }

    cout << "Enter number of Edges: ";
    cin >> m;

    cout << "Enter the edges in the graph as 'vertice_1 vertice_2':\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return graph;
}

void print_graph_as_adj_array(const map<int, vector<int>> &graph) {
    for (auto [u, adj] : graph) {
        if (adj.empty()) {
            cout << u << ": isolated\n";
        } else {
            for (int v : adj) {
                cout << u << "->" << v << "\n";
            }
        }
    }
}

int main() {
    map<int, vector<int>> graph = init_graphs_on_adj_array();

    cout << "Enter edge you want to delete: 'vertice_1 vertice_2'\n";
    int v, u;
    cin >> v >> u;


    if (!(graph.contains(v) && graph.contains(u))) {
        cout << "One of the vertices doesn't exist\n";
        return 1;
    }

    vector<int>& adj = graph[v];
    if (find(adj.begin(), adj.end(), u) == adj.end()) {
        cout << "This edge does not exist\n";
        return 1;
    }

    erase(graph[v], u);
    erase(graph[u], v);


    print_graph_as_adj_array(graph);

    return 0;
}

