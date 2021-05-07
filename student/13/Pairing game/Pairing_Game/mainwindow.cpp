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


    ui->playerHorizontalSlider->setMinimum(2);
    ui->playerHorizontalSlider->setMaximum(5);
    connect(ui->playerHorizontalSlider,&QSlider::valueChanged,this,&MainWindow::updateTable);
    connect(ui->cardLineEdit,&QLineEdit::editingFinished,this,&MainWindow::checkCardInput);
    ui->textBrowser->setText("Please input number of card");
    ui->okPushButton->setDisabled(true);

    /*
    if(!ui->textBrowser->toPlainText().isEmpty()){
        ui->okPushButton->setDisabled(true);
        //connect(ui->textBrowser,&QTextBrowser::text)
    }*/
    connect(ui->okPushButton,&QPushButton::clicked,this,&MainWindow::finishInput);


    //connect(ui->spinBox,&QSpinBox::valueChanged,this,&MainWindow::updateTable);
    // connect(ui->spinBox,&QSpinBox::valueChanged,this,&MainWindow::updateTable);

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
}

bool MainWindow::isPrime(int num_in)
{
    int i, chk=0;
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
    nearestFactor(card_nums_);
    initializeGame();
    //MainWindow::close();
}

void MainWindow::initializeGame()
{
    QWidget *widget_ = new QWidget;
    QVBoxLayout *ver_box_ = new QVBoxLayout;
    QHBoxLayout *hor_box_ = new QHBoxLayout();
    QPushButton *new_game_btn = new QPushButton("New Game");
    QPushButton *quit_btn = new QPushButton("Quit");
    QObject::connect(quit_btn,SIGNAL(clicked()),qApp,SLOT(closed()));
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


    int row = nearestFactorPair.first;
    int col = nearestFactorPair.second;

    //Initialize the game board
    //bool grid[10][10];
    Grid *gl = new Grid();

    QObject::connect(new_game_btn, SIGNAL(clicked()), gl, SLOT(restart()));
    QObject::connect(timer_,SIGNAL(lost()),gl,SLOT(end_lost()));
    QObject::connect(gl,SIGNAL(gridmatch()),score_board_,SLOT(increment()));
    QObject::connect(quit_btn,SIGNAL(clicked()),qApp,SLOT(quit()));


    bool grid[7][7] = {false};
    //std::srand(time(0));
    for(int i =0, c ='A'; i <row*col ; i+= 2, ++c){
        for(int j =0; j < 2; j++){
            Card *randButton = new Card(c,gl->curclicked);
            QObject::connect(randButton,SIGNAL(clicked()),
                             randButton,SLOT(reveal()));
            QObject::connect(randButton,SIGNAL(checknow()),
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

    widget_->setWindowTitle("Card Paring Game");
    widget_->resize(2000,960);
    widget_->setLayout(ver_box_);
    widget_->show();
}




