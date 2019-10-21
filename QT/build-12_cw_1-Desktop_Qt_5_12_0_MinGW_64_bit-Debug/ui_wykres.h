/********************************************************************************
** Form generated from reading UI file 'wykres.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYKRES_H
#define UI_WYKRES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wykres
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *grafika;
    QHBoxLayout *horizontalLayout;
    QPushButton *drawNewGraphButton;
    QPushButton *clearFieldButton;
    QPushButton *toPointButton;
    QPushButton *toLineButton;
    QPushButton *decreaseButton;
    QPushButton *enlargeButton;

    void setupUi(QWidget *Wykres)
    {
        if (Wykres->objectName().isEmpty())
            Wykres->setObjectName(QString::fromUtf8("Wykres"));
        Wykres->resize(1250, 780);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Wykres->sizePolicy().hasHeightForWidth());
        Wykres->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Wykres);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        grafika = new QGraphicsView(Wykres);
        grafika->setObjectName(QString::fromUtf8("grafika"));

        verticalLayout->addWidget(grafika);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        drawNewGraphButton = new QPushButton(Wykres);
        drawNewGraphButton->setObjectName(QString::fromUtf8("drawNewGraphButton"));

        horizontalLayout->addWidget(drawNewGraphButton);

        clearFieldButton = new QPushButton(Wykres);
        clearFieldButton->setObjectName(QString::fromUtf8("clearFieldButton"));

        horizontalLayout->addWidget(clearFieldButton);

        toPointButton = new QPushButton(Wykres);
        toPointButton->setObjectName(QString::fromUtf8("toPointButton"));

        horizontalLayout->addWidget(toPointButton);

        toLineButton = new QPushButton(Wykres);
        toLineButton->setObjectName(QString::fromUtf8("toLineButton"));

        horizontalLayout->addWidget(toLineButton);

        decreaseButton = new QPushButton(Wykres);
        decreaseButton->setObjectName(QString::fromUtf8("decreaseButton"));

        horizontalLayout->addWidget(decreaseButton);

        enlargeButton = new QPushButton(Wykres);
        enlargeButton->setObjectName(QString::fromUtf8("enlargeButton"));

        horizontalLayout->addWidget(enlargeButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Wykres);

        QMetaObject::connectSlotsByName(Wykres);
    } // setupUi

    void retranslateUi(QWidget *Wykres)
    {
        Wykres->setWindowTitle(QApplication::translate("Wykres", "Wykres", nullptr));
        drawNewGraphButton->setText(QApplication::translate("Wykres", "[ Rysuj nowy wykres ]", nullptr));
        clearFieldButton->setText(QApplication::translate("Wykres", "[ Wyczy\305\233\304\207 obszar ]", nullptr));
        toPointButton->setText(QApplication::translate("Wykres", "[ Zmie\305\204 na wykres punktowy ]", nullptr));
        toLineButton->setText(QApplication::translate("Wykres", "[ Zmie\305\204 na wykres liniowy ]", nullptr));
        decreaseButton->setText(QApplication::translate("Wykres", "[ Pomniejszenie ( - ) ]", nullptr));
        enlargeButton->setText(QApplication::translate("Wykres", "[ Powi\304\231kszenie ( + ) ]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wykres: public Ui_Wykres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYKRES_H
