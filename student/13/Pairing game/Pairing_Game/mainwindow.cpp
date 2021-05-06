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
    QWidget *widget_ = new QWidget;
    QVBoxLayout *ver_box_ = new QVBoxLayout;
    QHBoxLayout *hor_box_ = new QHBoxLayout();
    QPushButton *new_game_btn = new QPushButton("New Game");
    QPushButton *quit_btn = new QPushButton("Quit");
    QObject::connect(quit_btn,SIGNAL(clicked()), this, SLOT(quit()));
    Timer *timer_ = new Timer();
    Scoreboard *score_board_ = new Scoreboard(timer_->timer);

    hor_box_->addWidget(timer_->label);
    hor_box_->addWidget(score_board_->label);

    QSpacerItem *spacer_item_ = new QSpacerItem(10,0,
                                               QSizePolicy::Expanding,QSizePolicy::Expanding);
    hor_box_->addSpacerItem(spacer_item_);
    hor_box_->addWidget(new_game_btn);
    hor_box_->addWidget(quit_btn);

    ver_box_->addLayout(hor_box_);
    widget_->resize(640,480);
    widget_->setLayout(ver_box_);
    widget_->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

