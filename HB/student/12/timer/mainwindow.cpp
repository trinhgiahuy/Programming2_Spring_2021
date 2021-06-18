#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_LCD);

    QPalette Pal = ui->lcdNumberMin->palette();

    Pal.setColor(QPalette::Normal, QPalette::Background, Qt::green);

    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberMin->setPalette(Pal);
    QPalette Pal_sec = ui->lcdNumberSec->palette();

    Pal_sec.setColor(QPalette::Normal, QPalette::Background, Qt::red);

    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberSec->setPalette(Pal_sec);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (!timer->isActive()){
        timer->start(1000);
    }

}
void MainWindow::update_LCD()
{
    if (timer->isActive()){
        current_time += 1;
        QString minutes = QString::fromStdString(std::to_string(current_time/60));
        QString seconds = QString::fromStdString(std::to_string((current_time/1)%60));
        ui->lcdNumberMin->display(minutes);
        ui->lcdNumberSec->display(seconds);
    }

}

void MainWindow::on_stopButton_clicked()
{
    if (timer->isActive()){
        timer->stop();
    }
}

void MainWindow::on_resetButton_clicked()
{
    current_time = 0;
    QString minutes = QString::fromStdString(std::to_string(current_time/60));
    QString seconds = QString::fromStdString(std::to_string((current_time/1)%60));
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}
