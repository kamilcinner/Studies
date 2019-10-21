//Kamil Cinner IIST 3.2
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class L {
public:
	float* xSt;
	float mianownik;

	void build_xSt(int ile) {
		xSt = new float[ile];
		for (int i = 0; i < ile; i++) {
			xSt[i] = 1;
		}
	}
	L() {
		mianownik = 1;
	}
	~L() {
		delete[] xSt;
	}
};

class Wezel {
public:
	float x;
	float y;
};

class Sort {
	void SWAP(Wezel* W, int a, int b) {
		Wezel x = W[a];
		W[a] = W[b];
		W[b] = x;
	}
public:
	void quicksort(Wezel* W, int lewy, int prawy) {
		float v = W[(lewy + prawy) / 2].x;
		int i, j;
		i = lewy;
		j = prawy;
		do {
			while (W[i].x<v) i++;
			while (W[j].x>v) j--;
			if (i <= j)
			{
				SWAP(W, i, j);
				i++;
				j--;
			}
		} while (i <= j);
		if (j>lewy) quicksort(W, lewy, j);
		if (i<prawy) quicksort(W, i, prawy);
	}
};

class Data {
public:
	int liczba_wezlow;
	Wezel* W;
	float* P_xSt;
	Sort sort;

	bool proceed;
	int trials = 0;

	void pobierz_dane() {
		cout << "Podaj liczbe wezlow: "; cin >> liczba_wezlow;
		system("cls");
		if (liczba_wezlow < 2) {
			cout << "Liczba wezlow nie moze byc mniejsza niz 2! Program zostanie zakonczony" << endl;
			system("pause");
			exit(0);
		}
		W = new Wezel[liczba_wezlow];
		
		for (int i = 0; i < liczba_wezlow; i++) {
			do {
				if (trials >= 3) {
					cout << "Wykorzystano wszystkie mozliwe proby! Program zostanie zakonczony" << endl;
					system("pause");
					exit(0);
				}
				proceed = false;
				cout << "Wprowadz wezly:" << endl;
				cout << "Wezel " << i + 1 << " / " << liczba_wezlow << ":" << endl;
				cout << "x = "; cin >> W[i].x;
				if (i > 0) {
					for (int j = 0; j < i; j++) {
						if (W[i].x == W[j].x) {
							trials++;
							system("cls");
							cout << "Podana wartosc x juz istnieje! - Wprowadz inna..." << endl;
							cout << "Pozostalo prob: " << 3 - trials;
							Sleep(3000);
							proceed = true;
							continue;
						}
					}
				}
				if (!proceed) {
					cout << "y = "; cin >> W[i].y;
				}
				system("cls");
			} while (proceed);
		}
		sort.quicksort(W, 0, liczba_wezlow - 1);
	}
	void oblicz() {
		L* l = new L[liczba_wezlow];
		for (int i = 0; i < liczba_wezlow; i++) {
			l[i].build_xSt(liczba_wezlow);
		}

		int j;
		for (int i = 0; i < liczba_wezlow; i++) {
			j = 0;
			for (int k = 0; k < liczba_wezlow; k++) {
				if (k == i) continue;
				l[i].mianownik *= (W[i].x - W[k].x);

				if (j > 0) {
					for (int q = j; q > 0; q--) {
						l[i].xSt[q] *= (-W[k].x);
						l[i].xSt[q] += l[i].xSt[q - 1];
					}
				}
				l[i].xSt[0] *= (-W[k].x);
				j++;
			}
		}

		for (int i = 0; i < liczba_wezlow; i++) {
			for (j = 0; j < liczba_wezlow; j++) {
				l[i].xSt[j] *= (W[i].y / l[i].mianownik);
			}
		}

		P_xSt = new float[liczba_wezlow];
		for (int i = 0; i < liczba_wezlow; i++) {
			P_xSt[i] = 0;
		}

		for (int i = 0; i < liczba_wezlow; i++) {
			for (j = 0; j < liczba_wezlow; j++) {
				P_xSt[i] += l[j].xSt[i];
			}
			//zaokraglanie do 3-go miejsca po przecinku
			P_xSt[i] *= 1000;
			P_xSt[i] = round(P_xSt[i]);
			P_xSt[i] /= 1000;
		}

		delete[] l;
	}
	void pokaz_wynik() {
		bool isValue = false;
		cout << "Wielomian interpolacyjny wyglada nastepujaco:" << endl;
		for (int i = liczba_wezlow - 1; i >= 0; i--) {
			if (P_xSt[i] != 0) {
				if (i > 0) {
					if (P_xSt[i] == -1) {
						if (i > 1)cout << "-x^" << i << " ";
						else cout << "-x ";
					}
					else if (P_xSt[i] == 1) {
						if (i > 1) cout << "x^" << i << " ";
						else cout << "x ";
					}
					else {
						if (i > 1)cout << P_xSt[i] << "x^" << i << " ";
						else cout << P_xSt[i] << "x ";
					}
				} else cout<<P_xSt[i];
				isValue = true;
			}
			if (i > 0 && isValue) {
				if (P_xSt[i - 1] != 0) {
					if (P_xSt[i - 1] > 0) cout<<"+";
				}
			}
		}
		cout << endl << endl;
	}
	Data() {
		pobierz_dane();
		oblicz();
		pokaz_wynik();
	}
	~Data() {
		delete[] W;
		delete[] P_xSt;
	}
};

int main() {
	Data D;

	system("pause");
	return 0;
}