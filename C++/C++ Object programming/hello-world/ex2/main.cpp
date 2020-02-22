#include <iostream>
#include <time.h>
#include <windows.h>
#include <iomanip>

using namespace std;

class Data {
  public:
	int number;
	int choice;
	bool proceed;
	bool stay;

	Data() {
		stay = true;
	}
};

class Actions {
  public:
	void error() {
		system("cls");
		cout << "Error! Try again...";
		Sleep(1000);
		system("cls");
	}
};


int main() {
	Data Data;
	Actions Act;
	cout << showbase;

	/*cout << showbase;
	cout << dec << 114 << endl;
	cout << noshowbase;
	cout << dec << 114 << endl;

	cout << showbase;
	cout << hex << 114 << endl;
	cout << noshowbase;
	cout << hex << 114 << endl;

	cout << showbase;
	cout << oct << 114 << endl;
	cout << noshowbase;
	cout << oct << 114 << endl;

	system("pause");
	return 0;*/

	do {
		Data.proceed = true;

		cout << "Witaj w konwerterze liczb!" << endl;
		cout << "Z jakiego systemu liczbowego chcesz rozpoczac konwersje?" << endl;
		cout << "1. Osemkowy" << endl;
		cout << "2. Dziesietny" << endl;
		cout << "3. Szestnastkowy" << endl;
		cout << "4. Wybor automatyczny" << endl;
		cout << "5. Zakoncz program" << endl;
		cout << ": ";
		cin >> Data.choice;

		switch (Data.choice) {
		case 1: {
			cout << oct;
			break;
		}
		case 2: {
			cout << dec;
			break;
		}
		case 3: {
			cout << hex;
			break;
		}
		case 4: {
			cout << setbase(0);
			break;
		}
		case 5: {
			Data.proceed = false;
			Data.stay = false;
			break;
		}
		default: {
			Data.proceed = false;
			Act.error();
		}
		}

		if (Data.proceed) {
			system("cls");
			cout << "Podaj liczbe: ";
			cin >> Data.number;
			system("cls");

			do {
				Data.proceed = false;

				cout << "Konwertuj na system liczb" << endl;
				cout << "1. Osemkowy" << endl;
				cout << "2. Dziesietny" << endl;
				cout << "3. Szestnastkowy" << endl;
				cout << ": ";
				cin >> Data.choice;

				system("cls");
				
				switch (Data.choice) {
				case 1: {
					cout << oct << Data.number << endl;
					system("pause");
					break;
				}
				case 2: {
					cout << dec << Data.number << endl;
					system("pause");
					break;
				}
				case 3: {
					cout << hex << Data.number << endl;
					system("pause");
					break;
				}
				default: {
					Data.proceed = true;
					Act.error();
				}
				}
				system("cls");
			} while (Data.proceed);
		}
	} while (Data.stay);
	
	return 0;
}