#include "ui_mainwindow.h"
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Полином 2 степени");
}

MainWindow::~MainWindow()
{
    delete ui;
}
number Complex(QString data){
    number com;
    QRegExp rx("[\\+\\-]?\\d+(\\.\\d+)?i?");
    QStringList list;
    int pos=0;
    while ((pos = rx.indexIn(data, pos)) != -1) {
    list << rx.cap(0);
    pos += rx.matchedLength();
    }
    if(list.count()==2){
        list[1].replace('i',"");
        com=complex(list[0].toDouble(),list[1].toDouble());
    }
    else if(list.count()==1){
        if(list[0].contains('i'))
        {
            list[0].replace('i',"");
            com=complex(0,list[0].toDouble());
        }
        else {
            com=complex(list[0].toDouble(),0);
        }
    }
    else {
        com=complex(0,0);
    }
    return com;
}

void MainWindow::on_root_btn_clicked()
{
    number a,b,c;
    number x[2];
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    polinom p(a,b,c);
    int n = p.roots(x);
    switch(n)
    {
        case 1:
            ui->root_txt->setText("x1=x2="+x[0].toString());
            break;
        case 2:
            ui->root_txt->setText("x1="+x[0].toString()+" x2="+x[1].toString());
            break;
    }
}

void MainWindow::on_polinom_btn_clicked()
{
    number a,b,c;
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    polinom p(a,b,c);
    ui->polinom_txt->setText(p.text());
}

void MainWindow::on_value_btn_clicked()
{
    number a,b,c;
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    polinom p(a,b,c);
    number x;
    QString x_str = ui->x_txt->text();
    x=Complex(x_str);
    x=p.value(x);
    ui->value_txt->setText(x.toString());
}
