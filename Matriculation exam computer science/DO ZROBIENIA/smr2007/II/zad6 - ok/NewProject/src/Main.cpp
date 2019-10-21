#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Telefon {
public:
	string numer;
	unsigned int liczbaPolaczen = 1;
	void clear() {
		numer.clear();
		liczbaPolaczen = 1;
	}
};

void wczytaj(vector<string>& numery) {
	numery.resize(1000);
	ifstream file("telefony.txt");
	if (file.is_open()) {
		for (unsigned int i = 0; i < 1000; i++) {
			file >> numery[i];
		}
		file.close();
	}
}

vector<Telefon> utworzBazeTelefonow(const vector<string>& numery) {
	vector<Telefon> telefony;
	Telefon telefon;
	bool numerWBazie;
	for (unsigned int i = 0; i < 1000; i++) {
		numerWBazie = false;
		telefon.clear();
		for (unsigned int j = 0; j < telefony.size(); j++) {
			if (telefony[j].numer == numery[i]) {
				telefony[j].liczbaPolaczen++;
				numerWBazie = true;
				break;
			}
		}
		if (!numerWBazie) {
			telefon.numer = numery[i];
			telefony.push_back(telefon);
		}
	}
	return telefony;
}

unsigned int a(const vector<Telefon>& telefony) {
	unsigned int ile = 0;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		if (telefony[i].numer == "504669045") {
			ile = telefony[i].liczbaPolaczen;
			break;
		}
	}
	return ile;
}

Telefon b(const vector<Telefon>& telefony) {
	unsigned int max = 0;
	string numer;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		if (telefony[i].liczbaPolaczen > max) {
			max = telefony[i].liczbaPolaczen;
			numer = telefony[i].numer;
		}
	}
	return { numer, max };
}

unsigned int c(const vector<Telefon>& telefony) {
	unsigned int ile = 0;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		if (telefony[i].numer[0] == '5' && telefony[i].numer[1] == '1' && telefony[i].numer[2] == '1') {
			ile++;
		}
	}
	return ile;
}

unsigned int d(const vector<Telefon>& telefony) {
	unsigned int ile = 0;
	unsigned int cyfra, suma;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		suma = 0;
		for (unsigned int j = 0; j < telefony[i].numer.size(); j++) {
			cyfra = (unsigned int)telefony[i].numer[j] - 48;
			if (cyfra % 2 == 0) suma += cyfra;
		}
		if (suma > 42) ile++;
	}
	return ile;
}

unsigned int e(const vector<Telefon>& telefony) {
	unsigned int ile = 0;
	unsigned int liczbaJedynek;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		liczbaJedynek = 0;
		for (unsigned int j = 0; j < telefony[i].numer.size(); j++) {
			if (telefony[i].numer[j] == '1') liczbaJedynek++;
		}
		if (liczbaJedynek >= 4) ile++;
	}
	return ile;
}

unsigned int f(const vector<Telefon>& telefony) {
	unsigned int ile = 0;
	string numer;
	unsigned int mediana;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		numer = telefony[i].numer;
		if (numer[numer.size() - 1] != '2') continue;
		sort(numer.begin(), numer.end());
		if (numer.size() % 2 == 0) {
			mediana = (((unsigned int)numer[numer.size() / 2 - 1] - 48) + ((unsigned int)numer[numer.size() / 2 - 1] - 48)) / 2;
		}
		else mediana = (unsigned int)numer[numer.size() / 2] - 48;
		if (mediana % 3 == 0) ile++;
	}
	return ile;
}

vector<Telefon> g(const vector<Telefon>& telefony) {
	vector<Telefon> dane;
	for (unsigned int i = 0; i < telefony.size(); i++) {
		if (telefony[i].liczbaPolaczen >= 2) {
			dane.push_back(telefony[i]);
		}
	}
	return dane;
}

int main() {
	ofstream file("zad_6.txt");
	vector<string> numery;
	wczytaj(numery);
	vector<Telefon> telefony = utworzBazeTelefonow(numery);

	// a
	file << "a: " << a(telefony) << endl;
	// b
	Telefon tel = b(telefony);
	file << "b: " << tel.numer << "\t" << tel.liczbaPolaczen << endl;
	// c
	file << "c: " << c(telefony) << endl;
	// d
	file << "d: " << d(telefony) << endl;
	// e
	file << "e: " << e(telefony) << endl;
	// f
	file << "f: " << f(telefony) << endl;
	// g
	file << "g:" << endl;
	vector<Telefon> dane = g(telefony);
	for (unsigned int i = 0; i < dane.size(); i++) {
		file << dane[i].numer << "\t" << dane[i].liczbaPolaczen << endl;
	}

	file.close();

	cout << endl << "END"; cin.get();
}