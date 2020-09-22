#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circle.h"
#include "square.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lab8");
    ui->wSpinBox->setValue(10);
    ui->hSpinBox->setValue(10);
    ui->aSpinBox->setValue(1);
    ui->bSpinBox->setValue(1);
    ui->jSpinBox->setValue(1);
    ui->iSpinBox->setValue(1);
    ui->xSpinBox->setValue(1);
    ui->ySpinBox->setValue(1);
    scene = new QGraphicsScene(-300,-300, 600,600, nullptr);
    scene->addLine(-300, 0, 300, 0, QPen(Qt::black));
    scene->addLine(0, -300, 0, 300, QPen(Qt::black));
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    scene->clear();
    scene->addLine(-300, 0, 300, 0, QPen(Qt::black));
    scene->addLine(0, -300, 0, 300, QPen(Qt::black));
    qreal result =0;
    figure *fig=nullptr;
    qreal a= ui->aSpinBox->text().toDouble();
    qreal b= ui->bSpinBox->text().toDouble();
    qreal w= ui->wSpinBox->text().toDouble();
    qreal h= ui->hSpinBox->text().toDouble();
    qreal i= ui->iSpinBox->text().toDouble();
    qreal j= ui->jSpinBox->text().toDouble();
    qreal x= ui->xSpinBox->text().toDouble();
    qreal y= ui->ySpinBox->text().toDouble();
    target target(w, h);

    if (i*j==0)
    {
        QMessageBox::critical(this, "ERROR", "Количество узлов не может быть равно 0!");
        return;
    }


    if(ui->ellipsRadioButton->isChecked()){
        ellipse ellipseFig(a,b,x,y);
        scene->addEllipse(x-a/2, (-y-b/2), a, b,QPen(Qt::red));
        fig=&ellipseFig;
    }
    else if (ui->circleRadioButton->isChecked()) {
        circle circleFig(a,x,y);
        scene->addEllipse(x-a/2, (-y-a/2), a, a,QPen(Qt::red));
        fig = &circleFig;
    }
    else if(ui->rectangleRadioButton->isChecked()){
        rectangle rectFig(a,b,x,y);
        scene->addRect(x-a/2, (-y-a/2),a,b,QPen(Qt::red));
        fig=&rectFig;
    }
    else if (ui->squareRadioButton->isChecked()) {
        square squareFig(a,x,y);
        scene->addRect(x-a/2, (-y-a/2), a, a,QPen(Qt::red));
        fig = &squareFig;
    }
    else {
        QMessageBox::warning(this, "ERROR", "Выберите тип фигуры");
        return;
    }

    QRect Target(-w/2, -h/2, w, h);
    scene->addRect(Target, QPen(Qt::green));

    if(ui->randomRadioButton->isChecked()){
        result=target.attitudeNew(i,j,fig,1); //1=random
    }
    else if (ui->regularRadioButton->isChecked()) {
        result=target.attitudeNew(i,j,fig,0);  //0=regular
    }
    else{
        QMessageBox::warning(this, "ERROR", "Выберите способ рассчета");
        return;
    }
    ui->ansLineEdit->setText(QString::number(result,'g',5));
}


void MainWindow::on_squareRadioButton_clicked()
{
    ui->bSpinBox->setEnabled(false);
}


void MainWindow::on_ellipsRadioButton_clicked()
{
    ui->bSpinBox->setEnabled(true);
}

void MainWindow::on_circleRadioButton_clicked()
{
    ui->bSpinBox->setEnabled(false);
}

void MainWindow::on_rectangleRadioButton_clicked()
{
    ui->bSpinBox->setEnabled(true);
}
