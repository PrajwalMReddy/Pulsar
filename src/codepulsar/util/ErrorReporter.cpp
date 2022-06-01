#include "ErrorReporter.h"


void Pulsar::ErrorReporter::report(CompilerError *errors, std::string sourceCode) {
    if (!errors->hasError()) return;

    std::cout << "\n-- Errors --\n" << std::endl;
    reportErrors(errors, sourceCode);
}

void Pulsar::ErrorReporter::reportErrors(CompilerError *errors, std::string sourceCode) {
    std::vector<std::string> lines = splitString(sourceCode);

    for (int i = 0; i < errors->errorCount(); i++) {
        Error error = errors->getErrors()->at(i);

        std::cout << error.getErrorType() << " | ";
        std::cout << error.getMessage() << std::endl;
        std::cout << "Line " << error.getLine() << ": " << lines[error.getLine() - 1] << "\n" << std::endl;
    }

    exit(1);
}

std::vector<std::string> Pulsar::ErrorReporter::splitString(std::string sourceCode) {
    std::vector<std::string> lines;

    const char* charSourceCode = sourceCode.c_str();
    std::stringstream stringStreamSourceCode = std::stringstream(charSourceCode);

    std::string temp;

    while (std::getline(stringStreamSourceCode, temp, '\n')) {
        lines.push_back(temp);
    }

    return lines;
}
