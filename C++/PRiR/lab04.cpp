#include "lab04.h"
#include "kolory.h"

#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

const int OPOZNIENIE = 100;
int licznik = 50;

// Cwiczenie 2.1 ------------------------------------------------------------
class WatekA {
private:
  int numer;
  string k = Kolor::nastepny(), r = Kolor::reset() , info = "";

public:
  WatekA(int _numer): numer(_numer) {}
  void operator()() {
    while(licznik > 0){
      info = k + "w:" + to_string(numer) + " l:" + to_string(licznik);
      cout << info << endl;
      --licznik;
      //this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
      this_thread::sleep_for(chrono::microseconds(rand() % 500));
    }
  }
};

void lab04_cwiczenie_2_1(){
  srand (time(NULL));

  thread w1(WatekA(1));
  thread w2(WatekA(2));
  w1.join();
  w2.join();
}

// Cwiczenie 2.2 ------------------------------------------------------------
mutex licznikMutex;

class WatekB {
private:
  int numer;
  string k = Kolor::nastepny(), r = Kolor::reset() , info = "";

public:
  WatekB(int _numer): numer(_numer) {}
  void operator()(){
    while(true){
      {
        lock_guard<mutex> blokada(licznikMutex) ;
        if(licznik<=0) break;
        info = k + "w:" + to_string(numer) + " l:" + to_string(licznik);
        cout << info << endl;
        --licznik;
      }
      //this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
      this_thread::sleep_for(chrono::microseconds(rand() % 100));
    }
  }
};

void lab04_cwiczenie_2_2(){
  srand (time(NULL));

  thread w1(WatekB(1));
  thread w2(WatekB(2));
  w1.join();
  w2.join();
}

// Cwiczenie 2.3 ------------------------------------------------------------
class WatekC {
private:
  int numer;
  string k = Kolor::nastepny(), r = Kolor::reset() , info = "";

public:
  WatekC(int _numer): numer(_numer) {}
  void operator()(){
    while(true){
      licznikMutex.lock();
      if (licznik<=0) break;
      info = k + "w:" + to_string(numer) + " l:" + to_string(licznik);
      cout << info << endl;
      --licznik;
      licznikMutex.unlock();
      
      //this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
      this_thread::sleep_for(chrono::microseconds(rand() % 100));
    }
  }
};

void lab04_cwiczenie_2_3(){
  srand (time(NULL));
  
  thread w1(WatekC(1));
  thread w2(WatekC(2));
  w1.join();
  w2.join();
}

// Cwiczenie 2.4 ------------------------------------------------------------
const int LICZBA_WATKOW = 5;
const int ZNAKOW_DO_ZAPISANIA = 24;

mutex lancuchMutex;

class WatekD {
private:
  char znak;
  string &lancuch;

  int numer;
  string k = Kolor::nastepny(), r = Kolor::reset() , info = "";

public:
  WatekD(int _numer, char _znak, string &_lancuch): numer(_numer), znak(_znak), lancuch(_lancuch) {}

  void operator()() {
    lock_guard<mutex> blokada(lancuchMutex);
    for (int i = 0; i < ZNAKOW_DO_ZAPISANIA; i++) {
      lancuch[i] = znak;
      
      info = k + "w:" + to_string(numer) + " l:" + lancuch;
      cout << info << endl;

      //this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
      this_thread::sleep_for(chrono::microseconds(rand() % 100));
    }
  }
};

void lab04_cwiczenie_2_4(){
  string lancuch;
  lancuch.resize(ZNAKOW_DO_ZAPISANIA);

  vector<thread> watki;
  for (unsigned int i = 0; i < LICZBA_WATKOW; ++i) {
    watki.push_back(thread(WatekD(i, 'a' + i, lancuch)));  
  }

  for (thread& w: watki) w.join();

  cout << Kolor::reset() << "Wynik: " << lancuch << endl;
}

// Cwiczenie Dodatkowe ----------------------------------------------------------
const int RANDOM_MAX = 100;
const unsigned int ARRAY_SIZE = 100;
vector<mutex> vectorMutex;

void fillWithRandom(vector<int> &v) {
  random_device randomDevice;
  uniform_int_distribution<int> distribution(1, RANDOM_MAX);
  for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
    v.push_back(distribution(randomDevice));
  }
}

unsigned int printVector(vector<int> &v) {
  unsigned int sum = 0;
  cout << Kolor::reset();
  for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
    cout << v[i] << " ";
    sum += v[i];
  }
  cout << endl << "Sum = " << sum << endl;
  return sum;
}

bool isEmpty(vector<int> &v) {
  for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
    if (v[i] != 0) {
      return false;
    }
  }
  return true;
}

class SuperThread {
private:
  int &counter;
  vector<int> &vec;

  int id;
  string k = Kolor::nastepny(), info = "";

public:
  SuperThread(int _id, vector<int> &_vec, int &_counter): id(_id), vec(_vec), counter(_counter) {}

  void operator()() {
    while (!isEmpty(vec)) {
      const unsigned int index = rand() % ARRAY_SIZE;
      lock_guard<mutex> indexLock(vectorMutex[index]);
      if (vec[index] != 0) {
        counter += vec[index];

        info = k + "thread:" + to_string(id);
        info += " index:" + to_string(index);
        info += " value:" + to_string(vec[index]);
        info += " counter:" + to_string(counter);
        cout << info << endl;

        vec[index] = 0;

        this_thread::sleep_for(chrono::microseconds(counter));
      }
    }
  }
};

void lab04_zadanie_dodatkowe(){
  vector<mutex> list(ARRAY_SIZE);
  vectorMutex.swap(list);

  vector<int> vec;
  fillWithRandom(vec);
  unsigned int vecSum = printVector(vec);

  srand (time(NULL));
  int t1Counter = 0, t2Counter = 0;

  thread t1(SuperThread(1, vec, t1Counter));
  thread t2(SuperThread(2, vec, t2Counter));

  t1.join();
  t2.join();

  string answer = ((t1Counter + t2Counter) == vecSum) ? "true" : "false";

  cout << Kolor::reset() << endl;
  cout << "Thread 1 counter: " << to_string(t1Counter) << endl;
  cout << "Thread 2 counter: " << to_string(t2Counter) << endl;
  cout << "Initial array sum: " << to_string(vecSum) << endl;
  cout << "Does (counter1 + counter2 = arraySum): " << answer << endl;

  cout << "Array after operations:" << endl;
  printVector(vec);
}
