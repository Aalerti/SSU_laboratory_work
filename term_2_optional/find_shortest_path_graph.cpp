#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

map<int, vector<pair<int, int>>> init_weighted_graph_on_adj_array() {
    int n, m;
    cout << "Enter number of Vertices: ";
    cin >> n;
    map<int, vector<pair<int, int>>> graph;

    cout << "Enter vertices:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        graph[x];
    }

    cout << "Enter number of Edges: ";
    cin >> m;

    cout << "Enter the edges as 'vertice_1 vertice_2 weight':\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    return graph;
}

void print_graph_as_adj_array(const map<int, vector<pair<int, int>>>& graph) {
    for (auto [u, adj] : graph) {
        if (adj.empty()) {
            cout << u << ": isolated\n";
        } else {
            for (auto [v, w] : adj) {
                cout << u << " -(" << w << ")-> " << v << "\n";
            }
        }
    }
}

vector<int> restore_path(map<int, int>& parent, int start, int target) {
    vector<int> path;
    int curr = target;

    while (curr != start) {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

pair<map<int, int>, map<int, int>> bellman_ford(
    map<int, vector<pair<int, int>>>& graph,
    int start
) {
    map<int, int> dist;
    for (auto& [u, adj] : graph) {
        dist[u] = INT_MAX;
    }
    dist[start] = 0;

    map<int, int> parent;
    parent[start] = -1;
    int n = graph.size();

    for (int i = 0; i < n - 1; i++) {
        for (auto& [u, adj] : graph) {
            if (dist[u] == INT_MAX) continue;
            for (auto [v, w] : adj) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    for (auto& [u, adj] : graph) {
        if (dist[u] == INT_MAX) continue;
        for (auto [v, w] : adj) {
            if (dist[u] + w < dist[v]) {
                cout << "Graph contains a negative cycle\n";
                return {{}, {}};
            }
        }
    }
    return {dist, parent};
}

int main() {
    map<int, vector<pair<int, int>>> graph = init_weighted_graph_on_adj_array();
    cout << "\nGraph (adjacency list):\n";
    print_graph_as_adj_array(graph);


    cout << "\nEnter start vertice: ";
    int start;
    cin >> start;


    if (!graph.contains(start)) {
        cout << "Start vertice doesn't exist\n";
        return 0;
    }

    auto [dist, parent] = bellman_ford(graph, start);

    if (dist.empty()) return 0;

    cout << "\nShortest paths from vertice " << start << ":\n";
    for (auto& [v, d] : dist) {
        if (v == start) continue;
        cout << "\nTo vertice " << v << ": ";

        if (d == INT_MAX) {
            cout << "unreachable\n";
        } else {
            cout << "distance = " << d << "\n";
            vector<int> path = restore_path(parent, start, v);
            cout << "Path: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i != path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
    }

    return 0;
}