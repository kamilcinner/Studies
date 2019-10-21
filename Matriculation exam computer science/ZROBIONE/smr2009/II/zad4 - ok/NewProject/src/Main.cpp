#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;

class Punkt {
public:
	double x;
	double y;
	Punkt() { ; }
	Punkt(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

vector<Punkt> wczytaj() {
	vector<Punkt> smok;
	ifstream file("smok.txt");
	Punkt P;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 4900; i++) {
			file >> P.x;
			file >> P.y;
			smok.push_back(P);
		}
	}
	return smok;
}

Punkt funkcja1(const Punkt& P) {
	Punkt p;
	p.x = (-0.4) * P.x - 1;
	p.y = (-0.4) * P.y + 0.1;
	return p;
}

Punkt funkcja2(const Punkt& P) {
	Punkt p;
	p.x = (0.76) * P.x - (0.4) * P.y;
	p.y = (0.4) * P.x + (0.76) * P.y;
	return p;
}

void algorytm(vector<Punkt>& punkty, Punkt& P) {
	if (rand() % 2 == 0) {
		P = funkcja1(P);
	} else {
		P = funkcja2(P);
	}
	punkty.push_back(P);
}

vector<Punkt> a() {
	Punkt P(1, 1);
	vector<Punkt> punkty;
	for (unsigned int i = 0; i < 5000; i++) {
		algorytm(punkty, P);
	}
	return punkty;
}

Punkt c(const vector<Punkt>& smok) {
	Punkt srodek;
	double sumaX = 0, sumaY = 0;
	for (unsigned int i = 0; i < 4900; i++) {
		sumaX += smok[i].x;
		sumaY += smok[i].y;
	}
	srodek.x = sumaX / 4900;
	srodek.x = round(srodek.x * 10);
	srodek.x /= 10;

	srodek.y = sumaY / 4900;
	srodek.y = round(srodek.y * 10);
	srodek.y /= 10;
	return srodek;
}

void d(const vector<Punkt>& smok, double& maxX, double& maxY, double& minX, double& minY) {
	for (unsigned int i = 0; i < 4900; i++) {
		if (i == 0) {
			maxX = minX = smok[i].x;
			maxY = minY = smok[i].y;
		}
		else {
			if (smok[i].x > maxX) maxX = smok[i].x;
			else if (smok[i].x < minX) minX = smok[i].x;
			if (smok[i].y > maxY) maxY = smok[i].y;
			else if (smok[i].y < minY) minY = smok[i].y;
		}
	}
	maxX = round(maxX * 10);
	maxX /= 10;
	maxY = round(maxY * 10);
	maxY /= 10;
	minX = round(minX * 10);
	minX /= 10;
	minY = round(minY * 10);
	minY /= 10;
}

int main() {
	srand(time(NULL));

	ofstream file("zad_4n.txt");

	// a
	/*file << "a:" << endl << "x" << "\t" << "y" << endl;
	vector<Punkt> punkty = a();
	for (unsigned int i = 0; i < punkty.size(); i++) {
		file << punkty[i].x << "\t" << punkty[i].y << endl;
	}*/

	// c
	file << "c:" << endl;
	vector<Punkt> smok = wczytaj();
	Punkt srodek = c(smok);
	file << "x: " << srodek.x << "  y: " << srodek.y << endl;
	// d
	file << "d:" << endl;
	double maxX, maxY, minX, minY;
	d(smok, maxX, maxY, minX, minY);
	file << "maxX: " << maxX << "  minX: " << minX << endl;
	file << "maxY: " << maxY << "  minY: " << minY << endl;
	
	file.close();

	cout << endl << "END"; cin.get();
}