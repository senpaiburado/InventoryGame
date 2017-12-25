#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QSound>
#include <QMessageBox>
#include <QInputDialog>

#include <QDebug>

#include "inventory.h"
#include "resources.h"
#include "server.h"
#include "client.h"
#include "databasecontoller.h"

class Playground : public QMainWindow
{
    Q_OBJECT
    enum Type {
        SoloType = 0,
        ClientType = 1,
        ServerType = 2
    };
public:
    explicit Playground(QMainWindow *mainWin, QWidget *parent = nullptr);
    ~Playground();

private:
    QMainWindow *mainWindow;

    QPushButton *backButton;

    Inventory *inventory;

    Item *apple;

    Server *server;
    Client *client;

    QVBoxLayout *lay;

    Type type;

public slots:
    void back();

    void updateServerData();
    void setServerData();

    void updateClientData();
    void setClientData();

    void dbg();
};

#endif // PLAYGROUND_H
