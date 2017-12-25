#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QFrame>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QMetaEnum>
#include <QDataStream>

#include "resources.h"

class Item : public QLabel
{
    Q_OBJECT
public:

    explicit Item(const QString &type, QWidget *parent = nullptr);
    ~Item();

    const QString &getType() const;
    void setType(const QString &itemType);

    QImage *getImage() const;

    void mousePressEvent(QMouseEvent *event);

private:
    QString *type;
    QImage *image;
};

#endif // ITEM_H
