#include "calculation.h"
#include <iostream>
#include <string>
#include "complex.h"
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <QDebug>
using namespace std;
calculation::calculation(QObject *parent) :
    QObject(parent)
{
    socketServer=new QUdpSocket(this);
    socketServerRecive = new QUdpSocket(this);
    if(socketServerRecive->bind(QHostAddress::LocalHost,6666)){
        cout<<"bind on server: OK"<<endl;
    }
    connect(socketServerRecive,SIGNAL(readyRead()),this,SLOT(ReciveMessage()));
}

class WordDelimitedByCommas :  public string{};
istream& operator>>(istream& is, WordDelimitedByCommas& output)
{
   std::getline(is, output, '|');
   return is;
}



void calculation::ReciveMessage(){
    while(socketServerRecive->hasPendingDatagrams()){
        QByteArray buffer;
        double coeff[6];
        memset(coeff,0,6);
        buffer.resize(socketServerRecive->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        if(socketServerRecive->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort)){
            cout<<"read on server: OK"<<endl;
        }
        QString qq(buffer.data());
        string rec_msg=qq.toStdString();
        istringstream iss(rec_msg.substr(2));
        vector<string> results((istream_iterator<WordDelimitedByCommas>(iss)),
                                         istream_iterator<WordDelimitedByCommas>());
        for(int i=0;i<6;i++){
            coeff[i]=atof(results[i].c_str());
        }
        complex a,b,c;
        a=complex(coeff[0],coeff[1]);
        b=complex(coeff[2],coeff[3]);
        c=complex(coeff[4],coeff[5]);
        char choose=rec_msg[0];
        switch (choose) {
            case '1':{
                sendRoots(a,b,c);
                break;
            }
            case '2':{
                sendPolynom(a,b,c);
                break;
            }
            case '3':{
                complex x=complex(atof(results[6].c_str()),atof(results[7].c_str()));
                sendValue(a,b,c,x);
                break;
            }
            }
        }
}

void calculation::sendRoots(complex a,complex b, complex c){
    complex x[2];
    polinom p(a,b,c);
    int n = p.roots(x);
    stringstream ss;
    QByteArray buffer;
    QHostAddress senderClient;
    switch(n)
    {
        case 1:
            cout<<"x1=x2="<<x[0]<<endl;
            ss<<"1:"<<"x1=x2= "<<x[0];
            break;
        case 2:
            cout<<"x1= "<<x[0]<<"x2= "<<x[1]<<endl;
            ss<<"1:"<<"x1= "<<x[0]<<"x2= "<<x[1];
            break;
    }
    QString str =QString::fromStdString(ss.str());
    buffer.resize(socketServer->pendingDatagramSize());
    buffer=str.toUtf8();
    if(socketServer->writeDatagram(buffer.data(),QHostAddress::LocalHost,5555)){
        cout<<"write roots to client: OK"<<endl;
    }
}

void calculation::sendPolynom(complex a,complex b, complex c){
    polinom p(a,b,c);
    QString pol =p.text();
    cout<<"Polynom: "<<pol.toUtf8().constData()<<endl;
    stringstream ss;
    QByteArray buffer;
    QHostAddress senderClient;
    ss<<"2:"<<pol.toUtf8().constData();
    QString str =QString::fromStdString(ss.str());
    buffer.resize(socketServer->pendingDatagramSize());
    buffer=str.toUtf8();
    if(socketServer->writeDatagram(buffer.data(),QHostAddress::LocalHost,5555)){
        cout<<"write polynom to client: OK"<<endl;
    }
}

void calculation::sendValue(complex a, complex b, complex c, complex x){
    polinom p(a,b,c);
    x=p.value(x);
    cout<<"Value in point"<<x<<endl;
    stringstream ss;
    QByteArray buffer;
    QHostAddress senderClient;
    ss<<"3:"<<x;
    QString str =QString::fromStdString(ss.str());
    buffer.resize(socketServer->pendingDatagramSize());
    buffer=str.toUtf8();
    if(socketServer->writeDatagram(buffer.data(),QHostAddress::LocalHost,5555)){
        cout<<"write value in point to client: OK"<<endl;
    }
}
