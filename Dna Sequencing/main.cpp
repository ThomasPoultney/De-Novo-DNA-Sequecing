#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "node.h"
#include "graph.h"
#include "filereader.h"
using namespace std; // Sue me

int main(int argc, char const *argv[]) {
	bool DEBUG = true;
	DEBUG = argv[3];
	std::vector<Sequence> seqs = Filereader::readFile(argv[2],DEBUG);
	for (int i = 0; i < seqs.size(); i++) {
		cout << "Sequence read: " << seqs[i].seq.c_str() << endl;
	}

 	std::vector<string> kmerVector;
	int kmerSize = atoi(argv[1]);

	Graph DBgraph;
	DBgraph.createGraph(kmerSize,seqs,DEBUG);
	return 0;
}
