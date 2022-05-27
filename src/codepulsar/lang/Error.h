#ifndef CODEPULSAR_ERROR_H
#define CODEPULSAR_ERROR_H

#include <string>


namespace Pulsar {
    struct Error {
        std::string errorType;
        std::string message;
        int line;

        std::string getErrorType() { return this->errorType; }
        std::string getMessage() { return this->message; }
        int getLine() { return this->line; }
    };
}


#endif
