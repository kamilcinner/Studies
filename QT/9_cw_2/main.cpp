#include <QCoreApplication>

class Dog {
public:
    QString rodzaj() {
        return "Dog";
    }
};

class Cat {
public:
    QString rodzaj() {
        return "Cat";
    }
};

template <typename T, int capacity>
class House {
    T *p[capacity];
public:
    T *getPointer(int index) {
        return p[index];
    }
    void setPointer(T *p, int index) {
        this->p[index] = p;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dog Basta; Dog Rufus;
    Cat Rudy; Cat Szary;
    House<Dog, 2> doghouse;
    House<Cat, 2> catHut;
    doghouse.setPointer(&Basta, 0);
    doghouse.setPointer(&Rufus, 1);
    catHut.setPointer(&Rudy, 0);
    catHut.setPointer(&Szary, 1);

    return a.exec();
}
