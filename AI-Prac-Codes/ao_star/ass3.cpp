#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

class Node {
public:
    string name;
    int heuristic;
    bool isAND;

    vector<pair<Node*, int>> children;

    Node* bestChild;

    Node(string n, int h = 0, bool type = false) {
        name = n;
        heuristic = h;
        isAND = type;
        bestChild = NULL;
    }
};

// AO* Algorithm
int AOStar(Node* current) {

    // Leaf Node
    if (current->children.size() == 0) {
        return current->heuristic;
    }

    // AND Node
    if (current->isAND) {

        int totalCost = 0;

        cout << "\nAND Calculation for "
             << current->name << ":\n";

        for (auto child : current->children) {

            Node* nextNode = child.first;
            int edgeWeight = child.second;

            int childCost = AOStar(nextNode);

            int finalCost = edgeWeight + childCost;

            cout << current->name
                 << " -> "
                 << nextNode->name
                 << " = Edge("
                 << edgeWeight
                 << ") + Heuristic("
                 << childCost
                 << ") = "
                 << finalCost << endl;

            totalCost += finalCost;
        }

        current->heuristic = totalCost;

        cout << "Final Heuristic of "
             << current->name
             << " = "
             << totalCost << endl;

        return totalCost;
    }

    // OR Node
    else {

        int minimumCost = INT_MAX;

        cout << "\nOR Calculation for "
             << current->name << ":\n";

        for (auto child : current->children) {

            Node* nextNode = child.first;
            int edgeWeight = child.second;

            int childCost = AOStar(nextNode);

            int finalCost = edgeWeight + childCost;

            cout << current->name
                 << " -> "
                 << nextNode->name
                 << " = Edge("
                 << edgeWeight
                 << ") + Heuristic("
                 << childCost
                 << ") = "
                 << finalCost << endl;

            if (finalCost < minimumCost) {

                minimumCost = finalCost;

                current->bestChild = nextNode;
            }
        }

        current->heuristic = minimumCost;

        cout << "Final Heuristic of "
             << current->name
             << " = "
             << minimumCost << endl;

        return minimumCost;
    }
}

// Print Graph
void printGraph(Node* node, string indent = "") {

    cout << indent
         << node->name
         << " [H = "
         << node->heuristic
         << "]";

    if (node->children.size() != 0) {

        if (node->isAND)
            cout << " (AND)";
        else
            cout << " (OR)";
    }

    cout << endl;

    for (auto child : node->children) {

        cout << indent
             << "  |-- Edge Cost: "
             << child.second << endl;

        printGraph(child.first, indent + "     ");
    }
}

// Print Best Path
void printBestPath(Node* node) {

    cout << node->name;

    // Leaf Node
    if (node->children.size() == 0) {
        return;
    }

    // AND Node
    if (node->isAND) {

        for (auto child : node->children) {

            cout << "\n   AND -> ";

            printBestPath(child.first);
        }
    }

    // OR Node
    else {

        cout << "\n   OR -> ";

        printBestPath(node->bestChild);
    }
}

