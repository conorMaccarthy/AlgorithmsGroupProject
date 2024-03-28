#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Node {
    bool isChargingStation;
    vector<Edge> connectedEdges;
};

struct Edge {
    int weight;
    Node* front;
    Node* back;
};

vector<Node> readFile() {

}

int main()
{
    return 0;
}