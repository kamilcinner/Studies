//Kamil Cinner IIST 3.2
#include <iostream>
#include <Windows.h>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

class Math {
public:
	double roundMe(double val) {
		double d = val * 1000;
		return round(d) / 1000;
	}
};

class Exceptions {
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

class BuildTypeEnum {
public: enum BuildType { fully, partly };
};
class OptEnums {
public: enum UserOpt { testSet, userDefined };
};
class CalcFromEnum {
protected: enum CalcFrom { top, bottom };
};

class Matrix : private Math {
public:
	int rowCount, colCount;
	double** element;

	void setMatrixMemory() {
		element = new double*[rowCount];
		for (int i = 0; i < rowCount; i++)
			element[i] = new double[colCount];
	}
	double* getMatrixElementAddress(int rowNumber, int colNumber) const {
		double* p = element[rowNumber];
		return &p[colNumber];
	}
	void setMatrixElementOnAddress(double* pToElement, double value) {
		*pToElement = value;
	}
	double getMatrixElementByAddress(double* pToElement) const {
		return *pToElement;
	}
	void drawMatrix(string name) {
		cout << "Macierz " << name << ":" << endl;
		double* p = NULL;
		double temp;
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				p = getMatrixElementAddress(i, j);
				temp = getMatrixElementByAddress(p);
				temp = roundMe(temp); //zaokraglamy do 3 miejsc po przecinku przy wyswietlaniu
				cout << setw(8) << temp;
			} cout << endl << endl;
		}
		p = NULL; delete p;
	}
	~Matrix() {
		for (int i = 0; i < rowCount; i++) {
			element[i] = NULL; delete element[i];
		}
		element = NULL;  delete element;
	}
};

class set {
	void build(int rows, int cols, double* elems) {
		matrix.rowCount = rows;
		matrix.colCount = cols;
		matrix.setMatrixMemory();
		int testSetElementIndex = 0;
		double* p = NULL;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				p = matrix.getMatrixElementAddress(i, j);
				matrix.setMatrixElementOnAddress(p, elems[testSetElementIndex]);
				testSetElementIndex++;
			}
		p = NULL; delete p;
	}
public:
	Matrix matrix;
	string name;

	void make(int rowC, int colC, double* elems, string name) {
		build(rowC, colC, elems);
		this->name = name;
	}
};

class TestSets {
	void buildTestSets() {
		count = 2;
		MySet = new set[count];
		//1
		double cw[] = {
			1,		-2,		3,		1,		1,
			-2,		5,		-8,		1,		-1,
			3,		-8,		17,		-7,		3,
			1,		1,		-7,		18,		-4
		}; MySet[0].make(4, 5, cw, "CwCholeski: 12.5, 3.5, -1, -1.5");
		//2
		double wykladCholeski[] = {
			4,		2,		-2,		-4,		-12,
			2,		10,		-7,		4,		9,
			-2,		-7,		6,		-5,		-9,
			-4,		4,		-5,		18,		39
		}; MySet[1].make(4, 5, wykladCholeski, "WykladCholeski: -1, 1, 1, 2");
	}
public:
	int count;
	set* MySet = NULL;
	TestSets() {
		buildTestSets();
	}
	~TestSets() {
		delete[] MySet;
	}
};

class MatrixSetting : protected Exceptions, protected BuildTypeEnum {
	void setRowColCount(Matrix& MyMatrix) {
		int rowCount;
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
			}
			else {
				MyMatrix.rowCount = rowCount;
				MyMatrix.colCount = rowCount + 1;
				MyMatrix.setMatrixMemory();
			}
			system("cls");
		} while (faultCount < 3 && proceed);
	}
