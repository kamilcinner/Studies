//Kamil Cinner IIST 3.2
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
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
		cout << "Musi byc ona wieksza od 1!"; Sleep(1500); system("cls");
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

class OptEnums {
public:
	enum UserOpt { testSet, userDefined };
	enum SetType { ok, inf, contr };
};
class BuildTypeEnum {
public: enum BuildType { fully, partly };
};
class ResultEnum {
public: enum Result { _ok, _contr, _inf, _zeroDiv };
};

class Matrix : private Math {
public:
	int rowCount, colCount;
	double** element;

	void setMatrixMemory() {
		element = new double* [rowCount];
		for (int i = 0; i < rowCount; i++)
			element[i] = new double[colCount];
	}
	double* getMatrixElementAddress(int rowNumber, int colNumber) const {
		double* pointer = element[rowNumber];
		return &pointer[colNumber];
	}
	void setMatrixElementOnAddress(double* pointerToElement, double value) {
		*pointerToElement = value;
	}
	double getMatrixElementByAddress(double* pointerToElement) const {
		return *pointerToElement;
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
	Matrix() {}
	Matrix(const Matrix& CopiedMatrix) :
		rowCount(CopiedMatrix.rowCount), colCount(CopiedMatrix.colCount) {
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

class MatrixSetting : protected Exceptions, protected BuildTypeEnum {
	void setRowColCount(Matrix& MyMatrix) {
		int rowCount;
		bool proceed;
		int faultCount = 0;
		do {
			proceed = false;
			cout << "Podaj liczbe niewiadomych (bedzie potrzeba tyle samo rownan aby rozwiazac uklad): ";
			cin >> rowCount;
			if (rowCount < 2) {
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
		} p = NULL; delete p;
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
		} p = NULL; delete p;
	}
	void setMatrix_A_b(Matrix& Ab, Matrix& A, Matrix& b) {
		A.rowCount = A.colCount = b.rowCount = Ab.rowCount;
		b.colCount = 1;
		A.setMatrixMemory();
		b.setMatrixMemory();
		double* p = NULL;
		double temp;
		for (int i = 0; i < Ab.rowCount; i++) {
			for (int j = 0; j < Ab.colCount; j++) {
				p = Ab.getMatrixElementAddress(i, j);
				temp = Ab.getMatrixElementByAddress(p);
				if (j < A.colCount) {
					p = A.getMatrixElementAddress(i, j);
					A.setMatrixElementOnAddress(p, temp);
				}
				else {
					p = b.getMatrixElementAddress(i, 0);
					b.setMatrixElementOnAddress(p, temp);
				}
			}
		} p = NULL; delete p;
	}
};

class set {
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
class TestSets : private OptEnums {
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
class Householder : private MatrixSetting, private ResultEnum {
	Matrix* Ab = new Matrix;
	Matrix* A = new Matrix;
	Matrix* b = new Matrix;
	Matrix* I = new Matrix;
	Matrix* a = new Matrix;
	Matrix* u = new Matrix;
	Matrix* uT = new Matrix;
	double aNorm, a1, B, eiFi;
	bool zeroDividing = false;

	void createI(const int& n) { // tworzy macierz jednostkowa stopnia 'n'
		Matrix* MyMatrix = new Matrix;
		double* p = NULL;
		MyMatrix->rowCount = n;
		MyMatrix->colCount = n;
		MyMatrix->setMatrixMemory();
		for (int i = 0; i < n; i++) {
			p = MyMatrix->getMatrixElementAddress(i, i);
			MyMatrix->setMatrixElementOnAddress(p, 1);
			for (int j = i + 1; j < n; j++) {
				p = MyMatrix->getMatrixElementAddress(i, j);
				MyMatrix->setMatrixElementOnAddress(p, 0);
				p = MyMatrix->getMatrixElementAddress(j, i);
				MyMatrix->setMatrixElementOnAddress(p, 0);
			}
		} p = NULL; delete p;
		this->I = MyMatrix;
		MyMatrix = NULL; delete MyMatrix;
	}
	void createA(const Matrix& Ak, const int& step) { // tworzy macierz 'a' || 'Ak' <- macierz 'A' po k-tym kroku
		Matrix* MyMatrix = new Matrix;
		double* p = NULL;
		double temp;
		MyMatrix->rowCount = Ak.rowCount - step;
		MyMatrix->colCount = 1;
		MyMatrix->setMatrixMemory();
		int j = 0;
		for (int i = step; i < Ak.rowCount; i++) {
			p = Ak.getMatrixElementAddress(i, step);
			temp = Ak.getMatrixElementByAddress(p);
			p = MyMatrix->getMatrixElementAddress(j, 0);
			MyMatrix->setMatrixElementOnAddress(p, temp);
			j++;
		} p = NULL; delete p;
		this->a = MyMatrix;
		MyMatrix = NULL; delete MyMatrix;
	}
	void createU() { // tworzy macierz unitarna 'u'
		Matrix* MyMatrix = new Matrix;
		double* p = NULL;
		double temp;
		MyMatrix->rowCount = a->rowCount;
		MyMatrix->colCount = 1;
		MyMatrix->setMatrixMemory();

		temp = eiFi * (aNorm + fabs(a1));
		p = MyMatrix->getMatrixElementAddress(0, 0);
		MyMatrix->setMatrixElementOnAddress(p, temp);

		for (int i = 1; i < MyMatrix->rowCount; i++) {
			p = a->getMatrixElementAddress(i, 0);
			temp = a->getMatrixElementByAddress(p);
			p = MyMatrix->getMatrixElementAddress(i, 0);
			MyMatrix->setMatrixElementOnAddress(p, temp);
		} p = NULL; delete p;
		this->u = MyMatrix;
		MyMatrix = NULL; delete MyMatrix;
	}
	Matrix& multiplyTwoMatrix(const Matrix& a, const Matrix& b) { // zwraca wynik mnozenia macierzy 'a' przez macierz 'b'
		if (a.colCount != b.rowCount) {
			cout << "Blad Mnozenia" << endl; system("pause"); exit(0);
		}
		Matrix* MyMatrix = new Matrix;
		double* p = NULL;
		double temp, temp1, temp2;
		MyMatrix->rowCount = a.rowCount;
		MyMatrix->colCount = b.colCount;
		MyMatrix->setMatrixMemory();
		for (int i = 0; i < a.rowCount; i++) {
			for (int j = 0; j < b.colCount; j++) {
				temp = 0;
				for (int k = 0; k < a.colCount; k++) {
					p = a.getMatrixElementAddress(i, k);
					temp1 = a.getMatrixElementByAddress(p);
					p = b.getMatrixElementAddress(k, j);
					temp2 = b.getMatrixElementByAddress(p);
					temp += temp1 * temp2;
				}
				p = MyMatrix->getMatrixElementAddress(i, j);
				MyMatrix->setMatrixElementOnAddress(p, temp);
			}
		} p = NULL; delete p;
		return *MyMatrix;
	}
	void multiplyMatrixByValue(Matrix& m, const double& val) { // mnozy macierz 'm' przez wartosc 'val'
		double* p = NULL;
		double temp;
		for (int i = 0; i < m.rowCount; i++) {
			for (int j = 0; j < m.colCount; j++) {
				p = m.getMatrixElementAddress(i, j);
				temp = m.getMatrixElementByAddress(p);
				temp *= val;
				m.setMatrixElementOnAddress(p, temp);
			}
		} p = NULL; delete p;
	}
	void subTwoMatrix(Matrix& toSub, const Matrix& subBy) {	// odejmuje od macierzy 'toSub' macierz 'subBy'
		if (toSub.rowCount != subBy.rowCount || toSub.colCount != subBy.colCount) {
			cout << "Blad Odejmowania" << endl; system("pause"); exit(0);
		}
		double* p = NULL;
		double temp1, temp2;
		for (int i = 0; i < toSub.rowCount; i++) {
			for (int j = 0; j < toSub.colCount; j++) {
				p = subBy.getMatrixElementAddress(i, j);
				temp2 = subBy.getMatrixElementByAddress(p);
				p = toSub.getMatrixElementAddress(i, j);
				temp1 = toSub.getMatrixElementByAddress(p);
				toSub.setMatrixElementOnAddress(p, temp1 - temp2);
			}
		} p = NULL; delete p;
	}
	Matrix& doT(const Matrix& m) { // tworzy macierz 'm' transponowana
		Matrix* mT = new Matrix;
		double* p = NULL;
		double temp;
		mT->rowCount = m.colCount;
		mT->colCount = m.rowCount;
		mT->setMatrixMemory();
		for (int i = 0; i < m.rowCount; i++) {
			for (int j = 0; j < m.colCount; j++) {
				p = m.getMatrixElementAddress(i, j);
				temp = m.getMatrixElementByAddress(p);
				p = mT->getMatrixElementAddress(j, i);
				mT->setMatrixElementOnAddress(p, temp);
			}
		} p = NULL; delete p;
		return *mT;
	}
	Matrix& createP(const int& step) { // tworzy macierz 'P'
		Matrix* P = new Matrix;
		double* p = NULL;
		double temp;
		P->rowCount = P->colCount = I->rowCount + step;
		P->setMatrixMemory();
		for (int i = 0; i < step; i++) { // dokleja 0 i 1
			p = P->getMatrixElementAddress(i, i);
			P->setMatrixElementOnAddress(p, 1);
			for (int j = i + 1; j < P->rowCount; j++) {
				p = P->getMatrixElementAddress(j, i);
				P->setMatrixElementOnAddress(p, 0);
				p = P->getMatrixElementAddress(i, j);
				P->setMatrixElementOnAddress(p, 0);
			}
		}
		Matrix P_(*I);
		Matrix* U_UT = new Matrix;
		U_UT = &multiplyTwoMatrix(*u, *uT);
		multiplyMatrixByValue(*U_UT, B);
		subTwoMatrix(P_, *U_UT);
		int k = 0, l = 0;
		for (int i = step; i < P->rowCount; i++) { // kopiuje z falka
			for (int j = step; j < P->colCount; j++) {
				p = P_.getMatrixElementAddress(k, l);
				temp = P_.getMatrixElementByAddress(p);
				p = P->getMatrixElementAddress(i, j);
				P->setMatrixElementOnAddress(p, temp);
				l++;
			} l = 0; k++;
		} p = NULL; delete p;
		U_UT = NULL; delete U_UT;
		return *P;
	}
	void calcANormA1eiFi() { // oblicza 'norme a', 'e^iFI' oraz wyciaga 'pierwszy element' z macierzy 'a'
		double sq = 0;
		double* p = NULL;
		for (int i = 0; i < a->rowCount; i++) {
			p = a->getMatrixElementAddress(i, 0);
			sq += a->getMatrixElementByAddress(p) * a->getMatrixElementByAddress(p);
		}
		aNorm = sqrt(sq);
		p = a->getMatrixElementAddress(0, 0);
		a1 = a->getMatrixElementByAddress(p);
		if (a1 < 0) eiFi = -1;
		else eiFi = 1;
		p = NULL; delete p;
	}
	void calcB() { // oblicza 'B'
		double temp = aNorm * (aNorm + fabs(a1));
		if (fabs(temp) > 1e-12) B = 1 / temp;
		else {
			zeroDividing = true;
			HHres = _zeroDiv;
		}
	}
	Matrix& calcValues(const Matrix& A, const Matrix& b) {
		Matrix* x = new Matrix;
		double* p = NULL;
		double temp, rowValue, xValue;
		x->rowCount = A.rowCount;
		x->colCount = 1;
		x->setMatrixMemory();
		for (int i = A.rowCount - 1; i >= 0; i--) {
			p = b.getMatrixElementAddress(i, 0);
			rowValue = A.getMatrixElementByAddress(p);
			p = A.getMatrixElementAddress(i, i);
			xValue = A.getMatrixElementByAddress(p);
			for (int j = A.rowCount - 1; j > i; j--) {
				p = A.getMatrixElementAddress(i, j);
				temp = A.getMatrixElementByAddress(p);
				p = x->getMatrixElementAddress(j, 0);
				temp *= x->getMatrixElementByAddress(p);
				rowValue -= temp;
			}
			p = x->getMatrixElementAddress(i, 0);
			x->setMatrixElementOnAddress(p, rowValue / xValue);
		} p = NULL; delete p;
		return *x;
	}
	void HHresult(const Matrix& A, const Matrix& b) {
		double* p = NULL;
		double temp;
		bool zeroRow = true;
		bool zeroFree = true;
		for (int i = 0; i < A.rowCount; i++) {
			p = A.getMatrixElementAddress(A.rowCount - 1, i);
			temp = A.getMatrixElementByAddress(p);
			if (fabs(temp) > 1e-12) zeroRow = false;
		}
		p = b.getMatrixElementAddress(b.rowCount - 1, 0);
		temp = b.getMatrixElementByAddress(p);
		if (fabs(temp) > 1e-12) zeroFree = false;
		p = NULL; delete p;
		if (zeroRow) {
			if (zeroFree) HHres = _inf;
			else HHres = _contr;
		} else HHres = _ok;
	}
public:
	Result HHres;
	Matrix* x = new Matrix;
	void doHouseholder() {
		Matrix* Ak = new Matrix;
		Matrix* Q = new Matrix;
		Matrix* QT = new Matrix;
		Matrix* QTb = new Matrix;
		Matrix* R = new Matrix;
		stringstream name;

		setMatrix_A_b(*Ab, *A, *b);									A->drawMatrix("A"); b->drawMatrix("b");
		Ak = A;
		int max = A->rowCount - 1; // dla macierzy 3-go stopnia max == 2, kroki liczymy od zera czyli bedziemy pisac ' < max'
		Matrix* P = new Matrix[max];
		
		for (int i = 0; i < max; i++) {
			cout << endl << "Krok <<< " << i << " >>>" << endl << endl;
			createI(A->rowCount - i);								I->drawMatrix("I");
			createA(*Ak, i);										a->drawMatrix("a");
			calcANormA1eiFi();
			calcB(); if (zeroDividing) {
				Ak = NULL; delete Ak; Q = NULL; delete Q; QT = NULL; delete QT;
				QTb = NULL; delete QTb; R = NULL; delete R; delete[] P; return;
			}
			createU();												u->drawMatrix("u");
			uT = &doT(*u);											uT->drawMatrix("uT");
			name.str(""); name << "P[" << i << "]";
			P[i] = createP(i);										P[i].drawMatrix(name.str());
			name.str(""); name << "A po " << i << " kroku";
			Ak = &multiplyTwoMatrix(P[i], *Ak);						Ak->drawMatrix(name.str());
		}
		*Q = P[0];
		for (int i = 1; i < max; i++) {
			Q = &multiplyTwoMatrix(*Q, P[i]);
		}															Q->drawMatrix("Q");
		QT = &doT(*Q);												QT->drawMatrix("QT");

		R = Ak;														R->drawMatrix("R");
		QTb = &multiplyTwoMatrix(*QT, *b);							QTb->drawMatrix("QTb");
		HHresult(*R, *QTb);

		x = &calcValues(*R, *QTb);

		Ak	= NULL;	delete Ak;
		Q	= NULL;	delete Q;
		QT	= NULL;	delete QT;
		QTb	= NULL;	delete QTb;
		R	= NULL;	delete R;
					delete[] P;
	}
	Householder(Matrix& MyMatrix) {
		this->Ab = &MyMatrix;
	}
	~Householder() {
		Ab = NULL; delete Ab;
		A = NULL; delete A;
		b = NULL; delete b;
		I = NULL; delete I;
		a = NULL; delete a;
		u = NULL; delete u;
		uT = NULL; delete uT;
		x = NULL; delete x;
	}
};
class Menu : private MatrixSetting, private OptEnums {
	void drawOkSetsMenu() {
		TestSets* MyTestSets = new TestSets;
		int choice;
		bool proceed;
		do {
			proceed = false;
			for (int i = 0; i < MyTestSets->okCount; i++) {
				cout << i + 1 << ".ZESTAW '" << MyTestSets->okSet[i].name << "'" << endl;
				drawEquations(MyTestSets->okSet[i].matrix, MyTestSets->okSet[i].matrix.rowCount - 1, MyTestSets->okSet[i].matrix.colCount - 1, fully);
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
				drawEquations(MyTestSets->contrSet[i].matrix, MyTestSets->contrSet[i].matrix.rowCount - 1, MyTestSets->contrSet[i].matrix.colCount - 1, fully);
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
				drawEquations(MyTestSets->infSet[i].matrix, MyTestSets->infSet[i].matrix.rowCount - 1, MyTestSets->infSet[i].matrix.colCount - 1, fully);
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
	UserOpt userOpt;
	SetType setType;
	set* choosenSet = new set;

	void drawMainMenu() {
		int choice;
		bool proceed;
		do {
			proceed = false;
			cout << "<<<|METODA HOUSEHOLDERA|>>>" << endl << endl;
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

class UserInteraction : private OptEnums, private MatrixSetting, private ResultEnum {
	Menu* UserMenu = new Menu;
	Matrix* UserMatrix = new Matrix;
public:
	void startUI() {
		UserMenu->drawMainMenu();
		switch (UserMenu->userOpt) {
			case testSet:
				UserMenu->drawTestSetsTypesMenu();
				UserMenu->drawTestSetsMenu();
				UserMatrix = &UserMenu->choosenSet->matrix;
				cout << "Oczekiwany wynik>> " << UserMenu->choosenSet->name << endl << endl;
				break;
			case userDefined: setMatrix(*UserMatrix); break;
			default: fatalError();
		}
		Householder H(*UserMatrix);
		H.doHouseholder();
		switch (H.HHres) { //odczytujemy rezultat obliczen
		case _ok: H.x->drawMatrix("x"); break;
		case _inf: cout << "Podany uklad ma nieskonczenie wiele rozwiazan." << endl << endl; break;
		case _contr: cout << "Podany uklad jest sprzeczny." << endl << endl; break;
		case _zeroDiv: cout << "Podanego ukladu nie jestem w stanie rozwiazac (problem dzielenia przez 0)." << endl << endl; break;
		default: fatalError();
		}
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
				case 1: system("cls"); startUI(); iSawU = true; system("pause"); break;
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