#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
#include <QWidget>

class Encrypter : public QObject
{
   Q_OBJECT
public:
   explicit Encrypter(QWidget *parent = nullptr);

public slots:
    QString Encrypt(const QString &data,const QString &key);

    QString Decrypt(const QString &data,const QString &key);
private:

};


#endif // PASSWORD_H