protected:
	void drawEquations(Matrix& MyMatrix, int toRowNumber, int toColNumber, BuildType buildType) {
		double* p = NULL;
		double elem;
		int magicVar;
		for (int i = 0; i <= toRowNumber; i++) {
			if (i < toRowNumber) magicVar = MyMatrix.colCount - 1;
			else magicVar = toColNumber;
			for (int j = 0; j <= magicVar; j++) {
				if (i < toRowNumber || buildType == fully) {
					p = MyMatrix.getMatrixElementAddress(i, j);
					elem = MyMatrix.getMatrixElementByAddress(p);
					if (j == 0) cout << elem << "x" << j + 1 << " ";
					else if (j > 0 && j < MyMatrix.colCount - 1) {
						if (elem >= 0) cout << "+ ";
						cout << elem << "x" << j + 1 << " ";
					}
					else cout << "= " << elem << endl;
				}
				else {
					if (j < toColNumber) {
						p = MyMatrix.getMatrixElementAddress(i, j);
						elem = MyMatrix.getMatrixElementByAddress(p);
						if (j == 0) cout << elem << "x" << j + 1 << " ";
						else {
							if (elem >= 0) cout << "+ ";
							cout << elem << "x" << j + 1 << " ";
						}
					}
					else {
						if (j == 0) cout << "(*)x" << j + 1;
						else if (j < MyMatrix.colCount - 1) cout << "+ (*)x" << j + 1;
						else cout << "= (*)";
						cout << endl;
					}
				}
			}
		}
		p = NULL; delete p;
	}
	void setMatrix(Matrix& MyMatrix) {
		setRowColCount(MyMatrix);
		MyMatrix.setMatrixMemory();
		double* p = NULL;
		double value;
		for (int i = 0; i < MyMatrix.rowCount; i++) {
			for (int j = 0; j < MyMatrix.colCount; j++) {
				p = MyMatrix.getMatrixElementAddress(i, j);
				drawEquations(MyMatrix, i, j, partly);
				cout << endl << "Podaj wartosc (*): ";
				cin >> value;
				MyMatrix.setMatrixElementOnAddress(p, value);
				system("cls");
			}
		}
		p = NULL; delete p;
	}
	void setMatrix_A_b(Matrix& MyMatrix, Matrix& A, Matrix& b) {
		double* p = NULL;
		double temp;
		for (int i = 0; i < MyMatrix.rowCount; i++) {
			for (int j = 0; j < MyMatrix.colCount; j++) {
				p = MyMatrix.getMatrixElementAddress(i, j);
				temp = MyMatrix.getMatrixElementByAddress(p);
				if (j < A.colCount) {
					p = A.getMatrixElementAddress(i, j);
					A.setMatrixElementOnAddress(p, temp);
				}
				else {
					p = b.getMatrixElementAddress(i, 0);
					b.setMatrixElementOnAddress(p, temp);
				}
			}
		}
		p = NULL; delete p;
		A.drawMatrix("A");
		b.drawMatrix("b");
	}
};
class Choleski : private MatrixSetting, private CalcFromEnum, private Math {
	Matrix* A = new Matrix;
	Matrix* b = new Matrix;
	Matrix* L = new Matrix;
	Matrix* y = new Matrix;
	Matrix* x = new Matrix;
	Matrix* MyMatrix = new Matrix;

