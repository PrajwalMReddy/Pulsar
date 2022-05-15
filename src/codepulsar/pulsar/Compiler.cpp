#include "Compiler.h"
#include "ByteCodeCompiler.h"


Compiler::Compiler(string sourceCode) {
    this->sourceCode = sourceCode;
}

void Compiler::init() {
    ByteCodeCompiler* byteCodeCompiler = new ByteCodeCompiler(this->sourceCode);
    byteCodeCompiler->compileByteCode();
}
