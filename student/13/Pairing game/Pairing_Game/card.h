#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QStack>

enum Visibility_type {OPEN,HIDDEN,EMPTY};
class Card : public QPushButton
{
    Q_OBJECT

public:
    Card();
    Card(const QChar& text, QStack<Card*>* curclicked,
                QWidget* parent = 0);
    QString hiddentext;
    QStack<Card*>* curclicked;

    Visibility_type visibility_;

    Visibility_type get_visibility();

    //void set_letter (const char c);

    void setting(const QChar& text, QStack<Card*>* curclicked
                 );
    //QChar& text_ ;

public slots:
    void reveal();
    void matched();

    //void checkTurn();

signals:
    void checknow();
};

#endif // CARD_H
