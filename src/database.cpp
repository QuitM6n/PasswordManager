#include "database.h"

Database::Database(QWidget *parent) : QWidget(parent), err(nullptr) {

  if (QSqlDatabase::contains("MyConnect")) {
    db = QSqlDatabase::database("MyConnect");
  } else {
    db = QSqlDatabase::addDatabase("QPSQL", "MyConnect");
  }

  if(!db.isValid()){
        err.error("Database isn't valid",int(Code::NOT_VALID));
  }

  db.setHostName("localhost");
  db.setDatabaseName("postgres");
  db.setUserName("postgres");
  db.setPassword("Ruslan5655");
  bool ok = db.open();

  if (!ok) {
    err.error("Failed to open database",int(Code::OPEN_ERROR));

  }
}

auto Database::insertData(const QString &id_data, const QString &username,
                          const QString &pass) -> Code {

  QSqlQuery query(db);
  const QString insertSql = "INSERT INTO ManagePassword (id,username,password) "
                            "VALUES( ?, ?, ?)";

  if (query.prepare(insertSql)) {
    query.addBindValue(id_data);
    query.addBindValue(username);
    query.addBindValue(pass);
    query.exec();
  } else {
    err.error("Failed to add data to database",int(Code::BAD_REQUEST));
    return Code::BAD_REQUEST;
  }

  return Code::SUCCESS;
}

auto Database::getData(const QString &id_data) -> QString {
  QSqlQuery query(db);
  const QString selectSql =
      "SELECT username,password FROM ManagePassword WHERE id = :id_data";

  query.prepare(selectSql);
  query.bindValue(":id_data", id_data);
  if (!query.exec()) {
    err.error("Failed to get data from db",int(Code::BAD_REQUEST));
    return "BAD_REQUEST to database";
  }

  QString data;
  while (query.next()) {
    QString username = query.value(0).toString();
    QString password = query.value(1).toString();
    data = username+ " : " + password;
  }
  return data;
}

auto Database::deleteData(const QString &id_data) -> Code {
  QSqlQuery query(db);
  const QString deleteSql = "DELETE FROM ManagePassword WHERE id = ?";

  if (query.prepare(deleteSql)) {
    query.addBindValue(id_data);
    query.exec();
  } else {
    err.error("Failed to delete into db", int(Code::BAD_REQUEST));
  }

  return Code::SUCCESS;
}

auto Database::updateData(const QString &id, const QString &password) -> Code {
  if (id.isEmpty() && password.isEmpty()) {
    err.error("id or password is wrong", int(Code::NOT_VALID));
  }

  QSqlQuery query(db);

  const QString updateSql =
      "UPDATE ManagePassword SET password=:password WHERE id=:id";

  if (query.prepare(updateSql)) {
    query.bindValue(":id", id);
    query.bindValue(":password", password);
    query.exec();
  } else {
    err.error("Failed to update data", int(Code::BAD_REQUEST));
      qDebug() << "SqLite error:" << query.lastError();

  }

  return Code::SUCCESS;
}

bool Database::dbIsValid() const {
  return db.tables().contains(QLatin1String("ManagePassword")),
         db.tables().contains(QLatin1String("EncryptData"));
}

auto EncryptStorage::insertEncryptData(const QString &id, const QString &data)
    -> Code {
  if (id.isEmpty()) {
    err.error("Id id wrong", int(Code::WRONG_ID));
  }

  QSqlQuery query(db);
  const QString insertSql = "INSERT INTO EncryptData(id,data)"
                            "VALUES(?,?);";

  if (query.prepare(insertSql)) {
    query.addBindValue(id);
    query.addBindValue(data);
    query.exec();
  } else {
    err.error("Failed to insert db", int(Code::BAD_REQUEST));
  }

  return Code::SUCCESS;
}

auto  EncryptStorage::updateEncryptData(const QString &data,const QString &id) -> Code
{
    if(data.isEmpty()){
        err.error("Data is empty",int(Code::NOT_VALID));
    }
    QSqlQuery query(db);
    const QString updateSql = "UPDATE EncryptData SET data =:data WHERE id =:id";

    if(query.prepare(updateSql)){
        query.bindValue(":data",data);
        query.bindValue(":id",id);
        query.exec();
    }else{
         err.error("Failed to update db", int(Code::BAD_REQUEST));
    }

    return Code::SUCCESS;
}

auto EncryptStorage::getEncryptData(const QString &id) -> QString {
  QSqlQuery query(db);
  const QString selectSql = "SELECT data FROM EncryptData WHERE id = ?";

  if (query.prepare(selectSql)) {
    query.addBindValue(id);
    query.exec();
  } else {
    err.error("Failed to select db", int(Code::BAD_REQUEST));
  }

  QString data = "";
  while(query.next()){
    data = query.value(0).toString();
  }

  return data;
}
