//
// Created by Kamil Cinner on 23/04/2021.
//

#include "lab07.h"

#include <random>

std::random_device rd;
std::minstd_rand gen(rd());
std::uniform_int_distribution<int> eatTimeDistribution(0, MAX_EAT_TIME);

int Philosopher::counter = 0;

Philosopher::Philosopher() {
    selfNumber = ++Philosopher::counter;

    leftFork = selfNumber;
    rightFork = selfNumber + 1;
}

void Philosopher::operator()() {
    while (mealsEaten < MEAL_COUNT) {
        int eatTime = eatTimeDistribution(gen);

    }
}