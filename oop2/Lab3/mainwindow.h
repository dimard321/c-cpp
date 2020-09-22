#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "polinom.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_root_btn_clicked();

    void on_polinom_btn_clicked();

    void on_value_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
