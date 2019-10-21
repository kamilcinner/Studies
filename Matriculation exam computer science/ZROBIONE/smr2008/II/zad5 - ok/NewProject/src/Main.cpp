#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void wczytaj(vector<string>& slowa) {
	ifstream file("slowa.txt");
	string slowo;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 1000; i++) {
			file >> slowo;
			slowa.push_back(slowo);
		}
		file.close();
	}
}

void a(const vector<string>& slowa) {
	ofstream file("hasla_a.txt");
	unsigned int max, min;
	string minS, maxS, haslo;
	for (unsigned int i = 0; i < 1000; i++) {
		haslo.clear();
		for (unsigned int j = 0; j < slowa[i].size(); j++) {
			haslo.push_back(slowa[i][slowa[i].size() - 1 - j]);
		}
		if (i == 0) {
			max = min = haslo.size();
			maxS = minS = haslo;
		}
		else if (haslo.size() > max) {
			max = haslo.size();
			maxS = haslo;
		}
		else if (haslo.size() < min) {
			min = haslo.size();
			minS = haslo;
		}
		file << haslo << endl;
	}
	file.close();
	ofstream file2("slowa_a.txt");
	file2 << "najkrotsze haslo: " << minS << "  dlugosc: " << min << endl;
	file2 << "najdluzsze haslo: " << maxS << "  dlugosc: " << max << endl;
	file2.close();
}

void b(const vector<string>& slowa) {
	ofstream file("hasla_b.txt");
	vector<string> hasla12;
	string haslo, maxH, minH;
	unsigned int max, min;
	unsigned long long int suma = 0;
	bool czyPalindrom;
	for (unsigned int i = 0; i < 1000; i++) {
		haslo.clear();
		for (unsigned int j = 0; j < slowa[i].size(); j++) {
			czyPalindrom = true;
			for (unsigned int k = 0; k < (slowa[i].size() - j) / 2; k++) {
				if (slowa[i][k] != slowa[i][slowa[i].size() - 1 - j - k]) {
					czyPalindrom = false;
					break;
				}
			}
			if (czyPalindrom) {
				for (/*unsigned*/ int k = slowa[i].size() - 1; k >= slowa[i].size() - j; k--) {
					haslo.push_back(slowa[i][k]);
				}
				haslo += slowa[i];
				file << haslo << endl;

				if (haslo.size() == 12) {
					hasla12.push_back(haslo);
				}
				suma += haslo.size();
				if (i == 0) {
					max = min = haslo.size();
					maxH = minH = haslo;
				}
				else if (haslo.size() > max) {
					max = haslo.size();
					maxH = haslo;
				}
				else if (haslo.size() < min) {
					min = haslo.size();
					minH = haslo;
				}
				break;
			}
		}
	}
	file.close();
	ofstream file2("slowa_b.txt");
	// 1
	file2 << "1:" << endl;
	for (unsigned int i = 0; i < hasla12.size(); i++) {
		file2 << hasla12[i] << endl;
	}
	// 2
	file2 << "2:" << endl;
	file2 << "najkrotsze haslo: " << minH << endl;
	file2 << "najdluzsze haslo: " << maxH << endl;
	// 3
	file2 << "3:" << endl;
	file2 << "suma dlugosci: " << suma << endl;

	file2.close();
}

int main() {
	vector<string> slowa;
	wczytaj(slowa);

	// a
	a(slowa);
	// b
	b(slowa);

	cout << endl << "END"; cin.get();
}