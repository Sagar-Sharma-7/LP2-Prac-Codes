#include <iostream>
#include <vector>

using namespace std;

// =====================================================
// N QUEENS
// =====================================================

// Check safe position
bool isSafeQueen(vector<vector<int>>& board,
                 int row,
                 int col,
                 int n) {

    // Check upper column
    for (int i = 0; i < row; i++) {

        if (board[i][col] == 1) {

            return false;
        }
    }

    // Check left diagonal
    int i = row;
    int j = col;

    while (i >= 0 && j >= 0) {

        if (board[i][j] == 1) {

            return false;
        }

        i--;
        j--;
    }

    // Check right diagonal
    i = row;
    j = col;

    while (i >= 0 && j < n) {

        if (board[i][j] == 1) {

            return false;
        }

        i--;
        j++;
    }

    return true;
}

// Backtracking function
bool solveNQueens(vector<vector<int>>& board,
                  int row,
                  int n) {

    // Base condition
    if (row == n) {

        return true;
    }

    // Try all columns
    for (int col = 0; col < n; col++) {

        if (isSafeQueen(board, row, col, n)) {

            // Place queen
            board[row][col] = 1;

            // Recursive call
            if (solveNQueens(board, row + 1, n)) {

                return true;
            }

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

// Print board
void printBoard(vector<vector<int>>& board,
                int n) {

    cout << "\nSolution Board:\n\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (board[i][j] == 1) {

                cout << "Q ";
            }

            else {

                cout << ". ";
            }
        }

        cout << endl;
    }
}

// =====================================================
// GRAPH COLORING
// =====================================================

// Check safe color
bool isSafeColor(vector<vector<int>>& graph,
                 vector<int>& color,
                 int node,
                 int currentColor,
                 int vertices) {

    for (int i = 0; i < vertices; i++) {

        if (graph[node][i] == 1 &&
            color[i] == currentColor) {

            return false;
        }
    }

    return true;
}

// Backtracking coloring
bool solveGraphColoring(
    vector<vector<int>>& graph,
    int totalColors,
    vector<int>& color,
    int node,
    int vertices) {

    // Base condition
    if (node == vertices) {

        return true;
    }

    // Try all colors
    for (int c = 1; c <= totalColors; c++) {
        if (isSafeColor(graph,
                        color,
                        node,
                        c,
                        vertices)) {

            // Assign color
            color[node] = c;

            // Recursive call
            if (solveGraphColoring(
                    graph,
                    totalColors,
                    color,
                    node + 1,
                    vertices)) {

                return true;
            }

            // Backtrack
            color[node] = 0;
        }
    }

    return false;
}

// Print graph colors
void printColors(vector<int>& color,
                 int vertices) {

    cout << "\nColor Assignment:\n\n";

    for (int i = 0; i < vertices; i++) {

        cout << "Node "
             << i
             << " -> Color "
             << color[i]
             << endl;
    }
}

// =====================================================
// MAIN MENU
// =====================================================

int main() {

    int choice;

    do {

        cout << "\n===================================";
        cout << "\n CSP ALGORITHMS MENU";
        cout << "\n===================================";

        cout << "\n1. N Queens Problem";
        cout << "\n2. Graph Coloring Problem";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // =============================================
        // N QUEENS
        // =============================================

        if (choice == 1) {

            int n;

            cout << "\nEnter value of N: ";
            cin >> n;

            vector<vector<int>> board(
                n,
                vector<int>(n, 0)
            );

            bool possible =
                solveNQueens(board,
                             0,
                             n);

            if (possible == true) {

                printBoard(board, n);
            }

            else {

                cout << "\nNo Solution Exists\n";
            }
        }

        // =============================================
        // GRAPH COLORING
        // =============================================

        else if (choice == 2) {

            int vertices;

            cout << "\nEnter number of vertices: ";
            cin >> vertices;

            vector<vector<int>> graph(
                vertices,
                vector<int>(vertices)
            );

            cout << "\nEnter adjacency matrix:\n";

            // Input adjacency matrix
            for (int i = 0; i < vertices; i++) {

                for (int j = 0; j < vertices; j++) {

                    cin >> graph[i][j];
                }
            }

            int totalColors;

            cout << "\nEnter number of colors: ";
            cin >> totalColors;

            vector<int> color(vertices, 0);

            bool possible =
                solveGraphColoring(
                    graph,
                    totalColors,
                    color,
                    0,
                    vertices
                );

            if (possible == true) {

                printColors(color,
                            vertices);
            }

            else {

                cout << "\nNo Valid Coloring Possible\n";
            }
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
DUMMY INPUT FOR N QUEENS
=====================================================

1

4


=====================================================
OUTPUT
=====================================================

Solution Board:

. Q . .

. . . Q

Q . . .

. . Q .


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

N Queens:

Time Complexity:
O(N!)

Space Complexity:
O(N²)


=====================================================
BREAKING POINTS
=====================================================

1. Very slow for large N

2. Recursive calls increase heavily

3. Large search space



=====================================================
DUMMY INPUT FOR GRAPH COLORING
=====================================================

2

4

0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0

3


=====================================================
OUTPUT
=====================================================

Color Assignment:

Node 0 -> Color 1
Node 1 -> Color 2
Node 2 -> Color 3
Node 3 -> Color 2


=====================================================
TIME & SPACE COMPLEXITY
=====================================================

Graph Coloring:

Time Complexity:
O(M^V)

M = Number of Colors
V = Number of Vertices


Space Complexity:
O(V)


=====================================================
BREAKING POINTS
=====================================================

1. Extremely slow for large graphs

2. More colors increase combinations

3. Dense graphs become difficult

=====================================================

*/
/*

=====================================================
8(I). N-QUEENS PROBLEM
APPLICATIONS
=====================================================

1. Chess AI
2. Resource Allocation Problems
3. Parallel Processing
4. Constraint Satisfaction Problems
5. Scheduling Systems
6. Puzzle Solving AI
7. Robotics Position Planning
8. Backtracking Algorithm Learning


=====================================================
8(II). GRAPH COLORING PROBLEM
APPLICATIONS
=====================================================

1. Map Coloring
2. Timetable Scheduling
3. Register Allocation in Compilers
4. Frequency Assignment in Mobile Networks
5. Sudoku Solving
6. Task Scheduling
7. Resource Allocation
8. Traffic Signal Scheduling

*/
