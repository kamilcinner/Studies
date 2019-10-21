#include <iostream>
#include <fstream>
using namespace std;

void symulacja() {
	// grudzien 31 dni
	// styczen 31 dni
	// luty 28 dni
	// suma 90 dni

	unsigned int siano = 100000;
	unsigned int zoledzie = 5000;
	unsigned int liczba_zubrow = 90;

	// a
	unsigned int liczba_dostaw_siana = 0;
	unsigned int liczba_dostaw_zoledzi = 0;
	// b
	bool zoledzie_po_raz_pierwszy = true;
	// c
	unsigned int tylko_sianem = 0;
	unsigned int tylko_zoledziami = 0;
	// d
	ofstream file("dane.txt");

	for (unsigned int i = 1; i <= 90; i++) { // 1 to sobota
		// rano
		if (i == 31 || i == 62 || i == 90) { // d
			file << siano << "\t" << zoledzie << endl;
		}
		if (siano >= 50000) {
			siano -= liczba_zubrow * 40;
			tylko_sianem++; // c
		}
		else {
			zoledzie -= liczba_zubrow * 20;
			tylko_zoledziami++; // c
			if (zoledzie_po_raz_pierwszy) { // b
				zoledzie_po_raz_pierwszy = false;
				cout << "b: " << i << " dzien" << endl;
			}
		}
		// wieczor
		if ((i + 5) % 7 == 5) { // piatek
			siano += 15000;
			liczba_dostaw_siana++; // a
		}
		else if ((i + 5) % 7 == 2) { // wtorek
			zoledzie += 4000;
			liczba_dostaw_zoledzi++; // a
		}
	}

	// a
	cout << "a:\ndostawa siano - " << liczba_dostaw_siana << "\ndostawa zoledzie - " << liczba_dostaw_zoledzi << endl;
	// c
	cout << "c:\ntylko siano - " << tylko_sianem << "\ntylko zoledzie - " << tylko_zoledziami << endl;
	// d
	file.close();
}

unsigned int e() { // e
	int siano;
	int zoledzie;
	unsigned int bezpieczna_liczba_zubrow = 90;

	bool koniec = false;
	unsigned int liczba_zubrow = bezpieczna_liczba_zubrow;
	
	do {
		liczba_zubrow++;
		siano = 100000;
		zoledzie = 5000;
		for (unsigned int i = 1; i <= 90; i++) { // 1 to sobota
			// rano
			if (siano >= 50000) {
				siano -= liczba_zubrow * 40;
			}
			else { zoledzie -= liczba_zubrow * 20; }
			// wieczor
			if ((i + 5) % 7 == 5) { // piatek
				siano += 15000;
			}
			if ((i + 5) % 7 == 2) { // wtorek
				zoledzie += 4000;
			}
		}
		if (siano < 0 || zoledzie < 0) {
			koniec = true;
		}
		else {
			bezpieczna_liczba_zubrow = liczba_zubrow;
		}
	} while (!koniec);
	return bezpieczna_liczba_zubrow - 90;
}

int main() {
	symulacja();
	// e
	cout << "e: " << e() << endl;

	cout << endl << "END"; cin.get();
}