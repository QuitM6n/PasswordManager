#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QTab *tab = new QTab;
  tab->resize(550, 430);

  QPushButton *cancel_btn = new QPushButton(tr("Cancel"));
  cancel_btn->setMinimumSize(20,10);

  QVBoxLayout *vbox_layout = new QVBoxLayout(this);
  vbox_layout->addWidget(tab);
  vbox_layout->addWidget(cancel_btn);

  QPalette pal = QPalette();
  QWidget *wgt = new QWidget(this);
  wgt->setAutoFillBackground(true);
  wgt->setLayout(vbox_layout);
  wgt->setPalette(pal);

  QObject::connect(cancel_btn,SIGNAL(clicked(bool)),qApp,SLOT(quit()));

  this->setCentralWidget(wgt);
  this->setWindowTitle("Password Manager");
}

MainWindow::~MainWindow()
{
    delete ui;
}

