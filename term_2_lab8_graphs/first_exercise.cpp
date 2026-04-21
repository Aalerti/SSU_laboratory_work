#include <iostream>
#include <vector>
#include <map>
#include <set>


using namespace std;

int main() {
    int n,m;
    cout << "Enter number of Vertices: ";
    cin >> n;

    set<int> vertices;
    cout << "Enter vertices:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        vertices.insert(x);
    }

    cout << "Enter number of Edges: ";
    cin >> m;

    cout << "Enter the edges in the graph as 'vertice_1 vertice_2':\n";

    map<int, vector<int>> graph;


    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Enter a chosen vertice: ";
    int k;
    cin >> k;

    if (!vertices.contains(k)) {
        cout << k << " not found\n";
        return 0;
    }

    vector<int> adj = graph[k];
    vertices.erase(k);
    for (int v : adj) {
        vertices.erase(v);
    }
    cout << "Not adj vertices: ";
    for (int i: vertices) {
        cout << i << " ";
    }
}


