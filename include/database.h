#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "exception.h"

using namespace exception;

class Database : public QWidget
{
    Q_OBJECT
public:
   explicit Database(QWidget * parent = nullptr);

   ~Database() = default;


public:
  auto insertData(const QString &id_data, const QString &username="",
                  const QString &pass="") -> Code;

  auto getData(const QString &id_data) -> QString;

  auto deleteData(const QString &id_data) -> Code;

  auto updateData(const QString &id_data, const QString &password) -> Code;

protected:
    Exception err;
    QSqlDatabase db;
};

class EncryptStorage : protected Database {
public:
   auto insertEncryptData(const QString &id,const QString &data) -> Code;

   auto updateEncryptData(const QString &data,const QString& id) -> Code;

   auto getEncryptData(const QString& id) -> QString;

};


#endif // DATABASE_H
