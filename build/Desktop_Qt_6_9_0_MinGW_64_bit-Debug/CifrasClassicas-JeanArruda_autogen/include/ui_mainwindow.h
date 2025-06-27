/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboCifras;
    QLabel *label;
    QLineEdit *entradaTexto;
    QLabel *label_2;
    QLineEdit *entradaChave;
    QPushButton *btnCifrar;
    QPushButton *btnDecifrar;
    QLabel *resultadoLabel;
    QLabel *labelChave;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *labelAviso;
    QLineEdit *entradaChave2;
    QLabel *labelChave2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboCifras = new QComboBox(centralwidget);
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->addItem(QString());
        comboCifras->setObjectName("comboCifras");
        comboCifras->setGeometry(QRect(320, 100, 141, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 150, 161, 16));
        entradaTexto = new QLineEdit(centralwidget);
        entradaTexto->setObjectName("entradaTexto");
        entradaTexto->setGeometry(QRect(300, 170, 231, 101));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(300, 280, 131, 16));
        entradaChave = new QLineEdit(centralwidget);
        entradaChave->setObjectName("entradaChave");
        entradaChave->setGeometry(QRect(300, 320, 231, 31));
        btnCifrar = new QPushButton(centralwidget);
        btnCifrar->setObjectName("btnCifrar");
        btnCifrar->setGeometry(QRect(300, 410, 80, 24));
        btnDecifrar = new QPushButton(centralwidget);
        btnDecifrar->setObjectName("btnDecifrar");
        btnDecifrar->setGeometry(QRect(440, 410, 80, 24));
        resultadoLabel = new QLabel(centralwidget);
        resultadoLabel->setObjectName("resultadoLabel");
        resultadoLabel->setGeometry(QRect(80, 440, 671, 121));
        labelChave = new QLabel(centralwidget);
        labelChave->setObjectName("labelChave");
        labelChave->setGeometry(QRect(300, 300, 271, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 40, 131, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 80, 151, 20));
        labelAviso = new QLabel(centralwidget);
        labelAviso->setObjectName("labelAviso");
        labelAviso->setGeometry(QRect(130, 430, 611, 41));
        entradaChave2 = new QLineEdit(centralwidget);
        entradaChave2->setObjectName("entradaChave2");
        entradaChave2->setEnabled(true);
        entradaChave2->setGeometry(QRect(300, 370, 231, 31));
        labelChave2 = new QLabel(centralwidget);
        labelChave2->setObjectName("labelChave2");
        labelChave2->setEnabled(true);
        labelChave2->setGeometry(QRect(300, 350, 181, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboCifras->setItemText(0, QCoreApplication::translate("MainWindow", "C\303\251sar", nullptr));
        comboCifras->setItemText(1, QCoreApplication::translate("MainWindow", "Monoalfab\303\251tica", nullptr));
        comboCifras->setItemText(2, QCoreApplication::translate("MainWindow", "Playfair", nullptr));
        comboCifras->setItemText(3, QCoreApplication::translate("MainWindow", "Hill (2x2)", nullptr));
        comboCifras->setItemText(4, QCoreApplication::translate("MainWindow", "Vigenere", nullptr));
        comboCifras->setItemText(5, QCoreApplication::translate("MainWindow", "Vernam", nullptr));
        comboCifras->setItemText(6, QCoreApplication::translate("MainWindow", "One-Time Pad", nullptr));
        comboCifras->setItemText(7, QCoreApplication::translate("MainWindow", "Transposi\303\247\303\243o (Rail Fence)", nullptr));
        comboCifras->setItemText(8, QCoreApplication::translate("MainWindow", "Transposi\303\247\303\243o por Colunas", nullptr));
        comboCifras->setItemText(9, QCoreApplication::translate("MainWindow", "Dupla Transposi\303\247\303\243o", nullptr));
        comboCifras->setItemText(10, QCoreApplication::translate("MainWindow", "Cifra - Jean Arruda", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "Digite o seu texto:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Digite a chave:", nullptr));
        btnCifrar->setText(QCoreApplication::translate("MainWindow", "Cifrar", nullptr));
        btnDecifrar->setText(QCoreApplication::translate("MainWindow", "Decifrar", nullptr));
        resultadoLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Resultado:</p></body></html>", nullptr));
        labelChave->setText(QCoreApplication::translate("MainWindow", "Selecione o tipo de Cifra", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "AS CIFRAS CLASSICAS", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Selecione a Cifra desejada:", nullptr));
        labelAviso->setText(QString());
        labelChave2->setText(QCoreApplication::translate("MainWindow", "Digite a Segunda Chave:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
