#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class Bajt {
public: string bit = "";
};
class Para {
public:
	char znak;
	string kod = "";
};

bool testBit(Bajt bajt, int numerBitu) {
	if (bajt.bit[numerBitu] == '1') return true;
	return false;
}
Bajt ustawBit(const Bajt bajt, int numerBitu) {
	Bajt bajtT;
	for (int i = 0; i < 8; i++) bajtT.bit[i] = bajt.bit[i];
	bajtT.bit[numerBitu] = '1';
	return bajtT;
}

int main()
{
	const int bity = 2; // liczba bitow dla kodu znaku
	const int n = 2; // liczba bajtow
	const int r = 3; // liczba roznych zankow w tekscie
	Bajt bajtTS[n];
	Para paraZK[r];

	// ustawiamy pod 3.1 KAJAK
	bajtTS[0].bit = "01101110";
	bajtTS[1].bit = "01000000";
	paraZK[0].znak = 'K'; paraZK[0].kod = "01";
	paraZK[1].znak = 'A'; paraZK[1].kod = "10";
	paraZK[2].znak = 'J'; paraZK[2].kod = "11";
	// ---

	string bitTS = "";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 8; j++) {
			bitTS += bajtTS[i].bit[j];
		}
	}

	string temp;
	string tekst = "";
	for (int i = 0; i < n * 8; i += bity) {
		temp = "";
		for (int j = 0; j < bity; j++) {
			temp += bitTS[i + j];
		}
		for (int k = 0; k < r; k++) {
			if (temp == paraZK[k].kod) {
				tekst += paraZK[k].znak;
				break;
			}
		}
	}
	cout << tekst;

	cout << endl; system("pause");
	return 0;
}