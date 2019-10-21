#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void wczytaj(vector<vector<string>>& dane) {
	ifstream file("dane.txt");
	string slowo;
	vector<string> dwaSlowa;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 200; i++) {
			dwaSlowa.clear();
			for (unsigned int j = 0; j < 2; j++) {
				file >> slowo;
				dwaSlowa.push_back(slowo);
			}
			dane.push_back(dwaSlowa);
		}
		file.close();
	}
}

unsigned int a(const vector<vector<string>>& dane) {
	unsigned int ile = 0;
	bool czyPalindrom;
	for (unsigned int i = 0; i < 200; i++) {
		for (unsigned int j = 0; j < 2; j++) {
			czyPalindrom = true;
			for (unsigned int k = 0; k < dane[i][j].size() / 2; k++) {
				if (dane[i][j][k] != dane[i][j][dane[i][j].size() - 1 - k]) {
					czyPalindrom = false;
					break;
				}
			}
			if (czyPalindrom) ile++;
		}
	}
	return ile;
}

unsigned int b(const vector<vector<string>>& dane) {
	unsigned int ile = 0;
	bool rownosc;
	for (unsigned int i = 0; i < 200; i++) {
		for (unsigned int j = 0; j < dane[i][0].size() - dane[i][1].size() + 1; j++) {
			rownosc = true;
			for (unsigned int k = 0; k < dane[i][1].size(); k++) {
				if (dane[i][0][j + k] != dane[i][1][k]) {
					rownosc = false;
					break;
				}
			}
			if (rownosc) {
				ile++;
				break;
			}
		}
	}
	return ile;
}

vector<string> d(const vector<vector<string>>& dane, unsigned int& liczbaSklejonych) {
	liczbaSklejonych = 0;
	vector<string> slowaC;
	string slowoC_PK, slowoC_KP;
	bool rownosc, zawieraPK, zawieraKP; // K - koniec, P - poczatek
	unsigned int l;
	for (unsigned int i = 0; i < 200; i++) {
		// sprawdzamy czy A zawiera B
		for (unsigned int j = 0; j < dane[i][0].size() - dane[i][1].size() + 1; j++) {
			rownosc = true;
			for (unsigned int k = 0; k < dane[i][1].size(); k++) {
				if (dane[i][0][j + k] != dane[i][1][k]) {
					rownosc = false;
					break;
				}
			}
			if (rownosc) {
				slowaC.push_back(dane[i][0]);
				break;
			}
		}
		if (rownosc) continue;

		// skladamy poczatek A z koncem B
		slowoC_PK.clear();
		for (unsigned int j = 1; j < dane[i][1].size(); j++) { // 1 bo algorytm wyzej(1) sprawdza nam dla 0
			l = 0;
			zawieraPK = true;
			for (unsigned int k = j; k < dane[i][1].size(); k++) {
				if (dane[i][0][l] != dane[i][1][k]) {
					zawieraPK = false;
					break;
				}
				l++;
			}
			if (zawieraPK) {
				for (unsigned int k = 0; k < dane[i][1].size() - l; k++) {
					slowoC_PK.push_back(dane[i][1][k]);
				}
				slowoC_PK += dane[i][0];
				break;
			}
		}

		// skladamy koniec A z poczatkiem B
		slowoC_KP.clear();
		for (/*unsigned*/ int j = dane[i][1].size() - 2; j >= 0; j--) { // -2 bo algorytm wyzej(1) sprawdza nam dla -1
			l = dane[i][0].size() - 1;
			zawieraKP = true;
			for (/*unsigned*/ int k = j; k >= 0; k--) {
				if (dane[i][0][l] != dane[i][1][k]) {
					zawieraKP = false;
					break;
				}
				l--;
			}
			if (zawieraKP) {
				for (unsigned int k = 0; k <= l; k++) {
					slowoC_KP.push_back(dane[i][0][k]);
				}
				slowoC_KP += dane[i][1];
				break;
			}
		}

		// wybieramy krotszy zapis
		if (zawieraPK && zawieraKP) {
			if (slowoC_PK.size() <= slowoC_KP.size()) {
				slowaC.push_back(slowoC_PK);
			} else slowaC.push_back(slowoC_KP);
		}
		else if (zawieraPK) slowaC.push_back(slowoC_PK);
		else if (zawieraKP) slowaC.push_back(slowoC_KP);

		// sklejamy A i B
		else {
			slowoC_PK = dane[i][0] + dane[i][1];
			slowaC.push_back(slowoC_PK);
			liczbaSklejonych++;
		}
	}
	return slowaC;
}

int main() {
	ofstream file("zad_5.txt");
	vector<vector<string>> dane;
	wczytaj(dane);

	// a
	file << "a: " << a(dane) << endl;
	// b
	file << endl << "b: " << b(dane) << endl;
	// c
	unsigned int ile;
	vector<string> slowaC = d(dane, ile);
	file << endl << "c: " << ile << endl;
	// d
	file << endl << "d:" << endl;
	for (unsigned int i = 0; i < 200; i++) {
		file << i + 1 << ": " << slowaC[i] << endl;
	}
	
	file.close();

	cout << endl << "END"; cin.get();
}