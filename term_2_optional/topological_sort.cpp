#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;


map<int, vector<int>> init_dir_graph_on_adj_array() {
    int n, m;
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


void print_dir_graph_as_adj_array(const map<int, vector<int>>& graph, map<int, int>& in_degree) {
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

vector<int> topological_sort(map<int, vector<int>>& graph) {
    map<int, int> in_degree = compute_in_degree(graph);
    queue<int> q;
    for (auto& [u, degree] : in_degree) {
        if (degree == 0) {
            q.push(u);
        }
    }

    vector<int> topological_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topological_order.push_back(u);

        for (int v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (topological_order.size() != graph.size()) {
        return {};
    }

    return topological_order;
}

int main() {
    map<int, vector<int>> graph = init_dir_graph_on_adj_array();

    map<int, int> in_degree = compute_in_degree(graph);

    cout << "\nGraph (adjacency list):\n";
    print_dir_graph_as_adj_array(graph, in_degree);

    cout << "\nDegree of vertices:\n";
    for (auto [u, out_degree_arr] : graph) {
        cout << "Vertice: " << u << ": " << in_degree[u] + out_degree_arr.size() << "\n";
    }

    cout << "\nTopological sort (Kahn's Algorithm):\n";

    vector<int> result = topological_sort(graph);

    if (result.empty()) {
        cout << "Topological sort is not possible: graph contains a cycle\n";
        return 0;
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1) cout << " -> ";
    }
    cout << "\n";


    cout << "\nVerification:\n";
    map<int, int> position;
    for (int i = 0; i < result.size(); i++) {
        position[result[i]] = i;
    }

    for (auto& [u, adj] : graph) {
        for (int v : adj) {
            if (position[u] >= position[v]) {
                cout << "ERROR: edge " << u << "->" << v
                     << " violates topological order!\n";

            }
        }
    }

    return 0;
}