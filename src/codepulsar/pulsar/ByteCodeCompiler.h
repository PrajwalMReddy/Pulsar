#ifndef CODEPULSAR_BYTECODECOMPILER_H
#define CODEPULSAR_BYTECODECOMPILER_H

#include <string>

#include "Parser.h"


namespace Pulsar {
    class ByteCodeCompiler {
        public:
            ByteCodeCompiler(std::string sourceCode);
            void compileByteCode();

        private:
            std::string sourceCode;
    };
}


#endif
