#include "lab03.h"
#include "kolory.h"

#include <thread>
#include <iostream>
#include <random>

using namespace std;

void wypelnijLosowymi(short T[], int n) {
    random_device maszynkaLosujaca;
    uniform_int_distribution<short> dystrybucja(-10,10);
    for(int i=0; i< n; i++) T[i] = dystrybucja(maszynkaLosujaca);
}

template<typename T>
void wyswietlTablice(const T A[], int n) {
    T suma = (T)0;

    for(int i = 0; i < n; i++){
        cout << A[i] << " ";
        suma += A[i];
    }
    cout << endl << "Suma=" << suma << endl << endl;
}

void zadanie1(const short T[], int start, int end, short & result) {
    
    string k = Kolor::nastepny(), r = Kolor::reset(), info = "";
    
    result = 0;
    for(int i = start; i< end; i++){
      
      info = k + to_string(T[i]) + r + "\n";
      cout << info;

      result += T[i];
    }

    info = k + "wynik=" + to_string(result) + "\n" + r;
    cout << info;
}

void zadanie2(const short T[], int arraySize, bool even, short & result) {
  string k = Kolor::nastepny(), r = Kolor::reset(), info = "";

  result = 0;

  for (int i = 0; i < arraySize; i++) {
    if (i % 2 == 0 && even) {
      result += T[i];

      info = k + to_string(T[i]) + r + "\n";
      cout << info;
    } else if (i % 2 == 1 && !even) {
      result += T[i];

      info = k + to_string(T[i]) + r + "\n";
      cout << info;
    }
  }

  info = k + "wynik=" + to_string(result) + "\n" + r;
  cout << info;
}

void zadanie3(const short T[], int arraySize, bool positive, short & result) {
  string k = Kolor::nastepny(), r = Kolor::reset(), info = "";

  result = 0;

  for (int i = 0; i < arraySize; i++) {
    if (T[i] > 0 && positive) {
      result += T[i];

      info = k + to_string(T[i]) + r + "\n";
      cout << info;
    } else if (T[i] < 0 && !positive) {
      result += T[i];

      info = k + to_string(T[i]) + r + "\n";
      cout << info;
    }
  }

  info = k + "wynik=" + to_string(result) + "\n" + r;
  cout << info;
}

void zadanie4(short T[], int start, int end) {
  string k = Kolor::nastepny(), r = Kolor::reset(), info = "";
  
  for(int i = start; i < end; i++){
    
    info = k + to_string(T[i]) + " * " + to_string(T[i]) + r + "\n";
    cout << info;

    T[i] *= T[i];
  }
}

void zadanie5(const short T[], int start, int end, double result[]) {
    string k = Kolor::nastepny(), r = Kolor::reset(), info = "";
    
    for(int i = start; i < end; i++){
      if (i == 0) {
        result[i] = (double)(T[i] + T[i+1]) / 2.0;
      } else if (i == end - 1) {
        result[i] = (double)(T[i-1] + T[i]) / 2.0;
      } else {
        result[i] = (double)(T[i-1] + T[i] + T[i+1]) / 3.0;
      }
      info = k + to_string(result[i]) + r + "\n";
      cout << info;
    }
}

void lab03(unsigned int arraySize) {
  // Init --------------------------------------------------------
  static short * TAB;
  TAB = new short[arraySize];
  wypelnijLosowymi(TAB, arraySize);

  unsigned int halfIndex = arraySize / 2;

  // Zadanie 1 ---------------------------------------------------
  cout << endl << "Zadanie 1" << endl << endl;
  wyswietlTablice(TAB, arraySize);

  short z1res1, z1res2;

  thread z11(zadanie1, TAB, 0, halfIndex, ref(z1res1));
  thread z12(zadanie1, TAB, halfIndex, arraySize, ref(z1res2));

  z11.join();
  z12.join();

  cout<< endl << "Wyniki pracy wątków" << endl
      << "suma1=" << z1res1 << " suma2=" << z1res2
      << " suma=" << z1res1 + z1res2 << endl << endl;

  // Zadanie 2 ---------------------------------------------------
  cout << endl << "Zadanie 2" << endl << endl;
  wyswietlTablice(TAB, arraySize);

  short z2res1, z2res2;

  thread z21(zadanie2, TAB, arraySize, true, ref(z2res1));
  thread z22(zadanie2, TAB, arraySize, false, ref(z2res2));

  z21.join();
  z22.join();

  cout<< endl << "Wyniki pracy wątków" << endl
      << "suma1=" << z2res1 << " suma2=" << z2res2
      << " suma=" << z2res1 + z2res2 << endl << endl;

  // Zadanie 3 ---------------------------------------------------
  cout << endl << "Zadanie 3" << endl << endl;
  wyswietlTablice(TAB, arraySize);

  short z3res1, z3res2;

  thread z31(zadanie3, TAB, arraySize, true, ref(z3res1));
  thread z32(zadanie3, TAB, arraySize, false, ref(z3res2));

  z31.join();
  z32.join();

  cout<< endl << "Wyniki pracy wątków" << endl
      << "suma1=" << z3res1 << " suma2=" << z3res2
      << " suma=" << z3res1 + z3res2 << endl << endl;

  // Zadanie 4 ---------------------------------------------------
  cout << endl << "Zadanie 4" << endl << endl;
  wyswietlTablice(TAB, arraySize);

  thread z41(zadanie4, TAB, 0, halfIndex);
  thread z42(zadanie4, TAB, halfIndex, arraySize);

  z41.join();
  z42.join();

  cout<< endl << "Wyniki pracy wątków" << endl;
  wyswietlTablice(TAB, arraySize);

  // Zadanie 5 ---------------------------------------------------
  cout << endl << "Zadanie 5" << endl << endl;
  wyswietlTablice(TAB, arraySize);

  static double * superArray;
  superArray = new double[arraySize];

  thread z51(zadanie5, TAB, 0, halfIndex, superArray);
  thread z52(zadanie5, TAB, halfIndex, arraySize, superArray);

  z51.join();
  z52.join();

  cout<< endl << "Wyniki pracy wątków" << endl;
  wyswietlTablice(superArray, arraySize);

  delete [] TAB;
  delete [] superArray;
}
