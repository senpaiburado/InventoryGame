#include "playground.h"

Playground::Playground(QMainWindow *mainWin, QWidget *parent) :
    QMainWindow(parent)
{
    int port;
    QString ip;

    auto getType = [&]() {
        QMessageBox question;
        auto buttonClient = question.addButton(QString("Client"), QMessageBox::ApplyRole);
        auto buttonServer = question.addButton(QString("Server"), QMessageBox::ApplyRole);
        auto buttonSolo = question.addButton(QString("Solo"), QMessageBox::ApplyRole);

        question.about(nullptr, tr("New Game"), tr("Select mode!"));

        connect(buttonClient, &QPushButton::clicked, this, [&] {
           type = Type::ClientType;
           ip = QInputDialog::getText(this, tr("Client"), tr("Enter IP: "), QLineEdit::Normal, tr("127.0.0.1"));
           port = QInputDialog::getInt(this, tr("Client"), tr("Enter port: "), 1, 1);
        });
        connect(buttonServer, &QPushButton::clicked, this, [&] {
           type = Type::ServerType;
           port = QInputDialog::getInt(this, "Server", "Enter port: ", 1, 1);
        });
        connect(buttonSolo, &QPushButton::clicked, this, [&] {
           type = Type::SoloType;
        });

        question.exec();
    };

    getType();

    setAttribute(Qt::WA_DeleteOnClose, true);
    mainWindow = mainWin;
    setGeometry(mainWin->geometry());

    backButton = new QPushButton("Main Menu");
    connect(backButton, &QPushButton::clicked, this, &Playground::back);

    inventory = new Inventory(3, 3);
    inventory->initCells();

    apple = new Item(QString("Food"));
    apple->setPixmap(QPixmap::fromImage(*apple->getImage()));
    apple->resize(60, 65);

    QWidget *widget = new QWidget(this);

    lay = new QVBoxLayout(widget);

    lay->addWidget(backButton);

    lay->addWidget(apple, 0, Qt::AlignCenter);

    lay->addWidget(inventory, 0, Qt::AlignCenter);

    widget->setLayout(lay);

    setCentralWidget(widget);

    if (type == Type::ServerType)
    {
        this->setWindowTitle("InventoryGame [Server]");
        server = new Server(this);
        server->listenPort(port);
        connect(server, &Server::serverGotConnected, this, &Playground::updateServerData);
        connect(server, &Server::gotData, this, &Playground::setServerData);
        connect(inventory, &Inventory::somethingDone, this, &Playground::updateServerData);
    }
    else if (type == Type::ClientType)
    {
        this->setWindowTitle("InventoryGame [Client]");
        client = new Client(this);
        client->connectToServer(ip, port);
        connect(client, &Client::gotData, this, &Playground::setClientData);
        connect(inventory, &Inventory::somethingDone, this, &Playground::updateClientData);
    }
}

Playground::~Playground()
{
    delete backButton;
    delete inventory;
}

void Playground::back()
{
    mainWindow->show();
    close();
}

void Playground::updateServerData()
{
    if (type != Type::ServerType)
        return;

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    for (int i = 0; i < inventory->rowCount(); i++)
    {
        for (int j = 0; j < inventory->columnCount(); j++)
        {
            Cell *cell = static_cast<Cell*>(inventory->item(i, j));
            if (cell->getItem())
            {
                stream << cell->getItem()->getType() << cell->getCount();
            }
            else
                stream << "Unknown" << -999;
        }
    }

    //if (server->tableData() != data)
        server->updateData(data);
}

void Playground::setServerData()
{
    if (type != Type::ServerType)
        return;

    delete inventory;

    inventory = new Inventory(3, 3);
    inventory->initCells();
    connect(inventory, &Inventory::somethingDone, this, &Playground::updateServerData);

    lay->addWidget(inventory);

    QByteArray data = server->tableData();
    QDataStream stream(&data, QIODevice::ReadOnly);

    for (int i = 0; i < inventory->rowCount(); i++)
    {
        for (int j = 0; j < inventory->columnCount(); j++)
        {
            Cell *cell = static_cast<Cell*>(inventory->item(i, j));
            QString iType;
            int count;
            stream >> iType >> count;

            DatabaseContoller db("QSQLITE", "db.qlite");

            if (iType == "Unknown" || count == -999)
            {
                db.setCommand(tr("UPDATE Cell SET ItemName = \"\", ImagePath = \"\""
                                 ", count = 0 WHERE raw = %3 and column = %4").arg(i).arg(j).arg(i).arg(j));
                db.run();
                continue;
            }
            db.setCommand(tr("INSERT INTO Cell VALUES(%1, %2, %3, %4, %5);").arg(i).arg(j).arg(iType).arg(IMAGE_PATH)
                          .arg(count));
            db.run();
            Item item(iType);
            cell->setItem(item);
            cell->setCount(count);
        }
    }
}

void Playground::updateClientData()
{
    if (type != Type::ClientType)
        return;

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    for (int i = 0; i < inventory->rowCount(); i++)
    {
        for (int j = 0; j < inventory->columnCount(); j++)
        {
            Cell *cell = static_cast<Cell*>(inventory->item(i, j));
            if (cell->getItem())
                stream << cell->getItem()->getType() << cell->getCount();
            else
                stream << "Unknown" << -999;
        }
    }

    //if (client->tableData() != data)
        client->updateData(data);
}

void Playground::setClientData()
{
    if (type != Type::ClientType)
        return;

    delete inventory;

    inventory = new Inventory(3, 3);
    inventory->initCells();
    connect(inventory, &Inventory::somethingDone, this, &Playground::updateClientData);

    lay->addWidget(inventory);

    QByteArray data = client->tableData();
    QDataStream stream(&data, QIODevice::ReadOnly);

    for (int i = 0; i < inventory->rowCount(); i++)
    {
        for (int j = 0; j < inventory->columnCount(); j++)
        {
            Cell *cell = static_cast<Cell*>(inventory->item(i, j));
            QString iType;
            int count;
            stream >> iType >> count;
            if (iType == "Unknown" || count == -999)
                continue;
            Item item(iType);
            cell->setItem(item);
            cell->setCount(count);
        }
    }
}

void Playground::dbg()
{
    qDebug() << "DBG";
}
