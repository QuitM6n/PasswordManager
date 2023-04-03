#include "form.h"
#include "password.h"
#include "ui_form.h"
#include "database.h"
#include <iostream>

FormSearch::FormSearch(QWidget *parent) : QWidget(parent), validator() {
  QPushButton *btn_search = new QPushButton(tr("Search"));
  QLabel *id_search = new QLabel(tr("Search user by id"));
  id_search->font();

  id_edit = new QLineEdit();
  validator.isID(id_edit->text());

  txt_edit = new QTextEdit();
  txt_edit->setReadOnly(true);

  QGridLayout *grid_layout = new QGridLayout;
  grid_layout->addWidget(txt_edit, 0, 0);
  grid_layout->addWidget(id_edit, 2, 0);
  grid_layout->addWidget(id_search, 1, 0);
  grid_layout->addWidget(btn_search, 2, 1);

  QObject::connect(id_edit, SIGNAL(returnPressed()), this,
                   SLOT(add_text_to_text_edit()));

  Database *db = new Database;
  QObject::connect(btn_search, &QPushButton::clicked, db, [=]() {
    const QString data = db->getData(id_edit->text());
    txt_edit->append(data);
    id_edit->clear();
  });
  setLayout(grid_layout);

  QPalette pal = QPalette();
  pal.setColor(QPalette::Window,Qt::gray);
  this->setAutoFillBackground(true);
  this->setPalette(pal);
}

FormSearch::~FormSearch() {
  delete id_edit;
  delete txt_edit;
}

void FormSearch::add_text_to_text_edit() {
  txt_edit->setText(id_edit->text());
  id_edit->clear();
}

FormPassword::FormPassword(QWidget *parent) : QWidget(parent) {
  QPushButton *add_btn = new QPushButton(tr("Add"));
  QPushButton *encrypt_btn = new QPushButton(tr("Encrypt to Password"));
  QPushButton *decrypt_btn = new QPushButton(tr("Decrypt to Password"));
  QPushButton *generate_password = new QPushButton(tr("Generate Password"));

  QLabel *label_name = new QLabel(tr("Username"));
  QLabel *label_password = new QLabel(tr("Password"));
  QLabel *label_id = new QLabel(tr("ID"));

  line_password = new QLineEdit;
  line_password->setEchoMode(QLineEdit::Password);
  validator.isPassword(line_password->text());

  line_name = new QLineEdit;
  line_id = new QLineEdit;
  validator.isID(line_id->text());

  Encrypter  *encrypt = new Encrypter;
  QGridLayout *grid_layout = new QGridLayout;
  grid_layout->addWidget(label_id, 0, 0);
  grid_layout->addWidget(line_id, 1, 0);
  grid_layout->addWidget(label_name, 2, 0);
  grid_layout->addWidget(line_name, 3, 0);
  grid_layout->addWidget(label_password, 4, 0);
  grid_layout->addWidget(line_password, 5, 0);
  grid_layout->addWidget(add_btn,6,0);
  grid_layout->addWidget(decrypt_btn,6,1);
  grid_layout->addWidget(encrypt_btn,7,0);
  grid_layout->addWidget(generate_password,7,1);

  QGroupBox *group_box = new QGroupBox(this);
  group_box->setLayout(grid_layout);

  Database *db = new Database;
  EncryptStorage *encrypt_db = new EncryptStorage;

  QObject::connect(add_btn, &QPushButton::clicked, db, [=]() {
    db->insertData(line_id->text(), line_name->text(), line_password->text());
    line_id->clear();
    line_name->clear();
    line_password->clear();
  });

  QObject::connect(encrypt_btn, &QPushButton::clicked, encrypt, [=]() {
    const QString key = QInputDialog::getText(this, tr("Tab name "),
                                              tr("Enter key for enrcypt : "),
                                              QLineEdit::Normal);
    const QString data = db->getData(line_id->text());
    encrypt->Encrypt(line_id->text(),data.toStdString(), key.toStdString());
    line_id->clear();
  });

  QObject::connect(decrypt_btn, &QPushButton::clicked, db, [=]() {
    const QString key =
        QInputDialog::getText(this, tr("Tab name "),
                              tr("Enter key for decrypt: "), QLineEdit::Normal);

    QString data = encrypt_db->getEncryptData(line_id->text());
    std::string str = qPrintable(data);
    const QString decrypt_data =  encrypt->Decrypt(line_id->text(),str, key.toStdString());
    qDebug()<<decrypt_data;
    line_id->clear();
  });

  QObject::connect(generate_password, &QPushButton::clicked, db, [=] {
    int length =
        QInputDialog::getInt(this, tr("Enter length for generate password"),
                             tr("Length: "), QLineEdit::Normal);

    QString pass = encrypt->GeneratePassword(length);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Are you a new user?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      db->updateData(line_id->text(), pass);

    } else {
      db->insertData(line_id->text(), "", pass);
    }
  });

  QPalette pal = QPalette();
  pal.setColor(QPalette::Window,Qt::gray);
  this->setAutoFillBackground(true);
  this->setPalette(pal);
}

FormPassword::~FormPassword() {
  delete line_password;
  delete line_name;
  delete line_id;


}
