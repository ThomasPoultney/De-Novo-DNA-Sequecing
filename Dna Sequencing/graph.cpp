#include "graph.h"

Graph::Graph() {
	//cout << "Constructor called" << endl;
}

Graph::~Graph() {
	//std::cout << "Deconstructor called:" << std ::endl;
}

void Graph::addNode(Node node){
	this->nodeList.push_back(node);
}

void Graph::removeTips(){
	for (int i = 0; i < this->nodeList.size(); i++) {
		if (nodeList[i].inDegree == 0 && nodeList[i].outDegree == 1) {
			this->nodeList.erase(nodeList.begin()+i);
		}
	}
}

void Graph::simplification(){
	int simplificationNodesFound = 0;
	for (int i = 0; i < this->nodeList.size(); i++) {
		if (nodeList[i].outDegree == 1 && nodeList[i].adjacencyList[0].inDegree == 1) {
			simplificationNodesFound +=1;
			this->nodeList[i].seq.append(nodeList[i].adjacencyList[0].seq.substr(nodeList[i].adjacencyList[0].seq.length()-1,nodeList[i].adjacencyList[0].seq.length()));
			cout << "NEW NODE = " << nodeList[i].adjacencyList[0].seq << endl;
			nodeList[i].adjacencyList.erase(nodeList[i].adjacencyList.begin());
			nodeList[i].adjacencyList[0].seq;
			string targetSeq = nodeList[i].adjacencyList[0].seq;
			int targetSeqIndex;
			for (int j = 0; j < this->nodeList.size(); j++) {
				if (nodeList[j].seq == targetSeq) {
					targetSeqIndex = j;
				}
			}
			nodeList.erase(nodeList.begin() + targetSeqIndex);
			for (int j = 0; j < this->nodeList.size(); j++) {
				cout << this->nodeList[j].seq << endl;
			}
			printGraph();
			break;
		}
	}

	if (simplificationNodesFound != 0) {
		simplification();
	} else {
		cout << "After simplification: " << endl;
		printGraph();
	}

}

void Graph::createGraph(int kmerSize,std::vector<Sequence> seqs,bool DEBUG) {
	std::vector<string> kmerVector;
	this->kmerSize = kmerSize;
	if (DEBUG) {

		cout << "-----------------------------------------------" << endl;
		cout << "Creating nodes..." << endl;
	}
	for (int i = 0; i < seqs.size(); i++) {
		string currentSequence = seqs[i].seq;
		for (int j = 0; j < currentSequence.length() - kmerSize; j++) {
			string kmer = currentSequence.substr(j,kmerSize);
			//checks if the kmer has already been found
			int mycount = std::count(kmerVector.begin(), kmerVector.end(), kmer);
			if (mycount == 0) {
				if (DEBUG) {
					//
				}
				kmerVector.push_back(kmer);
				Node temp(kmer);
				this->addNode(temp);
				if (DEBUG) {
					cout << "Node created for kmer " << kmer << endl;
				}
			} else {
				//cout << "duplicate" << endl;
			}
		}

		if (DEBUG) {
			cout << "-----------------------------------------------" << endl;
		}
	}

	this-> createEdges(kmerSize,kmerVector,DEBUG);
	//simplification();
	this -> removeTips();
	if (checkEulerianExists() == true) {
		this-> findEulerian(DEBUG);
	} else {
		cout << "No eulerian path exists in this graph best approximation...." << endl;
		this-> findEulerian(DEBUG);
	}


}
void Graph::findEulerian(bool DEBUG) {
	int startNode = 0;
		for (int i = 0; i < this->nodeList.size(); i++) {
			if (nodeList[i].inDegree - nodeList[i].outDegree == -1) {
				startNode = i;
			}
		}
		if (DEBUG) {
			cout << "Finding Eulerian path... " << endl;
			cout << "Start Node = " << nodeList[startNode].seq << endl;
		}
		int numberOfEdges = calcNumberOfEdges();
		dfs(startNode,numberOfEdges,DEBUG);
		printEulerian();



		if (DEBUG == true) {
			cout << "-----------------------------------------------" << endl;
		}


}

void::Graph::printEulerian() {
	cout << eulerianPath.back().seq;
	for (int i = this->eulerianPath.size()-1; i > 0; i--) {
		cout << eulerianPath[i].seq.substr(this->kmerSize-1,this->kmerSize);
	}
	cout << endl;
}

