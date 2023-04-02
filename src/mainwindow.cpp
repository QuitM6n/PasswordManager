#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTab *tab = new QTab(this);
    tab->resize(550,430);
    setCentralWidget(tab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

