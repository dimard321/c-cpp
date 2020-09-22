#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include "shape.h"
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
    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    QRadioButton* parall;
    QRadioButton* rect;
    QRadioButton* rhomb;
    QRadioButton* square;
};

#endif // MAINWINDOW_H
