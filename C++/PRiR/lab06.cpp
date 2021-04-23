//
// Created by Kamil Cinner on 16/04/2021.
//

#include "lab06.h"

#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <iostream>
#include "Semafor.h"

using namespace std;

class Platform;

class Train {
private:
    string mName;
    Platform &platform;
    Platform &sparePlatform;

public:
    Train(string _name, Platform &p1, Platform &p2);

    void operator()();

    string name();
};

class Platform {
private:
    string name;
    bool empty;
    Semaphore semaphore = Semaphore(1);

public:
    Platform(string _name):
        name(_name), empty(true) {
    }

    void arrival(Train& t) {
        semaphore.wait();
        if (empty) {
            string info = "Pociag " + t.name() + " wjezdza na peron " + name + "\n";
            cout << info;
        } else {
            string info = "Pociag " + t.name() + " spowodowal katastrofe na peronie " + name + "\n";
            cout << info;
        }
        empty = false;
    }

    void departure(Train& t) {
        string info = "Pociag " + t.name() + " opuszcza peron " + name + "\n";
        cout << info;
        empty = true;
        semaphore.signals();
    }

    bool isEmpty() {
        return empty;
    }
};

minstd_rand generator;
uniform_int_distribution<int> range(0, 500);

Train::Train(string _name, Platform &p1, Platform &p2):
    mName(_name), platform(p1), sparePlatform(p2) {
}

string Train::name() {
    return mName;
}

void Train::operator()() {
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(range(generator)));
        if (platform.isEmpty()) {
            platform.arrival(*this);
            this_thread::sleep_for(chrono::milliseconds(range(generator)));
            platform.departure(*this);
        } else {
            sparePlatform.arrival(*this);
            this_thread::sleep_for(chrono::milliseconds(range(generator)));
            sparePlatform.departure(*this);
        }
    }
}

void lab06_cwiczenie_4_1() {
    Platform p1("p1"), p2("p2"), p3("p3");

    Train train1("pociag1", p2, p1);
    Train train2("pociag2", p2, p3);
    Train train3("pociag3", p2, p1);
    Train train4("pociag4", p2, p3);

    thread th1(train1);
    thread th2(train2);
    thread th3(train3);
    thread th4(train4);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
}
