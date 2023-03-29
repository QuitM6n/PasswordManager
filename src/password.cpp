#include "password.h"



Password::Password(QWidget *parent):
    QObject(parent)
{

}

void Password::HashPassword(const QString &pass)
{
    qDebug()<<pass;

}

void Password::UnHashPassword(const QString &pass)
{

}
