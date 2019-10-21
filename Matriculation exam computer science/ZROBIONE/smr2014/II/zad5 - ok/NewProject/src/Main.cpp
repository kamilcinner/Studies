#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void load(string* S) {
	ifstream file("NAPIS.TXT");
	if (file.is_open()) {
		for (int i = 0; i < 1000; i++) {
			file >> S[i];
		}
		file.close();
	}
}

int zad1(string* S) {
	int sum, count = 0;
	bool isF;
	for (int i = 0; i < 1000; i++) {
		sum = 0;
		isF = true;
		for (int j = 0; j < S[i].size(); j++) {
			sum += S[i][j];
		}
		for (int j = 2; j < sum; j++) {
			if (sum % j == 0) isF = false;
		}
		if (isF) count++;
	}
	return count;
}

void zad2(string* S) {
	bool t;
	for (int i = 0; i < 1000; i++) {
		t = true;
		for (int j = 1; j < S[i].size(); j++) {
			if (S[i][j] <= S[i][j - 1]) {
				t = false;
				break;
			}
		}
		if (t) cout << S[i] << endl;
	}
}

void zad3(string* S) {
	vector<string> buffer;
	bool t;
	for (int i = 0; i < 1000; i++) {
		t = false;
		for (int j = 0; j < 1000; j++) {
			if (i == j) continue;
			if (S[i] == S[j]) {
				for (int k = 0; k < buffer.size(); k++) {
					if (S[i] == buffer[k]) t = true;
				}
				if (!t) {
					buffer.push_back(S[i]);
					cout << S[i] << endl;
				}
				break;
			}
		}
	}
}

int main() {
	string* S = new string[1000];
	load(S);
	// zad 1
	cout << "zad1: " << zad1(S) << endl << endl;
	// zad 2
	cout << "zad2:" << endl;
	zad2(S);
	// zad 3
	cout <<endl<< "zad3:" << endl;
	zad3(S);

	cout << endl << "END"; cin.get();
}