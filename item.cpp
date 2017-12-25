#include "item.h"

Item::Item(const QString &type, QWidget *parent)
    : QLabel(parent)
{
    this->type = new QString(type);
    this->image = new QImage(QImage(IMAGE_PATH).scaled(150, 150));
}

void Item::setType(const QString &itemType)
{
    *type = itemType;
}

Item::~Item()
{
    delete image;
    delete type;
}

QImage *Item::getImage() const
{
    return image;
}

const QString &Item::getType() const
{
    return *type;
}

void Item::mousePressEvent(QMouseEvent *event)
{
    if (event->button()== Qt::LeftButton)
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);

        stream << getType() << 1 << getImage() << false;

        mimeData->setData(QString("Item"), data);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap::fromImage(*getImage()).scaled(100, 100));

        drag->exec(Qt::CopyAction);
    }
}
