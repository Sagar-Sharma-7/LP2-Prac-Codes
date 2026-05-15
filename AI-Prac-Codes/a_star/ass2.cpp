#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// =====================================================
// NODE STRUCTURE
// =====================================================

struct Node {

    int x, y;

    int g; // Actual Cost
    int h; // Heuristic Cost
    int f; // Total Cost

    // Constructor
    Node(int x, int y, int g, int h) {

        this->x = x;
        this->y = y;

        this->g = g;
        this->h = h;

        this->f = g + h;
    }
};

// =====================================================
// CUSTOM PRIORITY QUEUE COMPARATOR
// =====================================================

struct Compare {

    bool operator()(Node a, Node b) {

        // Priority 1:
        // Smaller f(n)

        if (a.f == b.f) {

            // Priority 2:
            // Smaller h(n)
            // Closer to goal gets priority

            return a.h > b.h;
        }

        return a.f > b.f;
    }
};

// =====================================================
// HEURISTIC FUNCTION
// MANHATTAN DISTANCE
// =====================================================

int heuristic(int x1, int y1,
              int x2, int y2) {

    return abs(x1 - x2) + abs(y1 - y2);
}

// =====================================================
// A* ALGORITHM
// =====================================================

void aStar(vector<vector<int>>& grid,
           int startX, int startY,
           int goalX, int goalY) {

    int rows = grid.size();
    int cols = grid[0].size();

    // =================================================
    // VISITED ARRAY
    // =================================================

    vector<vector<bool>> visited(rows,
                                 vector<bool>(cols, false));

    // =================================================
    // PARENT ARRAY
    // Used to reconstruct final shortest path
    // =================================================

    vector<vector<pair<int, int>>> parent(
        rows,
        vector<pair<int, int>>(cols, {-1, -1})
    );

    // =================================================
    // PRIORITY QUEUE
    // =================================================

    priority_queue<Node,
                   vector<Node>,
                   Compare> pq;

    // Initial heuristic
    int h = heuristic(startX,
                      startY,
                      goalX,
                      goalY);

    // Push start node
    pq.push(Node(startX,
                 startY,
                 0,
                 h));

    // Movement Directions
    // Up, Down, Left, Right

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // =================================================
    // MAIN LOOP
    // =================================================

    while (!pq.empty()) {

        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        // Skip if already visited
        if (visited[x][y])
            continue;

        visited[x][y] = true;

        // =================================================
        // GOAL FOUND
        // =================================================

        if (x == goalX && y == goalY) {

            vector<pair<int, int>> path;

            // Backtrack using parent array

            while (!(x == startX && y == startY)) {

                path.push_back({x, y});

                pair<int, int> p = parent[x][y];

                x = p.first;
                y = p.second;
            }

            // Add start node
            path.push_back({startX, startY});

            // Reverse path
            reverse(path.begin(), path.end());

            // Print shortest path

            cout << "\nShortest Path:\n";

            for (auto node : path) {

                cout << "("
                     << node.first
                     << ","
                     << node.second
                     << ") ";
            }

            cout << "\n\nGoal Reached!" << endl;

            return;
        }

        // =================================================
        // EXPLORE NEIGHBORS
        // =================================================

        for (int i = 0; i < 4; i++) {

            int newX = x + dx[i];
            int newY = y + dy[i];

            // Valid Cell Check

            if (newX >= 0 &&
                newX < rows &&
                newY >= 0 &&
                newY < cols &&
                grid[newX][newY] == 0 &&
                !visited[newX][newY]) {

                // New actual cost
                int newG = current.g + 1;

                // Heuristic cost
                int newH = heuristic(newX,
                                     newY,
                                     goalX,
                                     goalY);

                // Push into priority queue
                pq.push(Node(newX,
                             newY,
                             newG,
                             newH));

                // Store parent
                parent[newX][newY] = {x, y};
            }
        }
    }

    cout << "No Path Found!" << endl;
}

// =====================================================
// MAIN FUNCTION
// =====================================================

int main() {

    int rows, cols;

    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows,
                             vector<int>(cols));

    cout << "\nEnter grid values:\n";
    cout << "0 = Free Path\n";
    cout << "1 = Obstacle\n\n";

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            cin >> grid[i][j];
        }
    }

    int startX, startY;
    int goalX, goalY;

    cout << "\nEnter start coordinates: ";
    cin >> startX >> startY;

    cout << "Enter goal coordinates: ";
    cin >> goalX >> goalY;

    cout << "\nRunning A* Algorithm...\n";

    aStar(grid,
          startX,
          startY,
          goalX,
          goalY);

    return 0;
}


/*

=====================================================
DUMMY INPUT
=====================================================

Enter rows and columns:
3 4

Enter grid values:

0 0 0 0
1 1 0 0
0 0 0 0

Enter start coordinates:
0 0

Enter goal coordinates:
2 3


=====================================================
OUTPUT
=====================================================

A* Path Traversal:

(0,0)
(0,1)
(0,2)
(1,2)
(1,3)
(2,3)

Goal Reached!


=====================================================
THEORY OF A* BREAKING POINTS
=====================================================

1. BAD HEURISTIC PROBLEM

If heuristic is poor,
A* behaves almost like BFS.

It explores too many unnecessary nodes.


2. MEMORY CONSUMPTION

A* stores many nodes in memory.

Large maps consume huge RAM.


3. NOT GOOD FOR VERY LARGE SEARCH SPACES

Huge game worlds may become expensive.


4. HEURISTIC OVER-ESTIMATION

If heuristic overestimates actual cost:

A* may fail to find shortest path.

This breaks optimality.


5. DYNAMIC ENVIRONMENTS

If obstacles move continuously:

A* must recompute paths repeatedly.


6. INFINITE SEARCH SPACE

A* may become impractical.


=====================================================
WHEN A* IS USED
=====================================================

- Video Game AI
- GPS Navigation
- Robot Navigation
- Maze Solving
- Pathfinding Systems
- Strategy Games


=====================================================
IMPORTANT AI CONCEPT
=====================================================

A* is called:

INFORMED SEARCH ALGORITHM

because it uses heuristic knowledge
to intelligently guide the search.


=====================================================
TIME COMPLEXITY
=====================================================

Worst Case:

O(E log V)


=====================================================
SPACE COMPLEXITY
=====================================================

O(V)

*/
/*

=====================================================
2. A* ALGORITHM
APPLICATIONS
=====================================================

1. GPS Navigation Systems
2. Robotics Path Planning
3. Video Game AI
4. Maze Solving
5. Self-Driving Cars
6. Airline Route Optimization
7. Network Routing
8. Logistics and Delivery Optimization

*/
