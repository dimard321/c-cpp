#include "calculation.h"
#include <iostream>
#include <string>
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

        char ch_type=rec_msg[2];
        complex a,b,c;
        double _a=0,_b=0,_c=0;
        switch(ch_type){
            case 'd':{
                _a=atof(results[1].c_str());
                _b=atof(results[2].c_str());
                _c=atof(results[3].c_str());
                break;
            }
            case 'c':{
                a=complex(atof(results[1].c_str()),atof(results[2].c_str()));
                b=complex(atof(results[3].c_str()),atof(results[4].c_str()));
                c=complex(atof(results[5].c_str()),atof(results[6].c_str()));
                break;
            }
        }
        char choose=rec_msg[0];
        stringstream ss;
        switch(choose){
        case '1':{
            switch(ch_type){
            case 'd':{
                double x[2];
                polinom <double> p(_a,_b,_c);
                int n = p.roots(x);
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
                    case 3:
                        cout<<"1:"<<"no roots"<<endl;
                        ss<<"1:"<<"no roots";
                }
                break;
                }
            case 'c':{
                complex x[2];
                polinom <complex> p(a,b,c);
                int n = p.roots(x);
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
                break;
                }
            }
            sendMsg(ss);
            break;
        }
        case '2': {
          switch(ch_type){
            case 'd':{
                polinom <double> p(_a,_b,_c);
                cout<<"Polynom: "<<p;
                ss<<"2:"<<p;
                break;
                }
            case 'c':{
                polinom <complex> p(a,b,c);
                cout<<"Polynom: "<<p;
                ss<<"2:"<<p;
                break;
                }
            }
            sendMsg(ss);
            break;
        }
        case '3': {
            switch(ch_type){
            case 'd':{
                polinom <double> p(_a,_b,_c);
                double x =atof(results[4].c_str());
                x=p.value(x);
                cout<<"Value in point"<<x<<endl;
                ss<<"3:"<<x;
                break;
                }
            case 'c':{
                polinom <complex> p(a,b,c);
                complex x=complex(atof(results[7].c_str()),atof(results[8].c_str()));
                x=p.value(x);
                cout<<"Value in point"<<x<<endl;
                ss<<"3:"<<x;
                break;
                }
            }
            sendMsg(ss);
            break;
        }
      }
    }
}

void calculation::sendMsg(stringstream &ss){
    QByteArray buffer;
    QHostAddress senderClient;
    QString str =QString::fromStdString(ss.str());
    buffer.resize(socketServer->pendingDatagramSize());
    buffer=str.toUtf8();
    if(socketServer->writeDatagram(buffer.data(),QHostAddress::LocalHost,5555)){
        cout<<"write message to client: OK"<<endl;
    }
}

