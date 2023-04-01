#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>

#include "exception.h"

using namespace exception;

class Validator {
public:
    decltype(auto) isPassword(const QString& pass){
        if(pass.isEmpty()){
            err.error("Enter incorrect the password");
            return Code::WRONG_PASSWORD;
        }else if(pass.size()<=5){
            err.error("The password is shorter than necessary");
            return Code::WRONG_PASSWORD;
        }else if(!pass.at(0).isUpper()){
            err.error("The password must start with a capital letter");
            return Code::WRONG_PASSWORD;
        }
         for(int i = 0;i<pass.length();++i)
            if(pass.at(i).isDigit()){
                err.error("The password cannot contain only numbers");
                return Code::WRONG_PASSWORD;
            }

        return Code::CORRECT;
    }

    decltype(auto) isName(const QString &name){
        if(name.isEmpty()){
            err.error("Enter Incorrect name");
            return Code::WRONG_NAME;
        }

        return Code::CORRECT;
    }

    decltype(auto) isID(const QString& id){
        if(id.isEmpty()){
            err.error("Enter Incorrect ID");
            return Code::WRONG_ID;
        }
        return Code::CORRECT;
    }

    Validator() = default;
    ~Validator() = default;

private:
    Exception err;
};


#endif // VALIDATOR_H
