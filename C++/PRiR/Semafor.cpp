//
// Created by Kamil Cinner on 16/04/2021.
//

#include "Semafor.h"

Semaphore::Semaphore(int _count):
    resourcesCounter(_count) {}

int Semaphore::value() const {
    return resourcesCounter;
}

void Semaphore::signals() {
    unique_lock<mutex> counterLock(counterMutex);
    ++resourcesCounter;
    isCounterDifferentFromZero.notify_one();
}

void Semaphore::wait() {
    unique_lock<mutex> counterLock(counterMutex);
    while (resourcesCounter == 0) {
        isCounterDifferentFromZero.wait(counterLock);
    }
    --resourcesCounter;
}

bool Semaphore::try_wait() {
    unique_lock<mutex> counterLock(counterMutex);
    if (resourcesCounter != 0) {
        --resourcesCounter;
        return true;
    }
    return false;
}