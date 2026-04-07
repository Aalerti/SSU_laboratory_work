#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Square {
    int x, y;
    Square *parent;

    Square(int x, int y, Square *parent = nullptr) : x(x), y(y), parent(parent) {
    }

    string toChessView() const {
        string s = "";
        s += (char) (x + 'A');
        s += (char) (y + '1');
        return s;
    }
};

struct node {
    Square *square;
    node *next;
};

struct Queue {
    node *head;
    node *tail;

    Queue() : head(nullptr), tail(nullptr) {
    }

    ~Queue() {
        while (head) {
            node *temp = head;
            head = head->next;
            delete temp->square;
            delete temp;
        }
    }

    void push(Square *val) {
        node *r = new node;
        r->square = val;
        r->next = nullptr;
        if (!head && !tail) {
            head = tail = r;
        } else {
            tail->next = r;
            tail = r;
        }
    }

    Square *pop() {
        if (!head) return nullptr;
        Square *i = head->square;
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

bool isValidHod(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int main() {
    string start;
    string end;
    cout << "Enter starting position (x,y): ";
    if (!(cin >> start)) return 0;
    cout << "Enter ending position (x,y): ";
    if (!(cin >> end)) return 0;

    if (start.size() < 2 || end.size() < 2) {
        cout << "Incorrect input!!!";
        return 1;
    }
    if (start[0] < 'A' || start[0] > 'H') {
        cout << "Incorrect input!!!";
        return 1;
    }
    if (start[1] < '1' || start[1] > '8') {
        cout << "Incorrect input!!!";
        return 1;
    }
    if (end[0] < 'A' || end[0] > 'H') {
        cout << "Incorrect input!!!";
        return 1;
    }
    if (end[1] < '1' || end[1] > '8') {
        cout << "Incorrect input!!!";
        return 1;
    }


    int s_x = start[0] - 'A';
    int s_y = start[1] - '1';
    int e_x = end[0] - 'A';
    int e_y = end[1] - '1';

    int move_x[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int move_y[8] = {-1, 1, -2, 2, -2, 2, -1, 1};


    Queue queue;
    bool visited[8][8] = {false};

    Square *square = new Square(s_x, s_y);
    queue.push(square);
    visited[s_x][s_y] = true;

    Square *target = nullptr;

    while (!queue.empty()) {
        Square *curr = queue.pop();

        if (curr->x == e_x && curr->y == e_y) {
            target = curr;
            break;
        }

        for (int i = 0; i < 8; i++) {
            int next_x = curr->x + move_x[i];
            int next_y = curr->y + move_y[i];

            if (isValidHod(next_x, next_y) && !visited[next_x][next_y]) {
                visited[next_x][next_y] = true;
                queue.push(new Square(next_x, next_y, curr));
            }
        }
    }


    if (target != nullptr) {
        vector<string> path;
        Square *curr_path = target;
        while (curr_path != nullptr) {
            path.push_back(curr_path->toChessView());
            curr_path = curr_path->parent;
        }

        reverse(path.begin(), path.end());


        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << '\n';
    }


    return 0;
}