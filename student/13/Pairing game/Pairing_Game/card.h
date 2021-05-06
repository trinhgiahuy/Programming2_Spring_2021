#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QStack>


class Card : public QPushButton
{
    Q_OBJECT

public:
    Card(const QString& text, QStack<Card*>* curclicked,
                QWidget* parent = 0);
    QString hiddentext;
    QStack<Card*>* curclicked;
public slots:
    void reveal();
    void matched();

signals:
    void checknow();
};

#endif // CARD_H
