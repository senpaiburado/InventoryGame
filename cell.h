#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>

#include "item.h"

class Cell : public QTableWidgetItem
{
public:
    explicit Cell(const Item &item);
    explicit Cell();
    ~Cell();

    void setItem(const Item &item);
    Item *getItem();
    int getCount();

    void addCount(int value);
    void subCount(int value);

    void setCount(unsigned int value);

    void updateText();

private:
    Item *item;
    int count;
};

#endif // CELL_H
