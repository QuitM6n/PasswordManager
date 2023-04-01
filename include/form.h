#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QInputDialog>
#include "validator.h"
#include "database.h"

class FormSearch : public QWidget
{
    Q_OBJECT

public:
    explicit FormSearch(QWidget *parent = nullptr);
    ~FormSearch();

public slots:
    void add_text_to_text_edit();

private:
     QLineEdit *id_edit;
     QTextEdit *txt_edit;
     Validator validator;
};

class FormPassword : public QWidget {
    Q_OBJECT

public:
    explicit FormPassword(QWidget *parent = nullptr);
    ~FormPassword();

public slots:


private:
    QLineEdit *line_password;
    QLineEdit *line_name;
    QLineEdit * line_id;
    Validator validator;
};


#endif // FORM_H
