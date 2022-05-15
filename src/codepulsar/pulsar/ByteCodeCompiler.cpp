#include "ByteCodeCompiler.h"
#include "Parser.h"


ByteCodeCompiler::ByteCodeCompiler(string sourceCode) {
    this->sourceCode = sourceCode;
}

void ByteCodeCompiler::compileByteCode() {
    Parser* parser = new Parser(this->sourceCode);
    parser->parse();
}
