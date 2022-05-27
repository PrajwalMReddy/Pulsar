#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::ByteCodeCompiler::compileByteCode() {
    Pulsar::Parser parser = Parser(this->sourceCode);
    parser.parse();
}