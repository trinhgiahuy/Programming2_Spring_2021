#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(incrementer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incrementer()
{
    int second_num = ui->lcdNumberSec->value();
    int minute_num = ui->lcdNumberMin->value();
    if(second_num<59) {
        second_num++;
    }else{
        minute_num+=1;
        second_num=0;
    }
    ui->lcdNumberSec->setPalette(Qt::red);
    ui->lcdNumberMin->setPalette(Qt::green);
    ui->lcdNumberSec->display(second_num);
    ui->lcdNumberMin->display(minute_num);

}

void MainWindow::on_startButton_clicked()
{

    timer->start(1000);

}

void MainWindow::on_stopButton_clicked()
{
    interval_ = timer->remainingTime();
    if(timer->isActive()){
        timer->stop();
    }
}

void MainWindow::on_resetButton_clicked()
{
    int second_num = ui->lcdNumberSec->value();
    int minute_num = ui->lcdNumberMin->value();
    timer->stop();
   second_num=0;
   minute_num=0;
   ui->lcdNumberMin->display(minute_num);
    ui->lcdNumberSec->display(second_num);
}
