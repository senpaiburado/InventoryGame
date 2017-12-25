#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent)
{
    hasClient = false;
    client = nullptr;
    server = new QTcpServer(this);
    port = 0;
    connect(server, &QTcpServer::newConnection, this, &Server::connected);
}

void Server::listenPort(int port)
{
    server->listen(QHostAddress::Any, port);
}

QByteArray &Server::tableData()
{
    return data;
}

void Server::updateData(const QByteArray &newData)
{
    data = newData;
    if (hasClient)
    {
        sendMessage(client, data);
    }
}

void Server::sendMessage(QTcpSocket *client, const QByteArray &msgText)
{
    client->write(msgText.toStdString().c_str(), msgText.length() * sizeof(char));
    client->flush();
    qDebug() << msgText.toStdString().c_str() << endl;
}

void Server::connected()
{
    if (hasClient)
    {
        sendMessage(server->nextPendingConnection(), QByteArray("Sorry, but server is busy now!"));
        return;
    }
    client = server->nextPendingConnection();
    hasClient = true;

    connect(client, &QTcpSocket::readyRead, this, &Server::getData);
    connect(client, &QTcpSocket::disconnected, this, &Server::removeClient);

    emit serverGotConnected();
}

void Server::getData()
{
    data = client->readAll();
    emit gotData();
}

void Server::removeClient()
{
    client->close();
    hasClient = false;
}
