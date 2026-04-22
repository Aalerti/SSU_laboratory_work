#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

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


int bfs(map<int, vector<int> > &graph, set<int> &visited, queue<int> &q, map<int, int> &parent, int start, int target) {
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (!graph[u].empty()) {
            for (auto v: graph[u]) {
                if (!visited.contains(v)) {
                    q.push(v);
                    visited.insert(v);
                    parent[v] = u;
                }

                if (v == target) {
                    vector<int> path;
                    int curr = target;
                    while (curr != start) {
                        path.push_back(curr);
                        curr = parent[curr];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    for (int i = 0; i < path.size(); i++) {
                        cout << path[i] << " ";
                        if (i != path.size() - 1) cout << "-> ";
                    }
                    return parent.size();
                }


            }
        }
    }
    return -1;
}


int main() {
    map<int, vector<int> > graph = init_graphs_on_adj_array();
    print_raph_as_adj_array(graph);

    queue<int> q;
    set<int> visited;
    map<int,int> parent;



    cout << "Enter start and end vertice: ";
    int start, end;
    cin >> start >> end;

    if (!(graph.contains(start) && graph.contains(end))) {
        cout << "Start or end vertice don't exist";
        return 0;
    }


    q.push(start);
    visited.insert(start);

    int res = bfs(graph, visited, q, parent, start, end);

    if (res == -1) {
        cout << "Path not found\n";
        return 0;
    }

    cout << "Length: " << res << "\n";

    return 0;
}
