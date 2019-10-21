//Kamil Cinner IIST 3.2
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

class Logs {																									//klasa za pomoca ktorej realizujemy zapisywanie 
public:																											//naszych postepow w algorytmie do pliku logs.txt
	stringstream log;
	void saveToFile() {
		ofstream file;
		file.open("logs.txt", ios::app);
		if (!file.is_open()) {
			cout << endl << "nope file error" << endl;
			system("pause");
			return;
		}
		file << log.str();
		log.str("");
		file.close();
	}
};
class MemoryControl {																							//klasa zawierajaca metode zwracajaca rozszerzona tablice
public:																											//korzystamy z niej w Gaussie pelnym przy zamianie kolumn
	int* relocateMem(int* tab, int from, int to) {																//z pomoca tej metody rozszerzamy tablice zamian kolumn
		int* newTab = new int[to];																				//dodajac do niej jednoczesnie kolejne dwa numery
		for (int i = 0; i < from; i++) {
			newTab[i] = tab[i];
		} return newTab;
	}
};

class Math {																									//klasa, z ktorej dziedziczymy metode zaokraglajaca dana liczbe
public:																											//do 3 miejsc po przecinku
	double roundMe(double val) {
		double d = val * 1000;
		return round(d) / 1000;
	}
};

class OptEnums {																								//klasy zawierajace typy wyliczeniowe, ktore pomagaja
public:																											//w zrozumieniu kodu
	enum Methods { basic, columnChoice, fullChoice };
	enum UserOpt { testSet, userDefined };
	enum SetType { ok, inf, contr };
};
class BuildTypeEnum {
public: enum BuildType { fully, partly };
};
class ResultEnum {
public: enum Result { _ok, _contr, _inf, _zeroDiv };
};
class DrawOptEnum {
protected: enum DrawOpt { console, logs, consAndLogs };
};

class Exceptions {																								//klasa wyjatkow (wypisuje informacje o bledach)
protected:
	void error() {
		system("cls"); cout << "Blad! Sprobuj ponownie..."; Sleep(1500);
	}
	void settingError(int faultCount) {
		cout << "Podano nieprawidlowa liczbe niewiadomych!"; Sleep(1500); system("cls");
		cout << "Musi byc ona wieksza od 0!"; Sleep(1500); system("cls");
		cout << "Pozostalo (" << 3 - faultCount << ") nieudanych prob do zakonczenia programu."; Sleep(1500);
	}
	void fatalSettingError() {
		cout << "Zbyt wiele razy podano nieprawidlowa liczbe niewiadomych!" << endl;
		cout << "Program zostanie zakonczony..." << endl << endl;
		system("pause");
		exit(0);
	}
	void fatalError() {
		cout << "Cos poszlo okrutnie nie tak :/" << endl;
		cout << "Program musi zostac zakonczony..." << endl;
		cout << "Przepraszam" << endl;
		system("pause");
		exit(0);
	}
};

class Matrix : private Exceptions, private BuildTypeEnum, private DrawOptEnum, private Logs, private Math {		//klasa macierzy rozszerzonej A|b
public:
	int rowCount, colCount;
	double** element;

