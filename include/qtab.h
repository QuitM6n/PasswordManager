#ifndef QTAB_H
#define QTAB_H

#include <QTabWidget>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QInputDialog>

class QTab : public QTabWidget
{
    Q_OBJECT
public:
    QTab(QWidget *parent = nullptr);

public:
    QMenuBar* setUpMenu()const noexcept;

public slots:
    void removeTab() const noexcept;

public slots:
    void addTab();

private:
     QTabWidget *tabWidget;
};

#endif // QTAB_H
