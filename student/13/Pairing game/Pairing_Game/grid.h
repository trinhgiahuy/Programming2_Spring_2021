#ifndef GRID_H
#define GRID_H
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include <QStack>
#include "card.h"
#include <QEventLoop>
#include <QApplication>
#include <QProcess>

class Grid : public QGridLayout
{
    Q_OBJECT

public:
    Grid();
    QStack<Card*>* curclicked;

public slots:
    void check_match();
    void end_lost();
    void restart();

signals:
    void gridmatch();
};


#endif // GRID_H
