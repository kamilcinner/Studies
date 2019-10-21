#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Slowo {
	string tresc;
	unsigned int liczba_wystapien = 0;
};

void wczytaj(vector<string>& slowa) {
	ifstream file("dane.txt");
	slowa.resize(1000);
	if (file.is_open()) {
		for (unsigned int i = 0; i < 1000; i++) {
			file >> slowa[i];
		}
		file.close();
	}
}

void a(const vector<string>& slowa) {
	vector<unsigned int> liczba_wystapien;
	vector<string> slowa_w_bazie;
	bool slowo_jest_w_bazie;
	for (unsigned int i = 0; i < 1000; i++) {
		slowo_jest_w_bazie = false;
		for (unsigned int j = 0; j < slowa_w_bazie.size(); j++) {
			if (slowa[i] == slowa_w_bazie[j]) {
				slowo_jest_w_bazie = true;
				liczba_wystapien[j]++;
				break;
			}
		}
		if (!slowo_jest_w_bazie) {
			slowa_w_bazie.push_back(slowa[i]);
			liczba_wystapien.push_back(1);
		}
	}
	unsigned int ile_a1 = 0, ile_a3 = 0;
	string slowo_a2;
	for (unsigned int i = 0; i < slowa_w_bazie.size(); i++) {
		if (liczba_wystapien[i] > 1) { ile_a1++; }
		if (liczba_wystapien[i] > ile_a3) {
			ile_a3 = liczba_wystapien[i];
			slowo_a2 = slowa_w_bazie[i];
		}
	}
	cout << "a:\n1: " << ile_a1 << "\n2: " << slowo_a2 << "\n3: " << ile_a3 << endl;
}

void b(const vector<string>& slowa) {
	unsigned int ile = 0;
	for (unsigned int i = 0; i < 1000; i++) {
		if (slowa[i].back() == 'A' || slowa[i].back() == 'C' || slowa[i].back() == 'E') ile++;
	}
	cout << "b: " << ile << endl;
}

void c(const vector<string>& slowa) {
	unsigned int ile = 0;
	bool czy_palindrom;
	for (unsigned int i = 0; i < 1000; i++) {
		czy_palindrom = true;
		for (unsigned int j = 0; j < slowa[i].size() / 2; j++) {
			if (slowa[i][j] != slowa[i][slowa[i].size() - 1 - j]) {
				czy_palindrom = false;
				break;
			}
		}
		if (czy_palindrom) ile++;
	}
	cout << "c: " << ile << endl;
}

int main() {
	vector<string> S;
	wczytaj(S);

	a(S);
	b(S);
	c(S);

	cout << endl << "END"; cin.get();
}