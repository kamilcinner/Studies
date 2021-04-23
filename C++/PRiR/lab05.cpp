#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <condition_variable>
#include <random>
#include "kolory.h"

using namespace std;

// Cwiczenie 1 ----------------------------------------------------------------------
const int WORK_TIME = 5; // seconds

template<typename T> class Monitor {
private:
  T data;
  bool isDataUpToDate;

  mutex dataMutex;
  condition_variable newDataAvailable;
  condition_variable gotNewData;
public:
  Monitor() {
    isDataUpToDate = false;
  }

  void save(T newData) {
    unique_lock<mutex> lock(dataMutex);

    if (isDataUpToDate) {
      gotNewData.wait(lock);
    }

    isDataUpToDate = true;
    data = newData;

    newDataAvailable.notify_one();
  }

  T read() {
    unique_lock<mutex> lock(dataMutex);

    if (!isDataUpToDate) {
      newDataAvailable.wait(lock);
    }

    isDataUpToDate = false;
    gotNewData.notify_one();
    return data;
  }
};

class Producer {
private:
  int operationTime;
  Monitor<char>& container;
  char currentChar;

  minstd_rand generator;
  uniform_int_distribution<char> distribution;
public:
  Producer(Monitor<char>& _container):
    operationTime(0),
    container(_container),
    currentChar('a'),
    generator(random_device()()),
    distribution('a', 'z')
  {}

  void operator()() {
    while (operationTime < WORK_TIME) {
      container.save(currentChar);

      currentChar = (currentChar + 1 - 97) % 25 + 97;

      this_thread::sleep_for(chrono::seconds(1));
      ++operationTime;
    }
    container.save(EOF);
  }
};

class Consumer {
private:
  Monitor<char>& container;
public:
  Consumer(Monitor<char>& _container):
    container(_container)
  {}

  void operator()() {
    char data = container.read();
    while (data != EOF) {
      cout << data << endl;
      data = container.read();
    }
  }
};

void lab05_cwiczenie_3_1() {
  Monitor<char> container;

  Consumer consumer(container);
  Producer producer(container);

  thread consumerThread(consumer);
  thread producerThread(producer);

  producerThread.join();
  consumerThread.join();
}

// Cwiczenie 2 ----------------------------------------------------------------------
mutex consoleMutex;
const int MAX_RUNS_COUNT = 5;

template<typename T> class Monitor2 {
private:
    T data;
    bool isDataUpToDate;

    mutex dataMutex;
    condition_variable newDataAvailable;
    condition_variable gotNewData;
public:
    Monitor2() {
        isDataUpToDate = false;
    }

    void save(T newData) {
        unique_lock<mutex> lock(dataMutex);

        if (isDataUpToDate) {
            gotNewData.wait(lock);
        }

        isDataUpToDate = true;
        data = newData;

        newDataAvailable.notify_one();
    }

    T read() {
        unique_lock<mutex> lock(dataMutex);

        if (!isDataUpToDate) {
            newDataAvailable.wait(lock);
        }

        isDataUpToDate = false;
        gotNewData.notify_one();
        return data;
    }
};

class Producer2 {
private:
    int runNumber;
    Monitor2<char>& container;
    char currentChar;

    minstd_rand generator;
    uniform_int_distribution<char> distribution;

    int producerNumber;
    string k = Kolor::nastepny(), r = Kolor::reset() , info;

public:
    Producer2(int _producerNumber, Monitor2<char>& _container):
            runNumber(0),
            producerNumber(_producerNumber),
            container(_container),
            currentChar('a'),
            generator(random_device()()),
            distribution('a', 'z')
    {}

    void operator()() {
        while (runNumber < MAX_RUNS_COUNT) {
            info = k + "P:" + to_string(producerNumber) + " c:" + currentChar + r;
            {
                lock_guard<mutex> lock(consoleMutex);
                cout << info << endl;
            }

            container.save(currentChar);

            currentChar = (currentChar + 1 - 97) % 25 + 97;

            this_thread::sleep_for(chrono::milliseconds (rand() % 1000));
            runNumber++;
        }
        container.save(EOF);
    }
};

class Consumer2 {
private:
    Monitor2<char>& container;

    int consumerNumber;
    string k = Kolor::nastepny(), r = Kolor::reset() , info;
public:
    Consumer2(int _consumerNumber, Monitor2<char>& _container):
            consumerNumber(_consumerNumber),
            container(_container)
    {}

    void operator()() {
        char data = container.read();
        while (data != EOF) {
            info = k + "C:" + to_string(consumerNumber) + " data:" + data + r;
            {
                lock_guard<mutex> lock(consoleMutex);
                cout << info << endl;
            }

            data = container.read();
        }
    }
};

