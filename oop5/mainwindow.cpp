#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawer.h"

#include <QPainter>
#include <QPolygon>
#include <math.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(700,700);

    scene = new QGraphicsScene;

    ui->graphicsView->setScene(scene);

    scene->setSceneRect(-300, -300, 600, 600);
    scene->addLine(-300, 0, 300, 0, QPen(Qt::black));
    scene->addLine(0, -300, 0, 300, QPen(Qt::black));
    ui->aLineEdit->setEnabled(false);
    ui->bLineEdit->setEnabled(false);
    ui->cLineEdit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_rbTriangleRadioButton_clicked()
{
    ui->aLineEdit->setEnabled(true);
    ui->bLineEdit->setEnabled(true);
    ui->cLineEdit->setEnabled(false);
    isRB = true;
}

void MainWindow::on_rsTriangleRadioButton_clicked()
{
    ui->aLineEdit->setEnabled(true);
    ui->bLineEdit->setEnabled(false);
    ui->cLineEdit->setEnabled(false);
    isRS = true;
}

void MainWindow::on_triangleRadioButton_clicked()
{
    ui->aLineEdit->setEnabled(true);
    ui->bLineEdit->setEnabled(true);
    ui->cLineEdit->setEnabled(true);
    isAny=true;
}

void MainWindow::on_drawButton_clicked()
{
    scene->clear();
    scene->setSceneRect(-300, -300, 600, 600);
    scene->addLine(-300, 0, 300, 0, QPen(Qt::black));
    scene->addLine(0, -300, 0, 300, QPen(Qt::black));
    qreal a=0, b=0, c=0;
    qreal x = ui->xLineEdit->text().toDouble();
    qreal y = ui->yLineEdit->text().toDouble();
    if (ui->rsTriangleRadioButton->isChecked()){
        a = ui->aLineEdit->text().toDouble();
        b = a;
        c = a;
        isRB = false;
        isAny=false;
    }
    else if(ui->rbTriangleRadioButton->isChecked()){
        a = ui->aLineEdit->text().toDouble();
        b = ui->bLineEdit->text().toDouble();
        c = a;
        isRS = false;
        isAny=false;
    }
    else if(ui->triangleRadioButton->isChecked()){
        a = ui->aLineEdit->text().toDouble();
        b = ui->bLineEdit->text().toDouble();
        c = ui->cLineEdit->text().toDouble();
        isRB = false;
        isRS=false;
    }
    drawer draw(isRB,isRS,isAny);
    if (a >= b + c || b >= a + c || c >= a + b)
    {
        QMessageBox::critical(this, "Error", "Треугольника с такими сторонами не существует");
        return;
    }
    if (x > 250 || x < -250)
        QMessageBox::warning(this, "Warning", "Слишком большое знаение х.");

    if (y > 250 || y < -250)
        QMessageBox::warning(this, "Warning", "Слишком большое знаение y.");
    scene->addPolygon(draw.updateData(x, y, a, b, c));
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_clearButton_clicked()
{
    ui->aLineEdit->setText("0");
    ui->bLineEdit->setText("0");
    ui->cLineEdit->setText("0");
    ui->xLineEdit->setText("0");
    ui->yLineEdit->setText("0");
}
