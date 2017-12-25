#ifndef DATABASECONTOLLER_H
#define DATABASECONTOLLER_H

#include <QSql>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>

#include <QThread>
#include <QString>
#include <QDebug>

class DatabaseContoller : public QThread
{
    Q_OBJECT
public:
    explicit DatabaseContoller(const QString &dbType, const QString &dbName, QObject *parent = nullptr);
    ~DatabaseContoller();

    void run();

    void setCommand(const QString &request);

    QSqlQuery result();

private:
    QString *dbType;
    QString *dbName;

    QString request;
    QSqlQuery query;
};

#endif // DATABASECONTOLLER_H
