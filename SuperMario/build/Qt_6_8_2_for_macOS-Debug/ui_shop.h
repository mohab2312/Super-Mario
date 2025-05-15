/********************************************************************************
** Form generated from reading UI file 'shop.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOP_H
#define UI_SHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shop
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *coinCount;
    QLabel *label_3;
    QLabel *healthCount;
    QPushButton *extraLifeButton;
    QLabel *label_4;

    void setupUi(QWidget *Shop)
    {
        if (Shop->objectName().isEmpty())
            Shop->setObjectName("Shop");
        Shop->resize(555, 511);
        label = new QLabel(Shop);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 30, 361, 51));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        label_2 = new QLabel(Shop);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 100, 51, 16));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        coinCount = new QLabel(Shop);
        coinCount->setObjectName("coinCount");
        coinCount->setGeometry(QRect(80, 100, 58, 16));
        QFont font2;
        font2.setPointSize(18);
        coinCount->setFont(font2);
        label_3 = new QLabel(Shop);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 130, 61, 16));
        label_3->setFont(font1);
        healthCount = new QLabel(Shop);
        healthCount->setObjectName("healthCount");
        healthCount->setGeometry(QRect(80, 130, 58, 16));
        healthCount->setFont(font2);
        extraLifeButton = new QPushButton(Shop);
        extraLifeButton->setObjectName("extraLifeButton");
        extraLifeButton->setGeometry(QRect(20, 330, 101, 31));
        label_4 = new QLabel(Shop);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 200, 141, 141));
        label_4->setSizeIncrement(QSize(90, 6));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/Resources/images/marioHeart.png")));
        label_4->setScaledContents(true);

        retranslateUi(Shop);

        QMetaObject::connectSlotsByName(Shop);
    } // setupUi

    void retranslateUi(QWidget *Shop)
    {
        Shop->setWindowTitle(QCoreApplication::translate("Shop", "Form", nullptr));
        label->setText(QCoreApplication::translate("Shop", "Welcome To Mario's Shop!", nullptr));
        label_2->setText(QCoreApplication::translate("Shop", "Coins:", nullptr));
        coinCount->setText(QCoreApplication::translate("Shop", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Shop", "Health:", nullptr));
        healthCount->setText(QCoreApplication::translate("Shop", "TextLabel", nullptr));
        extraLifeButton->setText(QCoreApplication::translate("Shop", "Extra Life", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Shop: public Ui_Shop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOP_H
