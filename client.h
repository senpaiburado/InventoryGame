#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QMessageBox>
#include <QTextCodec>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);
    ~Client();

    void connectToServer(const QString &ip, int port);

    QByteArray &tableData();
    void updateData(const QByteArray &newData);

private:
    QTcpSocket *socket;

    QByteArray data;

private slots:
    void getData();
    void getError(QAbstractSocket::SocketError err);

signals:
    void gotData();
};

#endif // CLIENT_H
