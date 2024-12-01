/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *heures;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *demarrer;
    QLabel *label_5;
    QWidget *chartContainer;
    QLabel *label_6;
    QLabel *sauvegarde;
    QWidget *widget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *widget_RAM;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_RAM;
    QWidget *widget_LA;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_LA;
    QWidget *widget_Proc;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_Proc;
    QWidget *widget_rapport;
    QPlainTextEdit *rapport;
    QWidget *widget_diagram;
    QPlainTextEdit *diagram;
    QLabel *algo;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1530, 820);
        MainWindow->setMinimumSize(QSize(1530, 820));
        MainWindow->setMaximumSize(QSize(1530, 820));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaylistShuffle));
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(1.000000000000000);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 100, 331, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        heures = new QLabel(centralwidget);
        heures->setObjectName("heures");
        heures->setGeometry(QRect(780, 0, 101, 41));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        heures->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 250, 181, 31));
        label_2->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(200, 420, 301, 31));
        label_3->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1000, 260, 241, 31));
        label_4->setFont(font);
        demarrer = new QPushButton(centralwidget);
        demarrer->setObjectName("demarrer");
        demarrer->setGeometry(QRect(200, 18, 271, 61));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        demarrer->setFont(font2);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(900, 390, 441, 31));
        label_5->setFont(font);
        chartContainer = new QWidget(centralwidget);
        chartContainer->setObjectName("chartContainer");
        chartContainer->setGeometry(QRect(820, 60, 651, 201));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(930, 20, 401, 31));
        label_6->setFont(font);
        sauvegarde = new QLabel(centralwidget);
        sauvegarde->setObjectName("sauvegarde");
        sauvegarde->setGeometry(QRect(370, 290, 261, 31));
        sauvegarde->setFont(font);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 140, 691, 81));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 691, 81));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_RAM = new QWidget(centralwidget);
        widget_RAM->setObjectName("widget_RAM");
        widget_RAM->setGeometry(QRect(19, 330, 701, 81));
        gridLayoutWidget_2 = new QWidget(widget_RAM);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 691, 81));
        gridLayout_RAM = new QGridLayout(gridLayoutWidget_2);
        gridLayout_RAM->setObjectName("gridLayout_RAM");
        gridLayout_RAM->setContentsMargins(0, 0, 0, 0);
        widget_LA = new QWidget(centralwidget);
        widget_LA->setObjectName("widget_LA");
        widget_LA->setGeometry(QRect(20, 460, 701, 221));
        gridLayoutWidget_3 = new QWidget(widget_LA);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(0, 0, 691, 221));
        gridLayout_LA = new QGridLayout(gridLayoutWidget_3);
        gridLayout_LA->setObjectName("gridLayout_LA");
        gridLayout_LA->setContentsMargins(0, 0, 0, 0);
        widget_Proc = new QWidget(centralwidget);
        widget_Proc->setObjectName("widget_Proc");
        widget_Proc->setGeometry(QRect(760, 300, 711, 81));
        gridLayoutWidget_4 = new QWidget(widget_Proc);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(10, 0, 691, 81));
        gridLayout_Proc = new QGridLayout(gridLayoutWidget_4);
        gridLayout_Proc->setObjectName("gridLayout_Proc");
        gridLayout_Proc->setContentsMargins(0, 0, 0, 0);
        widget_rapport = new QWidget(centralwidget);
        widget_rapport->setObjectName("widget_rapport");
        widget_rapport->setGeometry(QRect(760, 430, 721, 191));
        rapport = new QPlainTextEdit(widget_rapport);
        rapport->setObjectName("rapport");
        rapport->setGeometry(QRect(10, 0, 701, 191));
        widget_diagram = new QWidget(centralwidget);
        widget_diagram->setObjectName("widget_diagram");
        widget_diagram->setGeometry(QRect(760, 630, 721, 51));
        diagram = new QPlainTextEdit(widget_diagram);
        diagram->setObjectName("diagram");
        diagram->setGeometry(QRect(10, 0, 701, 51));
        algo = new QLabel(centralwidget);
        algo->setObjectName("algo");
        algo->setGeometry(QRect(40, 290, 261, 31));
        algo->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(330, 290, 21, 31));
        label_7->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1530, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setMinimumSize(QSize(1366, 108));
        statusbar->setMaximumSize(QSize(1366, 1080));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simulation de la planification des processus", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Processus lanc\303\251s par l'utilisateur", nullptr));
        heures->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Visuel sur la RAM", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Visuel sur la LISTE D'ATTENTE", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Visuel sur le Processeur", nullptr));
        demarrer->setText(QCoreApplication::translate("MainWindow", "D\303\251marrer la simulation", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Rapport en temps r\303\251el pendant l'\303\251xecution", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Utilisation de la m\303\251moire en temps r\303\251el", nullptr));
        sauvegarde->setText(QString());
        algo->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "&", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
