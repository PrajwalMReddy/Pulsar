#ifndef CODEPULSAR_BYTECODECOMPILER_H
#define CODEPULSAR_BYTECODECOMPILER_H

#include <string>

#include "Parser.h"
#include "../util/ErrorReporter.h"


namespace Pulsar {
    class ByteCodeCompiler {
        public:
            ByteCodeCompiler(std::string sourceCode);
            void compileByteCode();
            CompilerError* getErrors();

        private:
            // Input Data
            std::string sourceCode;

            // Output Data
            CompilerError* errors;

            // Core Functions
            void compile();
    };
}


#endif
