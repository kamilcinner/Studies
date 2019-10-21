#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void symulacja() {
	ofstream file("dane.txt");
	double ilosc_dolanej_wody = 0.0;

	// minuta 0
	double poziom_cieczy = 5000.0; // ml
	double stezenie = 80.0; // %
	double substancja_chem = 4000.0; // ml
	double woda = 1000.0; // ml

	file << woda << "\t" << substancja_chem << endl;

	for (unsigned int i = 1; i <= 1500; i++) {
		// podpunkt 1
		if (i == 191) {
			cout << "1:\nilosc roztworu: " << poziom_cieczy << endl;
			cout << "ilosc wody: " << woda << endl;
			cout << "ilosc substancji chemicznej X: " << substancja_chem << endl;
			cout << "stezenie: " << stezenie << endl << endl;
		}

		// co 50 minut robot dolewa
		if (i > 1 && (i - 1) % 50 == 0) {
			woda += 5000.0 - poziom_cieczy;
			ilosc_dolanej_wody += 5000.0 - poziom_cieczy;
			poziom_cieczy = 5000.0;
			stezenie = (substancja_chem / poziom_cieczy) * 100.0;
		}

		// pod koniec parzystej minuty
		if (i % 2 == 0) {
			poziom_cieczy -= 20.0;
			substancja_chem -= 20.0 * (stezenie / 100.0);
			woda -= 20.0 * ((100.0 - stezenie) / 100.0);
		}

		file << woda << "\t" << substancja_chem << endl;
	}

	// podpunkt 2
	cout << "2:\nstezenie roztworu: " << stezenie << endl;
	cout << "ilosc dolanej wody: " << ilosc_dolanej_wody << endl << endl;
	
	file.close();
}

double podpunkt4() {
	double poziom_cieczy, stezenie, substancja_chem, woda;

	double bezpieczna_ilosc = 20.0, j = 20.0;
	bool dobre_stezenie = true;
	bool koniec = false;

	do {
		j += 0.01;

		poziom_cieczy = 5000.0; // ml
		stezenie = 80.0; // %
		substancja_chem = 4000.0; // ml
		woda = 1000.0; // ml

		for (unsigned int i = 1; i <= 1500; i++) {
			// co 50 minut robot dolewa
			if (i > 1 && (i - 1) % 50 == 0) {
				woda += 5000.0 - poziom_cieczy;
				poziom_cieczy = 5000.0;
				stezenie = (substancja_chem / poziom_cieczy) * 100.0;
			}

			// pod koniec parzystej minuty
			if (i > 0 && i % 2 == 0) {
				poziom_cieczy -= j;
				substancja_chem -= j * (stezenie / 100.0);
				woda -= j * ((100.0 - stezenie) / 100.0);
			}

			if (stezenie < 1) {
				dobre_stezenie = false;
				break;
			}
		}

		if (dobre_stezenie) bezpieczna_ilosc = j;
		else koniec = true;
	} while (!koniec);

	return bezpieczna_ilosc;
}

int main() {
	cout << setprecision(10);
	symulacja();
	// 4
	cout << "4:\nmozemy max odlewac: " << podpunkt4() << endl;

	cout << endl << "END"; cin.get();
}