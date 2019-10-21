#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void symulacja() {
	unsigned int liczba_jajek = 0;
	unsigned int liczba_kur = 200;

	// 1
	bool mamy_pierwszy_dzien = false;
	// 2
	double kwota_na_pasze = 0.0;
	// 3
	double dzienny_zysk;
	double realny_zysk = 0.0;
	bool pierwszy_relany_zysk = false;
	//4
	double dzienny_przychod, dzienny_koszt;
	ofstream file("dane.txt");

	for (unsigned int i = 1; i <= 180; i++) {
		dzienny_przychod = dzienny_koszt = 0.0; // 4
		dzienny_zysk = 0.0; // 3
		// rano przed posilkiem
		if (i % 30 == 0) { // co 30 dni kupno kur
			dzienny_zysk -= 18.0*floor((double)liczba_kur * (20.0 / 100.0)); // 3
			dzienny_koszt += 18.0*floor((double)liczba_kur * (20.0 / 100.0)); // 4
			liczba_kur += (unsigned int)floor((double)liczba_kur * (20.0 / 100.0));
		}
		if (i > 1 && liczba_kur == 200 && !mamy_pierwszy_dzien) { // 1
			cout << "1: dzien numer - " << i << ", rano" << endl;
			mamy_pierwszy_dzien = true;
		}
		// rano pora posilku
		dzienny_zysk -= ((double)liczba_kur * 0.2) * 1.9; // 3
		kwota_na_pasze += ((double)liczba_kur * 0.2) * 1.9; // 2
		dzienny_koszt += ((double)liczba_kur * 0.2) * 1.9; // 4
		//poludnie
		if (i % 7 != 0) { // NIE niedziela
			liczba_jajek += liczba_kur;
			dzienny_zysk += double(liczba_kur) * 0.9; // 3
			dzienny_przychod += double(liczba_kur) * 0.9; // 4
		}
		// zmrok - lis
		if (i % 2 != 0) { // dzien nieparzysty
			liczba_kur -= 2;
		}
		if (i > 1 && liczba_kur == 200 && !mamy_pierwszy_dzien) { // 1
			cout << "1: dzien numer - " << i << ", po zmroku" << endl;
			mamy_pierwszy_dzien = true;
		}
		realny_zysk += dzienny_zysk; // 3
		if (realny_zysk > 1500.0 && !pierwszy_relany_zysk) { // 3
			cout << "3: dzien numer - " << i << endl;
			pierwszy_relany_zysk = true;
		}
		// 4
		file << dzienny_przychod << "\t" << dzienny_koszt << endl;
	}

	// 2
	cout << "2: " << kwota_na_pasze << endl;
	// 3
	cout << "3: calkowity zysk: " << realny_zysk << endl;
	// 4
	file.close();
}

int main() {
	cout << fixed;
	symulacja();

	cout << endl << "END"; cin.get();
}