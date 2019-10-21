#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Urodzenia {
public:
	string rok;
	unsigned int liczba;
	Urodzenia() { liczba = 1; }
};

void wczytaj(vector<string>& pesel) {
	ifstream file("pesel.txt");
	string temp;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 150; i++) {
			file >> temp;
			pesel.push_back(temp);
		}
		file.close();
	}
}

unsigned int a(const vector<string>& pesel) {
	unsigned int ile = 0;
	for (unsigned int i = 0; i < 150; i++) {
		if (pesel[i][2] == '1' && pesel[i][3] == '2') ile++;
	}
	return ile;
}

unsigned int b(const vector<string>& pesel) {
	unsigned int ile = 0;
	for (unsigned int i = 0; i < 150; i++) {
		if (pesel[i][9] % 2 == 0) ile++;
	}
	return ile;
}

string c(const vector<string>& pesel) {
	vector<Urodzenia> zestawienie;
	Urodzenia urodzenia;
	bool nowyRokWBazie;
	for (unsigned int i = 0; i < 150; i++) {
		nowyRokWBazie = true;
		urodzenia.rok.clear();
		urodzenia.rok.push_back(pesel[i][0]);
		urodzenia.rok.push_back(pesel[i][1]);
		if (i == 0) {
			zestawienie.push_back(urodzenia);
		}
		else {
			for (unsigned int j = 0; j < zestawienie.size(); j++) {
				if (urodzenia.rok == zestawienie[j].rok) {
					nowyRokWBazie = false;
					zestawienie[j].liczba++;
					break;
				}
			}
			if (nowyRokWBazie) {
				zestawienie.push_back(urodzenia);
			}
		}
	}
	unsigned int max = 0;
	string rok;
	for (unsigned int i = 0; i < zestawienie.size(); i++) {
		if (zestawienie[i].liczba > max) {
			max = zestawienie[i].liczba;
			rok = zestawienie[i].rok;
		}
	}
	return rok;
}

vector<unsigned long long int> d(const vector<string>& pesel) {
	vector<unsigned long long int> nieprawidlowe;
	unsigned int k = 0;
	unsigned int wagi[] = { 1,3,7,9,1,3,7,9,1,3 };
	unsigned int suma, reszta, cyfraKontrolna;
	for (unsigned int i = 0; i < 150; i++) {
		suma = 0;
		for (unsigned int j = 0; j < pesel[i].size() - 1; j++) {
			suma += (pesel[i][j] - 48) * wagi[j];
		}
		reszta = suma % 10;
		if (reszta == 0) {
			cyfraKontrolna = 0;
		}
		else {
			cyfraKontrolna = 10 - reszta;
		}
		if (pesel[i][10] - 48 != cyfraKontrolna) {
			nieprawidlowe.push_back(0);
			for (unsigned int j = 0; j < pesel[i].size(); j++) {
				nieprawidlowe[k] += (pesel[i][j] - 48) * (unsigned long long int)pow(10, pesel[i].size() - 1 - j);
			}
			k++;
		}
	}
	sort(nieprawidlowe.begin(), nieprawidlowe.end());
	return nieprawidlowe;
}

vector<Urodzenia> e(const vector<string>& pesel) {
	vector<Urodzenia> zestawienie;
	Urodzenia urodzenia;
	unsigned int rok;
	urodzenia.liczba = 0;
	for (unsigned int i = 0; i < 5; i++) {
		urodzenia.rok.clear();
		urodzenia.rok.push_back('5' + i);
		urodzenia.rok.push_back('0');
		zestawienie.push_back(urodzenia);
	}
	for (unsigned int i = 0; i < 150; i++) {
		rok = (pesel[i][0] - 48) * 10 + (pesel[i][1] - 48);
		if (rok <= 59) zestawienie[0].liczba++;
		else if (rok <= 69) zestawienie[1].liczba++;
		else if (rok <= 79) zestawienie[2].liczba++;
		else if (rok <= 89) zestawienie[3].liczba++;
		else zestawienie[4].liczba++;
	}
	return zestawienie;
}

int main() {
	ofstream file("odp_5.txt");
	vector<string> pesel;
	wczytaj(pesel);
	// a
	file << "a: " << a(pesel) << endl;
	// b
	file << "b: " << b(pesel) << endl;
	// c
	file << "c: " << c(pesel) << endl;
	// d
	file << "d:" << endl;
	vector<unsigned long long int> nieprawidlowe = d(pesel);
	for (unsigned int i = 0; i < nieprawidlowe.size(); i++) {
		file << nieprawidlowe[i] << endl;
	}
	// e
	file << "e:" << endl;
	file << "lata" << "\t" << "liczba_urodzonych" << endl;
	vector<Urodzenia> zestawienie = e(pesel);
	for (unsigned int i = 0; i < zestawienie.size(); i++) {
		file << zestawienie[i].rok << "\t" << zestawienie[i].liczba << endl;
	}

	file.close();

	cout << endl << "END"; cin.get();
}