	void setMemoryForAll() {
		A->rowCount = A->colCount = L->rowCount = L->colCount = y->rowCount = b->rowCount = x->rowCount = MyMatrix->rowCount;
		y->colCount = b->colCount = x->colCount = 1;
		A->setMatrixMemory();
		b->setMatrixMemory();
		L->setMatrixMemory();
		y->setMatrixMemory();
		x->setMatrixMemory();
	}
	bool checkSymmetry() {
		double* p = NULL;
		double temp1, temp2;
		bool isASymmetry = true;
		for (int i = 0; i < A->rowCount - 1; i++)
			for (int j = i + 1; j < A->rowCount; j++) {
				p = A->getMatrixElementAddress(j, i);
				temp1 = A->getMatrixElementByAddress(p);
				p = A->getMatrixElementAddress(i, j);
				temp2 = A->getMatrixElementByAddress(p);
				if (temp1 != temp2) {
					cout << "Macierz nie jest symetryczna - przerywam algorytm." << endl << endl;
					p = NULL; delete p;
					return false;
				}
			} 
		p = NULL; delete p;
		return true;
	}
	bool buildL() {
		double s, temp;
		double* p = NULL;
		for (int k = 0; k < A->rowCount; k++)
			for (int i = k; i < A->rowCount; i++) {
				s = 0;
				for (int j = 0; j < k; j++) {
					p = L->getMatrixElementAddress(i, j);
					temp = L->getMatrixElementByAddress(p);
					p = L->getMatrixElementAddress(k, j);
					temp *= L->getMatrixElementByAddress(p);
					s += temp;
				}
				p = A->getMatrixElementAddress(i, k);
				temp = A->getMatrixElementByAddress(p);
				p = L->getMatrixElementAddress(i, k);
				L->setMatrixElementOnAddress(p, temp - s);
				if (k == i) {
					temp = L->getMatrixElementByAddress(p);
					if (temp <= 1e-12) {
						cout << "Macierz nie jest okreslona dodatnio - przerywam algorytm." << endl << endl;
						p = NULL; delete p;
						return false;
					} else
						L->setMatrixElementOnAddress(p, sqrt(temp));
				} else {
					p = L->getMatrixElementAddress(k, k);
					temp = L->getMatrixElementByAddress(p);
					p = L->getMatrixElementAddress(i, k);
					temp = L->getMatrixElementByAddress(p) / temp;
					L->setMatrixElementOnAddress(p, temp);
					p = L->getMatrixElementAddress(k, i);
					L->setMatrixElementOnAddress(p, temp);
				}
			}
		p = NULL; delete p;
		L->drawMatrix("L");
		return true;
	}
	double* calcVars(CalcFrom calcFrom) {
		double* p = NULL;
		double rowValue, xValue, temp;
		int* knownXes = NULL;
		double* MyXes = new double[L->rowCount];
		switch (calcFrom) {
		case top: //trojkatna dolna
			for (int i = 0; i < L->rowCount; i++) {
				p = b->getMatrixElementAddress(i, 0);
				rowValue = b->getMatrixElementByAddress(p);
				p = L->getMatrixElementAddress(i, i);
				xValue = L->getMatrixElementByAddress(p);
				for (int j = 0; j < i; j++) {
					p = L->getMatrixElementAddress(i, j);
					temp = L->getMatrixElementByAddress(p);
					temp *= MyXes[j];
					rowValue -= temp;
				}
				MyXes[i] = rowValue / xValue;
			}
			break;
		case bottom: //trojkatna gorna
			for (int i = L->rowCount - 1; i >= 0; i--) {
				p = y->getMatrixElementAddress(i, 0);
				rowValue = y->getMatrixElementByAddress(p);
				p = L->getMatrixElementAddress(i, i);
				xValue = L->getMatrixElementByAddress(p);
				for (int j = L->rowCount - 1; j > i; j--) {
					p = L->getMatrixElementAddress(i, j);
					temp = L->getMatrixElementByAddress(p);
					temp *= MyXes[j];
					rowValue -= temp;
				}
				MyXes[i] = rowValue / xValue;
			}
			break;
		default: fatalError();
		}
		p = NULL; delete p; delete[] knownXes;
		return MyXes;
	}
	void buildY() {
		double* Y = calcVars(top);
		double* p = NULL;
		for (int i = 0; i < y->rowCount; i++) {
			p = y->getMatrixElementAddress(i, 0);
			y->setMatrixElementOnAddress(p, Y[i]);
		}
		p = NULL; delete p; delete[] Y;
		y->drawMatrix("y");
	}
	void buildX() {
		double* X = calcVars(bottom);
		double* p = NULL;
		for (int i = 0; i < x->rowCount; i++) {
			p = x->getMatrixElementAddress(i, 0);
			x->setMatrixElementOnAddress(p, X[i]);
		}
		p = NULL; delete p; delete[] X;
		x->drawMatrix("x");
	}
	void showResult() {
		double* p = NULL;
		double temp;
		cout << "Obliczone niewiadome:" << endl;
		for (int i = 0; i < x->rowCount; i++) {
			p = x->getMatrixElementAddress(i, 0);
			temp = x->getMatrixElementByAddress(p);
			temp = roundMe(temp); //zaokraglamy do 3 miejsc po przecinku przy wyswietlaniu
			cout << "X" << i + 1 << " = " << temp << endl;
		} cout << endl;
	}
public:
	void doCholeski() {
		setMatrix_A_b(*MyMatrix, *A, *b);
		if (!checkSymmetry() || !buildL()) return;
		buildY();
		buildX();
		showResult();
	}
	Choleski(Matrix& MyMatrix) {
		this->MyMatrix = &MyMatrix;
		setMemoryForAll();
	}
	~Choleski() {
		A = NULL; delete A;
		b = NULL; delete b;
		L = NULL; delete L;
		y = NULL; delete y;
		x = NULL; delete x;
		MyMatrix = NULL; delete MyMatrix;
	}
};
class Menu : private MatrixSetting, private OptEnums {
	void drawSetsMenu() {
		TestSets* MyTestSets = new TestSets;
		int choice;
		bool proceed;
		do {
			proceed = false;
			for (int i = 0; i < MyTestSets->count; i++) {
				cout << i + 1 << ".ZESTAW '" << MyTestSets->MySet[i].name << "'" << endl;
				drawEquations(MyTestSets->MySet[i].matrix, MyTestSets->MySet[i].matrix.rowCount - 1, MyTestSets->MySet[i].matrix.colCount - 1, fully);
				cout << endl;
			}
			cout << "Wybierz zestaw testowy: ";
			cin >> choice;
			switch (choice) {
			case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:
				if (choice > MyTestSets->count) {
					error(); proceed = true;
				}
				else
					choosenSet = &MyTestSets->MySet[choice - 1];
				break;
			default: error(); proceed = true;
			}
			system("cls");
		} while (proceed);
		MyTestSets = NULL; delete MyTestSets;
	}
public:
	UserOpt userOpt;
	set* choosenSet = new set;

