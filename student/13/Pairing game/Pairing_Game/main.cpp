#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "main.h"
#include <iostream>

#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "card.h"
#include "timer.h"
#include "grid.h"
#include "scoreboard.h"
#include "gamecontrol.h"
#include <QTime>
#include <QProcess>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

