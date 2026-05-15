#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// =====================================================
// STRUCTURE FOR KRUSKAL EDGE
// =====================================================

struct Edge {

    int source;
    int destination;
    int weight;
};

// =====================================================
// STRUCTURE FOR DIJKSTRA GRAPH EDGE
// =====================================================

struct GraphEdge {

    int node;
    int weight;
};

// =====================================================
// COMPARE FUNCTION FOR KRUSKAL
// =====================================================

bool compareEdges(Edge a, Edge b) {

    return a.weight < b.weight;
}

// =====================================================
// FIND PARENT FUNCTION
// =====================================================

int findParent(vector<int>& parent,
               int node) {

    if (parent[node] == node) {

        return node;
    }

    return findParent(parent,
                      parent[node]);
}

// =====================================================
// UNION FUNCTION
// =====================================================

void unionSet(vector<int>& parent,
              int u,
              int v) {

    int parentU =
        findParent(parent, u);

    int parentV =
        findParent(parent, v);

    parent[parentU] = parentV;
}

// =====================================================
// FUNCTION TO PRINT PATH
// =====================================================

void printPath(vector<int>& parent,
               int node) {

    if (node == -1) {

        return;
    }

    printPath(parent,
              parent[node]);

    cout << node << " ";
}

// =====================================================
// KRUSKAL MST
// =====================================================

void kruskalMST() {

    int vertices, edges;

    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    vector<Edge> edgeList(edges);

    cout << "\nEnter edges:";
    cout << "\nFormat: source destination weight\n";

    // =================================================
    // INPUT EDGES
    // =================================================

    for (int i = 0; i < edges; i++) {

        cin >> edgeList[i].source
            >> edgeList[i].destination
            >> edgeList[i].weight;
    }

    // =================================================
    // SORT EDGES
    // =================================================

    sort(edgeList.begin(),
         edgeList.end(),
         compareEdges);

    // =================================================
    // PARENT ARRAY
    // =================================================

    vector<int> parent(vertices);

    for (int i = 0; i < vertices; i++) {

        parent[i] = i;
    }

    int totalCost = 0;

    cout << "\nEdges in MST:\n";

    // =================================================
    // KRUSKAL LOGIC
    // =================================================

    for (int i = 0; i < edges; i++) {

        int u =
            edgeList[i].source;

        int v =
            edgeList[i].destination;

        int w =
            edgeList[i].weight;

        int parentU =
            findParent(parent, u);

        int parentV =
            findParent(parent, v);

        // Avoid cycle
        if (parentU != parentV) {

            cout << "("
                 << u
                 << ","
                 << v
                 << ") ";

            totalCost =
                totalCost + w;

            unionSet(parent,
                     u,
                     v);
        }
    }

    cout << "\n\nMinimum Total Cost: "
         << totalCost
         << endl;
}

// =====================================================
// DIJKSTRA ALGORITHM
// =====================================================

