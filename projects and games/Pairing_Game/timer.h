#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include "grid.h"
#include "card.h"

class Timer : public QObject
{
    Q_OBJECT

public:
    Timer();
    QTimer *timer;
    QLabel *label;
    int counter;

public slots:
    void finished();

signals:
    void lost();
};

#endif // TIMER_H
