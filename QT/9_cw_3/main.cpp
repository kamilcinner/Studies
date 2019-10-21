#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QString> v;
    QString temp;
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);

    do {
        std::cout << "Wpisz slowo (exit konczy): ";
        qtin >> temp;
        v.push_back(temp);
    } while (v.back() != "exit");

    qtout << endl << "Wpisane slowa:" << endl;

    for (int i = 0; i < v.size(); i++) {
        qtout << v.at(i) << endl;
    }

    return a.exec();
}
