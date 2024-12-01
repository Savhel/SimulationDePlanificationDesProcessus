/********************************************************************************
** Form generated from reading UI file 'modal.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODAL_H
#define UI_MODAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parametre
{
public:
    QLabel *label;
    QPushButton *creerProcess;
    QPushButton *useProcess;
    QWidget *widget;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QWidget *widget_2;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_6;

    void setupUi(QDialog *parametre)
    {
        if (parametre->objectName().isEmpty())
            parametre->setObjectName("parametre");
        parametre->resize(526, 400);
        parametre->setMinimumSize(QSize(526, 400));
        parametre->setMaximumSize(QSize(526, 400));
        label = new QLabel(parametre);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 40, 391, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);
        creerProcess = new QPushButton(parametre);
        creerProcess->setObjectName("creerProcess");
        creerProcess->setGeometry(QRect(30, 310, 211, 41));
        QFont font1;
        font1.setBold(true);
        creerProcess->setFont(font1);
        useProcess = new QPushButton(parametre);
        useProcess->setObjectName("useProcess");
        useProcess->setGeometry(QRect(280, 310, 211, 41));
        useProcess->setFont(font1);
        widget = new QWidget(parametre);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 80, 271, 221));
        radioButton_5 = new QRadioButton(widget);
        radioButton_5->setObjectName("radioButton_5");
        radioButton_5->setGeometry(QRect(30, 180, 211, 26));
        radioButton_5->setFont(font);
        radioButton_5->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(30, 90, 112, 26));
        radioButton_2->setFont(font);
        radioButton_2->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(30, 60, 112, 26));
        radioButton->setFont(font);
        radioButton->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton_3 = new QRadioButton(widget);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(30, 120, 181, 26));
        radioButton_3->setFont(font);
        radioButton_3->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton_4 = new QRadioButton(widget);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(30, 150, 112, 26));
        radioButton_4->setFont(font);
        radioButton_4->setStyleSheet(QString::fromUtf8("color:gray;"));
        widget_2 = new QWidget(parametre);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(290, 80, 221, 221));
        radioButton_8 = new QRadioButton(widget_2);
        radioButton_8->setObjectName("radioButton_8");
        radioButton_8->setGeometry(QRect(41, 150, 161, 26));
        radioButton_8->setFont(font);
        radioButton_8->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton_7 = new QRadioButton(widget_2);
        radioButton_7->setObjectName("radioButton_7");
        radioButton_7->setGeometry(QRect(40, 100, 151, 26));
        radioButton_7->setFont(font);
        radioButton_7->setStyleSheet(QString::fromUtf8("color:gray;"));
        radioButton_6 = new QRadioButton(widget_2);
        radioButton_6->setObjectName("radioButton_6");
        radioButton_6->setGeometry(QRect(41, 60, 161, 26));
        radioButton_6->setFont(font);
        radioButton_6->setStyleSheet(QString::fromUtf8("color:gray;"));

        retranslateUi(parametre);

        QMetaObject::connectSlotsByName(parametre);
    } // setupUi

    void retranslateUi(QDialog *parametre)
    {
        parametre->setWindowTitle(QCoreApplication::translate("parametre", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("parametre", "PARAMETRES DE L'APPLICATION", nullptr));
        creerProcess->setText(QCoreApplication::translate("parametre", "Creer(recr\303\251er) les processus", nullptr));
        useProcess->setText(QCoreApplication::translate("parametre", "Utiliser les processus", nullptr));
        radioButton_5->setText(QCoreApplication::translate("parametre", "RR avec priorit\303\251", nullptr));
        radioButton_2->setText(QCoreApplication::translate("parametre", "SJF", nullptr));
        radioButton->setText(QCoreApplication::translate("parametre", "FCFS", nullptr));
        radioButton_3->setText(QCoreApplication::translate("parametre", "Round Robin", nullptr));
        radioButton_4->setText(QCoreApplication::translate("parametre", "SRTF", nullptr));
        radioButton_8->setText(QCoreApplication::translate("parametre", "WORST FIT", nullptr));
        radioButton_7->setText(QCoreApplication::translate("parametre", "BEST FIT", nullptr));
        radioButton_6->setText(QCoreApplication::translate("parametre", "FIRST FIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class parametre: public Ui_parametre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODAL_H
