#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList MyList;
    addToList(MyList);
    //ui->Lista->addItems(MyList);
    QStringListModel MyListModel;
    MyListModel.setStringList(MyList);
    ui->Lista->setModel(&MyListModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToList(QStringList &MyList) {
    MyList << "lama" << "owca" << "biedronka" << "familiada";
}
