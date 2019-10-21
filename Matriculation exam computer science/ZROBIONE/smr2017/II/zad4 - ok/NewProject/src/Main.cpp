#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void wczytaj(string* S) {
	ifstream file("binarne.txt");
	if (file.is_open()) {
		for (int i = 0; i < 500; i++)
			file >> S[i];
		file.close();
	}
}

void zad1(string* S, int& liczba, string& napis, int& dlugosc) {
	int k, j;
	dlugosc = 0;
	liczba = 0;
	for (int i = 0; i < 500; i++) {
		k = S[i].size() / 2;
		j = 0;
		while (j < S[i].size() / 2 && S[i][j] == S[i][k]) { j++; k++; }
		if (k == S[i].size()) { //mamy go
			liczba++;
			if (S[i].size() > dlugosc) {
				dlugosc = S[i].size();
				napis = S[i];
			}
		}
	}
}

void zad2(string* S, int& liczba, int& dlugosc) {
	liczba = 0;
	int suma;
	bool isSet = false;
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < S[i].size(); j += 4) {
			suma = 0;
			for (int k = 0; k < 4; k++)
				if (S[i][j + k] == '1') suma += pow(2, 3 - k); // tutaj pamietac od ktorej strony zaczynaja sie potegi od 0 XD
			if (suma > 9) {
				liczba++;
				if (!isSet) {
					dlugosc = S[i].size();
					isSet = true;
				} else if (S[i].size() < dlugosc) dlugosc = S[i].size();
				break;
			}
		}
	}
}

void zad3(string* S, int& najwiekszaD, string& najwiekszaB) {
	int suma;
	najwiekszaD = 0;
	for (int i = 0; i < 500; i++) {
		suma = 0;
		for (int j = 0; j < S[i].size(); j++)
			if (S[i][j] == '1') suma += pow(2, S[i].size() - 1 - j);
		if (suma <= 65535 && suma > najwiekszaD) {
			najwiekszaD = suma;
			najwiekszaB = S[i];
		}
	}
}

int main() {
	string* S = new string[500];
	wczytaj(S);

	// zad 1
	int liczba, dlugosc; string napis;
	zad1(S, liczba, napis, dlugosc);
	cout << "zad1:" << endl << "liczba napisow: " << liczba << endl << "najdluzszy napis: " << napis << endl << "jego dlugosc: " << dlugosc << endl << endl;
	// zad 2
	zad2(S, liczba, dlugosc);
	cout << "zad2:" << endl << "liczba niepoprawnych: " << liczba << endl << "najmniejsza dlugosc: " << dlugosc << endl << endl;
	// zad 3
	zad3(S, liczba, napis);
	cout << "zad3:" << endl << "najwieksza dziesietnie: " << liczba << endl << "najwieksza binarnie: " << napis << endl;

	cout << endl << "END"; cin.get();
}