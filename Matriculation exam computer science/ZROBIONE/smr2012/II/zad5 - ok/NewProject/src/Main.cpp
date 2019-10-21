#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Maksima {
public:
	int numerWiersza;
	unsigned long long int max;
};

void stworzTrojkatPascala(vector<vector<unsigned long long int>>& trojkat, const unsigned int& size) {
	vector<unsigned long long int> liczby;
	for (unsigned int i = 0; i < size; i++) {
		liczby.clear();
		for (unsigned int j = 0; j <= i; j++) {
			liczby.push_back(1);
		}
		trojkat.push_back(liczby);
	}
	for (unsigned int i = 1; i < trojkat.size(); i++) {
		for (unsigned int j = 1; j < i; j++) {
			trojkat[i][j] = trojkat[i - 1][j - 1] + trojkat[i - 1][j];
		}
	}
	for (unsigned int i = 0; i < trojkat.size(); i++) {
		for (unsigned int j = 0; j <= i; j++) {
			cout << trojkat[i][j] << "  ";
		}
		cout << endl;
	}
}

vector<Maksima> a(const vector<vector<unsigned long long int>>& trojkat) {
	vector<Maksima> maksima;
	Maksima maksimum;
	unsigned long long int max[2];
	for (unsigned int k : {9, 19, 29}) {
		maksimum.numerWiersza = k + 1;
		maksimum.max = 0;
		for (unsigned int i = 0; i < trojkat[k].size(); i++) {
			if (trojkat[k][i] > maksimum.max) maksimum.max = trojkat[k][i];
		}
		maksima.push_back(maksimum);
	}
	return maksima;
}

vector<unsigned int> b(const vector<vector<unsigned long long int>>& trojkat) {
	vector<unsigned int> zestawienie;
	unsigned int liczbaCyfr, suma;
	for (unsigned int i = 0; i < trojkat.size(); i++) {
		suma = 0;
		for (unsigned int j = 0; j < trojkat[i].size(); j++) {
			liczbaCyfr = 1;
			while (trojkat[i][j] / (unsigned long long int)pow(10, liczbaCyfr) != 0) {
				liczbaCyfr++;
			}
			suma += liczbaCyfr;
		}
		zestawienie.push_back(suma);
	}
	return zestawienie;
}

vector<unsigned int> c(const vector<vector<unsigned long long int>>& trojkat) {
	vector<unsigned int> wiersze;
	bool nieMaPodzielnych;
	for (unsigned int i = 0; i < trojkat.size(); i++) {
		nieMaPodzielnych = true;
		for (unsigned int j = 0; j < trojkat[i].size(); j++) {
			if (trojkat[i][j] % 5 == 0) nieMaPodzielnych = false;
		}
		if (nieMaPodzielnych) wiersze.push_back(i + 1);
	}
	return wiersze;
}

vector<string> d(const vector<vector<unsigned long long int>>& trojkat) {
	vector<string> graf;
	graf.resize(trojkat.size());
	for (unsigned int i = 0; i < trojkat.size(); i++) {
		for (unsigned int j = 0; j <= i; j++) {
			if (trojkat[i][j] % 3 == 0) {
				graf[i].push_back('X');
			}
			else graf[i].push_back(' ');
		}
	}
	return graf;
}

int main() {
	ofstream file("wynik5.txt");
	vector<vector<unsigned long long int>> trojkat;
	stworzTrojkatPascala(trojkat, 30);
	// a
	file << "a: " << endl;
	vector<Maksima> maksima = a(trojkat);
	for (unsigned int i = 0; i < 3; i++) {
		file << maksima[i].numerWiersza << ": " << maksima[i].max << endl;
	}
	// b
	file << endl << "b: " << endl;
	vector<unsigned int> zestawienie = b(trojkat);
	for (unsigned int i = 0; i < trojkat.size(); i++) {
		file << i + 1 << ": " << zestawienie[i] << endl;
	}
	// c
	file << endl << "c: " << endl;
	vector<unsigned int> numeryWierszy = c(trojkat);
	for (unsigned int i = 0; i < numeryWierszy.size(); i++) {
		file << numeryWierszy[i] << endl;
	}
	// d
	file << endl << "d: " << endl;
	vector<string> graf = d(trojkat);
	for (unsigned int i = 0; i < graf.size(); i++) {
		file << graf[i] << endl;
	}
	file.close();

	cout << endl << "END"; cin.get();
}