	void setMatrixMemory() {																					//metoda rezerwujaca pamiec dla macierzy
		element = new double* [rowCount];
		for (int i = 0; i < rowCount; i++)
			element[i] = new double[colCount];
	}
	double* getMatrixElementAddress(int rowNumber, int colNumber) const {										//metoda pobierajaca adres elementu macierzy
		double* pointer = element[rowNumber];
		return &pointer[colNumber];
	}
	void setMatrixElementOnAddress(double* pointerToElement, double value) {									//metoda ustawiajaca wartosc elementu macierzy o podanym adresie
		*pointerToElement = value;
	}
	double getMatrixElementByAddress(double* pointerToElement) const {											//metoda pobierajaca wartosc elementu macierzy o podanym adresie
		return *pointerToElement;
	}
	void setRowColCount() {																						//metoda ustawiajaca liczbe wierszy i kolumn macierzy
		bool proceed;
		int faultCount = 0;
		do {
			proceed = false;
			cout << "Podaj liczbe niewiadomych (bedzie potrzeba tyle samo rownan aby rozwiazac uklad): ";
			cin >> rowCount;
			if (rowCount < 1) {
				proceed = true;
				if (++faultCount == 3) fatalSettingError();
					else settingError(faultCount);
			} else {
				colCount = rowCount + 1;
			}
			system("cls");
		} while (faultCount < 3 && proceed);
	}
	void drawEquations(int toRowNumber, int toColNumber, BuildType buildType) {								//metoda wyswietlajaca rownania (pelne lub wlasnie tworzone - z gwiazdka)
		double* pointer = NULL;
		double elem;
		int magicVar;
		for (int i = 0; i <= toRowNumber; i++) {
			if (i < toRowNumber) magicVar = colCount - 1;
			else magicVar = toColNumber;
			for (int j = 0; j <= magicVar; j++) {
				if (i < toRowNumber || buildType == fully) {
					pointer = getMatrixElementAddress(i, j);
					elem = getMatrixElementByAddress(pointer);
					if (j == 0) cout << elem << "x" << j + 1 << " ";
					else if (j > 0 && j < colCount - 1) {
						if (elem >= 0) cout << "+ ";
						cout << elem << "x" << j + 1 << " ";
					} else cout << "= " << elem << endl;
				} else {
					if (j < toColNumber) {
						pointer = getMatrixElementAddress(i, j);
						elem = getMatrixElementByAddress(pointer);
						if (j == 0) cout << elem << "x" << j + 1 << " ";
						else {
							if (elem >= 0) cout << "+ ";
							cout << elem << "x" << j + 1 << " ";
						}
					} else { //w tej kolumnie jest (*)
						if (j == 0) cout << "(*)x" << j + 1;
						else if (j < colCount - 1) cout << "+ (*)x" << j + 1;
						else cout << "= (*)";
						cout << endl;
					}
				}
			}
		}
		pointer = NULL; delete pointer;
	}
	void drawMatrix(DrawOpt drawOpt) {																			//metoda wyswietlajaca macierz
		switch (drawOpt) {
			case console: cout << "Otrzymana macierz:" << endl; break;
			case logs: /*logs*/ log << "Macierz:" << endl; break;
			case consAndLogs: cout << "Otrzymana macierz:" << endl;
				/*logs*/ log << "Otrzymana macierz:" << endl; break;
			default: fatalError();
		}
		double* pointer = NULL;
		double temp;
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				pointer = getMatrixElementAddress(i, j);
				temp = getMatrixElementByAddress(pointer);
				temp = roundMe(temp); //przy wyswietlaniu zaokraglamy do trzech miejsc po przecinku
				switch (drawOpt) {
					case console: cout << setw(8) << temp; break;
					case logs: /*logs*/ log << setw(8) << temp; break;
					case consAndLogs: cout << setw(8) << temp;
						/*logs*/ log << setw(8) << temp; break;
					default: fatalError();
				}
			} 
			switch (drawOpt) {
				case console: cout << endl << endl; break;
				case logs: /*logs*/ log << endl << endl; break;
				case consAndLogs: cout << endl << endl;
					/*logs*/ log << endl << endl; break;
				default: fatalError();
			}
		}
		pointer = NULL; delete pointer;
		saveToFile();
	}
	void setMatrix() {																						//metoda budujaca macierz (w przypdaku gdy chce ja podac sam uzytkownik)
		double* pointer = NULL;
		double value;
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				pointer = getMatrixElementAddress(i, j);
				drawEquations(i, j, partly);
				cout << endl << "Podaj wartosc (*): ";
				cin >> value;
				setMatrixElementOnAddress(pointer, value);
				system("cls");
			}
		}
		pointer = NULL; delete pointer;
	}
	Matrix() {}
	Matrix(const Matrix& CopiedMatrix) :																		//konstruktor kopiujacy macierzy (raz z niego korzystamy
		rowCount(CopiedMatrix.rowCount), colCount(CopiedMatrix.colCount) {										//ale tylko w celu wyswietlenia - po zamianie kolumn w Gaussie pelnym)
		setMatrixMemory();
		double* p = NULL; double* pC = NULL;
		for (int i = 0; i < rowCount; i++)
			for (int j = 0; j < colCount; j++) {
				p = getMatrixElementAddress(i, j);
				pC = CopiedMatrix.getMatrixElementAddress(i, j);
				setMatrixElementOnAddress(p, CopiedMatrix.getMatrixElementByAddress(pC));
			}
		p = NULL; delete p;
		pC = NULL; delete pC;
	}
	~Matrix() {
		for (int i = 0; i < rowCount; i++) {
			element[i] = NULL; delete element[i];
		}
		element = NULL;  delete element;
	}
};

class set {																										//klasa pojedynczego zestawu testowewgo
	void build(int rows, int cols, double* elems) {
		matrix.rowCount = rows;
		matrix.colCount = cols;
		matrix.setMatrixMemory();
		int testSetElementIndex = 0;
		double* pointer = NULL;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				pointer = matrix.getMatrixElementAddress(i, j);
				matrix.setMatrixElementOnAddress(pointer, elems[testSetElementIndex]);
				testSetElementIndex++;
			}
		pointer = NULL; delete pointer;
	}
