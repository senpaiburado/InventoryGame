#include "client.h"

#include <QApplication>

Client::Client(QObject *parent)
    :QObject(parent)
{
    socket = nullptr;
}

Client::~Client()
{
    delete socket;
}

void Client::connectToServer(const QString &ip, int port)
{
    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::connected, this, [&] {
        QMessageBox::information(nullptr, tr("Server found!"), tr("You have found the server."), QMessageBox::Ok);
    });
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(getError(QAbstractSocket::SocketError)));
    connect(socket, &QTcpSocket::readyRead, this, &Client::getData);
    connect(this, &Client::destroyed, socket, &QTcpSocket::close);

    socket->connectToHost(ip, port);
}

QByteArray &Client::tableData()
{
    return data;
}

void Client::updateData(const QByteArray &newData)
{
    data = newData;
    socket->write(newData);
}

void Client::getData()
{
    data = socket->readAll();
    emit gotData();
}

void Client::getError(QAbstractSocket::SocketError err)
{
    QMessageBox::critical(nullptr, tr("Error!"), tr("Server not found! Game will be finished. Error: %1").arg(err),
                          QMessageBox::Ok);
    QApplication::exit(-1);
}
