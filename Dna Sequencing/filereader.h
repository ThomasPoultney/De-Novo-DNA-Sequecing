#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Sequence {
	string id;
	string seq;
	string qual;
};

namespace Filereader {
	void printSeq(Sequence s);
	vector<Sequence> readFile(string fileLoc,bool DEBUG);
};
