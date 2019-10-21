#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Komitet {
public:
	unsigned int liczbaMandatow = 0;
	unsigned int liczbaGlosow = 0;
	double X;
	void obliczX() {
		X = (double)liczbaGlosow / ((double)liczbaMandatow + 1);
	}
};

void wczytaj(vector<vector<unsigned int>>& dane) {
	vector<unsigned int> wiersz;
	unsigned int liczba;
	ifstream file("dane.txt");
	if (file.is_open()) {
		for (unsigned int i = 0; i < 20; i++) {
			wiersz.clear();
			for (unsigned int j = 0; j < 7; j++) {
				file >> liczba;
				wiersz.push_back(liczba);
			}
			dane.push_back(wiersz);
		}
		file.close();
	}
}

void a(const vector<vector<unsigned int>>& dane) {
	ofstream file("wybory.txt");
	// 1
	vector<unsigned int> glosy;
	unsigned int suma;
	for (unsigned int i = 0; i < 6; i++) {
		suma = 0;
		for (unsigned int j = 0; j < 20; j++) {
			suma += dane[j][i];
		}
		glosy.push_back(suma);
	}
	unsigned int k = 0;
	file << "1:" << endl;
	for (auto i : { 'A','B','C','D','E','F' }) {
		file << i << "\t" << glosy[k] << endl;
		k++;
	}
	// 2
	unsigned int numerOkreguMax, numerOkreguMin;
	unsigned int max, min;
	for (unsigned int i = 0; i < 20; i++) {
		suma = 0;
		for (unsigned int j = 0; j < 7; j++) {
			suma += dane[i][j];
		}
		if (i == 0) {
			max = min = suma;
			numerOkreguMax = numerOkreguMin = i + 1;
		}
		else if (suma > max) {
			max = suma;
			numerOkreguMax = i + 1;
		}
		else if (suma < min) {
			min = suma;
			numerOkreguMin = i + 1;
		}
	}
	file << "2:" << endl;
	file << "max_nr: " << numerOkreguMax << endl;
	file << "min_nr: " << numerOkreguMin << endl;
	// 3
	vector<Komitet> komitety;
	komitety.resize(6);
	double MAX;
	unsigned int MAX_index;
	for (unsigned int i = 0; i < 6; i++) {
		komitety[i].liczbaGlosow = dane[5][i];
	}
	for (unsigned int i = 0; i < dane[5][6]; i++) {
		MAX = 0;
		for (unsigned int j = 0; j < 6; j++) {
			komitety[j].obliczX();
			if (komitety[j].X > MAX) {
				MAX = komitety[j].X;
				MAX_index = j;
			}
		}
		komitety[MAX_index].liczbaMandatow++;
	}
	file << "3:" << endl;
	k = 0;
	for (auto i : { 'A','B','C','D','E','F' }) {
		file << i << ": " << komitety[k].liczbaMandatow << endl;
		k++;
	}
	// 4
	vector<unsigned int> mandatyKomitetow;
	for (unsigned int i = 0; i < 6; i++) {
		mandatyKomitetow.push_back(0);
	}
	for (unsigned int i = 0; i < 20; i++) { // po okregach
		komitety.clear();
		komitety.resize(6);
		for (unsigned int j = 0; j < 6; j++) {
			komitety[j].liczbaGlosow = dane[i][j];
		}
		for (unsigned int j = 0; j < dane[i][6]; j++) { // po liczbie madatow do rozdania
			MAX = 0;
			for (unsigned int m = 0; m < 6; m++) {
				komitety[m].obliczX();
				if (komitety[m].X > MAX) {
					MAX = komitety[m].X;
					MAX_index = m;
				}
			}
			komitety[MAX_index].liczbaMandatow++;
			mandatyKomitetow[MAX_index]++;
		}
	}
	file << "4:" << endl;
	k = 0;
	for (auto i : { 'A','B','C','D','E','F' }) {
		file << i << ": " << mandatyKomitetow[k] << endl;
		k++;
	}

	file.close();
}

int main() {
	vector<vector<unsigned int>> dane;
	wczytaj(dane);

	// a
	a(dane);

	cout << endl << "END"; cin.get();
}