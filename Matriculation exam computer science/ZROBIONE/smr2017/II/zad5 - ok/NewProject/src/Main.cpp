#include <iostream>
#include <fstream>
using namespace std;

void sezon() { // liczba dni 199
	ofstream file("masa.txt");
	bool pierwszyStanDrewna100 = true;
	unsigned int gazem = 0, drewnem = 0, dostaw = 0;

	unsigned int drewno = 550, wsad = 26;
	for (unsigned int i = 2; i <= 200; i++) { // bo zaczynamy od wtorku
		// poranek
		if (i % 7 != 6 && i % 7 != 0) { // dzien roboczy
			// gaz zawsze
			if (i % 7 == 5) { // piatek i mozliwa dostawa drewna
				if (drewno < 100) {
					drewno += 300;
					dostaw++;
				}
			}
		}
		else { // sobota lub niedziela
			if (drewno >= wsad) { // drewno
				drewno -= wsad;
				if (drewno < 100 && pierwszyStanDrewna100) {
					pierwszyStanDrewna100 = false;
					cout << "1: rano\tdzien nr: " << i - 1 << endl;
				}
			}
			// else gaz
		}

		// wieczor
		if (drewno >= wsad) { // drewno
			drewno -= wsad;
			drewnem++;
			if (drewno < 100 && pierwszyStanDrewna100) {
				pierwszyStanDrewna100 = false;
				cout << "1: wieczorem\tdzien nr: " << i - 1 << endl;
			}
		}
		else { gazem++; } // gaz
		file << drewno << endl;
	}
	cout << "2: gazem: " << gazem << "\tdrewnem: " << drewnem << "\tdostaw: " << dostaw << endl;
	file.close();
}


unsigned int ileDrewnaNaDostawe() {
	unsigned int dostawa = 300;
	unsigned int gazem;

	unsigned int drewno, wsad = 26;
	do {
		drewno = 550;
		dostawa++;
		gazem = 0;
		for (unsigned int i = 2; i <= 200; i++) {
			// poranek
			if (i % 7 != 6 && i % 7 != 0) { // dzien roboczy
				// gaz zawsze
				if (i % 7 == 5) { // piatek i mozliwa dostawa drewna
					if (drewno < 100) {
						drewno += dostawa;
					}
				}
			}
			else { // sobota lub niedziela
				if (drewno >= wsad) { // drewno
					drewno -= wsad;
				}
				else { gazem++; } // gaz
			}

			// wieczor
			if (drewno >= wsad) { // drewno
				drewno -= wsad;
			}
			else { gazem++; } // gaz
		}
	} while (gazem > 0);
	return dostawa;
}

int main() {
	sezon();
	cout << "4: " << ileDrewnaNaDostawe() << endl;
	cout << "dzien nr 14 to 28.09.2015" << endl;

	cout << endl << "END"; cin.get();
}