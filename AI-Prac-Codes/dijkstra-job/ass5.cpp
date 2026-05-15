#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// =====================================================
// STRUCTURE FOR GRAPH EDGE
// =====================================================

struct Edge {

    int node;
    int weight;
};

// =====================================================
// STRUCTURE FOR JOB
// =====================================================

struct Job {

    char id;
    int deadline;
    int profit;
};

// =====================================================
// FUNCTION TO PRINT PATH
// =====================================================

void printPath(vector<int>& parent,
               int node) {

    // Base condition
    if (node == -1) {

        return;
    }

    // Recursive call
    printPath(parent,
              parent[node]);

    cout << node << " ";
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

    // Graph
    vector<vector<Edge>> graph(vertices);

    cout << "\nEnter edges:";
    cout << "\nFormat: source destination weight\n";

    // Input edges
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

    int source;

    cout << "\nEnter source node: ";
    cin >> source;

    // Distance Array
    vector<int> dist(vertices,
                     INT_MAX);

    // Visited Array
    vector<bool> visited(vertices,
                         false);

    // Parent Array
    vector<int> parent(vertices,
                       -1);

    // Min Priority Queue
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // Source distance = 0
    dist[source] = 0;

    pq.push(make_pair(0, source));

    // =================================================
    // MAIN DIJKSTRA LOOP
    // =================================================

    while (!pq.empty()) {

        int currentDist =
            pq.top().first;

        int currentNode =
            pq.top().second;

        pq.pop();

        // Skip visited nodes
        if (visited[currentNode] == true) {

            continue;
        }

        // Mark visited
        visited[currentNode] = true;

        // Explore neighbors
        for (int i = 0; i < graph[currentNode].size(); i++) {

            int nextNode = graph[currentNode][i].node;

            int weight = graph[currentNode][i].weight;

            // Relaxation
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
    // PRINT SHORTEST DISTANCE + PATH
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
// COMPARATOR FOR JOB SORTING
// =====================================================

bool compare(Job a, Job b) {

    return a.profit > b.profit;
}


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

    // Sort by maximum profit
    sort(jobs.begin(),
         jobs.end(),
         compare);

    // Find maximum deadline
    int maxDeadline = 0;

    for (int i = 0; i < n; i++) {

        if (jobs[i].deadline >
            maxDeadline) {

            maxDeadline =
                jobs[i].deadline;
        }
    }

    // Slots
    vector<char> slot(maxDeadline,
                      '-');

    // Occupied array
    vector<bool> occupied(maxDeadline,
                          false);

    int totalProfit = 0;

    // =================================================
    // SCHEDULE JOBS
    // =================================================

    for (int i = 0; i < n; i++) {

        // Check slots backward
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
    // PRINT RESULT
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
// MAIN MENU
// =====================================================

int main() {

    int choice;

    do {

        cout << "\n===================================";
        cout << "\n AI ALGORITHMS MENU";
        cout << "\n===================================";

        cout << "\n1. Single Source Shortest Path";
        cout << "\n2. Job Scheduling";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // =============================================
        // DIJKSTRA
        // =============================================

        if (choice == 1) {

            dijkstra();
        }

        // =============================================
        // JOB SCHEDULING
        // =============================================

        else if (choice == 2) {

            jobScheduling();
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
DUMMY INPUT FOR DIJKSTRA
=====================================================

1

4
4

0 1 4
0 2 2
1 3 5
2 3 1

0

=====================================================
HOW PATH IS WORKING
=====================================================

Parent array stores:

parent[1] = 0
parent[2] = 0
parent[3] = 2

Meaning:

0 brought us to 1
0 brought us to 2
2 brought us to 3

So path to node 3 becomes:

0 -> 2 -> 3

=== job scheduling input ===
2

5

A 2 100
B 1 19
C 2 27
D 1 25
E 3 15

=====================================================
BREAKING POINTS
=====================================================

DIJKSTRA:

1. Does not work correctly for
   negative edge weights.

2. Large graphs consume more memory.

3. Dynamic graphs require recalculation.


JOB SCHEDULING:

1. Greedy approach may fail for
   complex scheduling constraints.

2. Assumes single machine only.

3. Fixed deadlines only.

*/

/*

=====================================================
DIJKSTRA ALGORITHM
=====================================================

Time Complexity:
O(E log V)

E = Number of Edges
V = Number of Vertices


Space Complexity:
O(V + E)



=====================================================
JOB SCHEDULING
=====================================================

Time Complexity:
O(n²)

n = Number of Jobs


Space Complexity:
O(n)

=====================================================

*/
/*

=====================================================
5(I). SINGLE SOURCE SHORTEST PATH
(DIJKSTRA ALGORITHM)
APPLICATIONS
=====================================================

1. GPS Navigation Systems
2. Internet Routing Protocols
3. Airline Route Planning
4. Robotics Pathfinding
5. Delivery Applications
6. Video Game Navigation
7. Network Packet Routing
8. Traffic Management Systems


=====================================================
5(II). JOB SCHEDULING PROBLEM
APPLICATIONS
=====================================================

1. CPU Process Scheduling
2. Manufacturing Systems
3. Cloud Computing Task Scheduling
4. Airline Scheduling
5. Hospital Appointment Systems
6. Advertisement Scheduling
7. Project Management
8. Industrial Production Planning

*/
