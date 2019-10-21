#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void wczytaj(vector<double>& kursy) {
	ifstream file("C.txt");
	kursy.resize(500);
	if (file.is_open()) {
		for (unsigned int i = 0; i < 500; i++) {
			file >> kursy[i];
		}
		file.close();
	}
}

void gra(const vector<double>& kursy) {
	ofstream file("4.txt");
	unsigned int najwiekszaLiczbaAkcji = 0, liczbaTransakcjiKupna = 0, liczba_akcji = 0;
	double kwota = 5000, wartoscKupionychAkcji = 0, kursMAX = kursy[0];
	bool ciagMalejacy = false, najwyzszyKurs = false;

	if (kursy[1] > kursMAX) {
		kursMAX = kursy[1];
		najwyzszyKurs = true;
	}

	// zakup 1-go dnia
	liczbaTransakcjiKupna++;
	while (wartoscKupionychAkcji + kursy[0] <= 1000) {
		wartoscKupionychAkcji += kursy[0];
		liczba_akcji++;
	} kwota -= wartoscKupionychAkcji;

	for (unsigned int i = 2; i < 500; i++) { // od 3-ciego dnia
		// sprzedaz akcji
		if (najwyzszyKurs && liczba_akcji > 0) {
			kwota += kursy[i] * (double)liczba_akcji;
			liczba_akcji = 0;
		}
		
		// zakup akcji
		if (ciagMalejacy && kwota >= 1000) {
			liczbaTransakcjiKupna++;
			wartoscKupionychAkcji = 0;
			while (wartoscKupionychAkcji + kursy[i] <= 1000) {
				wartoscKupionychAkcji += kursy[i];
				liczba_akcji++;
			} kwota -= wartoscKupionychAkcji;
			if (liczba_akcji > najwiekszaLiczbaAkcji) najwiekszaLiczbaAkcji = liczba_akcji;
		}
		
		// warunki na nastepne dni
		if (kursy[i - 2] > kursy[i - 1] && kursy[i - 1] > kursy[i]) ciagMalejacy = true;
		else ciagMalejacy = false;
		if (kursy[i] > kursMAX) {
			kursMAX = kursy[i];
			najwyzszyKurs = true;
		}
		else najwyzszyKurs = false;

		// test
		if (i == 99) {
			cout << "liczba akcji: " << liczba_akcji << endl;
			cout << "kwota: " << kwota << endl;
		}
	}

	file << "najwieksza liczba akcji: " << najwiekszaLiczbaAkcji << endl;
	file << "liczba transakcji kupna: " << liczbaTransakcjiKupna << endl;
	file << "500 dzien:" << endl;
	file << "liczba akcji: " << liczba_akcji << endl;
	file << "kwota: " << kwota << endl;
	file.close();
}

int main() {
	vector<double> kursy;
	wczytaj(kursy);
	gra(kursy);

	cout << endl << "END"; cin.get();
}