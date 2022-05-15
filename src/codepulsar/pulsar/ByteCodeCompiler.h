#ifndef CODEPULSAR_BYTECODECOMPILER_H
#define CODEPULSAR_BYTECODECOMPILER_H

#include <iostream>

using namespace std;


class ByteCodeCompiler {
    public:
        ByteCodeCompiler(string sourceCode);
        void compileByteCode();

    private:
        string sourceCode;
};


#endif
