#include <iostream>

using namespace std;

class Point {
	int x, y;

public:
	void setX(int x){
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}

	void vector() {
	cout << "[" << x << "," << y << "]";
	}
	float lenght() {
		return sqrt(x * x + y * y);
	}
	bool osX() {
		if (y == 0) return true;
		else return false;
	}
	bool osY() {
		if (x == 0) return true;
		else return false;
	}
	int ex() {
		if (x > 0 && y > 0) return 1;
		else if (x < 0 && y>0) return 2;
		else if (x < 0 && y < 0) return 3;
		else if (x > 0 && y < 0) return 4;
		else return 0;
	}

	Point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
};

int main() {
	Point* P = new Point[4];
	P[0].setX(4); P[0].setY(7);
	P[1].setX(-5); P[1].setY(3);
	P[2].setX(-9); P[2].setY(-65);
	P[3].setX(1); P[3].setY(-2);

	for (int i = 0; i < 4; i++) {
		P[i].vector(); cout << endl;
		if (P[i].ex() == 1) {
			cout << "1 cw" << endl;
		} else if (P[i].ex() == 2) {
			cout << "2 cw" << endl;
		} else if (P[i].ex() == 3) {
			cout << "3 cw" << endl;
		} else if (P[i].ex() == 4) {
			cout << "4 cw" << endl;
		} else {
			cout << "Os" << endl;
		}
		cout << "Odleglosc = " << P[i].lenght() << endl;
	}

	system("pause");
	delete[] P;
	return 0;
}