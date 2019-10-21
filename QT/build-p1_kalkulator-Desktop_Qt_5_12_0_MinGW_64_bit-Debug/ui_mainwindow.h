/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *calculateButton;
    QLineEdit *a;
    QLineEdit *b;
    QLineEdit *result;
    QComboBox *operation;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(465, 188);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        calculateButton = new QPushButton(centralWidget);
        calculateButton->setObjectName(QString::fromUtf8("calculateButton"));
        calculateButton->setGeometry(QRect(310, 90, 121, 51));
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        calculateButton->setFont(font1);
        calculateButton->setCursor(QCursor(Qt::PointingHandCursor));
        a = new QLineEdit(centralWidget);
        a->setObjectName(QString::fromUtf8("a"));
        a->setGeometry(QRect(15, 15, 81, 41));
        b = new QLineEdit(centralWidget);
        b->setObjectName(QString::fromUtf8("b"));
        b->setGeometry(QRect(175, 15, 81, 41));
        result = new QLineEdit(centralWidget);
        result->setObjectName(QString::fromUtf8("result"));
        result->setEnabled(false);
        result->setGeometry(QRect(305, 15, 121, 41));
        operation = new QComboBox(centralWidget);
        operation->addItem(QString());
        operation->addItem(QString());
        operation->addItem(QString());
        operation->addItem(QString());
        operation->setObjectName(QString::fromUtf8("operation"));
        operation->setGeometry(QRect(105, 15, 61, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 20, 21, 31));
        QFont font2;
        font2.setPointSize(20);
        label->setFont(font2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 465, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(a, SIGNAL(textChanged(QString)), calculateButton, SLOT(click()));
        QObject::connect(b, SIGNAL(textChanged(QString)), calculateButton, SLOT(click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Kalkulator", nullptr));
        calculateButton->setText(QApplication::translate("MainWindow", "Oblicz", nullptr));
        operation->setItemText(0, QApplication::translate("MainWindow", "+", nullptr));
        operation->setItemText(1, QApplication::translate("MainWindow", "-", nullptr));
        operation->setItemText(2, QApplication::translate("MainWindow", "*", nullptr));
        operation->setItemText(3, QApplication::translate("MainWindow", "/", nullptr));

        label->setText(QApplication::translate("MainWindow", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