// void Graph::dfs(Node curNode) {
// 	Node nextNode;
//  	while (curNode.outDegree != 0) {
// 		cout<< "Current Node is: " << curNode.seq <<endl;
// 	 	nextNode = curNode.adjacencyList[0];
// 		curNode.outDegree - 1;
// 		cout<< "Next Node is " << nextNode.seq << endl;
// 		curNode.adjacencyList.erase(curNode.adjacencyList.begin());
// 		cout<<"After erase next node is:  " << curNode.adjacencyList[0].seq <<endl;
// 		printGraph();
// 		cout << "\nRecursing\n" << endl;
// 		dfs(nextNode);
//  	}
// 	cout << "Stuck";
// 	auto it = eulerianPath.begin();
// 	it = eulerianPath.insert(it,curNode);
// 	cout << "Stuck" << endl;
// }


int Graph::calcNumberOfEdges() {
	int numberOfEdges = 0;
	for (int i = 0; i < this->nodeList.size(); i++) {
		numberOfEdges += nodeList[i].outDegree;
	}
	return numberOfEdges;
}

void Graph::dfs(int curNode,int numberOfEdges,bool DEBUG) {

	if(eulerianPath.size() == numberOfEdges) {
		if (DEBUG) {
			cout << "Current Node is: " << nodeList[curNode].seq <<endl;
			cout<< "Finished... \n";
			cout << "-----------------------------------------------" << endl;
		}
		auto it = eulerianPath.begin();
		it = eulerianPath.insert(it,nodeList[curNode]);

	} else  {
		auto it = eulerianPath.begin();
		it = eulerianPath.insert(it,nodeList[curNode]);
		if (DEBUG) {
			cout << "Current Node is: " << nodeList[curNode].seq <<endl;
		}
		while (nodeList[curNode].outDegree != 0) {
			if(eulerianPath.size() == numberOfEdges+1) {
				break;
			}
			string nextNodeSeq = nodeList[curNode].adjacencyList[0].seq;
			int nextNodeIndex = 0;
			for (int i = 0; i < this->nodeList.size(); i++) {
				if (nodeList[i].seq.compare(nextNodeSeq) == 0) {
					nextNodeIndex = i;
					if (DEBUG) {
						cout << "Next node index is: " << nextNodeIndex << endl;
					}
					break;
				}
			}
			nodeList[curNode].outDegree - 1;
			if (DEBUG) {
				cout<< "Next Node is " << nodeList[nextNodeIndex].seq << endl;
			}
			nodeList[curNode].adjacencyList.erase(nodeList[curNode].adjacencyList.begin());
			//cout<<"After erase next node is:  " << nodeList[curNode].adjacencyList[0].seq <<endl;
			if (DEBUG) {
				cout << "\nRecursing\n" << endl;
			}
			dfs(nextNodeIndex,numberOfEdges,DEBUG);
		}
	}
}

// void Graph::findEulerian() {
// 	std::vector<Node> oddNodes;
// 	int numberOfEdges = 0;
// 	for (int i = 0; i < this->nodeList.size(); i++) {
// 		int balence = (nodeList[i].inDegree - nodeList[i].outDegree);
// 		//cout << "Node = " << nodeList[i].seq << " has an outDegree of " << nodeList[i].outDegree<< endl;
// 		numberOfEdges += nodeList[i].outDegree;
// 			for (int j = 0; j < this->nodeList[i].adjacencyList.size(); j++) {
// 				cout << this->nodeList[i].seq << " has adjacent edges: " << this->nodeList[i].adjacencyList[j].seq << endl;
// 			}
// 		if (balence == -1) {
// 			oddNodes.push_back(nodeList[i]);
// 		}
// 	}
// 	Node startingNode;
// 	if (oddNodes.size() >= 1) {
// 			startingNode = oddNodes[0];
// 			cout << "Starting Node = " << startingNode.seq << endl;
// 	}
//
// 	Node currentNode = startingNode;
// 	std::vector<Node> nodePath;
// 	std::tuple<Node, Node> exploredEdges();
// 	int numExploredEdges = 0;
// 	nodePath.push_back(startingNode);
//
// 	while(numExploredEdges < numberOfEdges) {
// 		for (int i = 0; i < currentNode.adjacencyList.size(); i++) {
// 			if (checkConnected(currentNode.adjacencyList[i]) == true) {
// 				nodePath.push_back(currentNode.adjacencyList[i]);
// 				currentNode.adjacencyList.erase(currentNode.adjacencyList.begin()+i);
// 				numExploredEdges +=1;
// 				cout << numExploredEdges << endl;
// 				currentNode = nodePath.back();
// 				cout << currentNode.seq << endl;
// 				break;
// 			}
// 		}
// 	}
// }


