#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::ByteCodeCompiler::compileByteCode() {
    Pulsar::Parser parser = Parser(this->sourceCode);
    this->program = parser.parse();

    this->errors = parser.getErrors();
    if (this->errors->hasError()) return;

    ASTPrinter astPrinter = ASTPrinter();
    astPrinter.print(this->program);

    compile();
}

void Pulsar::ByteCodeCompiler::compile() {
}

Pulsar::CompilerError* Pulsar::ByteCodeCompiler::getErrors() {
    return this->errors;
}