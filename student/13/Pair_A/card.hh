#ifndef CARD_HH
#define CARD_HH
#include <QGraphicsRectItem>
struct Coord
{
    int x = 0;
    int y = 0;

    Coord():
        x(0), y(0)
    {
    }

    Coord(int p_x, int p_y):
        x(p_x), y(p_y)
    {
    }
};

/*
struct Square
{
    QGraphicsRectItem* block = NULL;
    Coord pos;
};
*/

struct Card
{
    //std::vector<Square> squares = std::vector<Square>(4, Square());
    QGraphicsRectItem* block = NULL;
    Coord pos;

    int type = 0;
    QColor color = Qt::white;

    Card():
        pos(0,0),
        type(0),
        color(Qt::white)
    {
    }


};
#endif // CARD_HH
