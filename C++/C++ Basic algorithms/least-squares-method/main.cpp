//Kamil Cinner IIST 3.2
#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;

void err() {
	system("cls");
	cout << "Blad! Sprobuj ponownie...";
	Sleep(2000);
	system("cls");
}

class node {
public:
	double x;
	double f;
};

class Data {
public:
	int n;
	node* Node;
	double a0, a1;

	enum Function {ex2, ex4};
	Function func;
	bool canWeDoEx4 = true;

	void setFunc() {
		int choice;
		bool repeat;
		do {
			repeat = false;
			cout << "Wybierz funkcje:" << endl;
			cout << "1. g(x) = c0 + c1x" << endl;
			cout << "2. g(x) = b * a^x" << endl;
			cout << "3. Zakoncz program" << endl;
			cout << ": "; cin >> choice;
			switch (choice) {
			case 1: func = ex2; break;
			case 2: func = ex4; break;
			case 3: exit(0);
			default: {
				err();
				repeat = true;
			}
			}
		} while (repeat);
	}
	void setN() {
		system("cls");
		cout << "Podaj liczbe wezlow: ";
		cin >> n;
		if (n <= 0) {
			err();
			setN();
		}
	}
	void setNodes() {
		Node = new node[n];
		for (int i = 0; i < n; i++) {
			system("cls");
			cout << "Node [" << i << "]" << endl;
			cout << "x = ";
			cin >> Node[i].x;
			cout << "f = ";
			cin >> Node[i].f;
			if (Node[i].f <= 0) canWeDoEx4 = false;
		}
	}
	double calcDet(double a0, double a1, double a2, double a3) {
		//	a0	a1
		//	
		//	a2	a3
		return a0 * a3 - a2 * a1;
	}
	void calc() {
		double xSum = 0, x2Sum = 0, fSum = 0, fxSum = 0;
		if (func == ex2) {
			for (int i = 0; i < n; i++) {
				xSum += Node[i].x;
				x2Sum += Node[i].x * Node[i].x;
				fSum += Node[i].f;
				fxSum += Node[i].f * Node[i].x;
			}
		}
		else { //ex4
			if (!canWeDoEx4) {
				system("cls");
				cout << "Wybrana funkcja obsluguje tylko wartosci dodatnie f." << endl;
				cout << "Czy mam obliczyc wynik funkcja pierwsza? :)" << endl;
				cout << "1 - Tak" << endl;
				cout << "# - Nie, zakoncz program" << endl;
				cout << ": ";
				int choice;
				cin >> choice;
				system("cls");
				switch (choice) {
					case 1: {
						func = ex2;
						calc();
						return;
					}
					default: exit(0);
				}
			}
			for (int i = 0; i < n; i++) {
				xSum += Node[i].x;
				x2Sum += Node[i].x * Node[i].x;
				fSum += log(Node[i].f);
				fxSum += log(Node[i].f) * Node[i].x;
			}
		}
		double W = calcDet(n, xSum, xSum, x2Sum);
		double W0 = calcDet(fSum, xSum, fxSum, x2Sum);
		double W1 = calcDet(n, fSum, xSum, fxSum);
		
		a0 = W0 / W;
		a1 = W1 / W;

		if (func == ex4) {
			a0 = exp(a0);
			a1 = exp(a1);
		}
	}
	void showResult() {
		cout << "g(x) = " << a0 << " ";
		switch (func) {
			case ex2: {
				if (a1 > 0) cout << "+ " << a1 << "x";
				else if (a1 < 0)cout << a1 << "x";
				break;
			}
			case ex4: {
				if (a1 > 0)cout << "* " << a1 << "^x";
				else if (a1 < 0)cout << "* (" << a1 << ")^x";
			}
		}
		cout << endl;
	}
	Data() {
		setFunc();
		setN();
		setNodes();
		calc();
		showResult();
	}
	~Data() {
		delete[] Node;
	}
};

int main() {
	Data D;
	system("pause");
	return 0;
}