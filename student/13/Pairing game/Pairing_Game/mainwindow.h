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

    //void initializeGamne();

    std::vector<QString> player_list;
    int card_nums_;

    void nearestFactor(int num_in);

    std::pair<int,int> nearestFactorPair;

    std::vector<Scoreboard*> all_score_board_vct;

    void checkGameIsOver(QTimer* timer);


private slots:
    //Game board operation
    void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns, Grid *gl_);

    unsigned int next_free(Game_board_type& g_board, unsigned int start);

    void init_with_cards(Game_board_type& g_board, int seed, Grid *gl_, int row_pair_, int col_pair_);

    void add_board_to_widget(Game_board_type& g_board,Grid *gl_);

    bool isPrime(int num_in);

    void checkCardInput();

    void updateTable();

    void finishInput();

    void initializeGame();

    //void gameControl();

    void changePlayer();

    void increaseTotalPoint();

    //void increasePointGame();

    void matchGridToScoreBoard();

    //void updatePlayerScore(Grid* gl_ , int turn_);

    void stopTheGame();
private:
    Ui::MainWindow *ui;

    unsigned int game_turn_ ;

    unsigned int player_turn_ ;

    bool gameOver = false;

    unsigned int gamePointCounter_;
    //Grid *gl ;

    QLabel* player_turn_name;

signals:

    void changeTurnInScoreBoard(const unsigned int& game_turn_);

    void stopGame();
};
#endif // MAINWINDOW_H
