#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <target.h>
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
    void on_runButton_clicked();

    void on_squareRadioButton_clicked();

    void on_ellipsRadioButton_clicked();

    void on_circleRadioButton_clicked();

    void on_rectangleRadioButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
