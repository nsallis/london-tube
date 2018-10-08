#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "utility.h"

using namespace std;

// there should be 13 stations in the test file


const string INPUT_FILE_NAME = "test.txt";

class Node {
    public:
        string name;
        int value;
        vector<Node*> children;

        string toString(void) {
            return "Name: " + name + " | Value: " + std::to_string(value);
        }
};

std::map<std::string, Node*> nodes;

Node* buildNodes(void) {
    string line;
    std::ifstream infile(INPUT_FILE_NAME);
    while (std::getline(infile, line)){
        vector <string> stations;
        stations = split(line, ", ");
//        cout << stations[0] << " | " << stations[1] << endl;
        Node* station1;
        Node* station2;

        if(nodes.find(stations[0]) == nodes.end()) {
            cout << "not found" << endl;
            station1 = new Node();
            station1-> name = stations[0];
        }else{
            cout << "here" << endl;
            station1 = nodes[stations[0]];
        }

        if(nodes.find(stations[1]) == nodes.end()) {
            cout << "not found" << endl;
            station2 = new Node();
            station2-> name = stations[1];
        }else{
            cout << "here" << endl;
            station2 = nodes[stations[1]];
        }

        station1->children.push_back(station2);
        station2->children.push_back(station1);
    }
    cout << nodes.size() << endl;
}

void doNode(Node* node, int currentValue) {
    if(node->value >= currentValue) {
        node->value = currentValue;
        // loop through all children in node
//        for(int i = 0; i < MAX_CHILD_NODES; i++) {
//            if(node->children[i] != nullptr) {
//                doNode(node->children[i], currentValue++);
//            }
//        }
    }
}

int main()
{
    buildNodes();
    Node root = Node();
    root.name = "East Ham";
    cout << root.toString() << endl;
    return 0;
}
