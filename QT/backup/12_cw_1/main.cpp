#include "wykres.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wykres w;
    w.show();

    return a.exec();
}
