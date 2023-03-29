#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>

class Database : public QWidget
{
    Q_OBJECT
public:
   explicit Database(QWidget * parent = nullptr);
};

#endif // DATABASE_H
