#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::ByteCodeCompiler::compileByteCode() {
    Pulsar::Parser parser = Parser(this->sourceCode);
    this->program = parser.parse();
    this->symbolTable = parser.getSymbolTable();

    this->errors = parser.getErrors();
    if (this->errors->hasError()) return;

    ASTPrinter astPrinter = ASTPrinter();
    astPrinter.print(this->program);

    Validator validator = Validator(this->program, this->symbolTable, this->errors);
    validator.validate();
    if (this->errors->hasError()) return;

    TypeChecker checker = TypeChecker(this->program, this->symbolTable, this->errors);
    checker.check();
    if (this->errors->hasError()) return;

    compile();
}

void Pulsar::ByteCodeCompiler::compile() {
}

Pulsar::CompilerError* Pulsar::ByteCodeCompiler::getErrors() {
    return this->errors;
}
