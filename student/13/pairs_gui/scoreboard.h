#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include "timer.h"


class Scoreboard : public QObject
{
    Q_OBJECT

public:

    Scoreboard(QTimer *timer, QString player_name_);

    //Scoreboard data member
    QLabel* label;

    int counter;

    QTimer* timer;

    QLabel* player_;

    unsigned int queue_;

    int returnPoint();

public slots:

    void increment(unsigned int game_turn);

signals:

    void inTurn();

    void changeTurn();

    void increasePoint(QTimer* timer);
};

#endif // SCOREBOARD_H
