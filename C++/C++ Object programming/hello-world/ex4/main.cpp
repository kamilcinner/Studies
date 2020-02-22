#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Worker {
	string name, lastname, date_of_employment;
	float hourly_rate, hours_count;

public:
	void setName(string name) {
		this->name = name;
	}
	void setLastname(string lastname) {
		this->lastname = lastname;
	}
	void setHourly_rate(float hourly_rate) {
		this->hourly_rate = hourly_rate;
	}
	void setHours_count(float hours_count) {
		this->hours_count = hours_count;
	}
	void setDate_of_employment(string date_of_employment) {
		this->date_of_employment = date_of_employment;
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
	float getHours_count() {
		return hours_count;
	}
	string getDate_of_employment() {
		return date_of_employment;
	}
};

int main() {

	Worker* Wor;
	ifstream infile("file.txt");
	string line;
	int lineCount = 0;
	string a, b, e;
	float c, d;
	int i = 0;
	//stringstream ss;

	//system("pause");

	/*if (infile.is_open()) {
		while (!infile.eof()) {
			getline(infile, line);
			lineCount++;
		}
		infile.close();
		Wor = new Worker[lineCount];
	} else cout << "Unable to open file1!" << endl;*/
	lineCount = 3; Wor = new Worker[lineCount];
	
	if (infile.is_open()) {
		while (!infile.eof()) {
			getline(infile, line);
			stringstream ss(line);
			if (ss >> a >> b >> c >> d >> e) {
				Wor[i].setName(a);
				Wor[i].setLastname(b);
				Wor[i].setHourly_rate(c);
				Wor[i].setHours_count(d);
				Wor[i].setDate_of_employment(e);
			}
			i++;
		}
		infile.close();
	} else cout << "Unable to open file2!" << endl;

	cout << "Preparing the table..." << endl;

	cout << setw(15) << left << "|Name" << setw(15) << left << "|Lastname" << setw(17) << left << "|Hourly rate" << setw(20) << left << "|Number of hours" << setw(23) << left << "|Date of employment" << "|" << endl;
	
	
	stringstream ss;
	//locale mylocale("");
	//ss.imbue(mylocale);

	//locale us("en_US.UTF-8");
	//ss.imbue(std::locale("en_US.utf8"));

	for (i = 0; i < lineCount; i++) {
		cout << "|" << setw(14) << left << Wor[i].getName() << "|" << setw(14) << left << Wor[i].getLastname() << "|" << setw(16) << left << Wor[i].getHoutly_rate() << "|" << setw(19) << left << Wor[i].getHours_count() << "|" << setw(22) << left << Wor[i].getDate_of_employment() << "|" << endl;
		
		ss.str("");
		ss << Wor[i].getHoutly_rate();
		
		cout << "|" << setw(14) << left << "" << "|" << setw(14) << left << "" << "|" << setw(16) << left << ss.str() << "|";
		
		ss.str("");
		ss << Wor[i].getHours_count();
		
		cout << setw(19) << left << ss.str() << "|" << setw(22) << left << "" << "|" << endl;
	}

	system("pause");
	return 0;
}