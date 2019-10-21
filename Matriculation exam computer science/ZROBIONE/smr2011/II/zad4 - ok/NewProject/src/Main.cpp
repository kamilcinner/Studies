#include <iostream>
#include <fstream>
using namespace std;

void symulacja() {
	// kwiecien 30
	// maj 31
	// czerwiec 30
	// lipiec 31
	// sierpien 31
	// wrzesien 30
	// pazdziernik 31 ale tylko do 30 liczymy
	// 210 + 3 = 213

	// b1, b2
	double skoszona_trawa_dzien_wczesniej_rano = 10000.0;
	bool mamy_dzien1 = false;
	bool mamy_dzien2 = false;
	
	double skoszona_trawa = 10000.0;

	for (unsigned int i = 1; i <= 213; i++) {
		if (i > 1 && skoszona_trawa > skoszona_trawa_dzien_wczesniej_rano && !mamy_dzien1) {
			mamy_dzien1 = true;
			cout << "b1: " << i - 1 << endl;
		}
		if (i > 1 && skoszona_trawa == skoszona_trawa_dzien_wczesniej_rano && !mamy_dzien2) {
			mamy_dzien2 = true;
			cout << "b2: " << i - 1 << endl;
		}
		skoszona_trawa_dzien_wczesniej_rano = skoszona_trawa;
		// przed poludniem
		skoszona_trawa -= 30.0 * 15.0;
		// w ciagu dnia
		skoszona_trawa += 600.0;
		// w nocy
		if (i == 9) {
			cout << "a: " << floor(skoszona_trawa * (3.0 / 100.0)) << endl;
		}
		skoszona_trawa -= floor(skoszona_trawa * (3.0 / 100.0));
	}
}

double b3() {
	double trawa;
	double liczba_samochodow = 0.0;
	bool koniec = false;

	double skoszona_trawa;

	do {
		skoszona_trawa = 10000.0;
		liczba_samochodow += 1.0;
		for (unsigned int i = 1; i <= 12; i++) { // na 12 dni
			// przed poludniem
			if (i == 12) {
				if (skoszona_trawa < liczba_samochodow * 15.0) {
					koniec = true;
				}
				break;
			}
			skoszona_trawa -= liczba_samochodow * 15.0;
			// w ciagu dnia
			skoszona_trawa += 600.0;
			// w nocy
			skoszona_trawa -= floor(skoszona_trawa * (3.0 / 100.0));
		}
	} while (!koniec);
	
	
	return liczba_samochodow;
}

void c() {
	ofstream file("dane.txt");
	double skoszona_trawa;
	for (auto j : { 10000.0,7000.0,4000.0 }) {
		skoszona_trawa = j;
		for (unsigned int i = 1; i <= 100; i++) { // na 100 dni
			// przed poludniem
			skoszona_trawa -= 30.0 * 15.0;
			// w ciagu dnia
			skoszona_trawa += 600.0;
			// w nocy
			skoszona_trawa -= floor(skoszona_trawa * (3.0 / 100.0));
		}
		file << j << "\t" << skoszona_trawa << endl;
	}
	file.close();
}

int main() {
	symulacja();
	cout << "b3: " << b3() << endl;
	c();

	cout << endl << "END"; cin.get();
}