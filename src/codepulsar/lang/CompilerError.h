#ifndef CODEPULSAR_COMPILERERROR_H
#define CODEPULSAR_COMPILERERROR_H

#include <vector>

#include "Error.h"

using namespace std;


class CompilerError {
    public:
        CompilerError();
        Error addError(string errorType, string message, int line);
        bool hasError();
        int errorCount();
        vector<Error> getErrors();

    private:
        vector<Error> errors;
};


#endif
