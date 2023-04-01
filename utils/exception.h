#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QChar>
#include <QException>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QLoggingCategory>


namespace exception {
    enum class Code : int {
        SUCCESS = 0,

        CORRECT = 0,

        OPEN_ERROR = -1,

        NOT_EXISTING = -2,

        WRONG_PASSWORD = -3,

        WRONG_NAME = -4,

        WRONG_ID = -5,

        WRONG_TYPE = -6,

        BAD_REQUEST = -7,

        NOT_VALID = -8
    };

class Exception {
public:
   Exception() {}

   Exception(const QChar *error) : err_message(error) {}

  ~Exception() noexcept {}

  const QChar *what() const noexcept { return err_message; }

  template<typename Type>
  void error(const Type error,const int code_error = 0) const noexcept {
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly)) {
      QTextStream stream(&file);  
      stream<< code_error <<error;
    }else{
        QMessageBox::critical(nullptr,"Error","Failed to open file");
    }
  }

private:
  const QChar *err_message;
  const QString file_name = "C:/Users/Ruslan/Documents/ManagePassword/loger.txt";
};

} // namespace exception

#endif // EXCEPTION_H
