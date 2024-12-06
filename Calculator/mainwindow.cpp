#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_point,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_degree,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_multi,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_open_brace,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_close_brace,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(input_button()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(function()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(function()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_button()
{
   QPushButton *button = (QPushButton *)sender();
   QString new_label;
   if (ui->result_show->text() == "0") {
       new_label = button->text();
   }else if (ui->result_show->text() == ".") {
       new_label = ("0" + ui->result_show->text() + button->text());
   }else{
       new_label = (ui->result_show->text() + button->text());
   }
   ui->result_show->setText(new_label);
}

void MainWindow::function()
{
   QPushButton *button = (QPushButton *)sender();
   QString new_label;
   if (ui->result_show->text() == "0") {
       new_label = button->text() + "(";
   }else{
       new_label = (ui->result_show->text() + button->text() + "(");
   }
   ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->result_show->setText("0");
}


void MainWindow::on_pushButton_equally_clicked()
{
    QString new_label;
    new_label = (ui->result_show->text());
    std::string my_string = new_label.toStdString();
    double res = 0;
    double x = 1.0;
    if (!ui->Xx->text().isEmpty()){
        x = ui->Xx->text().toDouble();
    }
    int status = process(my_string.c_str(), x, &res);
    if(status == 1) {
        ui->result_show->setText("Input error");
    }else{
        ui->result_show->setText(QString::number(res, 'f', 7));
    }
}


void MainWindow::on_pushButton_graphic_clicked()
{
    QString new_label;
    new_label = (ui->result_show->text());
    std::string my_string = new_label.toStdString();

    double maxX = ui->MAX_X->text().toDouble();
    double minX = ui->MIN_X->text().toDouble();
    double maxY = ui->MAX_Y->text().toDouble();
    double minY = ui->MIN_Y->text().toDouble();
    ui->widget->xAxis->setRange(minX, maxX);
    ui->widget->yAxis->setRange(minY, maxY);

    double X, res, h;
    h = 0.01;
    QVector<double> x, y;
    ui->widget->addGraph();
    int status = process(my_string.c_str(), minX, &res);
    for (X = minX; ((X <= maxX) && (!status)); X += h)
    {
            process(my_string.c_str(), X, &res);
            x.push_back(X);
            y.push_back(res);
    }
    ui->widget->graph()->addData(x, y);
    ui->widget->setNotAntialiasedElement(QCP::aeAll);
    ui->widget->graph()->setAdaptiveSampling(false);
    ui->widget->replot();
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
}

void MainWindow::on_credit_count_clicked()
{
    double credit_amount = ui->AMOUNT->text().toDouble();
    int time = ui->TIME->text().toInt();
    double rate = ui->RATE->text().toDouble();
    double monthly_payment = 0, min_payment = 0, overpayment = 0, total_payment = 0;

    if (ui->an_credit->isChecked()) {
        annuity_credit(credit_amount, time, rate, &monthly_payment, &overpayment, &total_payment);
        ui->m_payment->setText(QString::number(monthly_payment, 'f', 2));

       } else if (ui->dif_credit->isChecked()) {
        credit_differentiated(credit_amount, time, rate, &monthly_payment, &min_payment, &overpayment, &total_payment);
        ui->m_payment->setText(QString::number(monthly_payment, 'f', 2) + " ... " + QString::number(min_payment, 'f', 2));

    }
    ui->o_payment->setText(QString::number(overpayment, 'f', 2));
    ui->t_payment->setText(QString::number(total_payment, 'f', 2));
}

void MainWindow::on_deposit_count_clicked()
{
    double deposit = ui->DEPOSIT->text().toDouble();
    int time = ui->TIME_DEPOSIT->text().toInt();
    double rate = ui->RATE_DEPOSIT->text().toDouble();
    int period_payment = ui->PERIOD_PAYMENT->text().toInt();
    double nalog_rate = ui->NALOG_RATE->text().toDouble();
    double add_deposit = ui->ADD_DEPOSIT->text().toDouble();
    double remove_deposit = ui->REMOVE_DEPOSIT->text().toDouble();
    double profit = 0, tax = 0, deposit_end = 0;
    int capitalization = 0;
    int month = ui->MONTH->text().toInt();

    if (ui->capitalization_ON->isChecked()) {
        capitalization = 1;
    } else if (ui->dif_credit->isChecked()) {
        capitalization = 0;
    }

    deposit_count(deposit, time, rate, nalog_rate, period_payment, capitalization, add_deposit, remove_deposit, month, &profit, &tax, &deposit_end);
    ui->PROFIT->setText(QString::number(profit, 'f', 2));
    ui->TAX->setText(QString::number(tax, 'f', 2));
    ui->DEPOSIT_END->setText(QString::number(deposit_end, 'f', 2));
}

