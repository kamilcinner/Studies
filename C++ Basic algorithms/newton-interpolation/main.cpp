//Kamil Cinner IIST 3.2
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

using namespace std;

class node {
public:
	double x;
	double y;
};

class Sort {
	void SWAP(node* W, int a, int b) {
		node x = W[a];
		W[a] = W[b];
		W[b] = x;
	}
public:
	void quicksort(node* W, int lewy, int prawy) {
		double v = W[(lewy + prawy) / 2].x;
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
	int n;
	double x_s, Px_s, multiplier, left, right;
	node* nd;
	double* IR;
	Sort sort;

	bool checkX_s() {
		if (x_s < nd[0].x || x_s > nd[n - 1].x) return false;
		else return true;
	}
	void makeIRArray() {
		for (int i = 0; i < n; i++) {
			IR[i] = nd[i].y;
		}
		for (int i = 1; i < n; i++) {
			for (int k = n - 1; k >= i; k--) {
				IR[k] = (IR[k] - IR[k - 1]) / (nd[k].x - nd[k - i].x);
			}
		}
	}
	void calc() {
		Px_s = IR[0];
		for (int i = 1; i < n; i++) {
			multiplier *= (x_s - nd[i - 1].x);
			Px_s += (IR[i] * multiplier);
		}
	}
	void displayResult() {
		sort.quicksort(nd, 0, n - 1);
		if (checkX_s()) {
			makeIRArray();
			calc();
			cout << "Wartosc interpolowana = " << Px_s << endl;
		} else {
			cout << "Szukany punkt jest poza dopuszczalnym przedzialem!" << endl;
		}
		
	}

	Data(int n) {
		this->n = n;
		nd = new node[n];
		IR = new double[n];
		Px_s = 0;
		multiplier = 1;
	}
};

int main() {
	Data D(3);
	D.x_s = M_PI / 8;

	D.nd[0].x = 0;
	D.nd[1].x = M_PI / 4;
	D.nd[2].x = M_PI / 2;

	D.nd[0].y = 1;
	D.nd[1].y = sqrt(2) / 2;
	D.nd[2].y = 0;

	D.displayResult();

	Data D1(5);
	D1.x_s = M_PI / 8;

	D1.nd[0].x = -M_PI / 2;
	D1.nd[1].x = -M_PI / 4;
	D1.nd[2].x = 0;
	D1.nd[3].x = M_PI / 4;
	D1.nd[4].x = M_PI / 2;

	D1.nd[0].y = 0;
	D1.nd[1].y = sqrt(2) / 2;
	D1.nd[2].y = 1;
	D1.nd[3].y = sqrt(2) / 2;
	D1.nd[4].y = 0;

	D1.displayResult();

	system("pause");
	return 0;
}