//
// Created by Kamil Cinner on 16/04/2021.
//

#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {
public:
    Semaphore(int _count=1);

    void signals();

    void wait();

    bool try_wait();

    int value() const;
private:
    int resourcesCounter;

    mutex counterMutex;
    condition_variable isCounterDifferentFromZero;
};

#endif //SEMAFOR_H