void dijkstra() {

    int vertices, edges;

    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    // =================================================
    // GRAPH
    // =================================================

    vector<vector<GraphEdge>> graph(vertices);

    cout << "\nEnter edges:";
    cout << "\nFormat: source destination weight\n";

    // =================================================
    // INPUT GRAPH
    // =================================================

    for (int i = 0; i < edges; i++) {

        int u, v, w;

        cin >> u >> v >> w;

        GraphEdge e1;
        e1.node = v;
        e1.weight = w;

        GraphEdge e2;
        e2.node = u;
        e2.weight = w;

        graph[u].push_back(e1);
        graph[v].push_back(e2);
    }

    int source;

    cout << "\nEnter source node: ";
    cin >> source;

    // =================================================
    // DISTANCE ARRAY
    // =================================================

    vector<int> dist(vertices,
                     INT_MAX);

    // =================================================
    // VISITED ARRAY
    // =================================================

    vector<bool> visited(vertices,
                         false);

    // =================================================
    // PARENT ARRAY
    // =================================================

    vector<int> parent(vertices,
                       -1);

    // =================================================
    // MIN PRIORITY QUEUE
    // =================================================

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // =================================================
    // SOURCE INITIALIZATION
    // =================================================

    dist[source] = 0;

    pq.push(make_pair(0, source));

    // =================================================
    // DIJKSTRA LOOP
    // =================================================

    while (!pq.empty()) {

        int currentDist =
            pq.top().first;

        int currentNode =
            pq.top().second;

        pq.pop();

        // Skip visited node
        if (visited[currentNode] == true) {

            continue;
        }

        // Mark visited
        visited[currentNode] = true;

        // =================================================
        // EXPLORE NEIGHBORS
        // =================================================

        for (int i = 0;
             i < graph[currentNode].size();
             i++) {

            int nextNode =
                graph[currentNode][i].node;

            int weight =
                graph[currentNode][i].weight;

            // =================================================
            // RELAXATION
            // =================================================

            if (dist[currentNode] + weight
                < dist[nextNode]) {

                dist[nextNode] =
                    dist[currentNode] + weight;

                // Store parent
                parent[nextNode] =
                    currentNode;

                pq.push(
                    make_pair(
                        dist[nextNode],
                        nextNode
                    )
                );
            }
        }
    }

    // =================================================
    // PRINT SHORTEST PATHS
    // =================================================

    cout << "\nShortest Paths:\n";

    for (int i = 0; i < vertices; i++) {

        cout << "\nNode "
             << i
             << endl;

        cout << "Distance: "
             << dist[i]
             << endl;

        cout << "Path: ";

        printPath(parent, i);

        cout << endl;
    }
}

// =====================================================
// MAIN MENU
// =====================================================

int main() {

    int choice;

    do {

        cout << "\n===================================";
        cout << "\n AI ALGORITHMS MENU";
        cout << "\n===================================";

        cout << "\n1. Kruskal MST";
        cout << "\n2. Dijkstra Algorithm";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // =============================================
        // KRUSKAL
        // =============================================

        if (choice == 1) {

            kruskalMST();
        }

        // =============================================
        // DIJKSTRA
        // =============================================

        else if (choice == 2) {

            dijkstra();
        }

        // =============================================
        // EXIT
        // =============================================

        else if (choice == 3) {

            cout << "\nProgram Ended.\n";
        }

        else {

            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}


/*

=====================================================
DUMMY INPUT FOR KRUSKAL
=====================================================

1

4
5

0 1 10
0 2 6
0 3 5
1 3 15
2 3 4


=====================================================
OUTPUT
=====================================================

Edges in MST:

(2,3) (0,3) (0,1)

Minimum Total Cost: 19


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Kruskal MST:

Time Complexity:
O(E log E)

Space Complexity:
O(V)


=====================================================
BREAKING POINTS
=====================================================

1. Sorting expensive for huge graphs

2. Disconnected graph gives forest

3. DSU required for cycle handling



=====================================================
DUMMY INPUT FOR DIJKSTRA
=====================================================

2

4
4

0 1 4
0 2 2
1 3 5
2 3 1

0


=====================================================
OUTPUT
=====================================================

Shortest Paths:

Node 0
Distance: 0
Path: 0

Node 1
Distance: 4
Path: 0 1

Node 2
Distance: 2
Path: 0 2

Node 3
Distance: 3
Path: 0 2 3


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Dijkstra:

Time Complexity:
O(E log V)

Space Complexity:
O(V + E)


=====================================================
BREAKING POINTS
=====================================================

1. Negative edge weights fail

2. Large graphs consume more memory

3. Dynamic graph changes require recalculation

=====================================================

*/
/*

=====================================================
7(I). KRUSKAL'S MINIMUM SPANNING TREE
APPLICATIONS
=====================================================

1. Network Cable Optimization
2. Railway Network Planning
3. Electrical Grid Connections
4. Road Map Construction
5. Water Distribution Systems
6. Cluster Analysis in Machine Learning
7. Image Segmentation
8. Telecommunication Networks


=====================================================
7(II). DIJKSTRA ALGORITHM
APPLICATIONS
=====================================================

1. GPS Navigation
2. Internet Routing
3. Airline Path Optimization
4. Robotics Navigation
5. Shortest Path in Games
6. Delivery Route Optimization
7. Traffic Navigation Systems
8. Communication Networks

*/
