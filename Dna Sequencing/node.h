#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
class Node {
public:
	~Node();
	Node();
	Node(string seq);
	string seq;
	int inDegree;
	int outDegree;
	vector<Node> adjacencyList;
private:
};
