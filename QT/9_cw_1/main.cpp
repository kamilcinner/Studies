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

template <typename T>
class House {
    T *p;
public:
    T *getPointer() {
        return p;
    }
    void setPointer(T *p) {
        this->p = p;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dog Basta;
    Cat Rudy;
    House<Dog> doghouse;
    House<Cat> catHut;
    doghouse.setPointer(&Basta);
    catHut.setPointer(&Rudy);

    return a.exec();
}
