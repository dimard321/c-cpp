#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <QDebug>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socketClient = new QUdpSocket(this);
    socketClientRecive = new QUdpSocket(this);
    if(socketClientRecive->bind(QHostAddress::LocalHost,5555)){
         qDebug()<<"bind on client: OK";
    }
    connect(socketClientRecive,SIGNAL(readyRead()),this,SLOT(recMsg()));
    connect(this->ui->CloseProgramm, SIGNAL(clicked()), this, SLOT(close()));

    ui->root_txt->setEnabled(false);
    ui->polinom_txt->setEnabled(false);
    ui->value_txt->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

complex Complex(QString data){
    complex com;
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
    complex a,b,c;
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    stringstream ss;
    ss<<"1:";
    ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
    QString str=QString::fromStdString(ss.str());
    QByteArray buffer;
    buffer.resize(socketClient->pendingDatagramSize());
    QHostAddress senderClient;
    buffer=str.toUtf8();
    if(socketClient->writeDatagram(buffer.data(),QHostAddress::LocalHost,6666)){
        qDebug()<<"write coeffs to server: OK";
    }
}

void MainWindow::on_polinom_btn_clicked()
{
    complex a,b,c;
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    stringstream ss;
    ss<<"2:";
    ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
    QString str=QString::fromStdString(ss.str());
    QByteArray buffer;
    buffer.resize(socketClient->pendingDatagramSize());
    QHostAddress senderClient;
    buffer=str.toUtf8();
    if(socketClient->writeDatagram(buffer.data(),QHostAddress::LocalHost,6666)){
        qDebug()<<"write coeffs to server: OK";
    }
}

void MainWindow::on_value_btn_clicked()
{
    complex a,b,c,x;
    QString a_str = ui->a_txt->text();
    a=Complex(a_str);
    QString b_str = ui->b_txt->text();
    b=Complex(b_str);
    QString c_str = ui->c_txt->text();
    c=Complex(c_str);
    stringstream ss;
    ss<<"3:";
    ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
    QString x_str = ui->x_txt->text();
    x=Complex(x_str);
    ss<<x.Re()<<"|"<<x.Im()<<"|";
    QString str=QString::fromStdString(ss.str());
    QByteArray buffer;
    buffer.resize(socketClient->pendingDatagramSize());
    QHostAddress senderClient;
    buffer=str.toUtf8();
    if(socketClient->writeDatagram(buffer.data(),QHostAddress::LocalHost,6666)){
        qDebug()<<"write coeffs to server: OK";
    }
}

void MainWindow::recMsg()
{
    while(socketClientRecive->hasPendingDatagrams()){
        QByteArray buffer;
        buffer.resize(socketClientRecive->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        if(socketClientRecive->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort)){
            qDebug()<<"read on client: OK";
        }
        QString qq(buffer.data());
        int len = qq.length();
        string rec_msg=qq.toStdString();
        char choose=rec_msg[0];
        switch(choose){
            case '1':{
                ui->root_txt->setText(qq.right(len-2));
                break;
            }
            case '2':{
                ui->polinom_txt->setText(qq.right(len-2));
                break;
            }
            case '3':{
                ui->value_txt->setText(qq.right(len-2));
                break;
            }
        }
    }
}
