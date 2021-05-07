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

private slots:
    //void inputHandle();

    void updateTable();

    void finishInput();

private:
    Ui::MainWindow *ui;

    std::vector<QString> player_list;
    int card_nums_;
};
#endif // MAINWINDOW_H
