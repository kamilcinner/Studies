#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

void wczytaj_a(vector<double>& poczatek_roku) {
	ifstream file("lokaty.txt");
	poczatek_roku.resize(200);
	if (file.is_open()) {
		for (unsigned int i = 0; i < 200; i++) {
			file >> poczatek_roku[i];
		}
		file.close();
	}
}

void round(double& a,const unsigned int& i) {
	a *= pow(10, i);
	a = round(a);
	a /= pow(10, i);
}

void a(const vector<double>& poczatek_roku) {
	double koniec_roku, procent;
	double najwieksza_lokata = 0.0;
	double s_poczatek = 0.0, s_koniec = 0.0;
	for (unsigned int i = 0; i < 200; i++) {
		if (poczatek_roku[i] < 10000.0) procent = 6.0;
		else if (poczatek_roku[i] < 20000.0) procent = 7.0;
		else if (poczatek_roku[i] < 30000.0) procent = 8.0;
		else if (poczatek_roku[i] < 40000.0) procent = 9.0;
		else if (poczatek_roku[i] < 50000.0) procent = 10.0;
		else procent = 11.0;
		procent /= 100.0;
		koniec_roku = poczatek_roku[i] + poczatek_roku[i] * procent;
		if (koniec_roku > najwieksza_lokata) najwieksza_lokata = koniec_roku;
		s_poczatek += poczatek_roku[i];
		s_koniec += koniec_roku;
	}
	round(najwieksza_lokata, 2);
	round(s_poczatek, 2);
	round(s_koniec, 2);
	cout << "a:\nsuma_poczatek: " << s_poczatek << "\nsuma_koniec: " << s_koniec << "\nnajwieksza_lokata: " << najwieksza_lokata << endl;
}

void wczytaj_b(vector<double>& kursy) {
	ifstream file("kursy.txt");
	kursy.resize(365);
	if (file.is_open()) {
		for (unsigned int i = 0; i < 365; i++) {
			file >> kursy[i];
		}
		file.close();
	}
}

void b_1(const vector<double>& kursy) {
	double oszczednosci = 20000.0;
	unsigned int nr_dnia = 1;
	for (unsigned int i = 1; i <= 12; i++) {
		//cout << nr_dnia << endl;
		if (i % 2 == 1) { // na euro
			oszczednosci /= kursy[nr_dnia - 1];
			round(oszczednosci, 2);
		}
		else { // na zlote
			oszczednosci *= kursy[nr_dnia - 1];
			round(oszczednosci, 2);
		}
		if (i % 2 == 1) {
			if (i <= 7) {
				nr_dnia += 31;
			}
			else nr_dnia += 30;
		}
		else {
			if (i == 2) nr_dnia += 28;
			else if (i <= 7) {
				nr_dnia += 30;
			}
			else nr_dnia += 31;
		}
	}
	cout << "b1: " << oszczednosci << endl;
}

void b_2(const vector<double>& kursy) {
	double oszczednosci = 20000.0;
	oszczednosci /= kursy[0];
	round(oszczednosci, 2);
	bool euro = true;
	for (unsigned int i = 2; i <= 365; i++) {
		if (!euro) {
			euro = true;
			oszczednosci /= kursy[i - 1];
			round(oszczednosci, 2);
		}
		else if (kursy[i - 1] < kursy[i - 2]) {
			euro = false;
			oszczednosci *= kursy[i - 1];
			round(oszczednosci, 2);
		}
	}
	if (euro) {
		oszczednosci *= kursy[365 - 1];
		round(oszczednosci, 2);
	}
	cout << "b2: " << oszczednosci << endl;
}

void c(const vector<double>& kursy) {
	unsigned int ile = 0;
	for (unsigned int i = 1; i < 365; i++) {
		if (kursy[i] > kursy[i - 1]) ile++;
	}
	cout << "c: " << ile << endl;
}

int main() {
	cout << fixed;
	vector<double> poczatek;
	wczytaj_a(poczatek);
	a(poczatek);

	vector<double> kursy;
	wczytaj_b(kursy);
	b_1(kursy);
	b_2(kursy);
	c(kursy);

	cout << endl << "END"; cin.get();
}