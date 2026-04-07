#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    int id;
    Vertex *parent;

    Vertex(int id, Vertex *parent = nullptr) : id(id), parent(parent) {}
};


struct node {
    Vertex *vertex;
    node *next;
};

struct Queue {
    node *head;
    node *tail;

    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while (head) {
            node *temp = head;
            head = head->next;
            delete temp->vertex;
            delete temp;
        }
    }

    void push(Vertex *val) {
        node *r = new node;
        r->vertex = val;
        r->next = nullptr;
        if (!head && !tail) {
            head = tail = r;
        } else {
            tail->next = r;
            tail = r;
        }
    }

    Vertex *pop() {
        if (!head) return nullptr;
        Vertex *i = head->vertex;
        node *r = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete r;
        return i;
    }

    bool empty() const {
        return head == nullptr;
    }
};

struct Stack {
    node *head;

    Stack() : head(nullptr) {}

    ~Stack() {
        while (head) {
            node *temp = head;
            head = head->next;
            delete temp->vertex;
            delete temp;
        }
    }

    void push(Vertex *val) {
        node *r = new node;
        r->vertex = val;
        r->next = head;
        head = r;
    }

    Vertex *pop() {
        if (!head) return nullptr;
        Vertex *i = head->vertex;
        node *r = head;
        head = head->next;
        delete r;
        return i;
    }

    bool empty() const {
        return head == nullptr;
    }
};


void BFS(int start, const vector<vector<int>>& list_adj) {
    cout << "BFS: ";
    Queue q;
    vector<bool> visited(list_adj.size(), false);

    q.push(new Vertex(start));
    visited[start] = true;

    while (!q.empty()) {
        Vertex *curr = q.pop();
        cout << curr->id << " ";

        for (int neighbor : list_adj[curr->id]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(new Vertex(neighbor, curr));
            }
        }
        delete curr;
    }
    cout << "\n";
}


void DFS_non_recursive(int start, const vector<vector<int>>& list_adj) {
    cout << "DFS: ";
    Stack s;
    vector<bool> visited(list_adj.size(), false);

    s.push(new Vertex(start));

    while (!s.empty()) {
        Vertex *curr = s.pop();

        if (!visited[curr->id]) {
            visited[curr->id] = true;
            cout << curr->id << " ";

            for (int i = list_adj[curr->id].size() - 1; i >= 0; --i) {
                int neighbor = list_adj[curr->id][i];
                if (!visited[neighbor]) {
                    s.push(new Vertex(neighbor, curr));
                }
            }
        }
        delete curr;
    }
    cout << "\n";
}

int main() {
    int n, m;
    cout << "Enter the number of vertices (n) and edges (m): ";
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n);

    cout << "Enter " << m << " pair of connected vertices (from 0 to " << n - 1 << "):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start_node;
    cout << "Enter the starting vertex for traversal: ";
    cin >> start_node;

    cout << "\n--- Traversal Results ---" << endl;
    BFS(start_node, adj);
    DFS_non_recursive(start_node, adj);

    return 0;
}