//Kamil Cinner IIST 3.2
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void zad1(int k) {
	int klucz = k % 26; //3
	int g;
	string *S = new string[100];
	ifstream file("dane_6_1.txt");
	if (file.is_open()) {
		for (int i = 0; i < 100; i++) {
			file >> S[i];
		}
		file.close();
		ofstream fileW("wyniki_6_1.txt");
		if (klucz != 0)
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < S[i].size(); j++) {
					if (S[i][j] <= 90 - klucz) S[i][j] += klucz;
					else {
						g = S[i][j] - (90 - klucz);
						S[i][j] = 'A' + (g - 1);
					}
				}
			}
		for (int i = 0; i < 100; i++) {
			fileW << S[i] << endl;
		}
		fileW.close();
	}
}
void zad2() {
	int g, klucz;
	string *S = new string[3000];
	int *K = new int[3000];
	ifstream file("dane_6_2.txt");
	if (file.is_open()) {
		for (int i = 0; i < 3000; i++) {
			file >> S[i];
			file >> K[i];
		}
		file.close();
		ofstream fileW("wyniki_6_2.txt");
		for (int i = 0; i < 3000; i++) {
			klucz = K[i] % 26;
			if (klucz != 0)
				for (int j = 0; j < S[i].size(); j++) {
					if (S[i][j] >= 65 + klucz) S[i][j] -= klucz;
					else {
						g = 65 + klucz - S[i][j];
						S[i][j] = 'Z' - (g - 1);
					}
				}
		}
		for (int i = 0; i < 3000; i++) {
			fileW << S[i] << endl;
		}
		fileW.close();
	}
}
void zad3() {
	int g, klucz;
	string *S1 = new string[3000];
	string *S2 = new string[3000];
	ifstream file("dane_6_3.txt");
	if (file.is_open()) {
		for (int i = 0; i < 3000; i++) {
			file >> S1[i];
			file >> S2[i];
		}
		file.close();
		ofstream fileW("wyniki_6_3.txt");
		for (int i = 0; i < 3000; i++) {
			klucz = S2[i][0] - S1[i][0];
			if (klucz < 0) klucz += 26;
			for (int j = 0; j < S1[i].size(); j++) {
				g = S2[i][j] - S1[i][j];
				if (g < 0) g += 26;
				if (g != klucz) {
					fileW << S1[i] << endl;
					break;
				}
			}
		}
		fileW.close();
	}
}

int main() {
	// zad 1
	zad1(107);
	// zad 2
	zad2();
	// zad 3
	zad3();

	system("pause");
	return 0;
}