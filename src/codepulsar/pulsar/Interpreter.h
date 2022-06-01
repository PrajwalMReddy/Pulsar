#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <string>

#include "ByteCodeCompiler.h"
#include "../util/ErrorReporter.h"


namespace Pulsar {
    class Interpreter {
        public:
            Interpreter(std::string sourceCode);
            void interpret();

        private:
            // Input Data
            std::string sourceCode;

            // Output Data
            CompilerError* errors;
    };
}


#endif
