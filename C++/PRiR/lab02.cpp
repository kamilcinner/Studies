#include "lab02.h"
#include "kolory.h"

#include <thread>
#include <chrono>
#include <iostream>

//Listing 1.1 -----------------------------------------------
using namespace std;

void kodWatku() {
  string k = Kolor::nastepny();
  string r = Kolor::reset();

  for (int i=0; i<10; ++i) {
    cout << k << "Wątek: " << this_thread::get_id() << " mówi cześć, i=" << i << r << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
  }
}

void listing_1_1() {
  thread w1(kodWatku);
  thread w2(kodWatku);

  w1.join();
  w2.join();
}

//Listing 1.2 ------------------------------------------------
#include <cmath>

const int LICZBA_PUNKTOW = 10;
double a = 0.0;
double b = M_PI;
double wynik = 0.0;

void calkaSinusa() {
  string k = Kolor::nastepny();
  string r = Kolor::reset();

  cout << k << "Watek pracuje..." << r << endl;

  double h = (b - a ) / LICZBA_PUNKTOW;
  double s = sin(a);

  for (int i=1; i < LICZBA_PUNKTOW; i++) {
    this_thread::sleep_for(chrono::milliseconds(100));
    s += 2 * sin(a + i * h);
  }
  s += sin(b);

  wynik = s * h / 2;

  cout << k << "Wątek się zakończył ... " << r << endl;
}


void listing_1_2(){
  thread watek(calkaSinusa);

  cout << "Sprzetowa współbieżność: " << thread::hardware_concurrency() << endl;
  cout << "Id wątku " << watek.get_id() << endl;

  watek.join();

  cout << "wynik=" << wynik << endl;
}

//Listing 1.3 ------------------------------------------------
class CalkaSinusa {
private:
  double a, b;
  double *wartosc;
public:
  CalkaSinusa(double _a, double _b, double *_wartosc) :
  a(_a), b(_b), wartosc(_wartosc) {}

  void operator()();
};

void CalkaSinusa::operator()() {
  string k = Kolor::nastepny();
  string r = Kolor::reset();

  cout << k << "Watek pracuje..." << r << endl;

  double h = (b - a ) / LICZBA_PUNKTOW;
  double s = sin(a);

  for (int i=1; i < LICZBA_PUNKTOW; i++) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    s += 2 * sin(a + i * h);
  }
  s += sin(b);

  *wartosc = s * h / 2;

  cout << k << "Wątek się zakończył ... " << r << endl;
}

void listing_1_3(){
  double wynik = 0.0;

  CalkaSinusa calka(0, M_PI, &wynik);
  thread watek(calka);

  cout << "Sprzetowa współbieżność: " << thread::hardware_concurrency() << endl;
  cout << "Id wątku " << watek.get_id() << endl;

  watek.join();

  cout << "wynik=" << wynik << endl;
}