void lab05_cwiczenie_3_2() {
    const unsigned int THREADS_NUMBER = 3;

    Monitor2<char> container;

    vector<thread> producersThreads;
    vector<thread> consumersThreads;

    for (unsigned int i = 0; i < THREADS_NUMBER; ++i) {
        consumersThreads.emplace_back(Consumer2(i, container));
        producersThreads.emplace_back(Producer2(i, container));
    }

    for (thread& producerThread: producersThreads) {
        producerThread.join();
    }
    for (thread& consumerThread: consumersThreads) {
        consumerThread.join();
    }
}

// Cwiczenie 3 ----------------------------------------------------------------------
template<typename T> class Monitor3 {
private:
    vector<T> data;
    unsigned int size;
    vector<bool> isDataUpToDate;

    vector<mutex> dataMutex;
    vector<condition_variable> newDataAvailable;
    vector<condition_variable> gotNewData;
public:
    explicit Monitor3(unsigned int _size):
        size(_size)
    {
        vector<T> listData(size);
        vector<bool> listBool(size);
        vector<mutex> listMutex(size);
        vector<condition_variable> listNewData(size);
        vector<condition_variable> listGotData(size);

        data.swap(listData);
        isDataUpToDate.swap(listBool);
        dataMutex.swap(listMutex);
        newDataAvailable.swap(listNewData);
        gotNewData.swap(listGotData);

        for (unsigned int i = 0; i < size; i++) {
            isDataUpToDate[i] = false;
        }
    }

    void save(T newData, unsigned int index) {
        unique_lock<mutex> lock(dataMutex[index]);

        if (isDataUpToDate[index]) {
            gotNewData[index].wait(lock);
        }

        isDataUpToDate[index] = true;
        data[index] = newData;

        newDataAvailable[index].notify_one();
    }

    T read(unsigned int index) {
        unique_lock<mutex> lock(dataMutex[index]);

        if (!isDataUpToDate[index]) {
            newDataAvailable[index].wait(lock);
        }

        isDataUpToDate[index] = false;
        gotNewData[index].notify_one();
        return data[index];
    }
};

class Producer3 {
private:
    int runNumber;
    Monitor3<char>& container;
    char currentChar;

    minstd_rand generator;
    uniform_int_distribution<char> distribution;

    int producerNumber;
    unsigned int indexToOperate;
    string k = Kolor::nastepny(), r = Kolor::reset() , info;

public:
    Producer3(int _producerNumber, Monitor3<char>& _container, unsigned int _indexToOperate):
            runNumber(0),
            producerNumber(_producerNumber),
            container(_container),
            indexToOperate(_indexToOperate),
            currentChar('a'),
            generator(random_device()()),
            distribution('a', 'z')
    {}

    void operator()() {
        while (runNumber < MAX_RUNS_COUNT) {
            info = k + "P:" + to_string(producerNumber) + " c:" + currentChar + " i:" + to_string(indexToOperate) + r;
            {
                lock_guard<mutex> lock(consoleMutex);
                cout << info << endl;
            }

            container.save(currentChar, indexToOperate);

            currentChar = (currentChar + 1 - 97) % 25 + 97;

            this_thread::sleep_for(chrono::milliseconds (rand() % 1000));
            runNumber++;
        }
        container.save(EOF, indexToOperate);
    }
};

class Consumer3 {
private:
    Monitor3<char>& container;

    int consumerNumber;
    unsigned int indexToOperate;
    string k = Kolor::nastepny(), r = Kolor::reset() , info;
public:
    Consumer3(int _consumerNumber, Monitor3<char>& _container, unsigned int _indexToOperate):
            consumerNumber(_consumerNumber),
            container(_container),
            indexToOperate(_indexToOperate)
    {}

    void operator()() {
        char data = container.read(indexToOperate);
        while (data != EOF) {
            info = k + "C:" + to_string(consumerNumber) + " data:" + data + " i:" + to_string(indexToOperate) + r;
            {
                lock_guard<mutex> lock(consoleMutex);
                cout << info << endl;
            }

            data = container.read(indexToOperate);
        }
    }
};

void lab05_cwiczenie_3_3() {
    const unsigned int DATA_SIZE = 3;
    const unsigned int THREADS_COUNT = 10;

    Monitor3<char> container(DATA_SIZE);

    vector<thread> producersThreads;
    vector<thread> consumersThreads;

    for (unsigned int i = 0; i < THREADS_COUNT; ++i) {
        consumersThreads.emplace_back(Consumer3(i, container, i % DATA_SIZE));
        producersThreads.emplace_back(Producer3(i, container, i % DATA_SIZE));
    }

    for (thread& producerThread: producersThreads) {
        producerThread.join();
    }
    for (thread& consumerThread: consumersThreads) {
        consumerThread.join();
    }

    cout << "SUCCESS";
}
