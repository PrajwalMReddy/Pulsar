#ifndef CODEPULSAR_COMPILER_H
#define CODEPULSAR_COMPILER_H

#include <string>

#include "ByteCodeCompiler.h"
#include "../util/ErrorReporter.h"
#include "../util/Disassembler.h"
#include "../primitive/Value.h"


namespace Pulsar {
    class Compiler {
        public:
            Compiler(std::string sourceCode);
            void init();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Instruction> instructions;

            // Processing Data
            SymbolTable* symbolTable;
            std::vector<Value> values;

            // Output Data
            CompilerError* errors;
    };
}


#endif
