#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Najwieksza {
public:
	unsigned long long int dziesietnie;
	string dwojkowo;
};

void wczytaj(vector<string>& liczby) {
	ifstream file("liczby.txt");
	string temp;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 1000; i++) {
			file >> temp;
			liczby.push_back(temp);
		}
		file.close();
	}
}

int a(const vector<string>& liczby) {
	int ile = 0;
	for (unsigned int i = 0; i < 1000; i++) {
		if (liczby[i][liczby[i].size() - 1] == '0') ile++;
	}
	return ile;
}

Najwieksza b(const vector<string>& liczby) {
	Najwieksza max;
	max.dziesietnie = 0;
	unsigned long long int temp;
	for (unsigned int i = 0; i < 1000; i++) {
		temp = 0;
		for (unsigned int j = 0; j < liczby[i].size(); j++) {
			if (liczby[i][j] == '1') {
				temp += pow(2, liczby[i].size() - 1 - j);
			}
		}
		if (temp > max.dziesietnie) {
			max.dziesietnie = temp;
			max.dwojkowo = liczby[i];
		}
	}
	return max;
}

int c(const vector<string>& liczby, string& dwojkowo) {
	int ile = 0;
	unsigned long long int suma = 0;
	for (unsigned int i = 0; i < 1000; i++) {
		if (liczby[i].size() == 9) {
			ile++;
			for (unsigned int j = 0; j < liczby[i].size(); j++) {
				if (liczby[i][j] == '1') {
					suma += pow(2, liczby[i].size() - 1 - j);
				}
			}
		}
	}
	do {
		if (suma % 2 == 0) {
			dwojkowo.push_back('0');
		}
		else dwojkowo.push_back('1');
		suma /= 2;
	} while (suma != 0);
	char temp;
	for (unsigned int i = 0; i < dwojkowo.size() / 2; i++) {
		temp = dwojkowo[i];
		dwojkowo[i] = dwojkowo[dwojkowo.size() - 1 - i];
		dwojkowo[dwojkowo.size() - 1 - i] = temp;
	}
	return ile;
}

int main() {
	vector<string> liczby;
	wczytaj(liczby);
	// a
	cout << "a: " << a(liczby) << endl << endl;
	// b
	Najwieksza max = b(liczby);
	cout << "b:" << endl;
	cout << "dziesietnie: " << max.dziesietnie << endl;
	cout << "dwojkowo: " << max.dwojkowo << endl << endl;
	// c
	string dwojkowo;
	cout << "c: " << endl;
	cout << "ilosc: " << c(liczby, dwojkowo) << endl;
	cout << "liczba dwojkowo: " << dwojkowo << endl;

	cout << endl << "END"; cin.get();
}