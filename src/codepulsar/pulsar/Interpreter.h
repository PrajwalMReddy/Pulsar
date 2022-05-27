#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <string>

#include "ByteCodeCompiler.h"


namespace Pulsar {
    class Interpreter {
        public:
            Interpreter(std::string sourceCode);
            void interpret();

        private:
            std::string sourceCode;
    };
}


#endif