int main() {

    // Leaf Node Heuristics
    int hTrain, hWeapons, hBribe, hTunnel;

    cout << "Enter heuristic for Train Soldiers: ";
    cin >> hTrain;

    cout << "Enter heuristic for Buy Weapons: ";
    cin >> hWeapons;

    cout << "Enter heuristic for Bribe Guard: ";
    cin >> hBribe;

    cout << "Enter heuristic for Tunnel: ";
    cin >> hTunnel;

    // Leaf Nodes
    Node* trainSoldiers = new Node("Train Soldiers", hTrain);
    Node* buyWeapons = new Node("Buy Weapons", hWeapons);
    Node* bribeGuard = new Node("Bribe Guard", hBribe);
    Node* tunnel = new Node("Tunnel", hTunnel);

    // Intermediate Nodes
    Node* attack = new Node("Attack", 0, true);
    Node* stealth = new Node("Stealth", 0, false);

    // Root Node
    Node* rescueTreasure = new Node("Rescue Treasure", 0, false);

    // Edge Costs
    int attackTrainEdge, attackWeaponEdge;
    int stealthBribeEdge, stealthTunnelEdge;
    int rootAttackEdge, rootStealthEdge;

    cout << "\nEnter edge cost from Attack to Train Soldiers: ";
    cin >> attackTrainEdge;

    cout << "Enter edge cost from Attack to Buy Weapons: ";
    cin >> attackWeaponEdge;

    cout << "Enter edge cost from Stealth to Bribe Guard: ";
    cin >> stealthBribeEdge;

    cout << "Enter edge cost from Stealth to Tunnel: ";
    cin >> stealthTunnelEdge;

    cout << "Enter edge cost from Rescue Treasure to Attack: ";
    cin >> rootAttackEdge;

    cout << "Enter edge cost from Rescue Treasure to Stealth: ";
    cin >> rootStealthEdge;

    // Connections
    attack->children.push_back({trainSoldiers, attackTrainEdge});
    attack->children.push_back({buyWeapons, attackWeaponEdge});

    stealth->children.push_back({bribeGuard, stealthBribeEdge});
    stealth->children.push_back({tunnel, stealthTunnelEdge});

    rescueTreasure->children.push_back({attack, rootAttackEdge});
    rescueTreasure->children.push_back({stealth, rootStealthEdge});

    // Print Graph
    cout << "\n=========== GAME GRAPH ===========\n\n";

    printGraph(rescueTreasure);

    // AO* Execution
    cout << "\n=========== AO* EXECUTION ===========\n";

    int answer = AOStar(rescueTreasure);

    // Final Result
    cout << "\n=========== FINAL RESULT ===========\n";

    cout << "\nMinimum Cost to Rescue Treasure = "
         << answer << endl;

    // Best Path
    cout << "\n=========== BEST PATH ===========\n\n";

    printBestPath(rescueTreasure);

    cout << endl;

    return 0;
}

/*
====================================================
                AO* ALGORITHM
        Treasure Rescue Mission Game
====================================================

TIME COMPLEXITY:
Worst Case  : O(N)
Best Case   : O(Depth)

SPACE COMPLEXITY:
O(N)

WHERE AO* FAILS:
1. Cyclic AND-OR Graphs
   AO* may loop infinitely if cycles exist.

2. Poor Heuristic Values
   Wrong heuristic values can lead to non-optimal path.

3. Very Large Search Space
   Memory usage increases heavily.

4. Dynamic Environments
   If edge costs change during execution,
   AO* may produce incorrect result.

5. Non-Admissible Heuristic
   If heuristic overestimates actual cost,
   optimal solution is not guaranteed.

====================================================

DUMMY INPUT:

Heuristic Values:
Train Soldiers = 6
Buy Weapons    = 4
Bribe Guard    = 3
Tunnel         = 5

Edge Costs:
Attack -> Train Soldiers = 2
Attack -> Buy Weapons    = 3
Stealth -> Bribe Guard   = 1
Stealth -> Tunnel        = 2
Root -> Attack           = 4
Root -> Stealth          = 2

EXPECTED CALCULATION:

Attack
= (2 + 6) + (3 + 4)
= 8 + 7
= 15

Stealth
= MIN(1 + 3, 2 + 5)
= MIN(4, 7)
= 4

Rescue Treasure
= MIN(4 + 15, 2 + 4)
= MIN(19, 6)

FINAL ANSWER = 6

BEST PATH:
Rescue Treasure
   OR -> Stealth
   OR -> Bribe Guard

====================================================
*/
/*

=====================================================
3. AO* ALGORITHM
APPLICATIONS
=====================================================

1. Medical Diagnosis Systems
2. AI Planning Systems
3. Robotics Task Planning
4. Expert Systems
5. Problem Reduction Systems
6. Game AI
7. Natural Language Processing
8. Project Management Systems

*/
