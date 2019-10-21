#include <iostream>
#include <fstream>
using namespace std;

bool sumaCyfrLiczbaPierwsza(const unsigned int& liczba) {
	unsigned int sumaCyfr = 0, liczbaCyfr = 1;
	while (liczba / (unsigned int)pow(10, liczbaCyfr) != 0) {
		liczbaCyfr++;
	}
	for (unsigned int i = 0; i < liczbaCyfr; i++) {
		sumaCyfr += (liczba % (unsigned int)pow(10, i + 1)) / (unsigned int)pow(10, i);
	}
	if (sumaCyfr == 1) return false;
	for (unsigned int i = 2; i < sumaCyfr; i++) {
		if (sumaCyfr % i == 0) return false;
	}
	return true;
}

bool super_B_pierwsza(const unsigned int& liczba) {
	if (liczba == 1) return false;
	// warunek 1
	for (unsigned int i = 2; i < liczba; i++) {
		if (liczba % i == 0) return false;
	}
	// warunek 2
	if (!sumaCyfrLiczbaPierwsza(liczba)) return false;
	// warunek 3
	unsigned int temp = liczba;
	unsigned int sumaBinarnie = 0;
	do {
		if (temp % 2 == 1) sumaBinarnie++;
		temp /= 2;
	} while (temp != 0);
	if (sumaBinarnie == 1) return false;
	for (unsigned int i = 2; i < sumaBinarnie; i++) {
		if (sumaBinarnie % i == 0) return false;
	}
	return true;
}

void a() {
	unsigned int ile = 0;
	ofstream file1("1.txt");
	for (unsigned int i = 2; i <= 1000; i++) {
		if (super_B_pierwsza(i)) {
			ile++;
			file1 << i << endl;
		}
	}
	file1 << "liczba: " << ile << endl;
	file1.close();
	ile = 0;
	ofstream file2("2.txt");
	for (unsigned int i = 100; i <= 10000; i++) {
		if (super_B_pierwsza(i)) {
			ile++;
			file2 << i << endl;
		}
	}
	file2 << "liczba: " << ile << endl;
	file2.close();
	ile = 0;
	ofstream file3("3.txt");
	for (unsigned int i = 1000; i <= 100000; i++) {
		if (super_B_pierwsza(i)) {
			ile++;
			file3 << i << endl;
		}
	}
	file3 << "liczba: " << ile << endl;
	file3.close();
}

void b() {
	unsigned int ile = 0, suma = 0;
	ofstream file("b.txt");
	for (unsigned int i = 100; i <= 10000; i++) {
		if (sumaCyfrLiczbaPierwsza(i)) ile++;
		if (super_B_pierwsza(i)) suma += i;
	}
	file << "1: " << ile << endl;
	bool pierwsza = true;
	for (unsigned int i = 2; i < suma; i++) {
		if (suma % i == 0) {
			pierwsza = false;
			break;
		}
	}
	file << "2: ";
	if (pierwsza) file << "TAK";
	else file << "NIE";
	file << endl;
	file.close();
}

int main() {
	// a
	a();
	// b
	b();

	cout << endl << "END"; cin.get();
}