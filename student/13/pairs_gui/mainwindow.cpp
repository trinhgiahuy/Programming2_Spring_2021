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

/*
A constructor for initializing the mainwindow
*/
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

    //Setting the horizontal bar's min and max value num of players
    ui->playerHorizontalSlider->setMinimum(2);
    ui->playerHorizontalSlider->setMaximum(5);
    connect(ui->playerHorizontalSlider,&QSlider::valueChanged,this,&MainWindow::updateTable);
    connect(ui->cardLineEdit,&QLineEdit::editingFinished,this,&MainWindow::checkCardInput);

    //A test browser display number of card status and disable/enable the OK push button
    ui->textBrowser->setText("Please input number of card");
    ui->okPushButton->setDisabled(true);
    connect(ui->okPushButton,&QPushButton::clicked,this,&MainWindow::finishInput);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
A function that return 2 nearest factor of given input 
*/
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
}


/**
A functon check that if the game is over or not and 
if it is over, it will emit the signal stopGame to 
the mainwindow
*/
void MainWindow::checkGameIsOver(QTimer* timer)
{
    gamePointCounter_++;
    unsigned int rows = nearestFactorPair.first;
    unsigned int cols = nearestFactorPair.second;

    if(gamePointCounter_ == rows*cols/2){
        timer->stop();
        emit stopGame();
        gameOver = true;
    }
    gameOver = false;
}

/**
A function check return true value if the given input is a prime 
number and false if it is not 
*/
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

/*
A function that check the input number of card and output different
statement for text browser.
*/
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

/*
A slot signal that update the value of table 's rows based on the 
value of horizontal slider bar 
*/
void MainWindow::updateTable(){
    auto numRows = ui->playerHorizontalSlider->value();
    ui->tableWidget->setRowCount(numRows);
}

/*
A function control the input and initialze the game until the game is finished 
*/
void MainWindow::finishInput(){

    card_nums_  = ui->cardLineEdit->text().toInt();
    for(auto i = 0; i < ui->tableWidget->rowCount(); i++){
        if(ui->tableWidget->item(i,0) == nullptr){
            QString text = "NO NAME "+ QString::number(i+1);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(text));
        }
        player_list.push_back(ui->tableWidget->item(i,0)->text());
    }

    nearestFactor(card_nums_);

    initializeGame();

    MainWindow::close();
}

