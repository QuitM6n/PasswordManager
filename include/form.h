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

// user search tab
class FormSearch : public QWidget
{
    Q_OBJECT

public:
    explicit FormSearch(QWidget *parent = nullptr);
    ~FormSearch();

public slots:
    void add_text_to_text_edit();

private:
     QLineEdit *line_edit;
     QTextEdit *txt_edit;
};

// tab for adding a password
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
};


#endif // FORM_H
