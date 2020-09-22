#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <QCoreApplication>
#include <QUdpSocket>
#include <QHostAddress>
#include "complex.h"
#include "polinom.h"
class calculation: public QObject
{
    Q_OBJECT
public:
    explicit calculation(QObject *parent =0);
public slots:
    void ReciveMessage();
private:
    void sendMsg(stringstream &ss);
    QUdpSocket *socketServer;
    QUdpSocket *socketServerRecive;
    QHostAddress Host;
};

#endif // TAPPLICATION_H
