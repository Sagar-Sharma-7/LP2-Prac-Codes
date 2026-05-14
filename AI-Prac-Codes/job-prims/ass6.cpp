#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// =====================================================
// STRUCTURE FOR JOB
// =====================================================

struct Job {

    char id;
    int deadline;
    int profit;
};

// =====================================================
// STRUCTURE FOR EDGE
// =====================================================

struct Edge {

    int node;
    int weight;
};

// =====================================================
// STRUCTURE FOR MST NODE
// =====================================================

struct MSTNode {

    int weight;
    int current;
    int parent;
};

// =====================================================
// COMPARATOR FOR JOB SORTING
// =====================================================

bool compare(Job a, Job b) {

    return a.profit > b.profit;
}

// =====================================================
// COMPARATOR FOR PRIORITY QUEUE
// =====================================================

struct Compare {

    bool operator()(MSTNode a,
                    MSTNode b) {

        return a.weight > b.weight;
    }
};

// =====================================================
// JOB SCHEDULING
// =====================================================

void jobScheduling() {

    int n;

    cout << "\nEnter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);

    cout << "\nEnter Job Details:";
    cout << "\nFormat: ID Deadline Profit\n";

    // Input jobs
    for (int i = 0; i < n; i++) {

        cin >> jobs[i].id
            >> jobs[i].deadline
            >> jobs[i].profit;
    }

    // =================================================
    // SORT JOBS BY PROFIT
    // =================================================

    sort(jobs.begin(),
         jobs.end(),
         compare);

    // =================================================
    // FIND MAXIMUM DEADLINE
    // =================================================

    int maxDeadline = 0;

    for (int i = 0; i < n; i++) {

        if (jobs[i].deadline >
            maxDeadline) {

            maxDeadline =
                jobs[i].deadline;
        }
    }

    // =================================================
    // SLOT ARRAY
    // =================================================

    vector<char> slot(maxDeadline,
                      '-');

    // Occupied slots
    vector<bool> occupied(maxDeadline,
                          false);

    int totalProfit = 0;

    // =================================================
    // SCHEDULE JOBS
    // =================================================

    for (int i = 0; i < n; i++) {

        for (int j =
             jobs[i].deadline - 1;
             j >= 0;
             j--) {

            if (occupied[j] == false) {

                occupied[j] = true;

                slot[j] =
                    jobs[i].id;

                totalProfit =
                    totalProfit +
                    jobs[i].profit;

                break;
            }
        }
    }

    // =================================================
    // PRINT OUTPUT
    // =================================================

    cout << "\nScheduled Jobs:\n";

    for (int i = 0;
         i < slot.size();
         i++) {

        cout << slot[i] << " ";
    }

    cout << "\nTotal Profit: "
         << totalProfit
         << endl;
}

// =====================================================
// PRIM'S MST ALGORITHM
// =====================================================

void primsMST() {

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

        totalCost =
            totalCost + currentWeight;

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

        for (int i = 0;
             i < graph[currentNode].size();
             i++) {

            int nextNode =
                graph[currentNode][i].node;

            int nextWeight =
                graph[currentNode][i].weight;

            if (visited[nextNode] == false) {

                MSTNode newNode;

                newNode.weight =
                    nextWeight;

                newNode.current =
                    nextNode;

                newNode.parent =
                    currentNode;

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

        cout << "\n1. Job Scheduling Problem";
        cout << "\n2. Prim's MST Algorithm";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // =============================================
        // JOB SCHEDULING
        // =============================================

        if (choice == 1) {

            jobScheduling();
        }

        // =============================================
        // PRIM'S MST
        // =============================================

        else if (choice == 2) {

            primsMST();
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
DUMMY INPUT FOR JOB SCHEDULING
=====================================================

1

5

A 2 100
B 1 19
C 2 27
D 1 25
E 3 15


=====================================================
OUTPUT
=====================================================

Scheduled Jobs:

C A E

Total Profit: 142


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Job Scheduling:

Time Complexity:
O(n²)

Space Complexity:
O(n)


=====================================================
BREAKING POINTS
=====================================================

1. Assumes one machine only

2. Every job takes fixed unit time

3. Greedy approach may fail for
   complex scheduling constraints



=====================================================
DUMMY INPUT FOR PRIM'S MST
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

(0,3) (3,2) (0,1)

Minimum Total Cost: 19


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Prim's MST:

Time Complexity:
O(E log V)

Space Complexity:
O(V + E)


=====================================================
BREAKING POINTS
=====================================================

1. Disconnected graph fails

2. Large dense graphs expensive

3. Cycles must be handled carefully

=====================================================

*/