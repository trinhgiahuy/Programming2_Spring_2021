#include <QApplication>
#include "gamecontrol.h"
#include "mainwindow.h"
#include "card.h"
#include "grid.h"
//A pair of integer. First element is smaller and second element is larger.
void gameControl::nearestFactor(int num_in)
{
    //std::pair<int,int> temp_pair;
    int f1_min = num_in;
    int f2_min = 1;
    int min = abs(f1_min - f2_min);
    for (int i = 1; i <= num_in ; i++){
        if (num_in % i == 0){
            int f1 = num_in/i;
            int f2 = i;
            int delta = abs(f1-f2);
            if (delta <= min){
                min = delta;
                f1_min = f1;
                f2_min = f2;
            }
        }
    }
     if (f1_min < f2_min){
         nearestFactorPair.first = f1_min;
         nearestFactorPair.second = f2_min;
     }else{
         nearestFactorPair.first = f2_min;
         nearestFactorPair.second = f1_min;
     }
}

void gameControl::initializeGame(Grid* gl)
{
    int row = nearestFactorPair.first;
    int col = nearestFactorPair.second;
    //bool grid[10][10];
    bool grid[7][7] = {false};
    for(int i =0, c ='A'; i <row*col -1; i+= 2, ++c){
        for(int j =0; j < 2; j++){
            Card *randButton = new Card(c,gl->curclicked);
            QObject::connect(randButton,SIGNAL(clicked()),
                             randButton,SLOT(reveal()));
            QObject::connect(randButton,SIGNAL(checkhow()),
                             gl,SLOT(check_match()));

            int r = std::rand()%row;
            int c = std::rand()%col;

            while (grid[r][c]) {
                r = std::rand()%row;
                c = std::rand()%col;
            }
            gl->addWidget(randButton,r,c,1,1);
            grid[r][c] = true;
        }
    }
}