	void drawMainMenu() {
		int choice;
		bool proceed;
		do {
			proceed = false;
			cout << "<<<|ROZKLAD CHOLESKIEGO|>>>" << endl << endl;
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
	void drawTestSetsMenu() { drawSetsMenu(); }
	~Menu() {
		choosenSet = NULL; delete choosenSet;
	}
};
class UserInteraction : private OptEnums, private MatrixSetting {
	Menu* UserMenu = new Menu;
	Matrix* UserMatrix = new Matrix;
	void startUI() {
		UserMenu->drawMainMenu();
		switch (UserMenu->userOpt) {
			case testSet:
				UserMenu->drawTestSetsMenu();
				UserMatrix = &UserMenu->choosenSet->matrix;
				cout << "Oczekiwany wynik>> " << UserMenu->choosenSet->name << endl << endl;
				break;
			case userDefined: setMatrix(*UserMatrix); break;
			default: fatalError();
		}
		Choleski Ch(*UserMatrix);
		Ch.doCholeski();
	}
	void runProgram() {
		int choice;
		bool run = true;
		bool iSawU = false;
		do {
			if (iSawU) {
				cout << "Milo Cie znowu widziec! :D" << endl << endl;
				cout << "1 - Kontynuuj korzystanie z programu" << endl;
			}
			else {
				cout << "Witaj w programie!" << endl << endl;
				cout << "1 - Przejdz do programu" << endl;
			}
			cout << "2 - Zakoncz program" << endl << endl;
			cout << "<< ";
			cin >> choice;
			switch (choice) {
				case 1: system("cls"); startUI(); iSawU = true; system("pause"); break;
				case 2: run = false; break;
				default: error();
			}
			system("cls");
		} while (run);
	}
public:
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