/*
A function that initialize the game board and control the game logic
*/
void MainWindow::initializeGame(){

    //Create necessary widgets for the game board
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

    //Create a scoreboard for each player
    for(unsigned int i =0; i< player_list.size();i++){

        Scoreboard *score_board_ = new Scoreboard(timer_->timer,player_list.at(i));
        score_board_->queue_ = i;
        all_score_board_vct.push_back(score_board_);
        hor_box_->addWidget(score_board_->player_);
        hor_box_->addWidget(score_board_->label);
        hor_box_->addSpacerItem(spacer_item_hor);
    }


    //Add quit and start button
    hor_box_->addWidget(new_game_btn);
    hor_box_->addWidget(quit_btn);
    ver_box_->addLayout(hor_box_);

    //Add the player status layout to the game board
    QHBoxLayout* player_turn_hor_layout = new QHBoxLayout;
    QString textLabel = "PLAYER TURN:  " + all_score_board_vct.at(player_turn_)->player_->text();
    player_turn_name->setText(textLabel);
    player_turn_hor_layout->addWidget(player_turn_name);
    ver_box_->addLayout(player_turn_hor_layout);


    //Get the number of row and columns from given card input
    Game_board_type game_board_;
    int row_pair = nearestFactorPair.first;
    int col_pair = nearestFactorPair.second;


    QObject::connect(new_game_btn, SIGNAL(clicked()), gl, SLOT(restart()));
    QObject::connect(timer_,SIGNAL(lost()),gl,SLOT(end_lost()));
    QObject::connect(quit_btn,SIGNAL(clicked()),qApp,SLOT(quit()));


    //Start creating the game board grid with cards as push button
    std::vector<QColor> color_data = {Qt::blue,Qt::yellow,Qt::red,Qt::green,Qt::gray,Qt::cyan,Qt::white,
                                      Qt::darkRed,Qt::lightGray,Qt::darkBlue,Qt::darkCyan,Qt::darkGray};

    bool grid[20][20] = {};
    for(unsigned int i = 0 ; i < 20 ; i++){
        for(unsigned int j = 0 ; j < 20 ; j++){
            grid[i][j] = false;
        }
    }

    std::srand(time(0));
    for(int i =0, c ='A'; i <row_pair*col_pair ; i+= 2, ++c){
        for(int j =0; j < 2; j++){
            Card *randButton = new Card(c,gl->curclicked);
            QPalette pal = randButton->palette();
            pal.setColor(QPalette::Button,QColor(color_data.at(std::rand()%color_data.size())));
            randButton->setAutoFillBackground(true);
            randButton->setPalette(pal);
            randButton->update();
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

    // Add the grid to the gameboard
    ver_box_->addLayout(gl);
    QSpacerItem *spacer_item_ver = new QSpacerItem(0, 10,
                                                   QSizePolicy::Expanding,QSizePolicy::Expanding);
    ver_box_->addSpacerItem(spacer_item_ver);

    widget_->setWindowTitle("Card Paring Game");
    widget_->resize(2000,960);
    widget_->setLayout(ver_box_);
    widget_->show();

    //Connect the gridboard logic signal to each score board slots
    QObject::connect(gl,SIGNAL(gridmatch()),this,SLOT(matchGridToScoreBoard()));
    QObject::connect(gl,SIGNAL(changeTurn()),this,SLOT(changePlayer()));
    for(unsigned int i =0; i<all_score_board_vct.size();i++){
        QObject::connect(this,&MainWindow::changeTurnInScoreBoard,all_score_board_vct.at(i),&Scoreboard::increment);
        QObject::connect(all_score_board_vct.at(i),&Scoreboard::increasePoint,this,&MainWindow::checkGameIsOver);
    }

    //Connect the signal stopgGame to slot stopTheGame
    QObject::connect(this,&MainWindow::stopGame,this,&MainWindow::stopTheGame);

}

/*
A function that change the number of palyers turn if they do not match the pair and displays
the current player turn
*/
void MainWindow::changePlayer()
{
    player_turn_ ++;
    if(player_turn_== all_score_board_vct.size()){
        player_turn_ = 0;
    }

    QString textLabel = "PLAYER TURN:  "+all_score_board_vct.at(player_turn_)->player_->text();
    this->player_turn_name->setText(textLabel);

}

/*
A slot that increase the total point of the game board.
*/
void MainWindow::increaseTotalPoint()
{
    gamePointCounter_++;
}

/*
A function that will emit the signal with current turn to all scoreboards
*/
void MainWindow::matchGridToScoreBoard()
{
    emit changeTurnInScoreBoard(game_turn_);
}

/*
A slot that will receive the signal stopGame to stop the game flow 
and display the final message box
*/
void MainWindow::stopTheGame()
{
    QMessageBox *qm = new QMessageBox();

    qm->setWindowTitle("GAME OVER!");
    qm->setBaseSize(QSize(600,120));
    int max_point = all_score_board_vct.at(0)->returnPoint();
    int index =0;

    //A loop that find the maximum number of score get from all players
    //and store palyer's information
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
        //Case 2 or more players get the same score
        qm->setText("Drawing Game! Wanna new try?");
    }else{
        //Display the winner player
        QString wining_player = all_score_board_vct.at(index)->player_->text()+" won! Score is "
                + QString::number(max_point);
        qm->setText(wining_player);
    }

    qm->setStandardButtons(QMessageBox::Close);
    qm->exec();
}
