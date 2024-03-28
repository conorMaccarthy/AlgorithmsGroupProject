#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Node {
    int index;
    bool isChargingStation;
    string name;
};

struct Edge {
    int weight;
    Node start;
    Node end;
};

class Graph {
private:
    int nodeCount;
    vector<Node> nodes;
    vector<vector<Edge>> edges;

public:
    Graph(int nodeCountInit) : nodeCount(nodeCountInit) { 
        edges.resize(nodeCountInit); 
    }

    void addNode(string name, int index) {
        Node node;
        node.name = name;
        node.index = index;

        if (node.name == "H" || node.name == "K" || node.name == "Q" || node.name == "T") node.isChargingStation = true;
        else node.isChargingStation = false;
        
        nodes.push_back(node);
    }

    Node findNode(string name) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).name == name) return nodes.at(i);
        }
    }

    void addEdge(const string& startNode, const string& endNode, int weight) {
        Edge edge;
        edge.weight = weight;
        edge.start = findNode(startNode);
        edge.end = findNode(endNode);

        edges.at(findNode(startNode).index).push_back(edge);
        edges.at(findNode(endNode).index).push_back(edge);
    }

    void printNode(string name) {
        cout << "Node " << findNode(name).name << " is connected to: " << endl;
        for (int i = 0; i < edges.at(findNode(name).index).size(); i++) {
            cout << "\t" << edges.at(findNode(name).index).at(i).end.name << " with a weight of " << edges.at(findNode(name).index).at(i).weight << endl;
        }
    }
};

/*vector<Node> readFile() {

}*/

int main()
{
    Graph graph(5);

    graph.addNode("A", 0);
    graph.addNode("B", 1);
    graph.addNode("C", 2);
    graph.addNode("D", 3);
    graph.addNode("E", 4);

    graph.addEdge("A", "C", 7);
    graph.addEdge("A", "D", 5);

    graph.printNode("A");
    
    return 0;
}