//Kamil Cinner IIST 3.2
#include <iostream>
#include <fstream>

using namespace std;

void wczytaj(int **A) {
	ifstream file("dane.txt");
	if (file.is_open()) {
		for (int i = 0; i < 200; i++)
			for (int j = 0; j < 320; j++)
				file >> A[i][j];
		file.close();
	}
}
void zad1(int** A, int &J, int &C) {
	J = C = A[0][0];
	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 320; j++) {
			if (A[i][j] > J) J = A[i][j];
			if (A[i][j] < C) C = A[i][j];
		}
}
int zad2(int **A) {
	int licz = 0;
	int j, k;
	for (int i = 0; i < 200; i++) {
		j = 0; k = 319;
		while (j < k) {
			if (A[i][j] != A[i][k]) {
				licz++; break;
			}
			j++; k--;
		}
	}
	return licz;
}
// tu brakuje porownywania gora dol(w odpowiednim przypadku) i sprawdzania rogow
int zad3(int **A) {
	int licz = 0;
	for (int i = 1; i < 199; i++) {
		for (int j = 1; j < 319; j++) {
			if (abs(A[i][j] - A[i][j + 1]) > 128 || abs(A[i][j] - A[i][j - 1]) > 128 || abs(A[i][j] - A[i + 1][j]) > 128 || abs(A[i][j] - A[i - 1][j]) > 128) licz++;
		}
	}
	for (int i = 1; i < 199; i++) {
		if (abs(A[i][0] - A[i - 1][0]) > 128 || abs(A[i][0] - A[i + 1][0]) > 128) licz++;
		if (abs(A[i][319] - A[i - 1][319]) > 128 || abs(A[i][319] - A[i + 1][319]) > 128) licz++;
	}
	for (int i = 1; i < 319; i++) {
		if (abs(A[0][i] - A[0][i - 1]) > 182 || abs(A[0][i] - A[0][i + 1]) > 128) licz++;
		if (abs(A[199][i] - A[199][i - 1]) > 182 || abs(A[199][i] - A[199][i + 1]) > 128) licz++;
	}
	return licz;
}
int zad4(int **A) {
	int licz, licz2 = 1;
	for (int j = 0; j < 320; j++) {
		licz = 1;
		for (int i = 0; i < 199; i++) {
			if (A[i][j] == A[i + 1][j]) licz++;
			else {
				if (licz > licz2) licz2 = licz;
				licz = 1;
			}
		}
		if (licz > licz2) licz2 = licz;
	}
	return licz2;
}

int main() {
	int **A; A = new int *[200]; for (int i = 0; i < 200; i++) A[i] = new int[320];

	wczytaj(A);
	// zad1
	int najjasniejszy, najciemniejszy;
	zad1(A, najjasniejszy, najciemniejszy);
	cout << "najjasniejszy = " << najjasniejszy << endl;
	cout << "najciemniejszy = " << najciemniejszy << endl;
	// zad2
	cout << "Nalezy usunac: " << zad2(A) << " wierszy" << endl;
	// zad3
	cout << "Liczba sasiadujacych pikseli = " << zad3(A) << endl;
	// zad4
	cout << "Najdluzsza linia pionowa: " << zad4(A) << endl;

	system("pause");
	for (int i = 0; i < 200; i++) delete A[i]; delete A;
	return 0;
}