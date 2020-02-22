//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void error() {
	//system("cls");
	cout << "Error! Program will be terminated..." << endl;
	Sleep(1500);
	system("pause");
	exit(0);
}

class Array2D {
	int width, height;
	string name;
	int* start;
public:
	const int& getWidth() const {
		return width;
	}
	const int& getHeight() const {
		return height;
	}
	void changeName(string name) {
		this->name = name;
	}
	void setTabValue(int row, int column, int value) {
		if (row >= height || column >= width) {
			error();
		} else {
			int div = row * width + column;
			start[div] = value;
		}
	}
	const int& getTabValue(int row, int column) const {
		if (row >= this->height || column >= this->width) {
			error();
		}
		else {
			int div = row * this->width + column;
			return this->start[div];
		}
	}
	Array2D add(const Array2D& addedArray2D) const {
		if (addedArray2D.getWidth() != width || addedArray2D.getHeight() != height) {
			error();
		} else {
			Array2D newArray2D(width, height, "Adding Result");
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					newArray2D.setTabValue(i, j, getTabValue(i, j) + addedArray2D.getTabValue(i, j));
				}
			}
			return newArray2D;
		}
	}
	Array2D multiply(const Array2D& multipliedArray2D) const {
		if (this->width != multipliedArray2D.getHeight()) {
			error();
		} else {
			Array2D newArray2D(this->height, multipliedArray2D.getWidth(), "Multiplying Result");
			int val;
			for (int i = 0; i < this->height; i++) {
				for (int j = 0; j < multipliedArray2D.getWidth(); j++) {
					val = 0;
					for (int k = 0; k < this->width; k++) {
						val += (this->getTabValue(i, k) * multipliedArray2D.getTabValue(k, j));
					}
					newArray2D.setTabValue(i, j, val);
				}
			}
			return newArray2D;
		}
	}
	ostream& display(ostream& stream) const {
		stream << "Tablica: " << name << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				stream << this->getTabValue(i, j) << "\t";
			}
			stream << endl;
		}
		return stream;
	}
	Array2D(int height, int width, string name) {
		cout << endl << "Czesc! Tu konstruktor 1 Tablicy: " << name << " :)" << endl;
		this->width = width;
		this->height = height;
		this->name = name;
		start = new int[width * height];
		for (int i = 0; i < width * height; i++) {
			start[i] = 0;
		}
	}
	Array2D(const Array2D& copiedObject) :
		width(copiedObject.width), height(copiedObject.height), name("NowaKopia-" + copiedObject.name) {
		start = new int[this->width * this->height];
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->width; j++) {
				this->setTabValue(i, j, copiedObject.getTabValue(i, j));
			}
		}
		cout << endl << "Czesc! Tu konstruktor 2(kopiujacy) Tablicy: " << name << " :)" << endl;
	}
	~Array2D() {
		cout << endl << "Czesc! Tu destruktor Tablicy: " << name << " :)" << endl;
		delete[] start;
		system("pause");
	}
};

int main() {
	Array2D Arr(3, 3, "Andrzej");
	Arr.setTabValue(0, 0, 55);
	Arr.setTabValue(1, 1, 99);
	Arr.setTabValue(2, 2, 23);
	Arr.display(cout) << endl;

	Array2D Arr2(3, 5, "Ania");
	Arr2.setTabValue(0, 0, 10);
	Arr2.setTabValue(2, 2, 5);
	Arr2.setTabValue(1, 1, 4);
	Arr2.setTabValue(2, 4, 100);
	Arr2.display(cout) << endl;

	Array2D Arr3(Arr.multiply(Arr2));
	Arr3.display(cout) << endl;

	Array2D Arr4(3, 3, "Basia");
	Arr4.setTabValue(0, 1, 14);
	Arr4.setTabValue(2, 1, 120);
	Arr4.setTabValue(1, 0, 88);

	Array2D Arr5(Arr4.add(Arr));
	Arr5.display(cout) << endl;

	system("pause");
	return 0;
}