public:
	Matrix matrix;
	string name;

	void make(int rowC, int colC, double* elems, string name) {
		build(rowC, colC, elems);
		this->name = name;
	}
};
class TestSets : private OptEnums {																				//klasa przechowujaca wszystkie zestawy testowe
	void buildTestSets() {
		//OZNACZONE
		okCount = 10;
		okSet = new set[okCount];
		//1
		double one[] = {
			0,		1,		2,		3,		8,
			1,		0,		1,		2,		4,
			1,		2,		3,		4,		10,
			0,		1,		3,		2,		7
		}; okSet[0].make(4, 5, one, "Cw1: -1, 0, 1, 2");
		//2
		double two[] = {
			2,		4,		2,		0,		4,
			1,		0,		-1,		1,		2,
			0,		1,		3,		-1,		0,
			2,		1,		2,		1,		6
		}; okSet[1].make(4, 5, two, "Wyklad2: -4, 2, 2, 8");
		//3
		double three[] = {
			6,		-2,		2,		4,		12,
			12,		-8,		6,		10,		34,
			3,		-13,	9,		3,		27,
			-6,		4,		1,		-18,	-38
		}; okSet[2].make(4, 5, three, "Wyklad1: 1, -3, -2, 1");
		//4
		double cw2[] = {
			2,		3,		-4,		9,
			1,		2,		-2,		7,
			4,		-2,		5,		-5
		}; okSet[3].make(3, 4, cw2, "Cw2: -5/13, 5, 17/13 |~| -0.385, 5, 1.308");
		//5
		double cw3a[] = {
			1,		1,		0,		1,		-3,		1,
			2,		0,		-1,		0,		-2,		1,
			1,		-1,		-2,		1,		-2,		1,
			2,		0,		1,		0,		1,		-1,
			-3,		-1,		1,		2,		2,		1
		}; okSet[4].make(5, 6, cw3a, "Cw3a: -1, -7, 5, -3, -4");
		//6
		double wyklad[] = {
			1,		3,		2,		1,
			0,		4,		8,		2,
			5,		6,		4,		1
		}; okSet[5].make(3, 4, wyklad, "Wyklad3: -1/3, 5/12, 1/24 |~| -0.333, 0.417, 0.042");
		//7
		double cwCholeski[] = {
			1,		-2,		3,		1,		1,
			-2,		5,		-8,		1,		-1,
			3,		-8,		17,		-7,		3,
			1,		1,		-7,		18,		-4
		}; okSet[6].make(4, 5, cwCholeski, "CwCholeski: 12.5, 3.5, -1, -1.5");
		//8
		double wykladCholeski[] = {
			4,		2,		-2,		-4,		-12,
			2,		10,		-7,		4,		9,
			-2,		-7,		6,		-5,		-9,
			-4,		4,		-5,		18,		39
		}; okSet[7].make(4, 5, wykladCholeski, "WykladCholeski: -1, 1, 1, 2");
		//9
		double householder[] = {
			1,		2,		-1,		1,
			2,		-1,		1,		0,
			2,		1,		2,		3
		}; okSet[8].make(3, 4, householder, "CwHouseholder: 0, 1, 1");
		//10
		double hsWyklad[] = {
			1,		-1,		1,		1,
			2,		-1,		0,		1,
			2,		0,		1,		3
		}; okSet[9].make(3, 4, hsWyklad, "WykladHouseholder: 1, 1, 1");

		//NIEOZNACZONE
		infCount = 2;
		infSet = new set[infCount];
		//1
		double c[] = {
			1,		3,		2,		0,
			2,		-1,		1,		1,
			3,		2,		3,		1
		}; infSet[0].make(3, 4, c, "Analiza C: uklad nieoznaczony");
		//2
		double d[] = {
			3,		-1,		2,		1,
			1,		2,		-1,		2,
			4,		1,		1,		3
		}; infSet[1].make(3, 4, d, "Analiza D: uklad nieoznaczony");

		//SPRZECZNE
		contrCount = 2;
		contrSet = new set[contrCount];
		//1
		double i[] = {
			1,		2,		3,		1,		1,
			1,		1,		1,		1,		0,
			2,		4,		-1,		2,		2,
			3,		6,		10,		3,		2
		}; contrSet[0].make(4, 5, i, "Analiza I: uklad sprzeczny");
		//2
		double cw3b[] = {
			2,		4,		0,		-6,		1,
			1,		-5,		3,		-1,		-3,
			3,		2,		-1,		2,		9,
			6,		1,		2,		-5,		22
		}; contrSet[1].make(4, 5, cw3b, "Cw3b: uklad sprzeczny");
	}
public:
	set* okSet = NULL;
	set* contrSet = NULL;
	set* infSet = NULL;
	int okCount, contrCount, infCount;

