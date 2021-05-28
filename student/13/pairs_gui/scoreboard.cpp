#include "scoreboard.h"
#include "QDebug"
// this class displays player's current score
Scoreboard::Scoreboard(QTimer* timer, QString player_name_) : QObject()
{
    this->player_ = new QLabel(player_name_);
    this->label = new QLabel("Score: 0");
    this->counter = 0;
    this->timer = timer;
}

// A operation return the point of the scoreboard
int Scoreboard::returnPoint()
{
    return counter;
}

// this slot increments the score by 1 when a queue number of scoreboard
// match the current game turn and a pair is found
void Scoreboard::increment(unsigned int game_turn)
{
    if(game_turn == queue_){
        this->counter += 1;
        this->label->setText("Score: " + QString::number(counter));
        emit increasePoint(this->timer);
    }
}
