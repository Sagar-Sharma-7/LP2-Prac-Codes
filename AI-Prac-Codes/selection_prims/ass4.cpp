#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// =====================================================
// SELECTION SORT
// =====================================================

void selectionSort() {

    int n;

    cout << "\nEnter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "\nEnter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    // =================================================
    // SELECTION SORT
    // =================================================

    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        // Find smallest element
        for (int j = i + 1; j < n; j++) {

            if (arr[j] < arr[minIndex]) {

                minIndex = j;
            }
        }

        // Swap
        int temp = arr[i];

        arr[i] = arr[minIndex];

        arr[minIndex] = temp;

        // =============================================
        // PRINT EACH ITERATION
        // =============================================

        cout << "\nIteration "
             << i + 1
             << ":\n";

        for (int k = 0; k < n; k++) {

            cout << arr[k] << " ";
        }

        cout << endl;
    }

    // =================================================
    // FINAL SORTED ARRAY
    // =================================================

    cout << "\nFinal Sorted Array:\n";

    for (int i = 0; i < n; i++) {

        cout << arr[i] << " ";
    }

    cout << endl;
}


// =====================================================
// MINIMUM SPANNING TREE
// PRIM'S ALGORITHM
// =====================================================

// =====================================================
// STRUCTURE FOR EDGE
// =====================================================

struct Edge {

    int node;
    int weight;
};


struct MSTNode {

    int weight;
    int current;
    int parent;
};

// =====================================================
// COMPARATOR
// =====================================================

struct Compare {

    bool operator()(MSTNode a,
                    MSTNode b) {

        return a.weight > b.weight;
    }
};

// =====================================================
// MINIMUM SPANNING TREE
// PRIM'S ALGORITHM
// =====================================================

void minimumSpanningTree() {

    int vertices, edges;

    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<Edge>> graph(vertices);

    cout << "\nEnter edges:";
    cout << "\nFormat: source destination weight\n";

    // =================================================
    // INPUT GRAPH
    // =================================================

    for (int i = 0; i < edges; i++) {

        int u, v, w;

        cin >> u >> v >> w;

        Edge e1;
        e1.node = v;
        e1.weight = w;

        Edge e2;
        e2.node = u;
        e2.weight = w;

        graph[u].push_back(e1);
        graph[v].push_back(e2);
    }

    // =================================================
    // VISITED ARRAY
    // =================================================

    vector<bool> visited(vertices,
                         false);

    // =================================================
    // PRIORITY QUEUE
    // =================================================

    priority_queue<
        MSTNode,
        vector<MSTNode>,
        Compare
    > pq;

    // =================================================
    // START NODE
    // =================================================

    MSTNode start;

    start.weight = 0;
    start.current = 0;
    start.parent = -1;

    pq.push(start);

    int totalCost = 0;

    cout << "\nEdges in MST:\n";

    // =================================================
    // PRIM'S ALGORITHM
    // =================================================

    while (!pq.empty()) {

        MSTNode temp = pq.top();

        pq.pop();

        int currentNode = temp.current;
        int currentWeight = temp.weight;
        int parentNode = temp.parent;

        // Skip visited nodes
        if (visited[currentNode] == true) {

            continue;
        }

        // Mark visited
        visited[currentNode] = true;

        totalCost = totalCost + currentWeight;

        // =================================================
        // PRINT EDGE PAIR
        // =================================================

        if (parentNode != -1) {

            cout << "("
                 << parentNode
                 << ","
                 << currentNode
                 << ") ";

        }

        // =================================================
        // EXPLORE NEIGHBORS
        // =================================================

        for (int i = 0; i < graph[currentNode].size(); i++) {

            int nextNode = graph[currentNode][i].node;

            int nextWeight = graph[currentNode][i].weight;

            if (visited[nextNode] == false) {

                MSTNode newNode;

                newNode.weight = nextWeight;

                newNode.current = nextNode;

                newNode.parent = currentNode;

                pq.push(newNode);
            }
        }
    }

    // =================================================
    // PRINT TOTAL COST
    // =================================================

    cout << "\n\nMinimum Total Cost: "
         << totalCost
         << endl;
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

        cout << "\n1. Selection Sort";
        cout << "\n2. Minimum Spanning Tree";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // =============================================
        // SELECTION SORT
        // =============================================

        if (choice == 1) {

            selectionSort();
        }

        // =============================================
        // MST
        // =============================================

        else if (choice == 2) {

            minimumSpanningTree();
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
DUMMY INPUT FOR SELECTION SORT
=====================================================

1

5

64 25 12 22 11


=====================================================
OUTPUT
=====================================================

Sorted Array:

11 12 22 25 64


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Selection Sort:

Time Complexity:
O(n²)

Space Complexity:
O(1)


=====================================================
BREAKING POINTS
=====================================================

1. Slow for large arrays
2. Inefficient compared to quick sort
3. Always O(n²)



=====================================================
DUMMY INPUT FOR MST
=====================================================

2

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

Node 0 added with cost 0
Node 3 added with cost 5
Node 2 added with cost 4
Node 1 added with cost 10

Minimum Total Cost: 19


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Minimum Spanning Tree (Prim's):

Time Complexity:
O(E log V)

Space Complexity:
O(V + E)


=====================================================
BREAKING POINTS
=====================================================

1. Disconnected graph fails
2. Large dense graph expensive
3. Cycle handling important

=====================================================

*/