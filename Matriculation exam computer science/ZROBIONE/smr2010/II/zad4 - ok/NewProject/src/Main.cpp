#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

void wczytaj(vector<vector<string>>& plik) {
	ifstream file("anagram.txt");
	vector<string> wiersz;
	string slowo;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 200; i++) {
			wiersz.clear();
			for (unsigned int j = 0; j < 5; j++) {
				file >> slowo;
				wiersz.push_back(slowo);
			}
			plik.push_back(wiersz);
		}
		file.close();
	}
}

void a(const vector<vector<string>>& plik) {
	ofstream file("odp_4a.txt");
	file << "a:" << endl;
	unsigned int liczbaZnakow;
	bool wierszZgodny;
	for (unsigned int i = 0; i < 200; i++) {
		wierszZgodny = true;
		for (unsigned int j = 0; j < 5; j++) {
			if (j == 0) {
				liczbaZnakow = plik[i][j].size();
			}
			else if (plik[i][j].size() != liczbaZnakow) {
				wierszZgodny = false;
				break;
			}
		}
		if (wierszZgodny) {
			for (unsigned int j = 0; j < 5; j++) {
				file << plik[i][j] << " ";
			}
			file << endl;
		}
	}
	file.close();
}

/*void b(const vector<vector<string>>& plik) {
	ofstream file("odp_4b.txt");
	file << "b:" << endl;
	vector<char> slowo;
	vector<char> anagram;
	bool czyAnagram;
	for (unsigned int i = 0; i < 200; i++) {
		czyAnagram = true;
		slowo.clear();
		// czy to konieczne - ??? slowo.resize(0);
		for (unsigned int j = 0; j < 5; j++) {
			anagram.clear();
			// czy to konieczne - ??? anagram.resize(0);
			if (j == 0) {
				for (unsigned int k = 0; k < plik[i][j].size(); k++) {
					slowo.push_back(plik[i][j][k]);
				}
				sort(slowo.begin(), slowo.end());
			}
			else {
				for (unsigned int k = 0; k < plik[i][j].size(); k++) {
					anagram.push_back(plik[i][j][k]);
				}
				sort(anagram.begin(), anagram.end());
				if (slowo != anagram) {
					czyAnagram = false;
					break;
				}
			}
		}
		if (czyAnagram) {
			for (unsigned int j = 0; j < 5; j++) {
				file << plik[i][j] << " ";
			}
			file << endl;
		}
	}
	file.close();
}*/

void b(const vector<vector<string>>& plik) {
	ofstream file("odp_4b.txt");
	file << "b:" << endl;
	string slowo, anagram;
	bool czyAnagram;
	for (unsigned int i = 0; i < 200; i++) {
		czyAnagram = true;
		slowo = plik[i][0];
		sort(slowo.begin(), slowo.end());
		for (unsigned int j = 1; j < 5; j++) {
			anagram = plik[i][j];
			sort(anagram.begin(), anagram.end());
			if (slowo != anagram) {
				czyAnagram = false;
				break;
			}
		}
		if (czyAnagram) {
			for (unsigned int j = 0; j < 5; j++) {
				file << plik[i][j] << " ";
			}
			file << endl;
		}
	}
	file.close();
}

int main() {
	vector<vector<string>> plik;
	wczytaj(plik);

	// a
	a(plik);
	// b
	b(plik);

	cout << endl << "END"; cin.get();
}