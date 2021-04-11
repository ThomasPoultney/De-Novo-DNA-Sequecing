#include "node.h"

Node::Node() {

}

Node::Node(std::string seq) {
	this->seq = seq;
	this->inDegree = 0;
	this->outDegree = 0;
	vector<Node> nodeList;
	vector<Node> adjacencyList;
}

Node::~Node() {

}
