//
// Created by Kamil Cinner on 23/04/2021.
//

#ifndef PRIR_LAB07_H
#define PRIR_LAB07_H

#include <string>
#include "kolory.h"

const int MAX_EAT_TIME = 1000;
const int PHILOSOPHER_COUNT = 5;
const int MEAL_COUNT = 5;

class Philosopher {
private:
    static int counter;

    int selfNumber;
    int leftFork;
    int rightFork;
    int mealsEaten = 0;

    std::string k = Kolor::nastepny(), r = Kolor::reset() , console;

public:
    Philosopher();

    void operator()();
};

#endif //PRIR_LAB07_H
