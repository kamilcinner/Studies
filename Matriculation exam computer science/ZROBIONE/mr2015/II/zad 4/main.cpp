//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void wczytaj(string *S) {
	ifstream file("liczby.txt");
	if (file.is_open()) {
		for (int i = 0; i < 1000; i++) {
			file >> S[i];
		}
		file.close();
	}
}
int zad1(string *S) {
	int zera, jedynki, ile = 0;
	for (int i = 0; i < 1000; i++) {
		zera = 0;
		jedynki = 0;
		for (int j = 0; j < S[i].size(); j++) {
			if (S[i][j] == '0') zera++;
			else jedynki++;
		}
		if (zera > jedynki) ile++;
	}
	return ile;
}
void zad2(string *S, int &P2, int &P8) {
	P2 = 0; P8 = 0;
	int s;
	for (int i = 0; i < 1000; i++) {
		s = S[i].size();
		if (s > 3 && S[i][s - 1] == '0' && S[i][s - 2] == '0' && S[i][s - 3] == '0') {
			P2++;
			P8++;
		}
		else if (s > 1 && S[i][s - 1] == '0') P2++;
	}
}
void zad3(string *S, int &nrMax, int &nrMin) {
	string max, min;
	int minSize = 250, maxSize = 0;
	for (int i = 0; i < 1000; i++) {
		if (S[i].size() > maxSize) {
			maxSize = S[i].size();
			max = S[i];
			nrMax = i + 1;
		}
		if (S[i].size() < minSize) {
			minSize = S[i].size();
			min = S[i];
			nrMin = i + 1;
		}
	}
	for (int i = 0; i < 1000; i++) {
		if (S[i].size() == maxSize) {
			for (int j = 1; j < maxSize; j++) {
				if (S[i][j] > max[j]) {
					max = S[i];
					nrMax = i + 1;
					break;
				}
				else if (S[i][j] < max[j]) break;
			}
		}
		else if (S[i].size() == minSize) {
			for (int j = 1; j < minSize; j++) {
				if (S[i][j] < min[j]) {
					min = S[i];
					nrMin = i + 1;
					break;
				}
				else if (S[i][j] > min[j]) break;
			}
		}
	}
}

int main() {
	string *S = new string[1000];
	wczytaj(S);
	// zad 1
	cout << "zad1 = " << zad1(S) << endl;
	// zad 2
	int p2, p8;
	zad2(S, p2, p8);
	cout << "zad2:" << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p8 = " << p8 << endl;
	// zad 3
	int max, min;
	zad3(S, max, min);
	cout << "zad3:" << endl;
	cout << "max = " << max << endl;
	cout << "min = " << min << endl;

	system("pause");
	return 0;
}