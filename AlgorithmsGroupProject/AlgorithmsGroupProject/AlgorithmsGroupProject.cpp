#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int index; //Even though the nodes are already stored in a vector, providing them a custom index makes cross-referencing between nodes and edges easier later
    string name;

    //For Dijkstra's Algorithm
    int shortestDistance;
    Node* previousNode; //Necessary for determining route
    bool visited;
};

struct Edge {
    int weight;
    Node* start; //Even though the graph is undirected, we still need to distinguish the nodes being connected by each edge
    Node* end;
};

class Graph {
private:
    vector<Node> nodes;
    vector<vector<Edge>> edges; //Edges are stored in vectors for each node. eg: edges.at(0).at(0) will give the first edge connected to node A

public:
    Graph(int nodeCountInit) { 
        edges.resize(nodeCountInit);
    }

    void addNode(string name, int index) {
        Node node;
        node.name = name;
        node.index = index;

        node.shortestDistance = 1000; //Initial distance set to high value for use in Dijkstra's algorithm later
        node.previousNode = nullptr;
        node.visited = false;
        
        nodes.push_back(node); //Nodes are added in order according to text document, so we can always push to the back of the nodes vector when creating them
    }

    Node* findNode(string name) { //This will be used frequently to get references to nodes
        Node* temp;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).name == name) {
                temp = &nodes.at(i);
                return &(*temp);
            }
        }
        return nullptr;
    }
    Node* findNode(int index) { //Being able to find a node based on both name and index opens up more flexibility
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

        edges.at(findNode(startNode)->index).push_back(edge); //Both the start and end node store the edge
        edges.at(findNode(endNode)->index).push_back(edge);
    }

    void printNode(string name) {
        cout << "Node " << findNode(name)->name << " is connected to: " << endl;
        for (int i = 0; i < edges.at(findNode(name)->index).size(); i++) {
            if (edges.at(findNode(name)->index).at(i).end->name == name) { //Since one of the nodes is arbitrarily considered the "start" of an edge, we need to ensure we get the proper accompanying node
                cout << "\t" << edges.at(findNode(name)->index).at(i).start->name << " with a weight of " << edges.at(findNode(name)->index).at(i).weight << endl;
            }
            else {
                cout << "\t" << edges.at(findNode(name)->index).at(i).end->name << " with a weight of " << edges.at(findNode(name)->index).at(i).weight << endl;
            }
        }
    }

    void dijkstra(string startName) {
        Node* currentNode = &nodes.at(findNode(startName)->index);
        currentNode->shortestDistance = 0; //Per Dijkstra's algorithm, the distance of the start node from the start node is 0
        Node* nextNode;
        Node* nodeToVisit = nullptr;

        vector<Node*> unvisitedNodes; //This will create our priority queue for unvisited edges

        for (int i = 0; i < nodes.size(); i++) { //Iterates once per node, since each node is visited once
            for (int j = 0; j < edges.at(currentNode->index).size(); j++) { //Iterates through each edge for the current node
                if (edges.at(currentNode->index).at(j).end->name == currentNode->name) nextNode = edges.at(currentNode->index).at(j).start;
                else nextNode = edges.at(currentNode->index).at(j).end; //We need to distinguish if the "start" or "end" of the edge is the next node, instead of the current node

                if (currentNode->shortestDistance + edges.at(currentNode->index).at(j).weight < nextNode->shortestDistance) {
                    nextNode->shortestDistance = currentNode->shortestDistance + edges.at(currentNode->index).at(j).weight;
                    nextNode->previousNode = currentNode; //Update shortest distance and previous node per Dijkstra's algorithm
                }

                if (!nextNode->visited) unvisitedNodes.push_back(nextNode); //Each new node encountered gets added to the priority queue

                if (unvisitedNodes.size() > 0) nodeToVisit = unvisitedNodes.at(0); //Default assignment in case we need to go back in the priority queue (if all of the nodes connected to the current node have already been visited)

                for (int ii = 0; ii < unvisitedNodes.size(); ii++) { //Find next node to visit based on which is closest to the start
                    if (unvisitedNodes.at(ii)->shortestDistance < nodeToVisit->shortestDistance) nodeToVisit = unvisitedNodes.at(ii);
                    if (unvisitedNodes.at(ii)->name == currentNode->name) unvisitedNodes.erase(unvisitedNodes.begin() + ii); //Avoid repeats
                }
            }
            currentNode->visited = true; //Ensure we don't visit the same node twice
            currentNode = nodeToVisit; //Iterate to next node
        }


        int shortestDist = nodes.at(findNode("H")->index).shortestDistance;
        char closestStation = 'H'; //Determine distance of chosen node from first charging station
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node H: " << nodes.at(findNode("H")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        Node* nodeToPrint = &nodes.at(findNode("H")->index);
        while (nodeToPrint->name != startName) { //Print route from charging station to current node
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("K")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("K")->index).shortestDistance;
            closestStation = 'K';
        }//Determine distance of chosen node from second charging station
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node K: " << nodes.at(findNode("K")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("K")->index);
        while (nodeToPrint->name != startName) { //Print route from charging station to current node
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("Q")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("Q")->index).shortestDistance;
            closestStation = 'Q';
        }//Determine distance of chosen node from third charging station
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node Q: " << nodes.at(findNode("Q")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("Q")->index);
        while (nodeToPrint->name != startName) { //Print route from charging station to current node
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        if (nodes.at(findNode("T")->index).shortestDistance < shortestDist) {
            shortestDist = nodes.at(findNode("T")->index).shortestDistance;
            closestStation = 'T';
        }//Determine distance of chosen node from fourth charging station
        cout << "Distance of Node " << nodes.at(findNode(startName)->index).name << " From Charging Station at Node T: " << nodes.at(findNode("T")->index).shortestDistance << endl;
        cout << "Route From Station: ";
        nodeToPrint = &nodes.at(findNode("T")->index);
        while (nodeToPrint->name != startName) { //Print route from charging station to current node
            cout << nodeToPrint->name << ", ";
            nodeToPrint = nodeToPrint->previousNode;
        }
        cout << startName << "\n" << endl;


        //Tell user which route is the shortest, out of the above options
        cout << "The Closest Station is Station " << closestStation << ", so You Should Follow the Route From Station " << closestStation << "." << endl;
    }
};

vector<string> readFile() {
    vector<string> stringVector;
    string line;

    //Simply return a string vector where each index corresponds to a line from the text file
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

    //Returns a string vector. The input vector is one line from the text file. The output vector is that same line but split by commas
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
    for (int i = 0; i < stringVector.size(); i++) { //The first character of each line in the text file corresponds to a new node, so creating the nodes is actually very straightforward
        graph.addNode(stringVector.at(i).substr(0, stringVector.at(i).find(',')), i);
    }
}

void createEdges(Graph& graph, vector<string>& stringVector) {
    vector<string> line;
    
    string startNode = "";
    string endNode = "";
    int newWeight = 0;

    for (int i = 0; i < stringVector.size(); i++) { //Iterate through each line of the text file
        line = splitString(stringVector.at(i)); //Each line is split into substrings
        int j = 1;

        while (j < line.size()) { //Creates edge according to text data
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
    transform(input.begin(), input.end(), input.begin(), ::toupper); //Ignore case

    graph.dijkstra(input);

    return 0;
}