#ifndef CODEPULSAR_ERROR_H
#define CODEPULSAR_ERROR_H

#include <iostream>

using namespace std;


struct Error {
    string errorType;
    string message;
    int line;

    string getErrorType() { return this->errorType; }
    string getMessage() { return this->message; }
    int getLine() { return this->line; }
};

#endif
