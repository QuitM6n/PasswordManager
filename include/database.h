#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "exception.h"

using namespace exception;

class Database : public QWidget
{
    Q_OBJECT
public:
   explicit Database(QWidget * parent = nullptr);
   ~Database() = default;

public:
    auto insertData(const QString &id_data,const QString &username,const QString& pass)  -> Code ;

    auto getData(const QString &id_data) -> QString ;

    auto updateData(const QString &data,const QString &id_data)-> Code ;

    auto deleteData(const QString&id_data) -> Code ;

private:
    Exception err;
    QSqlDatabase db;
};


//class HashingDatabase  : public Database {

//public:


//private:
//};

#endif // DATABASE_H
