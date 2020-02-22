#include <iostream>
#include <string>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <cmath> 

using namespace std;

const int M_PI = 3.14;
//M_PI

class Circle {
	float radius;
	string colour;

public:
	void setRadius(float radius) {
		this->radius = radius;
	}
	void setColour(string colour) {
		this->colour = colour;
	}
	float getRadius() {
		return radius;
	}
	string getColour() {
		return colour;
	}

	float calcField() {
		return M_PI * getRadius() * getRadius();
	}
	float calcCircumference() {
		return 2 * M_PI * getRadius();
	}

	Circle(float radius = 1, string colour = "Bialy") {
		this->radius = radius;
		this->colour = colour;
	}
};

void showAll(Circle K) {
	cout << "Radius: " << K.getRadius() << endl;
	cout << "Colour: " << K.getColour() << endl;
	cout << "Circumference: " << K.calcCircumference() << endl;
	cout << "Field: " << K.calcField() << endl;
}

int main() {
	Circle K1, K2;

	cout << "K1" << endl;
	showAll(K1);
	cout << "K2" << endl;
	showAll(K2);

	K1.setColour("czerwony");
	K2.setColour("czerwony");

	cout << "K1" << endl;
	showAll(K1);
	cout << "K2" << endl;
	showAll(K2);

	K1.setColour("zielony");
	K2.setColour("pomaranczowy");

	cout << "K1" << endl;
	showAll(K1);
	cout << "K2" << endl;
	showAll(K2);

	system("pause");
	return 0;
}