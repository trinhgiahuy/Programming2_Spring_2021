#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "mainwindow.h"
#include "grid.h"
class gameControl : public MainWindow
{
     Q_OBJECT
public:

    void nearestFactor(int num_in);
    void initializeGame(Grid *gl);
private:

    std::pair<int,int> nearestFactorPair;
};



#endif // GAMECONTROL_H
