//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <limits>

typedef std::numeric_limits<double> dbl;

using namespace std;

double f(const double &x) { return x * x - 15; }

double fp(const double &x) { return 2 * x; }

double Bisekcja(double a, double b, int &k, const double &E) {
	double x;
	k = 0;
	do {
		k++;
		x = (a + b) / 2;
		if (fabs(f(x)) <= E) break;
		if (f(a)*f(x) < 0) b = x;
		else a = x;
	} while (fabs(b - a) >= E);
	return x;
}

bool Newton(double &x, const double &x0, int &k, const int &K_MAX, const double &E) {
	x = x0;
	k = 0;
	do {
		k++;
		x = x - f(x) / fp(x);
	} while (fabs(f(x)) > E && k < K_MAX);
	if (k == K_MAX) return false;
	return true;
}

void showResult(const string &name, const double &x, const int &k) {
	cout << name << endl;
	cout << "x = " << x << endl;
	cout << "Liczba krokow = " << k << endl;
	cout << endl;
}

void setPrecision(double &E) {
	int e;
	cout << "Podaj dokladnosc 'epsilon'\n(liczba miejsc po przecinku, min -> 0, max -> 15): ";
	cin >> e;
	if (e < 0 || e > 15) {
		cout << "Blad. Koncze dzialanie." << endl;
		cin.get(); cin.get();
		exit(0);
	}
	//cout << setprecision(e + 1);
	cout << setprecision(dbl::max_digits10);
	E = 1;
	for (int i = 0; i < e; i++) E /= 10;
}

int main() {
	double E, x;
	int K_MAX = 40, k;
	setPrecision(E);
	cout << endl << "Wartosc oczekiwana: sqrt(15) = " << sqrt(15) << endl << endl;

	// BISEKCJA
	if (f(3) * f(4) >= 0) {
		cout << "Nie mozemy obliczyc metoda Bisekcji dla a = 3, b = 4" << endl << endl;
	} else {
		x = Bisekcja(3, 4, k, E);
		showResult("Bisekcja dla a = 3, b = 4", x, k);
	}
	// NEWTON DLA 3
	if (Newton(x, 3, k, K_MAX, E)) {
		showResult("Newton dla x0 = 3", x, k);
	} else
		cout << "Nie mozemy obliczyc metoda Newtona dla x0 = 3" << endl << endl;
	// NEWTON DLA 4
	if (Newton(x, 4, k, K_MAX, E)) {
		showResult("Newton dla x0 = 4", x, k);
	}
	else
		cout << "Nie mozemy obliczyc metoda Newtona dla x0 = 4" << endl << endl;

	cin.get(); cin.get(); return 0;
}