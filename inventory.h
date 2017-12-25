#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include <QList>
#include <QHeaderView>
#include <QScrollBar>
#include <QSound>

#include <QDragEnterEvent>
#include <QDropEvent>

#include <QDebug>

#include "cell.h"
#include "item.h"

class Inventory : public QTableWidget
{
    Q_OBJECT
public:
    explicit Inventory(int rows, int columns,  QTableWidget *parent = nullptr);
    ~Inventory();

    void initCells();

    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

private:
    QList<Cell*> cells;

signals:
    void somethingDone();
};

#endif // INVENTORY_H
