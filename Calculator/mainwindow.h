#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QCoreApplication>
//#include "qcustomplot.h"

extern "C" {
    #include "../SmartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    void input_button();
    void function();
    void on_pushButton_AC_clicked();
    void on_pushButton_equally_clicked();
    void on_pushButton_graphic_clicked();
    void on_credit_count_clicked();
    void on_deposit_count_clicked();
};
#endif // MAINWINDOW_H
