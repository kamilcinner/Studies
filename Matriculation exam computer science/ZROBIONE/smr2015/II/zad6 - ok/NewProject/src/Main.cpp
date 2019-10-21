// UWAGA zapis 2500000 bez KROPKI i w innych zmiennych
// powodowal bardzo zle liczenie :/
// trzeba bylo uzyc kropek 2500000.0
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Dzien_ubogi {
public:
	double najmniej_wody_w_zbiorniku = 2500000.0;
	unsigned int numer_dnia;
};

void symulacja() {
	// zmienne do zadan
	unsigned int ile_razy_odprowadzana_deszczowka = 0;
	double ile_lacznie_wody_pobrano_do_uzupelnienia_zbiornika = 0.0;
	Dzien_ubogi dzien_ubogi;
	double woda_odprowadzona_w_sobote;
	double ilosc_dolanej_w_sobote;
	ofstream file2("soboty.txt");

	bool czy_pada[153];
	ifstream file("dane.txt");
	if (file.is_open()) {
		for (unsigned int i = 0; i < 153; i++) {
			file >> czy_pada[i];
		}
		file.close();
	}

	double powierzchnia_calkowita = 500.0 * 100.0;
	double poziom_deszczowki = 2500000.0;
	double wody_do_dolania;

	for (unsigned int i = 0; i < 153; i++) { // 0 dzien to czwartek
		woda_odprowadzona_w_sobote = 0;
		// 3
		if (poziom_deszczowki < dzien_ubogi.najmniej_wody_w_zbiorniku) {
			dzien_ubogi.najmniej_wody_w_zbiorniku = poziom_deszczowki;
			dzien_ubogi.numer_dnia = i + 1;
		}
		// TEST OK
		/*if (i == 32 - 1) {
			cout << "01.06.2014 RANO\nilosc wody w zbiorniku: " << round(poziom_deszczowki) << endl;
		}*/
		// poranek
		if (!czy_pada[i]) {
			poziom_deszczowki -= 2 * powierzchnia_calkowita;
		}
		// wieczor
		if (czy_pada[i]) { // dopada do zbiornika +3%
			poziom_deszczowki += (3.0 / 100.0)*poziom_deszczowki;
			if (poziom_deszczowki > 2500000.0) {
				woda_odprowadzona_w_sobote = poziom_deszczowki - 2500000.0;
				poziom_deszczowki = 2500000.0;
				ile_razy_odprowadzana_deszczowka++;
			}
		} else { // parowanie -1%
			poziom_deszczowki -= (1.0 / 100.0)*poziom_deszczowki;
		}
		// sobota wieczor
		if ((i + 4) % 7 == 6) {
			wody_do_dolania = 2500000.0 - poziom_deszczowki;
			if (wody_do_dolania > 500000.0)
				wody_do_dolania = 500000.0;
			poziom_deszczowki += wody_do_dolania;
			ile_lacznie_wody_pobrano_do_uzupelnienia_zbiornika += wody_do_dolania;
			ilosc_dolanej_w_sobote = wody_do_dolania;
			if ((i + 1) <= 31) { // sobota majowa
				file2 << i + 1 << "\t" << woda_odprowadzona_w_sobote << "\t" << ilosc_dolanej_w_sobote << endl;
			}
		}
	}

	// 1
	cout << "1: " << ile_razy_odprowadzana_deszczowka << endl;
	// 2
	cout << "2: " << round(ile_lacznie_wody_pobrano_do_uzupelnienia_zbiornika) << endl;
	// 3
	cout << "3:\ndzien numer: " << dzien_ubogi.numer_dnia << "\nilosc wody w zbiorniku: " << round(dzien_ubogi.najmniej_wody_w_zbiorniku) << endl;

	file2.close();
}

int main() {
	cout << setprecision(10);
	symulacja();

	cout << endl << "END"; cin.get();
}