#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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
    Node findNode(int index) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).index == index) return nodes.at(i);
        }
    }

    void addEdge(string startNode, string endNode, int weight) {
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

vector<string> readFile() {
    vector<string> stringVector;
    string line;

    ifstream myFile("GraphData.txt");
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            stringVector.push_back(line);
        }
        myFile.close();
    }

    return stringVector;
}

vector<string> splitString(string & input) {
    vector<string> substringVector;
    string newWord = "";

    for (int i = 0; i < input.size(); i++) {
        if (input[i] != ',') {
            newWord = newWord + input[i];
        }
        else {
            if (newWord.size() != 0) {
                substringVector.push_back(newWord);
                newWord = "";
            }
        }
    }

    return substringVector;
}

void createNodes(Graph & graph, vector<string> & stringVector) {
    for (int i = 0; i < stringVector.size(); i++) {
        graph.addNode(stringVector.at(i).substr(0, stringVector.at(i).find(',')), i);
    }
}

void createEdges(Graph& graph, vector<string>& stringVector) {
    vector<string> line;
    
    string startNode = "";
    string endNode = "";
    int newWeight = 0;

    for (int i = 0; i < stringVector.size(); i++) {
        line = splitString(stringVector.at(i));
        int j = 1;

        while (j < line.size()) {
            startNode = line.at(0);
            endNode = line.at(j);
            newWeight = stoi(line.at(j + 1));

            graph.addEdge(startNode, endNode, newWeight);
            j = j + 2;
        }
    }
}

int main()
{
    Graph graph(23);

    vector<string> fileData = readFile();

    createNodes(graph, fileData);

    createEdges(graph, fileData);

    for (int i = 0; i < 23; i++) {
        graph.printNode(graph.findNode(i).name);
    }
    
    return 0;
}