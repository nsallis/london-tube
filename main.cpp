#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "utility.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

// there should be 13 stations in the test file


const string INPUT_FILE_NAME = "lines.txt";
const int MAX_STEPS = 5;

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

void buildNodes(void) {
    string line;
    std::ifstream infile(INPUT_FILE_NAME);
    while (std::getline(infile, line)){
        vector <string> stations;
        stations = split(line, ", ");
        Node* station1;
        Node* station2;

        if(nodes.find(stations[0]) == nodes.end()) {
            station1 = new Node();
            station1->name = stations[0];
            station1->value = 9999;
            nodes[stations[0]] = station1;
        }else{
            station1 = nodes[stations[0]];
        }

        if(nodes.find(stations[1]) == nodes.end()) {
            station2 = new Node();
            station2->name = stations[1];
            station2->value = 9999;
            nodes[stations[1]] = station2;
        }else{
            station2 = nodes[stations[1]];
        }

        station1->children.push_back(station2);
        station2->children.push_back(station1);
    }
    return;
}

void doNode(Node* node, int currentValue) {
	if(currentValue > MAX_STEPS) {
		return;
	}
    if(node->value > currentValue || node->value == 0) {
        node->value = currentValue;
        int i;
        for(i = 0; i < static_cast<int>(node->children.size()); i++) {
        	doNode(node->children.at(i), currentValue + 1);
        }
        return;
    }
    return;
}

int main()
{
    auto t1 = chrono::high_resolution_clock::now(); // requires c++11
    buildNodes();
    Node* root = nodes.find("East Ham")->second;
    root->value = 0;
    doNode(root, 0);

    // iterate over mapped stations and find the ones with value of MAX_STEPS
    std::map<std::string, Node*>::iterator it = nodes.begin();
    while(it != nodes.end()) {

    	if(it->second->value == MAX_STEPS) {
    		cout << it->first << endl;
    	}
    	it++;
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() / float(1000000) << " milliseconds" << endl;

    return 0;
}
