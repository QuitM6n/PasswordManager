#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
#include <QWidget>

class Password : public QObject
{
   Q_OBJECT
public:
   explicit Password(QWidget *parent = nullptr);

public slots:
    void HashPassword(const QString &pass);
    void UnHashPassword(const QString &pass);
};


#endif // PASSWORD_H
