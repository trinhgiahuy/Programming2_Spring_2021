#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"
#include "grid.h"
#include "scoreboard.h"
#include "timer.h"

QT_BEGIN_NAMESPACE
using Game_row_type = std::vector<Card*>;
using Game_board_type = std::vector<std::vector<Card*>>;

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Game board operation

    bool isPrime(int num_in);

    std::vector<QString> player_list;

    int card_nums_;

    void nearestFactor(int num_in);

    std::pair<int,int> nearestFactorPair;

    std::vector<Scoreboard*> all_score_board_vct;

    void checkGameIsOver(QTimer* timer);


private slots:

    void checkCardInput();

    void updateTable();

    void finishInput();

    void initializeGame();

    void changePlayer();

    void increaseTotalPoint();

    void matchGridToScoreBoard();

    void stopTheGame();

private:

    Ui::MainWindow *ui;

    unsigned int game_turn_ ;

    unsigned int player_turn_ ;

    bool gameOver = false;

    unsigned int gamePointCounter_;

    QLabel* player_turn_name;

signals:

    void changeTurnInScoreBoard(const unsigned int& game_turn_);

    void stopGame();
};
#endif // MAINWINDOW_H
