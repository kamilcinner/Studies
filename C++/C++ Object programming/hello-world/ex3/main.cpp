#include <iostream>
#include <sstream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Worker {
	string name;
	string lastname;
	float hourly_rate;
	float number_of_hours;
	string date_of_employment;

public:
	void setName() {
		cout << "Enter name: ";
		string x;
		cin >> x;
		name = x;
	}
	void setLastname() {
		cout << "Enter lastname: ";
		string x;
		cin >> x;
		lastname = x;
	}
	bool setHourly_rate() {
		cout << "Enter hourly rate: ";
		float x;
		cin >> x;
		if (x <= 0) {
			return false;
		} else {
			hourly_rate = x;
			return true;
		}
	}
	bool setNumber_of_hours() {
		cout << "Enter number of hours: ";
		float x;
		cin >> x;
		if (x <= 0) {
			return false;
		}
		else {
			number_of_hours = x;
			return true;
		}
	}
	bool setDate_of_employment() {
		cout << "Enter date of employment (format: dd mm rrrr): ";
		int x, y, z;
		cin >> x >> y >> z;
		if (x < 0 || x>31) return false;
		else if (y <= 0 || y > 12) return false;
		else if (z <= 0 || z > 2018) return false;
		else {
			stringstream ss;
			ss << x; string xStr = ss.str(); ss.str("");
			ss << y; string yStr = ss.str(); ss.str("");
			ss << z; string zStr = ss.str();
			date_of_employment = xStr + "-" + yStr + "-" + zStr;
			return true;
		}
	}

	string getName() {
		return name;
	}
	string getLastname() {
		return lastname;
	}
	float getHoutly_rate() {
		return hourly_rate;
	}
	float getNumber_of_hours() {
		return number_of_hours;
	}
	string getDate_of_employment() {
		return date_of_employment;
	}
};

class Data {
	int number_of_workers;

public:
	bool setNumber_of_workers() {
		cout << "Podaj liczbe pracownikow: ";
		int x;
		cin >> x;
		if (x <= 0) {
			return false;
		} else {
			number_of_workers = x;
			return true;
		}
	}
	int getNumber_of_workers() {
		return number_of_workers;
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
	Data *D = new Data;
	Actions *Act = new Actions;

	while (!D->setNumber_of_workers()) Act->err();
	
	Worker* Wor = new Worker[D->getNumber_of_workers()];

	system("cls");
	cout << "Podaj dane kolejnych pracownikow:" << endl;
	for (int i = 0; i < D->getNumber_of_workers(); i++) {
		cout << "Pracownik nr " << i + 1 << ":" << endl;
		Wor[i].setName();
		Wor[i].setLastname();
		system("cls");
		cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		while (!Wor[i].setHourly_rate()) {
			Act->err();
			cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		}
		system("cls"); cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		while (!Wor[i].setNumber_of_hours()) {
			Act->err();
			cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		}
		system("cls");  cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		while (!Wor[i].setDate_of_employment()) {
			Act->err();
			cout << "Pracownik: " << Wor[i].getName() << " " << Wor[i].getLastname() << endl;
		}
		system("cls");
	}

	cout << "Preparing the table...";
	Sleep(700);
	system("cls");

	cout << setw(15) << left << "|Name" << setw(15) << left << "|Lastname" << setw(17) << left << "|Hourly rate" << setw(20) << left << "|Number of hours" << setw(23) << left << "|Date of employment" << "|" << endl;
	//for (int i = 0; i < 50; i++) cout << "_"; cout << endl;
	for (int i = 0; i < D->getNumber_of_workers(); i++) {
		cout << "|" << setw(14) << left << Wor[i].getName() << "|" << setw(14) << left << Wor[i].getLastname() << "|" << setw(16) << left << Wor[i].getHoutly_rate() << "|" << setw(19) << left << Wor[i].getNumber_of_hours() << "|" << setw(22) << left << Wor[i].getDate_of_employment() << "|" << endl;
	}

	system("pause");
	return 0;
}