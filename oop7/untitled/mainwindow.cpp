#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "painter.h"
#include "shape.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабораторная 8");
    ui->pLineEdit->setEnabled(false);
    ui->sEdit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_drawButton_clicked()
{
    Painter* ptr = new Painter();
    QString res_P;
    QString res_S;
    if(ui->parallRadioButton->isChecked()||ui->pryamougRadioButton->isChecked()||ui->trRadioButton->isChecked()||ui->rombRadioButton->isChecked()||ui->kvadratRadioButton->isChecked()){
    if (ui->aLineEdit->text().toDouble()==0){
        QMessageBox::critical(this, "Error", "Введите а");
        return;
    }
    if (ui->bLineEdit->text().toDouble()==0){
        QMessageBox::critical(this, "Error", "Введите b");
        return;
    }
    if (ui->cornerLineEdit->text().toDouble()==0){
        QMessageBox::critical(this, "Error", "Введите corner");
        return;
    }
    if (ui->parallRadioButton->isChecked())
    {
        Parallelogramm* parall = new Parallelogramm(ui->aLineEdit->text().toDouble(), ui->bLineEdit->text().toDouble(), ui->cornerLineEdit->text().toDouble());
        res_P = QString::number(parall->getPerimeter());
        res_S = QString::number(parall->getArea());
        ptr->setFigure(parall);
    }
    if (ui->pryamougRadioButton->isChecked())
    {
        Rectangular* rect = new Rectangular(ui->aLineEdit->text().toDouble(), ui->bLineEdit->text().toDouble());
        res_P = QString::number(rect->getPerimeter());
        res_S = QString::number(rect->getArea());
        ptr->setFigure(rect);
    }
    if (ui->rombRadioButton->isChecked())
    {
        Rhombus* rhomb = new Rhombus(ui->aLineEdit->text().toDouble(), ui->bLineEdit->text().toDouble());
        res_P = QString::number(rhomb->getPerimeter());
        res_S = QString::number(rhomb->getArea());
        ptr->setFigure(rhomb);
    }
    if (ui->kvadratRadioButton->isChecked())
    {
        Square* square = new Square(ui->aLineEdit->text().toDouble());
        res_P = QString::number(square->getPerimeter());
        res_S = QString::number(square->getArea());
        ptr->setFigure(square);
    }
    ui->pLineEdit->setText(res_P);
    ui->sEdit->setText(res_S);
    ptr->show();
    }
}
