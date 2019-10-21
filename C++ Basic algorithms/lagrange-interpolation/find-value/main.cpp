#include <iostream>
#include <Windows.h>

using namespace std;

class Data {
public:
	int liczba_wezlow;
	float* x_i;
	float* f_i;
	float x_szukany;
	float P_x;

	void pobierz_dane() {
		cout << "Podaj liczbe wezlow: "; cin >> liczba_wezlow;
		cout << endl;
		if (liczba_wezlow < 2) {
			cout << "Liczba wezlow nie moze byc mniejsza niz 2! Program zostanie zakonczony" << endl;
			system("pause");
			exit(0);
		}
		x_i = new float[liczba_wezlow];
		f_i = new float[liczba_wezlow];
		cout << "Podaj kolejne wartosci x:" << endl;
		for (int i = 0; i < liczba_wezlow; i++) {
			cout << "x_" << i << " = "; cin >> x_i[i];
			if (i > 0) {
				if (x_i[i - 1] > x_i[i]) {
					cout << "Podana wartosc x jest niepoprawna (mniejsza od poprzedniej)! Program zostanie zakonczony" << endl;
					system("pause");
					exit(0);
				}
				for (int j = 0; j < i; j++) {
					if (x_i[i] == x_i[j]) {
						cout << "Podana wartosc juz istnieje! Program zostanie zakonczony" << endl;
						system("pause");
						exit(0);
					}
				}
			}
		}
		cout << endl << "Podaj kolejne wartosci f(x):" << endl;
		for (int i = 0; i < liczba_wezlow; i++) {
			cout << "f(x_" << i << ") = "; cin >> f_i[i];
		}
		cout << endl << "Podaj x dla ktorego mam obliczyc wartosc: "; cin >> x_szukany;
		if (x_szukany < x_i[0] || x_szukany > x_i[liczba_wezlow - 1]) {
			cout << endl << "Podano x spoza zakresu funkcji! Program zostanie zakonczony" << endl;
			system("pause");
			exit(0);
		}
	}
	void oblicz() {
		float* l_i = new float[liczba_wezlow];
		for (int i = 0; i < liczba_wezlow; i++) {
			l_i[i] = 1;
			for (int k = 0; k < liczba_wezlow; k++) {
				if (k == i) continue;
				l_i[i] *= (x_szukany - x_i[k]) / (x_i[i] - x_i[k]);
			}
		}
		//obliczamy wielomian
		P_x = 0;
		for (int i = 0; i < liczba_wezlow; i++) {
			P_x += l_i[i] * f_i[i];
		}
		delete[] l_i;
	}
	void wyswietl_wynik() {
		cout << endl << "f(x) = " << P_x << endl;
	}
	Data() {
		pobierz_dane();
		oblicz();
		wyswietl_wynik();
	}
	~Data() {
		delete[] x_i;
		delete[] f_i;
	}
};

int main() {
	Data D;

	system("pause");
	return 0;
}