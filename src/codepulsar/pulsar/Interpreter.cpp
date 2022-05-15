#include "Interpreter.h"
#include "ByteCodeCompiler.h"


Interpreter::Interpreter(string sourceCode) {
    this->sourceCode = sourceCode;
}

void Interpreter::interpret() {
    ByteCodeCompiler* byteCodeCompiler = new ByteCodeCompiler(this->sourceCode);
    byteCodeCompiler->compileByteCode();
}
