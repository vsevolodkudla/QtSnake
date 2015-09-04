#include "cell.h"

Cell::Cell(int x, int y): x(x), y(y)
{

}

Cell* Cell::operator +(Cell *b)
{
    return new Cell(x + b->x, y + b->y);
}
Cell* Cell::operator +(Cell &b)
{
    return new Cell(x + b.x, y + b.y);
}

bool Cell::operator==(Cell &b)
{
    return (x == b.x && y == b.y)? true:false;
}
bool Cell::operator==(int b)
{
    return (x==b && y==b)?true:false;
}
void Cell::Add(Cell *b)
{
    x += b->x;
    y += b->y;
}
void Cell::operator =(Cell &b)
{
    x = b.x;
    y = b.y;
}
