#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "node.h"
#include "filereader.h"
using namespace std;
class Graph {
public:
	Graph();
	~Graph();
	vector<Node> nodeList;
	int kmerSize;
	void addNode(Node node);
	void createGraph(int kmerSize,std::vector<Sequence> seq,bool DEBUG);
	string fileString;

private:
	std::vector<string> getRightKmer(int kmerSize,std::vector<string> kmerVector);
	std::vector<string> getLeftKmer(int kmerSize,std::vector<string> kmerVector);
	std::vector<Node> eulerianPath;
	void createEdges(int kmerSize,std::vector<string> kmerVector,bool DEBUG);
	bool checkEulerianExists();
	bool checkDegree();
	void findEulerian(bool DEBUG);
	bool checkConnected(Node node);
	void printGraph();
	void dfs(int node, int numberOfEdges,bool DEBUG);
	void printDegrees();
	void printAdjaceny();
	void printEulerian();
	int calcNumberOfEdges();
	void removeTips();
	void simplification();

};
