#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::ByteCodeCompiler::compileByteCode() {
    Pulsar::Parser parser = Parser(this->sourceCode);
    parser.parse();
    this->errors = parser.getErrors();

    if (this->errors->hasError()) return;
    compile();
}

void Pulsar::ByteCodeCompiler::compile() {
}

Pulsar::CompilerError* Pulsar::ByteCodeCompiler::getErrors() {
    return this->errors;
}