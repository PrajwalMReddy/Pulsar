#include "CompilerError.h"


Pulsar::CompilerError::CompilerError() {
    this->errors = new std::vector<Pulsar::Error>;
}

Pulsar::Error Pulsar::CompilerError::addError(std::string errorType, std::string message, int line) {
    Error error = {errorType, message, line};
    this->errors->push_back(error);
    return error;
}

bool Pulsar::CompilerError::hasError() {
    return this->errors->size() != 0;
}

int Pulsar::CompilerError::errorCount() {
    return this->errors->size();
}

std::vector<Pulsar::Error>* Pulsar::CompilerError::getErrors() {
    return this->errors;
}
