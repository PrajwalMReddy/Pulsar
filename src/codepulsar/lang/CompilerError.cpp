#include "CompilerError.h"


CompilerError::CompilerError() {
}

Error CompilerError::addError(string errorType, string message, int line) {
    Error error = {errorType, message, line};
    this->errors.push_back(error);
    return error;
}

bool CompilerError::hasError() {
    return errorCount() == 0;
}

int CompilerError::errorCount() {
    return this->errors.size();
}

vector<Error> CompilerError::getErrors() {
    return this->errors;
}