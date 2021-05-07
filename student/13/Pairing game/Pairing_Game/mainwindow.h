#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
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

private slots:
    //void inputHandle();
    bool isPrime(int num_in);

    void checkCardInput();

    void updateTable();

    void finishInput();

    void initializeGame();



private:
    Ui::MainWindow *ui;




};
#endif // MAINWINDOW_H
