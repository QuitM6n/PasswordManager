#include "form.h"
#include "password.h"
#include "ui_form.h"

FormSearch::FormSearch(QWidget *parent) : QWidget(parent) {
  QPushButton *btn_search = new QPushButton(tr("search"));
  QLabel *id_search = new QLabel(tr("Search user by id"));
  id_search->font();

  line_edit = new QLineEdit();
  txt_edit = new QTextEdit();
  txt_edit->setReadOnly(true);

  QGridLayout *grid_layout = new QGridLayout;
  grid_layout->addWidget(txt_edit, 0, 0);
  grid_layout->addWidget(line_edit, 2, 0);
  grid_layout->addWidget(id_search, 1, 0);
  grid_layout->addWidget(btn_search, 2, 1);

  QObject::connect(line_edit, SIGNAL(returnPressed()), this,
                   SLOT(add_text_to_text_edit()));
  QObject::connect(btn_search, SIGNAL(clicked()), this,
                   SLOT(add_text_to_text_edit()));

  setLayout(grid_layout);
}

FormSearch::~FormSearch() {
  delete line_edit;
  delete txt_edit;
}

void FormSearch::add_text_to_text_edit() {
  txt_edit->setText(line_edit->text());
  line_edit->clear();
}

FormPassword::FormPassword(QWidget *parent) : QWidget(parent) {

  QPushButton *add_btn = new QPushButton(tr("Add"));
  QPushButton *hash_btn = new QPushButton(tr("Hash Password"));
  QPushButton *unhash_btn = new QPushButton(tr("UnHash Password"));

  QLabel *label_name = new QLabel(tr("Username"));
  QLabel *label_password = new QLabel(tr("Password"));
  QLabel *label_id = new QLabel(tr("ID"));

  line_password = new QLineEdit;
  line_name = new QLineEdit;
  line_id = new QLineEdit;

  Password *pass = new Password;

  QGridLayout *grid_layout = new QGridLayout;
  grid_layout->addWidget(label_id, 0, 0);
  grid_layout->addWidget(line_id, 1, 0);
  grid_layout->addWidget(label_name, 2, 0);
  grid_layout->addWidget(line_name, 3, 0);
  grid_layout->addWidget(label_password, 4, 0);
  grid_layout->addWidget(line_password, 5, 0);
  grid_layout->addWidget(add_btn, 1, 1);
  grid_layout->addWidget(hash_btn, 3, 1);
  grid_layout->addWidget(unhash_btn, 5, 1);

  QGroupBox *group_box = new QGroupBox(this);
  group_box->setLayout(grid_layout);

  QObject::connect(hash_btn, &QPushButton::clicked, pass, [=]() {
    QString password = line_password->text();
    pass->HashPassword(password);
  });

  QObject::connect(unhash_btn, SIGNAL(clicked(true)), pass,
                   SLOT(UnHashPassword()));
}

FormPassword::~FormPassword() {
  delete line_password;
  delete line_name;
  delete line_id;
}
