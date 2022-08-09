#include "Interpreter.h"


Pulsar::Interpreter::Interpreter(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::Interpreter::interpret() {
    Pulsar::ByteCodeCompiler bcc = ByteCodeCompiler(this->sourceCode);
    this->instructions = bcc.compileByteCode();


    this->symbolTable = bcc.getSymbolTable();
    this->values = bcc.getValues();

    this->errors = bcc.getErrors();
    ErrorReporter::report(this->errors, this->sourceCode);

    Disassembler disassembler = Disassembler(this->instructions, this->symbolTable, this->values);
    disassembler.disassemble();
}