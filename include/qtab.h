#ifndef QTAB_H
#define QTAB_H

#include <QTabWidget>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QInputDialog>
#include <QStringList>
#include <QByteArray>
#include "exception.h"

using namespace exception;

class QTab : public QTabWidget
{
    Q_OBJECT
public:
    QTab(QWidget *parent = nullptr);

public:
    QMenuBar* setUpMenu()const noexcept;

    QWidget *widgetLoggerSetUP() noexcept;

public slots:
    void removeTab() const noexcept;

    void checkLogger() noexcept;

    void addTab() noexcept;

    void clearLogsFile();

    void showLoggers();

private:
     QTabWidget *tabWidget;
     QWidget *logger_wgt;
     QTableWidget *table;
     Exception err;
};

#endif // QTAB_H
