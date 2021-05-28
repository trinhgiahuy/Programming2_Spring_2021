#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <fstream>
#include <utility>
#include <QColor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    Scene = new QGraphicsScene(this);
    nextScene = new QGraphicsScene(this);
    holdScene = new QGraphicsScene(this);
    */

    timer_.setSingleShot(false);
    gameRealTime.setSingleShot(false);

   connect(&timer_, &QTimer::timeout, this, &MainWindow::automaticDrop);
   connect(&gameRealTime, &QTimer::timeout, this, &MainWindow::playingTime);

   connect(ui->pausePushButton, &QPushButton::clicked, this, &MainWindow::pauseGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

