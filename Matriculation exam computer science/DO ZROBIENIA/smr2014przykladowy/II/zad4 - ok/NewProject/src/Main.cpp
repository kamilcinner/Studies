#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

class Punkt {
public:
	double x;
	double y;
};

Punkt oblicz_punkt(const double& r, const double& t, const double& T) {
	Punkt P;
	P.x = r * sin((2 * M_PI * t) / T);
	P.y = r * cos((2 * M_PI * t) / T);
	return P;
}

void p1() {
	double t = 2.95;
	Punkt P;
	do {
		t += 0.05;
		P = oblicz_punkt(5.0, t, 12.5);
	} while (P.x >= P.y);
	cout << "1: " << t - 3.0 << endl;
}

void p2() {
	ofstream file("dane.txt");
	double t = 0.0;
	Punkt P;
	do {
		P = oblicz_punkt(t, t, 10);
		file << P.x << "\t" << P.y << endl;
		t += 0.5;
	} while (t <= 10.0);
	file.close();
}

void p3() {
	//21 punktow
	ifstream file("dane.txt");
	vector<Punkt> punkty;
	Punkt P;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 21; i++) {
			file >> P.x;
			file >> P.y;
			punkty.push_back(P);
		}
		file.close();
	}
	double d = 0;
	for (unsigned int i = 1; i < 21; i++) {
		d += sqrt(pow(punkty[i - 1].x - punkty[i].x, 2) + pow(punkty[i - 1].y - punkty[i].y, 2));
	}
	cout << "3: " << d << endl;
}

int main() {
	p1();
	p2();
	p3();

	cout << endl << "END"; cin.get();
}