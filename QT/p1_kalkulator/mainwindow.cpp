#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculateButton_clicked()
{
    double a = ui->a->text().toDouble();
    double b = ui->b->text().toDouble();
    double result = 0;
    switch (ui->operation->currentIndex()) {
    case 0: result = a + b; break;
    case 1: result = a - b; break;
    case 2: result = a * b; break;
    case 3: result = a / b; break;
    }
    ui->result->setText(QString::number(result));
}
