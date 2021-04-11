#include "filereader.h"


void Filereader::printSeq(Sequence s) {
	printf("id: %s\nsequence: %s\nquality: %s\n", s.id.c_str(), s.seq.c_str(), s.qual.c_str());
}

vector<Sequence> Filereader::readFile(string fileLoc,bool DEBUG) {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	ifstream file(fileLoc.c_str());
	if (DEBUG) {
		cout << "Reading... " << endl;
	}

	if (!file) {
		printf("Error opening file: \"%s\"\n", fileLoc.c_str());
		return {};
	}

	vector<Sequence> seqs = {};

	string line;
	while (getline(file, line)) {
		Sequence s;
		s.id = line;
		getline(file, s.seq);
		getline(file, s.qual);
		getline(file, s.qual);
		seqs.push_back(s);

	}
	if (DEBUG) {
		milliseconds duration = duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - ms;
		cout << "Done\nSequences read: " << seqs.size() << "\nDuration: "  << duration.count() << endl;
	}
	return seqs;
}
