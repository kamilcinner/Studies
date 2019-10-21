#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void wczytaj(vector<unsigned int>& skoki) {
	ifstream file("dziennik.txt");
	skoki.resize(310);
	if (file.is_open()) {
		for (unsigned int i = 0; i < 310; i++) {
			file >> skoki[i];
		}
		file.close();
	}
}

void p1(const vector<unsigned int>& skoki) {
	unsigned int ile = 0, seria = 1;
	for (unsigned int i = 1; i < 310; i++) {
		if (skoki[i] > skoki[i - 1]) {
			seria++;
		}
		else {
			if (seria > 3) ile++;
			seria = 1;
		}
	}
	cout << "1: " << ile << endl;
}

void p2(const vector<unsigned int>& skoki) {
	unsigned int max, min, nr_max, nr_min;
	max = min = skoki[0];
	nr_max = nr_min = 1;
	for (unsigned int i = 1; i < 310; i++) {
		if (skoki[i] > max) {
			max = skoki[i];
			nr_max = i + 1;
		}
		else if (skoki[i] < min) {
			min = skoki[i];
			nr_min = i + 1;
		}
	}
	cout << "2:\nmin: " << min << "\nnr_min: " << nr_min << "\nmax: " << max << "\nnr_max: " << nr_max << endl;
}

void p3(const vector<unsigned int>& skoki) {
	unsigned int max = 0, seria = 1, index_start, index_end;
	for (unsigned int i = 1; i < 310; i++) {
		if (skoki[i] > skoki[i - 1]) {
			seria++;
		}
		else {
			if (seria > max) {
				max = seria;
				index_end = i - 1;
				index_start = index_end + 1 - seria;
			}
			seria = 1;
		}
	}
	if (seria > max) {
		max = seria;
		index_end = 310 - 1;
		index_start = index_end + 1 - seria;
	}
	cout << "3:\ndlugosc: " << max << "\ncm: " << skoki[index_end] - skoki[index_start] << endl;
}

int main() {
	vector<unsigned int> S;
	wczytaj(S);
	p1(S);
	p2(S);
	p3(S);

	cout << endl << "END"; cin.get();
}