bool checkConnected(Node node) {
	return true;
}

void Graph::printAdjaceny(){
	for (int i = 0; i < this->nodeList.size(); i++) {
		cout << "Node: " << nodeList[i].seq << " Has: ";
		for (int j = 0; j < this->nodeList[i].adjacencyList.size(); j++) {
			cout << nodeList[i].adjacencyList[j].seq << " ";
		}
		cout << endl;
	}
}

bool Graph::checkEulerianExists() {
	if (checkDegree() == true) {
		return true;
	} else {
		return false;
	}
}

bool Graph::checkDegree() {
	int numberOfBalencedNodes = 0;
	int numberOfInNodes = 0;
	int numberOfOutNodes = 0;

	for (int i = 0; i < this->nodeList.size(); i++) {
	 	int outBalence = (nodeList[i].outDegree - nodeList[i].inDegree);
		int inBalence  = (nodeList[i].inDegree - nodeList[i].outDegree);
		int balence = (nodeList[i].inDegree - nodeList[i].outDegree);
		if(balence == 0) {
			numberOfBalencedNodes +=1;
		} else if (outBalence == 1) {
			numberOfOutNodes += 1;
		} else if (inBalence == 1 ) {
			numberOfInNodes +=1;
		}
	}

	if (numberOfInNodes == 1 && numberOfOutNodes == 1 && numberOfBalencedNodes == nodeList.size() - 2) {
		return true;
	} else {
		return false;
	}
}

void Graph::createEdges(int kmerSize,std::vector<string> kmerVector,bool DEBUG) {
	std::vector<string> LeftKmerVector = getLeftKmer(kmerSize, kmerVector);
	std::vector<string> RightKmerVector = getRightKmer(kmerSize, kmerVector);

	if (DEBUG) {
		cout << "Creating Edges..." << endl;
	}

	for (int i = 0; i < kmerVector.size(); i++) {
		for (int j = 0; j < kmerVector.size(); j++) {
			if (j != i) {
				if (RightKmerVector[i] == LeftKmerVector[j]) {
					//
					if (DEBUG) {
						cout << "edge exists between node " <<kmerVector[i]<<" and node "  << kmerVector[j]<< endl;
					}
					this->nodeList[i].outDegree +=1;
					this->nodeList[j].inDegree +=1;
					this->nodeList[i].adjacencyList.push_back(this->nodeList[j]);
				}
				//edge exists
			}
		}
	}

	if (DEBUG) {
		printGraph();
		cout << "-----------------------------------------------" << endl;
	}
}

void Graph::printGraph() {
	int numberOfEdges = 0;
	for (int i = 0; i < this->nodeList.size(); i++) {
		numberOfEdges += nodeList[i].outDegree;
		for (int j = 0; j < this->nodeList[i].adjacencyList.size(); j++) {
	 		//cout << this->nodeList[i].seq << " has adjacent edges: " << this->nodeList[i].adjacencyList[j].seq << endl;
		}
	}
		cout << "The Graph has " << this->nodeList.size()  << " Nodes and " << numberOfEdges << " Edges" << endl;
}

void Graph::printDegrees() {
	int numberOfEdges = 0;
	for (int i = 0; i < this->nodeList.size(); i++) {
		cout << "Node: " << this->nodeList[i].seq << "Has inDegree: " << this->nodeList[i].inDegree << "and outDegree " << this->nodeList[i].outDegree << endl;
	}
}
std::vector<string> Graph::getLeftKmer(int kmerSize,std::vector<string> kmerVector) {
	std::vector<string> LeftKmerVector;
	for (int i = 0; i < kmerVector.size(); i++) {
		LeftKmerVector.push_back(kmerVector[i].substr(0,kmerSize-1));
	}
	return LeftKmerVector;
}

std::vector<string> Graph::getRightKmer(int kmerSize,std::vector<string> kmerVector) {
	std::vector<string> RightKmerVector;
	for (int i = 0; i < kmerVector.size(); i++) {
		RightKmerVector.push_back(kmerVector[i].substr(1,kmerSize));
	}
	return RightKmerVector;

}
