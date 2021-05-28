#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QTimer>
#include <QGraphicsRectItem>
#include "card.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Group of function display the window
    void setInitialWindow();
    void setInitialGame();
    void playingTime();
    void updateGame();
    void updateGameBoard();

    //Group of function to control the Card
    void newCard();
    void getPosition();
    void drawNextCard();
    void rotate();

    //Group of function control the flow of game
    void continueGame();
    bool isOver();
    void finishedGame();
    void pauseGam();

    //Group of function control the buttons
    void on_startButton_clicked();
    void on_rotateButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene*  Scene;
    QGraphicsScene*  nextScene;
    QGraphicsScene*  holdScene;

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 480;

    const int CARD_SIZE = 48;

    const int COLUMNS = BORDER_RIGHT / CARD_SIZE;
    const int ROW = BORDER_DOWN / CARD_SIZE;

    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    QTimer timer_;

    //For calculate time of playing
    QTimer gameRealTime;

    int bottomLimit;
    int leftLimit;
    int rightLimit;
    int upLimit;

    bool gameIsStarted = false;
    bool gameIsRunning = false;
    bool gameIsOver    = false;

    Card currentCard;
    Card nextCard;
    Card holdCard;

    bool canHold;
    bool isHoldEmpty;

    std::vector<QString> colorData = {{"#0444BF","#0584F2","#BE3B45","#55D9C0","#EDF259","#F07995"}};
    std::vector<std::vector<Card>> gameBoard;
    int playSpeed = 0;

    int min  = 0;
    int sec  = 0;
    int hour = 0;


};

#endif // MAINWINDOW_HH
