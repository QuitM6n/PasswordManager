#include "qtab.h"
#include "form.h"


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
    QAction *loger = new QAction(tr("Logger"));
    QAction *settings = new QAction(tr("Settings"));
    menu->addAction(add_tab);
    menu->addAction(loger);
    menu->addAction(settings);
    menu_bar->addMenu(menu);

   QObject::connect(add_tab,SIGNAL(triggered(bool)),this,SLOT(addTab()));
   QObject::connect(loger,SIGNAL(triggered(bool)),this,SLOT(checkLogger()));

   return menu_bar;
}

QWidget *QTab::widgetLoggerSetUP()  noexcept {

   QWidget *log_wgt = new QWidget;
   QStringList list_labels = {"Code Error","About Error"};
   table = new QTableWidget(2,2);
   table->setHorizontalHeaderLabels(list_labels);
   table->setSelectionMode(QAbstractItemView::SingleSelection);
   table->setSelectionBehavior(QAbstractItemView::SelectRows);

   QPushButton *clear_btn = new QPushButton(tr("Clear logs"));
   QPushButton *show_btn = new QPushButton(tr("Show logs"));
   QHBoxLayout * hbox_layout = new QHBoxLayout;
   QVBoxLayout* vbox_layout = new QVBoxLayout;

   vbox_layout->addWidget(show_btn);
   hbox_layout->addWidget(clear_btn);

   hbox_layout->addWidget(table);
   hbox_layout->addLayout(vbox_layout);

   QObject::connect(clear_btn,SIGNAL(clicked(bool)),this,SLOT(clearLogsFile()));
   QObject::connect(show_btn,SIGNAL(clicked(bool)),this,SLOT(showLoggers()));

   log_wgt->setLayout(hbox_layout);

   return log_wgt;
}

void QTab::removeTab() const noexcept {
   tabWidget->removeTab(tabWidget->currentIndex());
}

void QTab::checkLogger() noexcept {
   auto wgt = widgetLoggerSetUP();
   tabWidget->insertTab(tabWidget->count(), wgt, QIcon(QString("")),
                        "Logger");
}

void QTab::addTab()noexcept
{
   QString name_tab =  QInputDialog::getText(this,tr("Tab name "),
                                             tr("Enter new tab name: "),QLineEdit::Normal);

   tabWidget->addTab(new QWidget(),name_tab);
}

void QTab::clearLogsFile() {
   QFile file("C:/Users/Ruslan/Documents/ManagePassword/loger.txt");
   try {
     if (file.remove()) {
       file.open(QIODevice::WriteOnly);
       file.close();
     }
   } catch (...) {
      err.error("Failed to clear file",int(Code::BAD_REQUEST));
   }
}

void QTab::showLoggers() {
   QFile file("C:/Users/Ruslan/Documents/ManagePassword/loger.txt");
   if (!file.open(QIODevice::ReadOnly)) {
      err.error("Failed to open file for read", int(Code::OPEN_ERROR));
   }

   QTextStream stream(&file);
   while (!stream.atEnd()) {
       QString fieldVal, line = stream.readLine();
       QStringList list = line.split(":");
       if(list.count() > 1)
           fieldVal = list.at(1).trimmed();
      QTableWidgetItem *item_code = new QTableWidgetItem(fieldVal);
      table->setItem(0, 0, item_code);
   }


   // TODO
   file.close();
}
