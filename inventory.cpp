#include "inventory.h"

Inventory::Inventory(int rows, int columns, QTableWidget *parent) : QTableWidget(parent)
{
    setRowCount(rows);
    setColumnCount(columns);

    setMinimumSize(QSize(width(), height()));
    setMaximumSize(QSize(width(), height()));

    horizontalHeader()->setDefaultSectionSize(65);
    verticalHeader()->setDefaultSectionSize(60);

    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);

    setIconSize(QSize(40, 40));
    setFont(QFont(QString("Arial"), 7));

    setDragEnabled(true);
    setDragDropOverwriteMode(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setAcceptDrops(true);

    setDefaultDropAction(Qt::MoveAction);
    setDropIndicatorShown(true);
}

Inventory::~Inventory()
{
    for (Cell *cell : cells)
        delete cell;
}

void Inventory::initCells()
{
    for (int i = 0; i < rowCount(); i++)
    {
        for (int j = 0; j < columnCount(); j++)
        {
            Cell *cell = new Cell();
            setItem(i, j, cell);
            cells.append(cell);
        }
    }
}

void Inventory::mousePressEvent(QMouseEvent *event)
{
    Cell *cell = static_cast<Cell*> (itemAt(event->pos()));

    if (event->button() == Qt::LeftButton)
    {
        if (itemAt(event->pos()))
        {
            if (cell->getCount() == 0)
                return;

            QDrag *drag = new QDrag(this);
            QMimeData *mimedata = new QMimeData;

            QByteArray data;
            QDataStream stream(&data, QIODevice::WriteOnly);

            stream << cell->getItem()->getType() << cell->getCount() << cell->getItem()->getImage();

            mimedata->setData("Item", data);

            drag->setMimeData(mimedata);
            drag->setPixmap(QPixmap(IMAGE_PATH).scaled(100, 100));

            cell->subCount(cell->getCount());
            cell->updateText();
            drag->exec();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (cell->getCount())
        {
            cell->subCount(1);
            QSound::play(SOUND_PATH);
        }
    }

    emit somethingDone();
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("Item"))
        event->acceptProposedAction();
    else
        event->accept();
    //emit somethingDone();
}

void Inventory::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("Item") && itemAt(event->pos()))
    {
        QByteArray data = event->mimeData()->data("Item");
        QDataStream stream(&data, QIODevice::ReadOnly);

        QString type;
        int count;

        stream >> type >> count;

        Cell *cell = static_cast<Cell*>(itemAt(event->pos()));

        Item dItem(type);
        cell->setItem(dItem);
        cell->addCount(count - 1);

        event->acceptProposedAction();
        event->accept();

        emit somethingDone();
    }
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("Item"))
    {
        event->acceptProposedAction();
        viewport()->update();
        //emit somethingDone();
    }
    else
        event->accept();
    //emit somethingDone();
}
