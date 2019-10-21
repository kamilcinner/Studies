//Kamil Cinner IIST 3.2
#include <iostream>

using namespace std;

class Data {
public:
	double h, a, b;
	int n;
	double* x;
	double* f_x;

	double T, S;

	void loadData() {
		cout << "Podaj przedzial dolny calkowania: ";
		cin >> a;
		cout << "Podaj przedzial gorny calkowania: ";
		cin >> b;
		cout << "Podaj krok calkowania: ";
		cin >> h;
	}
	void showResult() {
		prepare();
		makeTabs();
		trapezoidalMethod();
		SimpsonMethod();
		cout << "Wzor trapezow: " << T << endl;
		cout << "Wzor Simpsona: " << S << endl;
	}
	void makeTabs() {
		x = new double[n + 1];
		f_x = new double[n + 1];
		x[0] = a;
		f_x[0] = 2 / (1 + (x[0] * x[0]));
		for (int i = 1; i <= n; i++) {
			x[i] = x[i - 1] + h;
			f_x[i] = 2 / (1 + (x[i] * x[i]));
		}
	}
	void prepare() {
		if (a >= b) {
			cout << "Przedzial <a,b> zostal podany niepoprawnie! Program zostanie zakonczony..." << endl;
			system("pause");
			exit(0);
		} else if (h <= 0 || h > b - a) {
			cout << "Podane h jest poza dopuszczonymi wartosciami! Program zostanie zakonczony..." << endl;
			system("pause");
			exit(0);
		} else {
			n = ceil((b - a) / h);
			h = (b - a) / n;

			cout << "n = " << n << endl;
			cout << "h = " << h << endl;
		}
	}
	void trapezoidalMethod() {
		T = 0;
		for (int i = 1; i < n; i++) {
			T += f_x[i];
		}
		T += (f_x[0] + f_x[n]) / 2;
		T *= h;
	}
	void SimpsonMethod() {
		if (n % 2 == 0) {
			S = f_x[0] + f_x[n];
			for (int i = 1; i < n; i++) {
				if (i % 2 == 0) S += f_x[i] * 2;
				else S += f_x[i] * 4;
			}
			S *= h / 3;
		} else {
			cout << "fixing values for Simpson Method" << endl;
			n++;
			h = (b - a) / n;

			cout << "new n = " << n << endl;
			cout << "new h = " << h << endl;

			makeTabs();
			SimpsonMethod();
		}
	}
	~Data() {
		delete[] x;
		delete[] f_x;
	}
};

int main() {

	Data data;
	data.loadData();
	data.showResult();

	system("pause");
	return 0;
}