#include "scoreboard.h"

// this class displays player's current score
Scoreboard::Scoreboard(QTimer* timer) : QObject()
{
    this->label = new QLabel("Score: 0");
    this->counter = 0;
    this->timer = timer;
}

// this slot increments the score by 1 when a match
// happens, also ends the game with a win scenario
// when the score reaches 15.
void Scoreboard::increment()
{
    this->counter += 1;
    this->label->setText("Score: " + QString::number(counter));
    if (this->counter >= 15)
    {
        QMessageBox *qm = new QMessageBox();
        qm->setText("Well done, you've matched them all!");
        qm->setWindowTitle("You won!");
        qm->setStandardButtons(QMessageBox::Close);
        timer->stop();
        qm->exec();
    }
}
