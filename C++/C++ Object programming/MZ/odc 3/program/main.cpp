#include <iostream>
#include "event.h"

using namespace std;

int main()
{
    Event w1("Apokalipsa Zombie",6,8,2045,8,15);
    w1.show();

    Event w2;
    w2.show();

    Event w3("Apokalipsa Zombie");
    w3.show();

    return 0;
}
