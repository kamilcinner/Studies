//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void wczytaj(string *S) {
	ifstream file("sygnaly.txt");
	if (file.is_open()) {
		for (int i = 0; i < 1000; i++) {
			file >> S[i];
		}
		file.close();
	}
}
string zad1(string *S) {
	stringstream ss;
	for (int i = 39; i < 1000; i += 40) {
		ss << S[i][9];
	}
	return ss.str();
}
string zad2(string *S) {
	int liczba_liter, liczba_max = 0;
	string wyraz;
	char litery[100];
	bool is;
	for (int i = 0; i < 1000; i++) {
		liczba_liter = 0;
		for (int j = 0; j < S[i].size(); j++) {
			is = false;
			for (int k = liczba_liter - 1; k >= 0; k--)
				if (S[i][j] == litery[k]) { is = true; break; }
			if (!is) {
				litery[liczba_liter] = S[i][j];
				liczba_liter++;
			}
		}
		if (liczba_liter > liczba_max) {
			liczba_max = liczba_liter;
			wyraz = S[i];
		}
	}
	return wyraz;
}
void zad3(string *S) {
	ofstream file("zad3.txt");
	char min, max;
	for (int i = 0; i < 1000; i++) {
		min = max = S[i][0];
		for (int j = 0; j < S[i].size(); j++) {
			if (S[i][j] > max) max = S[i][j];
			if (S[i][j] < min) min = S[i][j];
		}
		if (max - min <= 10) {
			cout << S[i] << endl;
			file << S[i] << endl;
		}
	}
	file.close();
}

int main() {
	string *S = new string[1000];
	wczytaj(S);
	// zad1
	cout << "Przeslanie: " << zad1(S) << endl;
	// zad2
	cout << "Wyraz z najwieksza iloscia roznych liter: " << endl << zad2(S) << endl;
	// zad3
	cout << "WYrazy, ktorych liteery oddalone sa od siebie o co najwyzej 10:" << endl;
	zad3(S);
	
	system("pause");
	return 0;
}
