#ifndef PASSWORD_H
#define PASSWORD_H

#include "exception.h"
#include "database.h"
#include <QObject>
#include <QtGlobal>
#include <QPalette>
#include <QWidget>
#include <QRandomGenerator>

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
      data[i] = data[i] + key.size()/2;
    }

    db.insertEncryptData(id,QString::fromStdString(data));
  }

  QString &Decrypt(const QString &id,std::string &data, const std::string key) {
    if (!key.size())
      err.error("Key incorrect: ", int(Error::KeyIsNotValid));

    for (int i = 0; i < data.size(); ++i) {
      data[i] = data[i] - key.size()/2;
    }

    db.updateEncryptData(QString::fromStdString(data),id);
  }

  QString GeneratePassword(int length) const {
    if (length <= 0) {
      err.error("size is wrong", int(Code::NOT_VALID));
      return "";
    }

    const QString possibleCharacters(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    for (int i = 0; i < length; ++i) {
      int index = rand() % possibleCharacters.length();
      QChar nextChar = possibleCharacters.at(index);
      randomString.append(nextChar);
    }
    return randomString;
  }

private:
  Exception err;
  EncryptStorage db;
};

#endif // PASSWORD_H
