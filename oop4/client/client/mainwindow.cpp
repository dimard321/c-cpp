#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Полином 2 степени");
    QWidget *find= this->findChild<QWidget*>("widget");
    find->setVisible(false);
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

void MainWindow::on_ok_btn_clicked()
{
    QLabel* label=this->findChild<QLabel*>("coeff_text");
    label->setAlignment(Qt::AlignCenter);
    QWidget *find= this->findChild<QWidget*>("widget");
    if(ui->ch_double->isChecked() || ui->ch_complex->isChecked()){
        find->setVisible(true);
        if(ui->ch_double->isChecked()){
            ui->coeff_text->setText("Введите вещественные коэффициенты полинома");
        }
        if (ui->ch_complex->isChecked()) {
            ui->coeff_text->setText("Введите комплексные коэффициенты полинома");
        }

    }
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

void MainWindow::sndMsg(stringstream &ss){
    QString str=QString::fromStdString(ss.str());
    QByteArray buffer;
    buffer.resize(socketClient->pendingDatagramSize());
    QHostAddress senderClient;
    buffer=str.toUtf8();
    if(socketClient->writeDatagram(buffer.data(),QHostAddress::LocalHost,6666)){
        qDebug()<<"write coeffs to server: OK";
    }
}

void MainWindow::on_root_btn_clicked()
{
    stringstream ss;
    if(ui->ch_double->isChecked()){
        double a = ui->a_txt->text().toDouble();
        double b = ui->b_txt->text().toDouble();
        double c = ui->c_txt->text().toDouble();
        ss<<"1"<<"|"<<"d"<<"|";
        ss<<a<<"|"<<b<<"|"<<c<<"|";
    }
    if(ui->ch_complex->isChecked()){
        complex a,b,c;
        QString a_str = ui->a_txt->text();
        a=Complex(a_str);
        QString b_str = ui->b_txt->text();
        b=Complex(b_str);
        QString c_str = ui->c_txt->text();
        c=Complex(c_str);
        ss<<"1"<<"|"<<"c"<<"|";
        ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
    }
    sndMsg(ss);
}



void MainWindow::on_polinom_btn_clicked()
{
    stringstream ss;
    if(ui->ch_double->isChecked()){
        double a = ui->a_txt->text().toDouble();
        double b = ui->b_txt->text().toDouble();
        double c = ui->c_txt->text().toDouble();
        ss<<"2"<<"|"<<"d"<<"|";
        ss<<a<<"|"<<b<<"|"<<c<<"|";
    }
    if(ui->ch_complex->isChecked()){
        complex a,b,c;
        QString a_str = ui->a_txt->text();
        a=Complex(a_str);
        QString b_str = ui->b_txt->text();
        b=Complex(b_str);
        QString c_str = ui->c_txt->text();
        c=Complex(c_str);
        ss<<"2"<<"|"<<"c"<<"|";
        ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
    }
    sndMsg(ss);
}



void MainWindow::on_value_btn_clicked()
{
    stringstream ss;
    if(ui->ch_complex->isChecked()){
        complex a,b,c,x;
        QString a_str = ui->a_txt->text();
        a=Complex(a_str);
        QString b_str = ui->b_txt->text();
        b=Complex(b_str);
        QString c_str = ui->c_txt->text();
        c=Complex(c_str);
        ss<<"3"<<"|"<<"c"<<"|";
        ss<<a.Re()<<"|"<<a.Im()<<"|"<<b.Re()<<"|"<<b.Im()<<"|"<<c.Re()<<"|"<<c.Im()<<"|";
        QString x_str = ui->x_txt->text();
        x=Complex(x_str);
        ss<<x.Re()<<"|"<<x.Im()<<"|";
    }
    if(ui->ch_double->isChecked()){
        double a = ui->a_txt->text().toDouble();
        double b = ui->b_txt->text().toDouble();
        double c = ui->c_txt->text().toDouble();
        double x = ui->x_txt->text().toDouble();
        ss<<"3"<<"|"<<"d"<<"|";
        ss<<a<<"|"<<b<<"|"<<c<<"|"<<x<<"|";
    }
    sndMsg(ss);
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
