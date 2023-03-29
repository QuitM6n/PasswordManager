#include "qtab.h"
#include "form.h"
#include <QIcon>

QTab::QTab(QWidget *parent)
: QTabWidget(parent)
{
   auto bar = this->setUpMenu();

   tabWidget = new QTabWidget;
   tabWidget->resize(350,150);
   tabWidget->setTabShape(QTabWidget::Triangular);
   tabWidget->setTabPosition(QTabWidget::North);
   tabWidget->setUsesScrollButtons(true);
   tabWidget->setTabsClosable(true);
   tabWidget->setMovable(true);

   tabWidget->insertTab(tabWidget->count(),new FormSearch(),QIcon(QString("")),"Search User");
   tabWidget->insertTab(tabWidget->count(),new FormPassword(),QIcon(QString("")),"Password");

   QGridLayout*  layout = new QGridLayout;
   layout->addWidget(tabWidget,0,0);
   layout->addWidget(bar,0,1);

   QObject::connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTab()));

   setLayout(layout);
}

QMenuBar* QTab::setUpMenu() const noexcept
{
    QMenuBar *menu_bar = new QMenuBar(nullptr);
    QMenu *menu = new QMenu(tr("Menu"));

    QAction *add_tab = new QAction(tr("Add Tab"));
    QAction *settings = new QAction(tr("Settings"));
    menu->addAction(add_tab);
    menu->addAction(settings);
    menu_bar->addMenu(menu);


   QObject::connect(add_tab,SIGNAL(triggered(bool)),this,SLOT(addTab()));

    return menu_bar;
}

void QTab::removeTab() const noexcept
{
    tabWidget->removeTab(tabWidget->currentIndex());
}

void QTab::addTab()
{
   QString name_tab =  QInputDialog::getText(this,tr("Tab name "),
                                             tr("Enter new tab name: "),QLineEdit::Normal);

   tabWidget->addTab(new QWidget(),name_tab);
}


