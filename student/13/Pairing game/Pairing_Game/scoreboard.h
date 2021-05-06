#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

class Scoreboard : public QObject
{
    Q_OBJECT

public:
    Scoreboard(QTimer *timer);
    QLabel* label;
    int counter;
    QTimer* timer;

public slots:
    void increment();
};

#endif // SCOREBOARD_H
