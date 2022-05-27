#include "Interpreter.h"


Pulsar::Interpreter::Interpreter(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::Interpreter::interpret() {
    Pulsar::ByteCodeCompiler bcc = ByteCodeCompiler(this->sourceCode);
    bcc.compileByteCode();
}