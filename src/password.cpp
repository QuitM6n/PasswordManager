#include "password.h"


Encrypter ::Encrypter(QWidget *parent) : QObject(parent) {}

QString Encrypter ::Encrypt(const QString &data, const QString &key) {
  // TODO // In the other case, stuck in an infinite loop.

}

QString Encrypter::Decrypt(const QString &data, const QString &key) {
 // TODO
}
