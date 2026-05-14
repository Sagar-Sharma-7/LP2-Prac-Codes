#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {

    int vertices;
    vector<vector<int>> adj;

public:

    Graph(int v) {
        vertices = v;
        adj.resize(v);
    }

    void addEdge(int u, int v) {

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void recursiveDFS(int node, vector<bool>& visited) {

        visited[node] = true;

        cout << node << " ";

        for (int neighbor : adj[node]) {

            if (!visited[neighbor]) {

                recursiveDFS(neighbor, visited);
            }
        }
    }

    void iterativeDFS(int start) {

        vector<bool> visited(vertices, false);

        stack<int> st;

        st.push(start);

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            if (!visited[node]) {

                visited[node] = true;

                cout << node << " ";
                for (int i = adj[node].size() - 1; i >= 0; i--) {

                    int neighbor = adj[node][i];

                    if (!visited[neighbor]) {

                        st.push(neighbor);
                    }
                }
            }
        }
    }

    void BFS(int start) {

        vector<bool> visited(vertices, false);

        queue<int> q;

        visited[start] = true;

        q.push(start);

        while (!q.empty()) {

            int current = q.front();
            q.pop();

            cout << current << " ";

            for (int neighbor : adj[current]) {

                if (!visited[neighbor]) {

                    visited[neighbor] = true;

                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    Graph g(vertices);

    cout << "Enter edges (u v):" << endl;

    for (int i = 0; i < edges; i++) {

        int u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    vector<bool> visited(vertices, false);

    cout << "\nRecursive DFS Traversal: ";

    g.recursiveDFS(start, visited);

    cout << "\nBFS Traversal: ";

    g.BFS(start);

    return 0;
}


/*

========================
DUMMY INPUT
========================

Enter number of vertices: 5
Enter number of edges: 4

Enter edges (u v):

0 1
0 3
1 2
3 4

Enter starting vertex: 0


========================
OUTPUT
========================

DFS Traversal: 0 1 2 3 4

BFS Traversal: 0 1 3 2 4


=====================================================
THEORY OF BREAKING POINTS / LIMITATIONS OF DFS & BFS
=====================================================

-------------------
1. DFS LIMITATIONS
-------------------

A) Stack Overflow

DFS uses recursion.
If graph depth becomes extremely large,
the recursion stack becomes full.

Example:

1 -> 2 -> 3 -> 4 -> ... -> 100000

Program may crash.

Reason:
System stack memory gets exhausted.


B) Infinite Loop in Cyclic Graph

If visited array is not used,
DFS may revisit same nodes forever.

Example:

0 -> 1 -> 0 -> 1 -> 0 ...

Program never stops.


C) Does Not Guarantee Shortest Path

DFS goes deep first.

It may find a longer path before shorter one.

Example:

A -> B -> C -> Goal
A -> Goal

DFS may unnecessarily travel deeper.


D) Poor for Wide Graphs

DFS may completely ignore nearby solutions
while exploring a deep branch.


-------------------
2. BFS LIMITATIONS
-------------------

A) High Memory Usage

BFS stores all nodes level by level in queue.

If graph is very wide:

Level 1 -> 10 nodes
Level 2 -> 100 nodes
Level 3 -> 1000 nodes

Memory usage increases rapidly.


B) Slow for Deep Solutions

If target node is very deep,
BFS still explores all previous levels first.

Can become inefficient.


C) Not Suitable for Infinite Graphs

If graph is infinite,
BFS may continue forever.


-------------------
3. WHEN DFS IS USED
-------------------

- Maze solving
- Backtracking
- Sudoku Solver
- N Queens Problem
- Game Trees


-------------------
4. WHEN BFS IS USED
-------------------

- Shortest Path
- GPS Navigation
- Social Networks
- Level Order Traversal
- AI State Space Search


-------------------
5. TIME COMPLEXITY
-------------------

DFS  -> O(V + E)

BFS  -> O(V + E)

Where:
V = Number of Vertices
E = Number of Edges


-------------------
6. SPACE COMPLEXITY
-------------------

DFS  -> O(V)

BFS  -> O(V)


-------------------
7. IMPORTANT AI CONCEPT
-------------------

DFS and BFS are called:

UNINFORMED SEARCH ALGORITHMS

because they search without heuristics
or intelligent guidance.

Advanced AI algorithms like:

- A*
- Greedy Best First Search
- Uniform Cost Search

are built using concepts of DFS and BFS.

*/