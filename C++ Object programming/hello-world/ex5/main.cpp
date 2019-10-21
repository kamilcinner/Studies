#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class BinaryMaker {
	int number;
	int numberOriginal;
	string binaryInversed;
	string binary;

public:
	bool setNumber() {
		cout << "Enter number: ";
		int x;
		cin >> x;
		if (x <= 0) return false;
		else {
			number = x;
			return true;
		}
	}
	void makeBinary() {
		numberOriginal = number;
		while (number / 2 != 0) {
			if (number % 2 != 0) {
				binaryInversed += '1';
			} else {
				binaryInversed += '0';
			}
			number /= 2;
		}
		for (int i = binaryInversed.length() - 1; i >= 0; i--) {
			binary += binaryInversed[i];
		}
	}
	void showResult() {
		cout << numberOriginal << ": " << binary << endl;
	}
};
class Actions {
public:
	void err() {
		system("cls");
		cout << "Error! Try again...";
		Sleep(500);
		system("cls");
	}
};

int main() {
	BinaryMaker* BM = new BinaryMaker;
	Actions* Act = new Actions;
	while (!BM->setNumber()) Act->err();
	BM->makeBinary();
	BM->showResult();
	system("pause");
	BM = NULL; delete BM;
	Act = NULL; delete Act;
	return 0;
}