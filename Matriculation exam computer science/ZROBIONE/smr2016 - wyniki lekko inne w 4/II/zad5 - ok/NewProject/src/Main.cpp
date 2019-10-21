#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void wczytaj(char** S) {
	ifstream file("gra.txt");
	if (file.is_open()) {
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 20; j++)
				file >> S[i][j];
		file.close();
	}
}

void wyswietlPokolenie(char** S) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			cout << S[i][j] << " ";
		}
		cout << endl;
	} cout << endl;
}

void kopiuj(char** S1, char** S2) {
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 20; j++)
			S1[i][j] = S2[i][j];
}

bool czyRowne(char** S1, char** S2) {
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 20; j++)
			if (S1[i][j] != S2[i][j]) return false;
	return true;
}

void nowePokolenie(char** S) {
	char** SN;
	SN = new char* [12];
	for (int i = 0; i < 12; i++)
		SN[i] = new char[20];

	kopiuj(SN, S);

	int liczba_sasiadow;

	unsigned int* wiersz = new unsigned int[14];
	wiersz[0] = 11;
	for (int i = 0; i < 12; i++) wiersz[i + 1] = i;
	wiersz[13] = 0;

	unsigned int* kolumna = new unsigned int[22];
	kolumna[0] = 19;
	for (int i = 0; i < 20; i++) kolumna[i + 1] = i;
	kolumna[21] = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			liczba_sasiadow = 0;
			for (int k = -1; k <= 1; k++) { // wiersze
				for (int l = -1; l <= 1; l++) { // kolumny
					if (k == 0 && l == 0) continue;
					if (S[wiersz[i + 1 + k]][kolumna[j + 1 + l]] == 'X') liczba_sasiadow++;
				}
			}
			if (S[i][j] == 'X' && liczba_sasiadow != 2 && liczba_sasiadow != 3)  SN[i][j] = '.';
			else if (S[i][j] == '.' && liczba_sasiadow == 3) SN[i][j] = 'X';
		}
	}
	kopiuj(S, SN);
	//wyswietlPokolenie(S);
}

int liczbaZywychKomurek(char** S) {
	int licz = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			if (S[i][j] == 'X') licz++;
		}
	}
	return licz;
}

int zad1(char** S) {
	wczytaj(S);
	int liczba_sasiadow = 0;
	for (int i = 2; i <= 37; i++) nowePokolenie(S);
	for (int k = -1; k <= 1; k++) { // wiersze
		for (int l = -1; l <= 1; l++) { // kolumny
			if (k == 0 && l == 0) continue;
			if (S[1 + k][18 + l] == 'X') liczba_sasiadow++;
		}
	}
	return liczba_sasiadow;
}

int zad2(char** S) {
	wczytaj(S);
	wyswietlPokolenie(S);
	nowePokolenie(S);
	return liczbaZywychKomurek(S);
}

int zad3(char** S, int& numerPokolenia) {
	wczytaj(S);
	char** S1; char** S2;
	S1 = new char*[12]; S2 = new char*[12];
	for (int i = 0; i < 12; i++) {
		S1[i] = new char[20];
		S2[i] = new char[20];
	}
	kopiuj(S1, S);
	nowePokolenie(S);
	kopiuj(S2, S);
	for (int i = 2; i <= 100; i++) {
		if (!czyRowne(S1,S2)) {
			cout << " NIE PASUJE:((((((((((((((((((((((((((((((" << endl;
			cout << "S1:" << endl;
			wyswietlPokolenie(S1);
			cout << "S2:" << endl;
			wyswietlPokolenie(S2);
			nowePokolenie(S);
			kopiuj(S1, S2);
			kopiuj(S2, S);
		} else {
			cout << "PASUJE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "S1:" << endl;
			wyswietlPokolenie(S1);
			cout << "S2:" << endl;
			wyswietlPokolenie(S2);
			numerPokolenia = i;
			return liczbaZywychKomurek(S2);
		}
	}
	return -1;
}

int main() {
	char** S;
	S = new char* [12];
	for (int i = 0; i < 12; i++) S[i] = new char[20];

	// zad 1
	cout << "zad1: " << zad1(S) << endl;
	// zad 2
	cout << "zad2: " << zad2(S) << endl;
	// zad 3
	int liczba, nr;
	liczba = zad3(S, nr);
	cout << "zad3: " << endl << "liczba zywych: " << liczba << endl << "to pokolenie nr: " << nr << endl;

	cout << endl << "END"; cin.get();
}