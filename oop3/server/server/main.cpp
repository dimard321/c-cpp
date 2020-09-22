#include <QCoreApplication>
#include "calculation.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    calculation server;
    return a.exec();
}
