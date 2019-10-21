#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void wczytaj(string** S) {
	ifstream file("slowa.txt");
	if (file.is_open()) {
		for (int i = 0; i < 1000; i++)
			for (int j = 0; j < 2; j++)
				file >> S[i][j];
		file.close();
	}
}

int zad1(string** S) {
	int licz = 0;
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 2; j++)
			if (S[i][j].back() == 'A') licz++;
	return licz;
}

int zad2(string** S) {
	int licz = 0;
	int k;
	for (int i = 0; i < 1000; i++) {
		if (S[i][0].size() > S[i][1].size()) continue;
		for (int j = 0; j < S[i][1].size(); j++) {
			k = 0;
			while (k < S[i][0].size() && k + j < S[i][1].size() && S[i][0][k] == S[i][1][k + j]) {
				k++;
			}
			if (k == S[i][0].size()) {
				licz++;
				break;
			}
		}
	}
	return licz;
}

int zad3(string** S) {
	int licz = 0;
	vector<char> V1, V2;

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < S[i][0].size(); j++) V1.push_back(S[i][0][j]);
		sort(V1.begin(), V1.end());
		for (int j = 0; j < S[i][1].size(); j++) V2.push_back(S[i][1][j]);
		sort(V2.begin(), V2.end());
		if (V1 == V2) licz++;

		//V1.empty(); V2.empty();
		//V1.resize(0); V2.resize(0);
		V1.clear(); V2.clear();
	}
	return licz;
}

int main() {
	string** S;
	S = new string* [1000];
	for (int i = 0; i < 1000; i++)
		S[i] = new string[2];
	
	wczytaj(S);

	// zad 1
	cout << "zad1: " << zad1(S) << endl;
	// zad 2
	cout << "zad2: " << zad2(S) << endl;
	// zad 3
	cout << "zad3: " << zad3(S) << endl;
		
	cout << endl << "END";
	cin.get();
}