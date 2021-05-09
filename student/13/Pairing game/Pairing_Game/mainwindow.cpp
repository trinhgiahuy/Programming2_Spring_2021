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
#include <QDebug>
#include <random>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(1);
    gameOver = false;
    game_turn_ = 0;
    player_turn_ = 0;
    gamePointCounter_=0;
    player_turn_name = new QLabel();
    ui->playerHorizontalSlider->setMinimum(2);
    ui->playerHorizontalSlider->setMaximum(5);
    connect(ui->playerHorizontalSlider,&QSlider::valueChanged,this,&MainWindow::updateTable);
    connect(ui->cardLineEdit,&QLineEdit::editingFinished,this,&MainWindow::checkCardInput);
    ui->textBrowser->setText("Please input number of card");
    ui->okPushButton->setDisabled(true);
    connect(ui->okPushButton,&QPushButton::clicked,this,&MainWindow::finishInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nearestFactor(int num_in)
{
    int f1_min = num_in;
    int f2_min = 1;
    int min = abs(f1_min - f2_min);
    for (int i = 1; i <= num_in ; i++){
        if (num_in % i == 0){
            int f1 = num_in/i;
            int f2 = i;
            int delta = abs(f1-f2);
            if (delta <= min){
                min = delta;
                f1_min = f1;
                f2_min = f2;
            }
        }
    }
    if (f1_min < f2_min){
        nearestFactorPair.first = f1_min;
        nearestFactorPair.second = f2_min;
    }else{
        nearestFactorPair.first = f2_min;
        nearestFactorPair.second = f1_min;
    }
    //qDebug() << f1_min << f2_min;
}

void MainWindow::checkGameIsOver(QTimer* timer)
{
    gamePointCounter_++;
    qDebug()<<"Increase total point"<<gamePointCounter_;
    unsigned int rows = nearestFactorPair.first;
    unsigned int cols = nearestFactorPair.second;

    qDebug() << rows << "   " << cols;
    if(gamePointCounter_ == rows*cols/2){
        timer->stop();
        qDebug()<<"Game over!";
        emit stopGame();
        gameOver = true;
    }
    gameOver = false;
}

bool MainWindow::isPrime(int num_in)
{
    int chk=0;
    for(int i=2; i<num_in; i++)
    {
        if(num_in%i==0)
        {
            chk++;
            break;
        }
    }
    if(chk==0){
        //Input is prime number
        return true;
    }else{
        return false;
    }
}

void MainWindow::checkCardInput()
{
    int input_ = ui->cardLineEdit->text().toInt();
    if(input_ <= 0){
        ui->textBrowser->setText("Please input possitive number of cards");
        ui->textBrowser->show();
    }else{
        if(input_> 52){
            //Number of card exceed all alphabet letters
            ui->textBrowser->setText("Please input number of card lower than 52");
            ui->textBrowser->show();
        }else{
            if(input_ % 2 != 0){
                ui->textBrowser->setText("Please input a odd number of cards");
                ui->textBrowser->show();
            }else{
                if(isPrime(input_)){
                    ui->textBrowser->setText("Please input a non-prime number of card");
                    ui->textBrowser->show();
                }else{
                    ui->textBrowser->setText("OK");
                    ui->textBrowser->show();
                    ui->okPushButton->setEnabled(true);
                }
            }
        }
    }
}

void MainWindow::updateTable(){
    auto numRows = ui->playerHorizontalSlider->value();
    ui->tableWidget->setRowCount(numRows);
}

void MainWindow::finishInput(){
    card_nums_  = ui->cardLineEdit->text().toInt();
    for(auto i = 0; i < ui->tableWidget->rowCount(); i++){
        player_list.push_back(ui->tableWidget->item(i,0)->text());
    }
    nearestFactor(card_nums_);

    initializeGame();

    MainWindow::close();
}

void MainWindow::initializeGame()
{
    QWidget *widget_ = new QWidget;
    QVBoxLayout *ver_box_ = new QVBoxLayout;
    QPushButton *new_game_btn = new QPushButton("New Game");
    QPushButton *quit_btn = new QPushButton("Quit");
    QObject::connect(quit_btn,SIGNAL(clicked()),qApp,SLOT(closed()));
    Timer *timer_ = new Timer();
    QHBoxLayout *hor_box_ = new QHBoxLayout();

    QSpacerItem *spacer_item_hor = new QSpacerItem(10,0,
                                                   QSizePolicy::Expanding,QSizePolicy::Expanding);
    hor_box_->addWidget(timer_->label);

    Grid *gl = new Grid();
    for(unsigned int i =0; i< player_list.size();i++){
        Scoreboard *score_board_ = new Scoreboard(timer_->timer,player_list.at(i));
        score_board_->queue_ = i;
        all_score_board_vct.push_back(score_board_);
        hor_box_->addWidget(score_board_->player_);
        hor_box_->addWidget(score_board_->label);
        hor_box_->addSpacerItem(spacer_item_hor);
    }

    hor_box_->addWidget(new_game_btn);
    hor_box_->addWidget(quit_btn);
    ver_box_->addLayout(hor_box_);
    QHBoxLayout* player_turn_hor_layout = new QHBoxLayout;
    QLabel* player_turn_label = new QLabel("PLAYER TURN:");
    QLabel* player_turn_name = new QLabel();
    player_turn_hor_layout->addWidget(player_turn_label);
    player_turn_hor_layout->addSpacerItem(spacer_item_hor);
    player_turn_hor_layout->addWidget(player_turn_name);

    ver_box_->addLayout(player_turn_hor_layout);

    Game_board_type game_board_;
    int row_pair = nearestFactorPair.first;
    int col_pair = nearestFactorPair.second;
    qDebug()<<row_pair<<"   "<<col_pair;

    QObject::connect(new_game_btn, SIGNAL(clicked()), gl, SLOT(restart()));
    QObject::connect(timer_,SIGNAL(lost()),gl,SLOT(end_lost()));
    QObject::connect(quit_btn,SIGNAL(clicked()),qApp,SLOT(quit()));

    bool grid[20][20] = {false};
    std::srand(time(0));
    for(int i =0, c ='A'; i <row_pair*col_pair ; i+= 2, ++c){
        for(int j =0; j < 2; j++){
            Card *randButton = new Card(c,gl->curclicked);
            QObject::connect(randButton,SIGNAL(clicked()),
                             randButton,SLOT(reveal()));
            QObject::connect(randButton,SIGNAL(checknow()),
                             gl,SLOT(check_match()));

            int r = std::rand()%row_pair;
            int c = std::rand()%col_pair;

            while (grid[r][c]) {
                r = std::rand()%row_pair;
                c = std::rand()%col_pair;
            }
            gl->addWidget(randButton,r,c,1,1);
            grid[r][c] = true;
        }
    }


    ver_box_->addLayout(gl);
    QSpacerItem *spacer_item_ver = new QSpacerItem(0, 10,
                                                   QSizePolicy::Expanding,QSizePolicy::Expanding);
    ver_box_->addSpacerItem(spacer_item_ver);

    widget_->setWindowTitle("Card Paring Game");
    widget_->resize(2000,960);
    widget_->setLayout(ver_box_);
    widget_->show();

    QObject::connect(gl,SIGNAL(gridmatch()),this,SLOT(matchGridToScoreBoard()));
    QObject::connect(gl,SIGNAL(changeTurn()),this,SLOT(changePlayer()));

    for(unsigned int i =0; i<all_score_board_vct.size();i++){
        QObject::connect(this,&MainWindow::changeTurnInScoreBoard,all_score_board_vct.at(i),&Scoreboard::increment);
        QObject::connect(all_score_board_vct.at(i),&Scoreboard::increasePoint,this,&MainWindow::checkGameIsOver);
        qDebug() << "IIII" <<i;
    }
    QObject::connect(this,&MainWindow::stopGame,this,&MainWindow::stopTheGame);

}

void MainWindow::changePlayer()
{
    player_turn_ ++;
    if(player_turn_== all_score_board_vct.size()){
        player_turn_ = 0;
    }
    this->player_turn_name->setText(all_score_board_vct.at(player_turn_)->player_->text());
    this->player_turn_name->show();

    this->game_turn_ = player_turn_;
}

void MainWindow::increaseTotalPoint()
{
    gamePointCounter_++;
    qDebug()<<"Increase total point"<<gamePointCounter_;
}

void MainWindow::matchGridToScoreBoard()
{
    qDebug() << "emti signal change turn in gb"<<game_turn_;
    emit changeTurnInScoreBoard(game_turn_);

}

void MainWindow::stopTheGame()
{
    qDebug() <<"Connected to stopTheGame";
    QMessageBox *qm = new QMessageBox();

    qm->setWindowTitle("GAME OVER!");
    qm->setBaseSize(QSize(600,120));
    int max_point = all_score_board_vct.at(0)->returnPoint();
    int index =0;
    for(unsigned int i =1; i<all_score_board_vct.size();i++){
        if(all_score_board_vct.at(i)->returnPoint() > max_point){
            max_point = all_score_board_vct.at(i)->returnPoint();
            index = i;
        }else{
            if(all_score_board_vct.at(i)->returnPoint() == max_point){
                index = -1;
                break;
            }
        }
    }
    if(index == -1){
        qm->setText("Drawing Game! Wanna new try?");
    }else{
        QString wining_player = all_score_board_vct.at(index)->player_->text()+" won!";
        qm->setText(wining_player);
    }
    qm->setStandardButtons(QMessageBox::Close);
    qm->exec();
}
