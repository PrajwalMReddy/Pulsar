#include "Compiler.h"


Pulsar::Compiler::Compiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::Compiler::init() {
    Pulsar::ByteCodeCompiler bcc = ByteCodeCompiler(this->sourceCode);
    bcc.compileByteCode();

    this->errors = bcc.getErrors();
    ErrorReporter::report(this->errors, this->sourceCode);
}