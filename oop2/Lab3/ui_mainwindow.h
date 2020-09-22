/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *CloseProgramm;
    QLabel *coeff_text;
    QLineEdit *a_txt;
    QLineEdit *b_txt;
    QLineEdit *c_txt;
    QLabel *a;
    QLabel *c;
    QLabel *b;
    QPushButton *root_btn;
    QPushButton *polinom_btn;
    QPushButton *value_btn;
    QLabel *value_text;
    QLabel *x_text;
    QLineEdit *x_txt;
    QLineEdit *value_txt;
    QLineEdit *root_txt;
    QLineEdit *polinom_txt;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(450, 330);
        MainWindow->setMinimumSize(QSize(450, 330));
        MainWindow->setMaximumSize(QSize(450, 330));
        MainWindow->setCursor(QCursor(Qt::PointingHandCursor));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CloseProgramm = new QPushButton(centralWidget);
        CloseProgramm->setObjectName(QString::fromUtf8("CloseProgramm"));
        CloseProgramm->setGeometry(QRect(20, 240, 421, 41));
        QFont font;
        font.setPointSize(12);
        CloseProgramm->setFont(font);
        coeff_text = new QLabel(centralWidget);
        coeff_text->setObjectName(QString::fromUtf8("coeff_text"));
        coeff_text->setGeometry(QRect(80, 0, 291, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        coeff_text->setFont(font1);
        a_txt = new QLineEdit(centralWidget);
        a_txt->setObjectName(QString::fromUtf8("a_txt"));
        a_txt->setGeometry(QRect(150, 30, 151, 21));
        b_txt = new QLineEdit(centralWidget);
        b_txt->setObjectName(QString::fromUtf8("b_txt"));
        b_txt->setGeometry(QRect(150, 60, 151, 21));
        c_txt = new QLineEdit(centralWidget);
        c_txt->setObjectName(QString::fromUtf8("c_txt"));
        c_txt->setGeometry(QRect(150, 90, 151, 21));
        a = new QLabel(centralWidget);
        a->setObjectName(QString::fromUtf8("a"));
        a->setGeometry(QRect(130, 30, 21, 21));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        a->setFont(font2);
        c = new QLabel(centralWidget);
        c->setObjectName(QString::fromUtf8("c"));
        c->setGeometry(QRect(130, 90, 21, 21));
        c->setFont(font2);
        b = new QLabel(centralWidget);
        b->setObjectName(QString::fromUtf8("b"));
        b->setGeometry(QRect(130, 60, 21, 21));
        b->setFont(font2);
        root_btn = new QPushButton(centralWidget);
        root_btn->setObjectName(QString::fromUtf8("root_btn"));
        root_btn->setGeometry(QRect(20, 130, 91, 21));
        polinom_btn = new QPushButton(centralWidget);
        polinom_btn->setObjectName(QString::fromUtf8("polinom_btn"));
        polinom_btn->setGeometry(QRect(20, 160, 91, 21));
        value_btn = new QPushButton(centralWidget);
        value_btn->setObjectName(QString::fromUtf8("value_btn"));
        value_btn->setGeometry(QRect(130, 210, 80, 21));
        value_text = new QLabel(centralWidget);
        value_text->setObjectName(QString::fromUtf8("value_text"));
        value_text->setGeometry(QRect(70, 190, 321, 20));
        value_text->setFont(font1);
        x_text = new QLabel(centralWidget);
        x_text->setObjectName(QString::fromUtf8("x_text"));
        x_text->setGeometry(QRect(30, 210, 21, 20));
        QFont font3;
        font3.setPointSize(10);
        x_text->setFont(font3);
        x_txt = new QLineEdit(centralWidget);
        x_txt->setObjectName(QString::fromUtf8("x_txt"));
        x_txt->setGeometry(QRect(50, 210, 71, 21));
        value_txt = new QLineEdit(centralWidget);
        value_txt->setObjectName(QString::fromUtf8("value_txt"));
        value_txt->setGeometry(QRect(220, 210, 221, 21));
        root_txt = new QLineEdit(centralWidget);
        root_txt->setObjectName(QString::fromUtf8("root_txt"));
        root_txt->setEnabled(true);
        root_txt->setGeometry(QRect(120, 130, 321, 21));
        polinom_txt = new QLineEdit(centralWidget);
        polinom_txt->setObjectName(QString::fromUtf8("polinom_txt"));
        polinom_txt->setGeometry(QRect(120, 160, 321, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 450, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);
        QObject::connect(CloseProgramm, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        CloseProgramm->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203", nullptr));
        coeff_text->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260", nullptr));
        a->setText(QCoreApplication::translate("MainWindow", "a", nullptr));
        c->setText(QCoreApplication::translate("MainWindow", "c", nullptr));
        b->setText(QCoreApplication::translate("MainWindow", "b", nullptr));
        root_btn->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\320\275\320\270 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260", nullptr));
        polinom_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\270\320\275\320\276\320\274", nullptr));
        value_btn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        value_text->setText(QCoreApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260 \320\262 \320\267\320\260\320\264\320\260\320\275\320\275\320\276\320\271 \321\202\320\276\321\207\320\272\320\265", nullptr));
        x_text->setText(QCoreApplication::translate("MainWindow", "x=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
