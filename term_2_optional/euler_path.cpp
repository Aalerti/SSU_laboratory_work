#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>

using namespace std;

map<int, vector<int>> init_graphs_on_adj_array() {
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

    cout << "Enter the edges in the graph as 'vertice_1 vertice_2':\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return graph;
}

void print_graph_as_adj_array(const map<int, vector<int>>& graph) {
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

void dfs_connectivity(map<int, vector<int>>& graph, set<int>& visited, int curr) {
    visited.insert(curr);
    for (int vertice : graph[curr]) {
        if (!visited.contains(vertice)) {
            dfs_connectivity(graph, visited, vertice);
        }
    }
}

bool is_connected(map<int, vector<int>>& graph) {
    set<int> visited;

    int start = -1;
    for (auto& [u, adj] : graph) {
        if (!adj.empty()) {
            start = u;
            break;
        }
    }

    if (start == -1) return true;

    dfs_connectivity(graph, visited, start);
    for (auto& [u, adj] : graph) {
        if (!adj.empty() && !visited.contains(u)) {
            return false;
        }
    }
    return true;
}

void dfs_count(map<int, vector<int>>& graph, set<int>& visited, int curr) {
    visited.insert(curr);
    for (int vertice : graph[curr]) {
        if (!visited.contains(vertice)) {
            dfs_count(graph, visited, vertice);
        }
    }
}

bool is_bridge(map<int, vector<int>>& graph, int u, int v) {
    set<int> visited_before;
    dfs_count(graph, visited_before, u);
    int count_before = visited_before.size();

    erase(graph[u], v);
    erase(graph[v], u);

    set<int> visited_after;
    dfs_count(graph, visited_after, u);
    int count_after = visited_after.size();

    graph[u].push_back(v);
    graph[v].push_back(u);
    return count_after < count_before;
}

vector<int> fleury(map<int, vector<int>>& graph, int start) {
    vector<int>  euler_path;
     euler_path.push_back(start);

    int curr = start;

    while (!graph[curr].empty()) {
        bool moved = false;
        for (int v : graph[curr]) {
            if (!is_bridge(graph, curr, v) || graph[curr].size() == 1) {
                erase(graph[curr], v);
                erase(graph[v], curr);

                 euler_path.push_back(v);
                curr = v;
                moved = true;
                break;
            }
        }

        if (!moved && !graph[curr].empty()) {
            int v = graph[curr][0];
            erase(graph[curr], v);
            erase(graph[v], curr);
             euler_path.push_back(v);
            curr = v;
        }
    }

    return  euler_path;
}

int main() {
    map<int, vector<int>> graph = init_graphs_on_adj_array();

    cout << "\nGraph:\n";
    print_graph_as_adj_array(graph);
    vector<int> odd_degree_vertices;
    for (auto& [u, adj] : graph) {
        if (adj.size() % 2 != 0) {
            odd_degree_vertices.push_back(u);
        }
    }

    int odd_count = odd_degree_vertices.size();

    if (!is_connected(graph)) {
        cout << "\nEulerian path/cycle does not exist: graph is not connected\n";
        return 0;
    }




    bool has_euler_cycle = (odd_count == 0);
    bool has_euler_path  = (odd_count == 2);

    if (!has_euler_cycle && !has_euler_path) {
        cout << "\nEulerian path/cycle does not exist: "
             << odd_count << " vertices have odd degree (need 0 or 2)\n";
        return 0;
    }
    int start;
    if (has_euler_cycle) {
        start = graph.begin()->first;
        cout << "\nEulerian cycle exists. Starting from vertice " << start << ":\n";
    } else {
        start = odd_degree_vertices[0];
        cout << "\nEulerian path exists. Starting from vertice " << start << ":\n";
    }

    map<int, vector<int>> graph_copy = graph;
    vector<int> euler_path = fleury(graph_copy, start);

    for (int i = 0; i < euler_path.size(); i++) {
        cout << euler_path[i];
        if (i != euler_path.size() - 1) cout << " -> ";
    }
    cout << "\n";

    return 0;
}