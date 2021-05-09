#include "scoreboard.h"
#include "QDebug"
// this class displays player's current score
Scoreboard::Scoreboard(QTimer* timer, QString player_name_) : QObject()
{
    this->player_ = new QLabel(player_name_);
    this->label = new QLabel("Score: 0");
    this->counter = 0;
    this->timer = timer;
    this->turn_ = false;
}

void Scoreboard::isInturn()
{
    this->turn_ = true;
}

int Scoreboard::returnPoint()
{
    return counter;
}

// this slot increments the score by 1 when a match
// happens, also ends the game with a win scenario
// when the score reaches 15.
void Scoreboard::increment(unsigned int game_turn)
{
    if(game_turn == queue_){
        this->counter += 1;
        qDebug() << "Num counter"<<counter;
        this->label->setText("Score: " + QString::number(counter));

        emit increasePoint(this->timer);
    }
}
