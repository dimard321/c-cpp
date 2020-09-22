#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>

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


    void on_rbTriangleRadioButton_clicked();

    void on_rsTriangleRadioButton_clicked();

    void on_triangleRadioButton_clicked();

    void on_drawButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    bool isRS = false;
    bool isRB = false;
    bool isAny=false;
};

#endif // MAINWINDOW_H
