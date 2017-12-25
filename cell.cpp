#include "cell.h"

Cell::Cell(const Item &item)
    : QTableWidgetItem()
{
    count = 0;
    this->item = nullptr;

    setTextAlignment(Qt::AlignLeft);

    setItem(item);
}

Cell::Cell()
{
    count = 0;
    item = nullptr;
}

Cell::~Cell()
{
    delete item;
}

void Cell::setItem(const Item &item)
{
    if (this->item != nullptr && this->item->getType() != item.getType())
    {
        QMessageBox::information(nullptr, QString("Incorrect item!"), "Cell's item is " + this->item->getType()
                                 + ". You can't add " + item.getType() + "!", QMessageBox::Ok);
        return;
    }
    else
    {
        if (this->item == nullptr)
            this->item = new Item(item.getType());
        else
        {
            count++;
            updateText();
            return;
        }
        count++;

        setIcon(QIcon(QPixmap::fromImage(*item.getImage())));
        updateText();
    }
}

Item *Cell::getItem()
{
    return item;
}

int Cell::getCount()
{
    return count;
}

void Cell::addCount(int value)
{
    count += value;
    updateText();
}

void Cell::subCount(int value)
{
    int res = count - value;
    if (res > 0)
    {
        count -= value;
        updateText();
    }
    else if (res == 0)
    {
        count = 0;
        delete item;
        item = nullptr;
        setIcon(QIcon());
        updateText();
    }
    else
        throw std::runtime_error("Count of item cannot be zero!");
}

void Cell::setCount(unsigned int value)
{
    count = value;
    if (count == 0)
    {
        delete item;
        item = nullptr;
        setIcon(QIcon());
        updateText();
    }
    else
        updateText();
}

void Cell::updateText()
{
    setText(count == 0 ? QString("") : QString::number(count));
}
