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

auto Database::updateData(const QString &data, const QString &id_data) -> Code {
  QSqlQuery query(db);

  return Code::SUCCESS;
}

auto Database::deleteData(const QString &id_data) -> Code {
    QSqlQuery query(db);

   return Code::SUCCESS;
}
