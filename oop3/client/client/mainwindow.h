#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>
#include "complex.h"
#include <QUdpSocket>
#include <QHostAddress>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int waitUntilSignalIsEmitted(QObject *sender, const char *signal) {
            QEventLoop loop;
            connect(sender, signal,&loop, SLOT(quit()));
            return loop.exec();
        }
public slots:
    void recMsg();

private slots:
    void on_root_btn_clicked();

    void on_polinom_btn_clicked();

    void on_value_btn_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socketClient;
    QUdpSocket *socketClientRecive;
    QHostAddress host;
};

#endif // MAINWINDOW_H
