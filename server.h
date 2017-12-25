#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>

#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);

    void listenPort(int port);

    QByteArray &tableData();
    void updateData(const QByteArray &newData);

private:
    QTcpServer *server;
    QTcpSocket *client;
    int port;

    QByteArray data;

    bool hasClient;

    void sendMessage(QTcpSocket *client, const QByteArray &msgText);

private slots:
    void connected();
    void getData();
    void removeClient();

signals:
    void serverGotConnected();
    void gotData();
};

#endif // SERVER_H
