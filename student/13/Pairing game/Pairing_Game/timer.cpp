#include "timer.h"

// this class is taken directly from the PS code
// it is a timer that shows seconds elapsed since
// the start of the game
Timer::Timer()
{
    timer = new QTimer(this);
    label = new QLabel("Time (secs): 0");
    counter = 0;

    connect(timer, SIGNAL(timeout()),
          this, SLOT(finished()));

    timer->start(1000);
}

// this slot increments the counter display
// each second and ends the game with a
// loss scenario if the game is not won in 180 seconds
void Timer::finished()
{
    counter += 1;
    label->setText("Time (secs): "+
                   QString::number(this->counter));
    if(counter>=180){
        this->timer->stop();
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText("Better luck next time!");
        msgBox->setWindowTitle("You lost!");
        msgBox->setStandardButtons(QMessageBox::Cancel);
        emit lost();
        msgBox->exec();
    }
}

