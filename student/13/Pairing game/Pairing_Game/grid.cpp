#include "grid.h"

// this is the grid that holds 30 cards
Grid::Grid() : QGridLayout(){
    this->curclicked = new QStack<Card*>();
}

// this slot checks if the two last pressed buttons were a match
void Grid::check_match(){
    Card* firstcard = curclicked->pop();
    Card* secondcard = curclicked->pop();

    if((firstcard->hiddentext == secondcard->hiddentext) && firstcard != secondcard){
        emit gridmatch();
        firstcard->matched();
        secondcard->matched();
    }
    else {
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit()));
        loop.exec();
        firstcard->setText("?");
        secondcard->setText("?");
    }
}

// this slot ends the game with a loss scenario, disabling all buttons
// and revealing all names
void Grid::end_lost() {
    for (int i = 0; i < this->count(); i++) {
        Card* but = qobject_cast<Card*>(this->itemAt(i)->widget());
        but->setText(but->hiddentext);
        but->setDisabled(true);
    }
}

// this slot restarts the game by exiting and relaunching
void Grid::restart() {

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

