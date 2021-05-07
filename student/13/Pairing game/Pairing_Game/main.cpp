#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "main.h"
#include <iostream>

#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "card.h"
#include "timer.h"
#include "grid.h"
#include "scoreboard.h"
#include "gamecontrol.h"
#include <QTime>
#include <QProcess>
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    /* ---------------------------------------
    QWidget *widget_ = new QWidget;
    QVBoxLayout *ver_box_ = new QVBoxLayout;
    QHBoxLayout *hor_box_ = new QHBoxLayout();
    QPushButton *new_game_btn = new QPushButton("New Game");
    QPushButton *quit_btn = new QPushButton("Quit");

    //Quit button does not work
    QObject::connect(quit_btn,SIGNAL(clicked()), &a, SLOT(quit()));

    Timer *timer_ = new Timer();
    Scoreboard *score_board_ = new Scoreboard(timer_->timer);

    hor_box_->addWidget(timer_->label);
    hor_box_->addWidget(score_board_->label);

    QSpacerItem *spacer_item_hor = new QSpacerItem(10,0,
                                               QSizePolicy::Expanding,QSizePolicy::Expanding);
    hor_box_->addSpacerItem(spacer_item_hor);
    hor_box_->addWidget(new_game_btn);
    hor_box_->addWidget(quit_btn);

    ver_box_->addLayout(hor_box_);

    int row = w.nearestFactorPair.first;
    int col = w.nearestFactorPair.second;

    //Initialize the game board
    //bool grid[10][10];
    Grid *gl = new Grid();

    QObject::connect(new_game_btn, SIGNAL(clicked()), gl, SLOT(restart()));


    bool grid[7][7] = {false};
    for(int i =0, c ='A'; i <row*col -1; i+= 2, ++c){
        for(int j =0; j < 2; j++){
            Card *randButton = new Card(c,gl->curclicked);
            QObject::connect(randButton,SIGNAL(clicked()),
                             randButton,SLOT(reveal()));
            QObject::connect(randButton,SIGNAL(checkhow()),
                             gl,SLOT(check_match()));

            int r = std::rand()%row;
            int c = std::rand()%col;

            while (grid[r][c]) {
                r = std::rand()%row;
                c = std::rand()%col;
            }
            gl->addWidget(randButton,r,c,1,1);
            grid[r][c] = true;
        }
    }

    ver_box_->addLayout(gl);
    QSpacerItem *spacer_item_ver = new QSpacerItem(0, 10,
                                                   QSizePolicy::Expanding,QSizePolicy::Expanding);
    ver_box_->addSpacerItem(spacer_item_ver);

    widget_->resize(640,480);
    widget_->setLayout(ver_box_);
    widget_->show();
    //initializeGame();
    */
    return a.exec();
}

