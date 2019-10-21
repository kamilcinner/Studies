#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void wczytaj(string* S) {
	ifstream file("slowa.txt");
	if (file.is_open()) {
		for (int i = 0; i < 1000; i++)
			file >> S[i];
		file.close();
	}
}

int zad1(string* S) {
	int jedynki, zera, ile = 0;
	for (int i = 0; i < 1000; i++) {
		jedynki = 0;
		zera = 0;
		for (int j = 0; j < S[i].size(); j++) {
			if (S[i][j] == '1') jedynki++;
			else zera++;
		}
		if (zera > jedynki) ile++;
	}
	return ile;
}

int zad2(string* S) {
	int l, p, licz = 0;
	for (int i = 0; i < 1000; i++) {
		if (S[i][0] != '0' || S[i][S[i].size() - 1] != '1') continue;
		l = -1;
		p = S[i].size();
		while (l + 1 < S[i].size() && S[i][l + 1] == '0') l++;
		while (p - 1 >= 0 && S[i][p - 1] == '1') p--;
		if (l == p - 1) licz++;
	}
	return licz;
}

int zad3(string* S) {
	ofstream file("wynik.txt");
	int max1, max2, MAX = 0;
	for (int i = 0; i < 1000; i++) {
		max1 = 0;
		max2 = 0;
		for (int j = 0; j < S[i].size(); j++) {
			if (S[i][j] == '0') max2++;
			else if (max2 > max1) {
				max1 = max2;
				max2 = 0;
			}
			else max2 = 0;
		}
		if (max2 > max1) max1 = max2;
		if (max1 > MAX) {
			MAX = max1;
			file << endl << MAX << endl << S[i] << endl;
		}
		else if (max1 == MAX) {
			file << S[i] << endl;
		}
	}
	file.close();
	return MAX;
}

int main() {
	string* S = new string[1000];
	wczytaj(S);
	// zad 1
	cout << "zad1: " << zad1(S) << endl;
	// zad 2
	cout << "zad2: " << zad2(S) << endl;
	// zad 3
	cout << "zad3: " << zad3(S) << endl;

	cout << endl << "END"; cin.get();
}