#include <iostream>
#include <string>
#include <windows.h>

#define ILE_PSOW 2
#define ILE_KOTOW 2

using namespace std;

class State {
public:
	string imie;
	int humor, glod, zmeczenie;

	State(string imie = "NoName", int humor = 0, int glod = 2, int zmeczenie = 1) {
		this->imie = imie;
		this->humor = humor;
		this->glod = glod;
		this->zmeczenie = zmeczenie;
	}
};

State* Kot = new State[ILE_KOTOW];
State* Pies = new State[ILE_PSOW];

void err() {
	system("cls");
	cout << "Blad! Sprobuj ponownie...";
	Sleep(700);
	system("cls");
}

namespace pies {
	int wybierz(string info) {
		int ktory;
		int proceed;
		do {
			proceed = true;
			cout << "Wybierz pieska" << info << " (0 - " << ILE_PSOW - 1 << "): "; cin >> ktory;
			if (ktory < 0 || ktory >= ILE_PSOW) {
				proceed = false;
				err();
			}
		} while (!proceed);
		return ktory;
	}
	void odpoczywaj(int* czas, State* Pies) {
		Pies[wybierz("")].zmeczenie -= *czas;
	}
	void jedz(int* ilosc, State* Pies) {
		Pies[wybierz("")].glod -= *ilosc;
	}
	void baw_sie(int* czas, State* Pies, State* Kot);
}
namespace kot {
	int wybierz(string info) {
		int ktory;
		int proceed;
		do {
			proceed = true;
			cout << "Wybierz kotka" << info << " (0 - " << ILE_KOTOW - 1 << "): "; cin >> ktory;
			if (ktory < 0 || ktory >= ILE_KOTOW) {
				proceed = false;
				err();
			}
		} while (!proceed);
		return ktory;
	}
	void odpoczywaj(int* czas, State* Kot) {
		Kot[wybierz("")].zmeczenie -= *czas;
	}
	void jedz(int* ilosc, State* Kot) {
		Kot[wybierz("")].glod -= *ilosc;
	}
	void baw_sie(int* czas, State* Kot, State* Pies);
}

void pies::baw_sie(int* czas, State* Pies, State* Kot) {
	int ktory_piesek = pies::wybierz(" ktory ma sie bawic");
	int ktory_kotek = kot::wybierz(" ktorego chcesz denerwowac");
	Pies[ktory_piesek].humor += *czas;
	Pies[ktory_piesek].glod += *czas;
	Pies[ktory_piesek].zmeczenie += *czas;
	Kot[ktory_kotek].humor -= *czas;
}
void kot::baw_sie(int* czas, State* Kot, State* Pies) {
	int ktory_kotek = kot::wybierz(" ktory ma sie bawic");
	int ktory_piesek = pies::wybierz(" ktorego chcesz denerwowac");
	Kot[ktory_kotek].humor += *czas;
	Kot[ktory_kotek].glod += *czas;
	Kot[ktory_kotek].zmeczenie += *czas;
	Pies[ktory_piesek].humor -= *czas;
}

int main() {
	int* choice = new int;
	int* ile = new int;
	bool* proceed = new bool;

	do {
		for (int i = 0; i < ILE_KOTOW; i++) {
			cout << Kot[i].imie << endl;
			cout << "Humor: " << Kot[i].humor << endl;
			cout << "Glod: " << Kot[i].glod << endl;
			cout << "Zmeczenie: " << Kot[i].zmeczenie << endl;
			cout << endl;
		}
		for (int i = 0; i < ILE_PSOW; i++) {
			cout << Pies[i].imie << endl;
			cout << "Humor: " << Pies[i].humor << endl;
			cout << "Glod: " << Pies[i].glod << endl;
			cout << "Zmeczenie: " << Pies[i].zmeczenie << endl;
			cout << endl;
		}

		cout << "1.Kot - odpoczywaj" << endl;
		cout << "2.Kot - baw sie" << endl;
		cout << "3.Kot - jedz" << endl << endl;

		cout << "4.Pies - odpoczywaj" << endl;
		cout << "5.Pies - baw sie" << endl;
		cout << "6.Pies - jedz" << endl << endl;

		cout << "7.Zakoncz program" << endl << endl;

		cout << "Dzialanie: "; cin >> *choice;
		system("cls");

		switch (*choice) {
		case 1: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			kot::odpoczywaj(ile, Kot);
			break;
		}
		case 2: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			kot::baw_sie(ile, Kot, Pies);
			break;
		}
		case 3: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			kot::jedz(ile, Kot);
			break;
		}
		case 4: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			pies::odpoczywaj(ile, Pies);
			break;
		}
		case 5: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			pies::baw_sie(ile, Pies, Kot);
			break;
		}
		case 6: {
			cout << "Podaj czas/ilosc (liczba calkowita): "; cin >> *ile;
			pies::jedz(ile, Pies);
			break;
		}
		case 7: {
			*proceed = false;
			break;
		}
		default: {
			system("cls");
			cout << "blad";
			Sleep(1000);
		}
		}//koniec switch
		system("cls");
	} while (*proceed);

	delete[] Kot;
	delete[] Pies;
	delete ile;
	delete proceed;
	delete choice;

	return 0;
}