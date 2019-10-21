#include <iostream>
using namespace std;

int main() {

	unsigned int number = 12;
	unsigned int digitsCount = (unsigned int)log10(number) + 1;
	cout << "liczba: " << number << endl;
	cout << "liczba cyfr: " << digitsCount << endl;

	cout << endl << "END"; cin.get();
}