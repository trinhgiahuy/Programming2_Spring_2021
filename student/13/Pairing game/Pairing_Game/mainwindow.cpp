#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "card.h"
#include "timer.h"
#include "grid.h"
#include "scoreboard.h"
#include <QTime>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    ui->tableWidget->setColumnCount(1);
    //ui->tableWidget->setRowCount(3);

    //auto numRow = ui->spinBox->value();
    //connect(ui->spinBox,&QSpinBox::valueChanged,ui->tableWidget,&QTableWidget::setRowCount(numRow));
    //ui->tableWidget->setRowCount(numRow_);


    //connect(ui->spinBox,&QSpinBox::valueChanged,ui->tableWidget,QTableWidget::insertRow(1));


    //connect(ui->cardLineEdit,&QLineEdit::editingFinished,this,&MainWindow::inputHandle);

    connect(ui->okPushButton,&QPushButton::clicked,this,&MainWindow::finishInput);

    ui->playerHorizontalSlider->setMinimum(2);
    ui->playerHorizontalSlider->setMaximum(5);
    connect(ui->playerHorizontalSlider,&QSlider::valueChanged,this,&MainWindow::updateTable);

    //connect(ui->spinBox,&QSpinBox::valueChanged,this,&MainWindow::updateTable);
   // connect(ui->spinBox,&QSpinBox::valueChanged,this,&MainWindow::updateTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::inputHandle(){
    int cardAmount_str = ui->cardLineEdit->text().toInt();

}*/

void MainWindow::updateTable(){
    //ui->tableWidget->setColumnCount(2);
    auto numRows = ui->playerHorizontalSlider->value();
    //auto numRow = ui->spinBox->value();
    //ui->tableWidget->setRowCount(numRowss);
    ui->tableWidget->setRowCount(numRows);
}

void MainWindow::finishInput(){
    card_nums_  = ui->cardLineEdit->text().toInt();
    for(auto i = 0; i < ui->tableWidget->rowCount(); i++){
        player_list.push_back(ui->tableWidget->itemAt(0,i)->text());
    }
    MainWindow::close();
}




