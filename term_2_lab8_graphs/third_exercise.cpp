#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


map<int, vector<int>> init_dir_graph_on_adj_array() {
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

    cout << "Enter the edges in the graph as 'vertice_1 vertice_2'\nIt means vertice_1 -> vertice_2:\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    return graph;
}

map<int, int> compute_in_degree(const map<int, vector<int>>& graph) {
    map<int, int> in_degree;
    for (auto& [u, adj] : graph) {
        in_degree[u];
        for (int v : adj) {
            in_degree[v]++;
        }
    }
    return in_degree;
}

void print_dir_graph_as_adj_array(const map<int, vector<int>> &graph, map<int, int> &in_degree) {
    for (auto [u, adj] : graph) {
        if (adj.empty() && in_degree[u] == 0) {
            cout << u << ": isolated\n";
        } else {
            for (int v : adj) {
                cout << u << "->" << v << "\n";
            }
        }
    }
}

int main() {
    map<int, vector<int>> graph = init_dir_graph_on_adj_array();

    map<int,int > in_degree = compute_in_degree(graph);

    print_dir_graph_as_adj_array(graph, in_degree);

    cout << "Degree of vertices:\n";
    for (auto [u, out_degree_arr]: graph) {
        cout << "Vertice: " << u << ": " << in_degree[u] + out_degree_arr.size() << "\n";
    }

    return 0;
}