	TestSets() {
		buildTestSets();
	}
	~TestSets() {
		delete[] okSet; delete[] contrSet; delete[] infSet;
	}
};
class Menu : private Exceptions, private OptEnums, private BuildTypeEnum {							//klasa posiadajaca metody odpowiadaace za wyswietlanie interfejsu uzytkownika
	void drawOkSetsMenu() {																			//odpowiada rowniez za zapisanie wyborow uzytkownika i przekazuje je dalej
		TestSets* MyTestSets = new TestSets;
		int choice;
		bool proceed;
		do {
			proceed = false;
			for (int i = 0; i < MyTestSets->okCount; i++) {
				cout << i + 1 << ".ZESTAW '" << MyTestSets->okSet[i].name << "'" << endl;
				MyTestSets->okSet[i].matrix.drawEquations(MyTestSets->okSet[i].matrix.rowCount - 1, MyTestSets->okSet[i].matrix.colCount - 1, fully);
				cout << endl;
			}
			cout << "Wybierz zestaw testowy: ";
			cin >> choice;
			switch (choice) {
				case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:
					if (choice > MyTestSets->okCount) {
						error(); proceed = true;
					} else
						choosenSet = &MyTestSets->okSet[choice - 1];
					break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
		MyTestSets = NULL; delete MyTestSets;
	}
	void drawContrSetsMenu() {
		TestSets* MyTestSets = new TestSets;
		int choice;
		bool proceed;
		do {
			proceed = false;
			for (int i = 0; i < MyTestSets->contrCount; i++) {
				cout << i + 1 << ".Zestaw '" << MyTestSets->contrSet[i].name << "'" << endl;
				MyTestSets->contrSet[i].matrix.drawEquations(MyTestSets->contrSet[i].matrix.rowCount - 1, MyTestSets->contrSet[i].matrix.colCount - 1, fully);
				cout << endl;
			}
			cout << "Wybierz zestaw testowy: ";
			cin >> choice;
			switch (choice) {
				case 1:case 2:case 3:case 4:case 5:
					if (choice > MyTestSets->contrCount) {
						error(); proceed = true;
					}
					else
						choosenSet = &MyTestSets->contrSet[choice - 1];
					break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
		MyTestSets = NULL; delete MyTestSets;
	}
	void drawInfSetsMenu() {
		TestSets* MyTestSets = new TestSets;
		int choice;
		bool proceed;
		do {
			proceed = false;
			for (int i = 0; i < MyTestSets->infCount; i++) {
				cout << i + 1 << ".Zestaw '" << MyTestSets->infSet[i].name << "'" << endl;
				MyTestSets->infSet[i].matrix.drawEquations(MyTestSets->infSet[i].matrix.rowCount - 1, MyTestSets->infSet[i].matrix.colCount - 1, fully);
				cout << endl;
			}
			cout << "Wybierz zestaw testowy:" << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1:case 2:case 3:case 4:case 5:
					if (choice > MyTestSets->infCount) {
						error(); proceed = true;
					}
					else
						choosenSet = &MyTestSets->infSet[choice - 1];
					break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
		MyTestSets = NULL; delete MyTestSets;
	}
public:
	Methods method;
	UserOpt userOpt;
	SetType setType;
	set* choosenSet = new set;

	void drawMainMenu() {
		int choice;
		bool proceed;
		do {
			proceed = false;
			cout << "<<<|ELIMINACJA GAUSS'A|>>>" << endl << endl;
			cout << "Wybierz metode:" << endl << endl;
			cout << "1.Metoda podstawowa" << endl;
			cout << "2.Metoda z wyborem elementu maksymalnego w kolumnie" << endl;
			cout << "3.Metoda z pelnym wyborem elementu maksymalnego" << endl << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1: method = basic; break;
				case 2: method = columnChoice; break;
				case 3: method = fullChoice; break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
	}
	void drawSubMenu() {
		int choice;
		bool proceed;
		do {
			proceed = false;
			cout << "Wybierz jedna z opcji:" << endl << endl;
			cout << "1.Zestaw testowy" << endl;
			cout << "2.Wybor wlasny" << endl << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1: userOpt = testSet; break;
				case 2: userOpt = userDefined; break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
	}
	void drawTestSetsMenu() {
		switch (setType) {
			case ok: drawOkSetsMenu(); break;
			case inf: drawInfSetsMenu(); break;
			case contr: drawContrSetsMenu(); break;
			default: fatalError();
		}
	}
	void drawTestSetsTypesMenu() {
		int choice;
		bool proceed;
		do {
			proceed = false;
			cout << "Wybierz typ zestawu:" << endl << endl;
			cout << "1.Zestawy Oznaczone" << endl;
			cout << "2.Zestawy Nieoznaczone" << endl;
			cout << "3.Zestawy Sprzeczne" << endl << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1: setType = ok; break;
				case 2: setType = inf; break;
				case 3: setType = contr; break;
				default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
	}
	~Menu() {
		choosenSet = NULL; delete choosenSet;
	}
};
class Gauss : private ResultEnum, private Logs, private DrawOptEnum {											//klasa realizujaca nasze algorytmy
	Matrix* MyMatrix = new Matrix;
	bool zeroDividing = false;
	int* MyXesIndex = NULL;
	void replaceTwoRows(int firstRowNumber, int secondRowNumber, int from) {									//metoda przestawiajaca dwa wiersze miedzy soba
		double temp;
		double* firstPointer = NULL;
		double* secondPointer = NULL;
		for (int i = from; i < MyMatrix->colCount; i++) { //w celu optymalizacji pomijamy poprzednio wyeliminowane kolumny aby nie zamieniac zera z zerem
			firstPointer = MyMatrix->getMatrixElementAddress(firstRowNumber, i);
			secondPointer = MyMatrix->getMatrixElementAddress(secondRowNumber, i);
			temp = MyMatrix->getMatrixElementByAddress(firstPointer);

			MyMatrix->setMatrixElementOnAddress(firstPointer, MyMatrix->getMatrixElementByAddress(secondPointer));
			MyMatrix->setMatrixElementOnAddress(secondPointer, temp);
		}
		firstPointer = NULL; delete firstPointer;
		secondPointer = NULL; delete secondPointer;
	}
	void replaceTwoCols(int firstColNumber, int secondColNumber) {												//metoda przestawiajaca dwie kolumny miedzy soba
		double temp;
		double* firstPointer = NULL;
		double* secondPointer = NULL;
		for (int i = 0; i < MyMatrix->rowCount; i++) {
			firstPointer = MyMatrix->getMatrixElementAddress(i, firstColNumber);
			secondPointer = MyMatrix->getMatrixElementAddress(i, secondColNumber);
			temp = MyMatrix->getMatrixElementByAddress(firstPointer);

			MyMatrix->setMatrixElementOnAddress(firstPointer, MyMatrix->getMatrixElementByAddress(secondPointer));
			MyMatrix->setMatrixElementOnAddress(secondPointer, temp);
		}
		firstPointer = NULL; delete firstPointer;
		secondPointer = NULL; delete secondPointer;
	}
	void subRowByMultipliedRow(int multiplierRowNumber, int toSubRowNumber, double value) {				//metoda odejmujaca od jednego wiersza drugi - pomnozony przez dana wartosc
		double temp;																			//w celu optymalizacji pomijamy elmenty pod przekatna,
		double* toSubPointer = NULL;															//ktore wyeliminowalismy w poprzednim kroku
		double* multiplierPointer = NULL;														//bo i tak od zera odejmowalibysmy 0
		for (int i = multiplierRowNumber; i < MyMatrix->colCount; i++) {//<<<<<<<<<<<<<<<<<<<<<<//dlatego tutaj pomijamy odpowiednio pierwsze kolumny,
			toSubPointer = MyMatrix->getMatrixElementAddress(toSubRowNumber, i);				//a i==0 tylko w pierwszym kroku
			multiplierPointer = MyMatrix->getMatrixElementAddress(multiplierRowNumber, i);
			temp = MyMatrix->getMatrixElementByAddress(toSubPointer) - value * MyMatrix->getMatrixElementByAddress(multiplierPointer);

			MyMatrix->setMatrixElementOnAddress(toSubPointer, temp);
		}
		toSubPointer = NULL; delete toSubPointer;
		multiplierPointer = NULL; delete multiplierPointer;
	}
	void eliminate(int i, string GaussType) {																	//metoda odpowiadajaca za wyzerowanie elementow pod przekatna
		/*logs*/ if (i < MyMatrix->rowCount - 1) MyMatrix->drawMatrix(logs);
		/*logs*/ log << "Eliminujemy:" << endl;
		double temp1, temp2, temp;
		double* pointer = NULL;
		for (int j = i + 1; j < MyMatrix->rowCount; j++) {
			pointer = MyMatrix->getMatrixElementAddress(j, i);
			temp1 = MyMatrix->getMatrixElementByAddress(pointer);
			pointer = MyMatrix->getMatrixElementAddress(i, i);
			temp2 = MyMatrix->getMatrixElementByAddress(pointer);
			if (fabs(temp2) <= 1e-12) { //jezeli mamy zero to przerywamy algorytm
				zeroDividing = true;
				/*logs*/ log << ">>>Musialbym podzielic przez 0 - przerywam algorytm" << endl << endl;
				/*logs*/ saveToFile();
				pointer = NULL; delete pointer;
				return;
			}
			temp = temp1 / temp2;
			/*logs*/ log << "Mnoznik (" << j << ") wiersza: " << temp << endl;
			subRowByMultipliedRow(i, j, temp);
		}
		/*logs*/ log << "Dokonalismy " << i + 1 << " krok w eliminacji Gaussa " << GaussType << " :D" << endl;
		/*logs*/ saveToFile();
		pointer = NULL; delete pointer;
	}
public:
	void basicGauss() {																							//nasz Gauss bez wyboru
		/*logs*/ log << "GAUSS PODSTAWOWY" << endl; saveToFile();
		for (int i = 0; i < MyMatrix->rowCount - 1; i++) {
			eliminate(i,"'podstawowej'"); //standardowa eliminacja Gaussa
			if (zeroDividing) { MyMatrix->drawMatrix(console); return; }
		}
		/*logs*/ MyMatrix->drawMatrix(consAndLogs);
	}
	void colChoiceGauss() {																						//nasz Gauss z wyborem w kolumnie
		/*logs*/ log << "GAUSS Z WYBOREM W KOLUMNIE" << endl; saveToFile(); MyMatrix->drawMatrix(logs);
		double temp, temp1;
		int colMaxRowNumber;
		double* pointer = NULL;
		for (int i = 0; i < MyMatrix->rowCount - 1; i++) {
			pointer = MyMatrix->getMatrixElementAddress(i, i);
			temp = MyMatrix->getMatrixElementByAddress(pointer);
			/*logs*/ log << "Szukamy elementu najwiekszego (co do modulu) w kolumnie:" << endl;
			colMaxRowNumber = i;
			for (int j = i + 1; j < MyMatrix->rowCount; j++) { //szukamy elementu najwiekszego (co do modulu) w kolumnie
				/*logs*/ log << "Hello Gauss (petla) | j = " << j << endl;
				pointer = MyMatrix->getMatrixElementAddress(j, i);
				temp1 = MyMatrix->getMatrixElementByAddress(pointer);
				if (fabs(temp1) > fabs(temp)) {
					temp = temp1;
					colMaxRowNumber = j;
				}
			}
			/*logs*/ log << "Mamy najwiekszego :D" << endl;
			if (i != colMaxRowNumber) { //zamieniamy wiersze jesli potrzeba
				/*logs*/ log << "Przestawiamy wiersze (" << i << " z " << colMaxRowNumber << ")" << endl;
				replaceTwoRows(colMaxRowNumber, i, i);
			}
			/*logs*/ saveToFile();
			eliminate(i, "z 'wyborem w kolumnie'"); //standardowa eliminacja Gaussa
			if (zeroDividing) { MyMatrix->drawMatrix(console); return; }
			/*logs*/ if (i < MyMatrix->rowCount - 2) MyMatrix->drawMatrix(logs);
		}
		pointer = NULL; delete pointer;
		/*logs*/ MyMatrix->drawMatrix(consAndLogs);
	}
	void fullChoiceGauss() {																					//nasz Gauss z pelnym wyborem
		/*logs*/ log << "GAUSS Z WYBOREM PELNYM" << endl; saveToFile(); MyMatrix->drawMatrix(logs);
		MemoryControl MemC;
		int* colsSwapped = NULL;
		double temp, temp1;
		int colMaxRowNumber, rowMaxColNumber, t, colsSwpCount = 0;
		double* pointer = NULL;
		for (int i = 0; i < MyMatrix->rowCount - 1; i++) {
			pointer = MyMatrix->getMatrixElementAddress(i, i);
			temp = MyMatrix->getMatrixElementByAddress(pointer);
			/*logs*/ log << "Szukamy elementu najwiekszego (co do modulu):" << endl;
			colMaxRowNumber = rowMaxColNumber = i;
			for (int j = i; j < MyMatrix->rowCount; j++) { //szukamy elementu najwiekszego (co do modulu)
				for (int k = i; k < MyMatrix->rowCount; k++) {
					/*logs*/ log << "Hello Gauss (petla) | j = " << j << " | k = " << k << endl;
					pointer = MyMatrix->getMatrixElementAddress(j, k);
					temp1 = MyMatrix->getMatrixElementByAddress(pointer);
					if (fabs(temp1) > fabs(temp)) {
						temp = temp1;
						colMaxRowNumber = j;
						rowMaxColNumber = k;
					}
				}
			}
			/*logs*/ log << "Mamy najwiekszego :D" << endl;
			if (i != colMaxRowNumber) { //zamieniamy wiersze jesli potrzeba
				/*logs*/ log << "Przestawiamy wiersze (" << i << " z " << colMaxRowNumber << ")" << endl;
				replaceTwoRows(colMaxRowNumber, i, i); 
			}
			if (i != rowMaxColNumber) { //zamieniamy kolumny jesli potrzeba i zapisujemy ich numery (numery zapisujemy tylko w celu wyswietlenia macierzy z przywroconym
				/*logs*/ log << "Przestawiamy kolumny (" << i << " z " << rowMaxColNumber << ")" << endl;								//pierwotnym ustawieniem kolumn) :)
				replaceTwoCols(i, rowMaxColNumber);
				colsSwapped = MemC.relocateMem(colsSwapped, colsSwpCount, colsSwpCount + 2);
				colsSwapped[colsSwpCount] = rowMaxColNumber;
				colsSwapped[colsSwpCount + 1] = i;
				colsSwpCount += 2;

				t = MyXesIndex[i]; //przestawiamy indeksy Xow aby odpowiadaly przestawieniom kolumn
				MyXesIndex[i] = MyXesIndex[rowMaxColNumber];
				MyXesIndex[rowMaxColNumber] = t;
			}
			/*logs*/ saveToFile();
			eliminate(i, "z 'wyborem pelnym'"); //standardowa eliminacja Gaussa
			if (zeroDividing) { MyMatrix->drawMatrix(console); return; }
			/*logs*/ if (i < MyMatrix->rowCount - 2 || colsSwpCount > 0) MyMatrix->drawMatrix(logs);
		}
		pointer = NULL; delete pointer;
		/*logsStart*/
		if (colsSwpCount > 0) {
			log << "Kolejno zamieniane kolumny:" << endl; cout << "Kolejno zamieniane kolumny:" << endl;
			for (int i = 0; i < colsSwpCount; i++) { log << colsSwapped[i] << "\t"; cout << colsSwapped[i] << "\t"; }
			Matrix CopiedMatrix(*MyMatrix); //zobaczymy jak wygladalaby nasza macierz po przywroceniu pierwotnego ustawienia kolumn :)
			Gauss GGC(CopiedMatrix);		//oryginalu nie zmieniamy w celu zachowania optymalnego algorytmu liczenia niewiadomych
			for (int i = colsSwpCount - 1; i >= 1; i -= 2) //tutaj przywracamy pierwotne ustawienie kolumn (od konca)
				GGC.replaceTwoCols(colsSwapped[i], colsSwapped[i - 1]);
			log << endl << endl << "Tak wygladalaby nasza macierz po przywroceniu pierwotnego ustawienia kolumn:" << endl << endl;
			cout << endl << endl << "Tak wygladalaby nasza macierz po przywroceniu pierwotnego ustawienia kolumn:" << endl << endl;
			saveToFile();
			GGC.MyMatrix->drawMatrix(consAndLogs);
		} else MyMatrix->drawMatrix(consAndLogs);
		/*logsEnd*/
	}
	Result GaussResult() {																						//metoda bada ostatni wiersz przeksztalconej macierzy
		if (zeroDividing) return _zeroDiv;																		//i zwraca rezultat naszych dzialan
		double* pointer = NULL;
		double temp;
		bool zeroRow = true;
		bool zeroFree = true;
		for (int i = 0; i < MyMatrix->rowCount; i++) {
			pointer = MyMatrix->getMatrixElementAddress(MyMatrix->rowCount - 1, i);
			temp = MyMatrix->getMatrixElementByAddress(pointer);
			if (fabs(temp) > 1e-12) zeroRow = false;
		}
		pointer = MyMatrix->getMatrixElementAddress(MyMatrix->rowCount - 1, MyMatrix->colCount - 1);
		temp = MyMatrix->getMatrixElementByAddress(pointer);
		if (fabs(temp) > 1e-12) zeroFree = false;
		pointer = NULL; delete pointer;
		if (zeroRow) {
			if (zeroFree) return _inf;
			else return _contr;
		}
		else return _ok;
	}

	double* calcVars() {																						//metoda oblicza nasze niewiadome
		double* p = NULL;
		double rowValue, xValue, temp;
		double* MyXes = new double[MyMatrix->rowCount];
		for (int i = MyMatrix->rowCount - 1; i >= 0; i--) {
			p = MyMatrix->getMatrixElementAddress(i, MyMatrix->colCount - 1);
			rowValue = MyMatrix->getMatrixElementByAddress(p);
			p = MyMatrix->getMatrixElementAddress(i, i);
			xValue = MyMatrix->getMatrixElementByAddress(p);
			for (int j = MyMatrix->rowCount - 1; j > i; j--) {
				p = MyMatrix->getMatrixElementAddress(i, j);
				temp = MyMatrix->getMatrixElementByAddress(p);
				temp *= MyXes[MyXesIndex[j]];
				rowValue -= temp;
			}
			MyXes[MyXesIndex[i]] = rowValue / xValue;
		}
		p = NULL; delete p;
		return MyXes;
	}
	Gauss(Matrix& UserMatrix) {
		for (int i = 0; i < 32; i++) log << "\\/";
		log << endl << "-----------------------Zebrane informacje-----------------------" << endl;
		for (int i = 0; i < 32; i++) log << "\\/"; log << endl;
		MyMatrix = &UserMatrix;
		MyXesIndex = new int[MyMatrix->rowCount];
		for (int i = 0; i < MyMatrix->rowCount; i++) MyXesIndex[i] = i;
	}
	~Gauss() {
		MyMatrix = NULL; delete MyMatrix; delete[] MyXesIndex;
	}
};
class UserInteraction : private OptEnums, private Exceptions, private ResultEnum, private Logs, private Math {	//klasa odpowiadajaca za interakcje z uzytkownikiem
	Menu* UserMenu = new Menu;																					//pobiera i analizuje wybory uzytkownika
	Matrix* UserMatrix = new Matrix;																			//w celu wykonania zadanego polecenia
public:
	void startUI() {
		UserMenu->drawMainMenu(); //pobieramy wybory uzytkownika
		UserMenu->drawSubMenu();
		switch (UserMenu->userOpt) { //ladujemy do klasy macierz, na ktorej bedziemy pracowac
			case testSet: {
				UserMenu->drawTestSetsTypesMenu();
				UserMenu->drawTestSetsMenu();
				UserMatrix = &UserMenu->choosenSet->matrix;
				cout << "Oczekiwany wynik>> " << UserMenu->choosenSet->name << endl << endl;
				log << "Oczekiwany wynik>> " << UserMenu->choosenSet->name << endl << endl;
				break;
			}
			case userDefined: {
				UserMatrix->setRowColCount();
				UserMatrix->setMatrixMemory();
				UserMatrix->setMatrix();
				break;
			}
			default: fatalError();
		}
		Gauss GG(*UserMatrix); //przesylamy nasza macierz do obiektu klasy Gauss, ktory wykona na niej algorytm
		switch (UserMenu->method) {
			case basic: GG.basicGauss(); break;
			case columnChoice: GG.colChoiceGauss(); break;
			case fullChoice: GG.fullChoiceGauss(); break;
			default: fatalError();
		}
		switch (GG.GaussResult()) { //odczytujemy rezultat obliczen
			case _ok: {
				double temp;
				double* calculatedXes = GG.calcVars();
				cout << "Obliczone niewiadome:" << endl;
				/*logs*/ log << "Obliczone niewiadome:" << endl;
				for (int i = 0; i < UserMatrix->rowCount; i++) {
					temp = roundMe(calculatedXes[i]); //przy wyswietlaniu zaokraglamy do trzech miejsc po przecinku
					cout << "x" << i << " = " << temp << endl;
					/*logs*/ log << "x" << i << " = " << temp << endl;
				} /*logs*/ log << endl;
				delete[] calculatedXes;
				break;
			}
			case _inf: cout << "Podany uklad ma nieskonczenie wiele rozwiazan." << endl; /*logs*/ log << ">>>UKLAD NIEOZNACZONY" << endl << endl; break;
			case _contr: cout << "Podany uklad jest sprzeczny." << endl; /*logs*/ log << ">>>UKLAD SPRZECZNY" << endl << endl; break;
			case _zeroDiv: cout << "Podanego ukladu nie jestem w stanie rozwiazac (problem dzielenia przez 0)." << endl; break;
			default: fatalError();
		}
		cout << endl << "Zajrzyj do pliku 'logs.txt' po wiecej informacji :)" << endl << endl;
	}
	void runProgram() {
		int choice;
		bool run = true;
		bool iSawU = false;
		do {
			if (iSawU) {
				cout << "Milo Cie znowu widziec! :D" << endl << endl;
				cout << "1 - Kontynuuj korzystanie z programu" << endl;
			} else {
				cout << "Witaj w programie!" << endl << endl;
				cout << "1 - Przejdz do programu" << endl;
			}
			cout << "2 - Zakoncz program" << endl << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1: system("cls"); startUI(); saveToFile(); iSawU = true; system("pause"); break;
				case 2: run = false; break;
				default: error();
			}
			system("cls");
		} while (run);
	}
	UserInteraction() {
		runProgram();
	}
	~UserInteraction() {
		UserMenu = NULL; delete UserMenu; UserMatrix = NULL; delete UserMatrix;
	}
};
int main() {
	UserInteraction UI; return 0;
}