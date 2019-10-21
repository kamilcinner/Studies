#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void wczytaj(vector<string>& slowa, vector<string>& klucze, const string& nazwa1, const string& nazwa2) {
	fstream fSlowa(nazwa1);
	string linia;
	if (fSlowa.is_open()) {
		while (!fSlowa.eof()) {
			getline(fSlowa, linia);
			slowa.push_back(linia);
		}
		fSlowa.close();
	}
	fstream fKlucze(nazwa2);
	if (fKlucze.is_open()) {
		while (!fKlucze.eof()) {
			getline(fKlucze, linia);
			klucze.push_back(linia);
		}
		fKlucze.close();
	}
}

void a(const vector<string>& slowa, const vector<string>& klucze) {
	unsigned int k;
	string szyfr;
	char znakSzyfru;
	vector<string> slowaZaszyfrowane;
	for (unsigned int i = 0; i < slowa.size(); i++) {
		k = 0;
		szyfr.clear();
		for (unsigned int j = 0; j < slowa[i].size(); j++) {
			znakSzyfru = slowa[i][j] + (klucze[i][k] - 64);
			if (znakSzyfru > 90) znakSzyfru -= 26;
			szyfr.push_back(znakSzyfru);
			k++;
			if (k >= klucze[i].size()) k = 0;
		}
		slowaZaszyfrowane.push_back(szyfr);
	}
	ofstream file("wynik4a.txt");
	for (unsigned int i = 0; i < slowaZaszyfrowane.size(); i++) {
		file << slowaZaszyfrowane[i] << endl;
	}
	file.close();
}

void b(const vector<string>& slowa, const vector<string>& klucze) {
	unsigned int k;
	string slowo;
	char znakSlowa;
	vector<string> slowaOdszyfrowane;
	for (unsigned int i = 0; i < slowa.size(); i++) {
		k = 0;
		slowo.clear();
		for (unsigned int j = 0; j < slowa[i].size(); j++) {
			znakSlowa = slowa[i][j] - (klucze[i][k] - 64);
			if (znakSlowa < 65) znakSlowa += 26;
			slowo.push_back(znakSlowa);
			k++;
			if (k >= klucze[i].size()) k = 0;
		}
		slowaOdszyfrowane.push_back(slowo);
	}
	ofstream file("wynik4b.txt");
	for (unsigned int i = 0; i < slowaOdszyfrowane.size(); i++) {
		file << slowaOdszyfrowane[i] << endl;
	}
	file.close();
}

int main() {
	// a
	vector<string> slowa1, klucze1;
	wczytaj(slowa1, klucze1, "tj.txt", "klucze1.txt");
	a(slowa1, klucze1);
	// b
	vector<string> slowa2, klucze2;
	wczytaj(slowa2, klucze2, "sz.txt", "klucze2.txt");
	b(slowa2, klucze2);

	cout << endl << "END"; cin.get();
}