#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int index;
    bool isChargingStation;
    string name;

    //For Dijkstra's Algorithm
    int shortestDistance;
    Node* previousNode;
    bool visited;
};

struct Edge {
    int weight;
    Node* start;
    Node* end;
};

class Graph {
private:
    int nodeCount;
    vector<Node> nodes;
    vector<vector<Edge>> edges;
    Node* startNode;

public:
    Graph(int nodeCountInit) : nodeCount(nodeCountInit) { 
        edges.resize(nodeCountInit); 
        startNode = findNode("A");
    }

    void addNode(string name, int index) {
        Node node;
        node.name = name;
        node.index = index;

        node.shortestDistance = 1000;
        node.previousNode = nullptr;
        node.visited = false;

        if (node.name == "H" || node.name == "K" || node.name == "Q" || node.name == "T") node.isChargingStation = true;
        else node.isChargingStation = false;
        
        nodes.push_back(node);
    }

    Node* findNode(string name) {
        Node* temp;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).name == name) {
                temp = &nodes.at(i);
                return &(*temp);
            }
        }
        return nullptr;
    }
    Node* findNode(int index) {
        Node* temp;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).index == index) {
                temp = &nodes.at(i);
                return &(*temp);
            }
        }
        return nullptr;
    }

    void addEdge(string startNode, string endNode, int weight) {
        Edge edge;
        edge.weight = weight;
        edge.start = findNode(startNode);
        edge.end = findNode(endNode);

        edges.at(findNode(startNode)->index).push_back(edge);
        edges.at(findNode(endNode)->index).push_back(edge);
    }

    void printNode(string name) {
        cout << "Node " << findNode(name)->name << " is connected to: " << endl;
        for (int i = 0; i < edges.at(findNode(name)->index).size(); i++) {
            if (edges.at(findNode(name)->index).at(i).end->name == name) {
                cout << "\t" << edges.at(findNode(name)->index).at(i).start->name << " with a weight of " << edges.at(findNode(name)->index).at(i).weight << endl;
            }
            else {
                cout << "\t" << edges.at(findNode(name)->index).at(i).end->name << " with a weight of " << edges.at(findNode(name)->index).at(i).weight << endl;
            }
        }
    }

    void dijkstra(string startName) {
        Node* currentNode = &nodes.at(findNode(startName)->index);
        currentNode->shortestDistance = 0;
        Node* nextNode;
        Node* nodeToVisit = nullptr;

        vector<Node*> unvisitedNodes;

        for (int i = 0; i < nodes.size(); i++) {
            for (int j = 0; j < edges.at(currentNode->index).size(); j++) {
                if (edges.at(currentNode->index).at(j).end->name == currentNode->name) nextNode = edges.at(currentNode->index).at(j).start;
                else nextNode = edges.at(currentNode->index).at(j).end;

                if (currentNode->shortestDistance + edges.at(currentNode->index).at(j).weight < nextNode->shortestDistance) {
                    nextNode->shortestDistance = currentNode->shortestDistance + edges.at(currentNode->index).at(j).weight;
                    nextNode->previousNode = currentNode;
                }

                if (!nextNode->visited) unvisitedNodes.push_back(nextNode);

                if (unvisitedNodes.size() > 0) nodeToVisit = unvisitedNodes.at(0);

                for (int ii = 0; ii < unvisitedNodes.size(); ii++) {
                    if (unvisitedNodes.at(ii)->shortestDistance < nodeToVisit->shortestDistance) nodeToVisit = unvisitedNodes.at(ii);
                    if (unvisitedNodes.at(ii)->name == currentNode->name) unvisitedNodes.erase(unvisitedNodes.begin() + ii);
                }
            }
            currentNode->visited = true;
            currentNode = nodeToVisit;
        }


        int shortestDist = nodes.at(findNode("H")->index).shortestDistance;
        char closestStation = 'H';
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node H: " << nodes.at(findNode("H")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        Node* nodeToPrint = &nodes.at(findNode("H")->index);
        while (nodeToPrint->name != startName) {
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("K")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("K")->index).shortestDistance;
            closestStation = 'K';
        }
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node K: " << nodes.at(findNode("K")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("K")->index);
        while (nodeToPrint->name != startName) {
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("Q")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("Q")->index).shortestDistance;
            closestStation = 'Q';
        }
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node Q: " << nodes.at(findNode("Q")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("Q")->index);
        while (nodeToPrint->name != startName) {
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("T")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("T")->index).shortestDistance;
            closestStation = 'T';
        }
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node T: " << nodes.at(findNode("T")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("T")->index);
        while (nodeToPrint->name != startName) {
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        cout << "The Closest Station is Station " << closestStation << ", so You Should Follow the Route From Station " << closestStation << "." << endl;
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

    cout << "Which Node Would You Like to Start At? (Type a Character From A-W) ";
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);

    graph.dijkstra(input);

    return 0;
}