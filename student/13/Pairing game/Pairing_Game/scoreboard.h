#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

class Scoreboard : public QObject
{
    Q_OBJECT

public:
    Scoreboard(QTimer *timer, QString player_name_);
    QLabel* label;
    int counter;
    QTimer* timer;

    QLabel* player_;

    unsigned int queue_;


    void isInturn();

    bool turn_;

public slots:

    void increment(unsigned int game_turn);

signals:

    void inTurn();

    void changeTurn();

    void increasePoint();
};

#endif // SCOREBOARD_H
