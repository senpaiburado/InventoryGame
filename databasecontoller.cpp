#include "databasecontoller.h"

DatabaseContoller::DatabaseContoller(const QString &dbType, const QString &dbName, QObject *parent)
    : QThread(parent)
{
    this->dbType = new QString(dbType);
    this->dbName = new QString(dbName);
}

DatabaseContoller::~DatabaseContoller()
{
    delete dbName;
    delete dbType;
}

void DatabaseContoller::run()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(*dbType);
    db.setDatabaseName(*dbName);
    if (!db.open())
    {
        qDebug() << "Error opening db" << endl;
        return;
    }
    query = db.exec(request);
    db.close();
}

void DatabaseContoller::setCommand(const QString &request)
{
    this->request = request;
}

QSqlQuery DatabaseContoller::result()
{
    return query;
}
