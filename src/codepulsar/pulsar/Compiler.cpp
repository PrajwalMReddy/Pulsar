#include "Compiler.h"


Pulsar::Compiler::Compiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::Compiler::init() {
    Pulsar::ByteCodeCompiler bcc = ByteCodeCompiler(this->sourceCode);
    bcc.compileByteCode();
}