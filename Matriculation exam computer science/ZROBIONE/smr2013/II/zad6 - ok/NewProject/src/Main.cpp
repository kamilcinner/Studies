#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void loadData(string* S) {
	ifstream file("dane.txt");
	if (file.is_open()) {
		for (int i = 0; i < 5000; i++) {
			file >> S[i];
		}
		file.close();
	}
}

int a(string* S) {
	int count = 0;
	for (int i = 0; i < 5000; i++) {
		if (S[i][0] == S[i][S[i].size() - 1]) count++;
	}
	return count;
}

/*int b(string* S) { // dzialamy na ASCII
	int count = 0;
	int numberOfDigits;
	unsigned long long int* numbers = new unsigned long long int[5000];
	string* newS = new string[5000];
	for (int i = 0; i < 5000; i++) {
		numberOfDigits = 1;
		numbers[i] = 0;
		for (unsigned int j = 0; j < S[i].size(); j++) {
			numbers[i] += static_cast<unsigned long long int>(((int)S[i][j] - 48) * pow(8 , S[i].size() - 1 - j));
		}
		while (numbers[i] / static_cast<unsigned long long int>(pow(10, numberOfDigits)) != 0) {
			numberOfDigits++;
		}
		if (numbers[i] / static_cast<unsigned long long int>(pow(10, numberOfDigits - 1)) == numbers[i] % 10) {
			count++;
		}
	}
	delete[] numbers;
	delete[] newS;
	return count;
}*/

int b(string* S) { // dzialamy na ASCII
	unsigned int ile = 0, liczba;
	string dziesietnie;
	stringstream ss;
	for (unsigned int i = 0; i < 5000; i++) {
		ss.str("");
		liczba = 0;
		for (unsigned int j = 0; j < S[i].size(); j++) {
			liczba +=(S[i][j]-48) * pow(8, S[i].size() - 1 - j);
		}
		ss << liczba;
		dziesietnie = ss.str();
		if (dziesietnie[0] == dziesietnie.back()) ile++;
	}
	return ile;
}

vector<string> c(string* S, unsigned int& count) {
	count = 0;
	bool goodS, gotMinMax = false;
	unsigned long long int number, max, min;
	string maxS, minS;
	for (unsigned int i = 0; i < 5000; i++) {
		goodS = true;
		for (unsigned int j = 1; j < S[i].size(); j++) {
			if ((int)S[i][j - 1] > (int)S[i][j]) {
				goodS = false;
				break;
			}
		}
		if (goodS) {
			count++;
			number = 0;
			for (unsigned int j = 0; j < S[i].size(); j++) {
				number += static_cast<unsigned long long int>(((int)S[i][j] - 48) * pow(8, S[i].size() - 1 - j));
			}
			if (!gotMinMax) {
				max = min = number;
				gotMinMax = true;
			}
			else if (number > max) {
				max = number;
				maxS = S[i];
			}
			else if (number < min) {
				min = number;
				minS = S[i];
			}
		}
	}
	return { maxS, minS };
}

int main() {
	string* S = new string[5000];
	loadData(S);

	// zad 1
	cout << "a: " << a(S) << endl;
	// zad 2
	cout << "b: " << b(S) << endl;
	// zad 3
	unsigned  count;
	vector<string>max_min = c(S, count);
	cout << "c:" << " ilosc: " << count << " max: " << max_min[0] << " min: " << max_min[1] << endl;

	delete[] S;
	cout << endl << "END"; cin.get();
}