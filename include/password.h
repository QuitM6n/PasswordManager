#ifndef PASSWORD_H
#define PASSWORD_H

#include "exception.h"
#include "database.h"
#include <QObject>
#include <QWidget>

using namespace exception;

enum class Error : int {

  NotKey = -1,

  KeyIsWrong = -2,

  KeyIsNotValid = -3

};

class Encrypter : public QObject {
  Q_OBJECT
public:
  explicit Encrypter(QWidget *parent = nullptr) : QObject(parent) {}

  ~Encrypter() = default;

public slots:

  void Encrypt(const QString &id,std::string data, const std::string key) {
    if (!key.size())
      err.error("Key is empty: ", int(Error::KeyIsNotValid));

    for (int i = 0; i < data.size(); ++i) {
      data[i] = data[i] + 2;
    }

    db.insertEncryptData(id,QString::fromStdString(data));
  }

  QString &Decrypt(const QString &id,std::string &data, const std::string key) {
    if (!key.size())
      err.error("Key incorrect: ", int(Error::KeyIsNotValid));

    for (int i = 0; i < data.size(); ++i) {
      data[i] = data[i] - 2;
    }

    db.updateEncryptData(QString::fromStdString(data),id);
  }

private:
  Exception err;
  EncryptStorage db;
};

#endif // PASSWORD_H
