#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell(int x = 0, int y = 0);
    Cell* operator+(Cell *b);
    Cell *operator+(Cell &b);
    bool operator ==(Cell &b);
    bool operator ==(int b);
    void operator=(Cell &b);
    void Add(Cell*);
    int x, y;
};

#endif // CELL_H
