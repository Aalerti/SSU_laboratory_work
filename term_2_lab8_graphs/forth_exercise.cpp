#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


map<int, vector<int> > init_graphs_on_adj_array() {
    int n, m;
    cout << "Enter number of Vertices: ";
    cin >> n;

    map<int, vector<int> > graph;

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

void print_raph_as_adj_array(const map<int, vector<int> > &graph) {
    for (auto [u, adj]: graph) {
        if (adj.empty()) {
            cout << u << ": isolated\n";
        } else {
            for (int v: adj) {
                cout << u << "->" << v << "\n";
            }
        }
    }
}


void dfs(map<int, vector<int> > &graph, set<int> &visited, int curr) {
    visited.insert(curr);
    for (auto vertice: graph[curr]) {
        if (!visited.contains(vertice)) {
            dfs(graph, visited, vertice);
        }
    }
}

int main() {
    map<int, vector<int> > graph = init_graphs_on_adj_array();

    print_raph_as_adj_array(graph);

    set<int> visited;


    dfs(graph, visited, graph.begin()->first);

    if (visited.size() == graph.size()) {
        cout << "Graph is connected" << "\n";
    }
    else {
        cout << "Graph is not connected" << "\n";
    }

    return 0;
}
