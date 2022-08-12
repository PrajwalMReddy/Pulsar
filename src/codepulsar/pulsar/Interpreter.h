#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <string>

#include "ByteCodeCompiler.h"
#include "../util/ErrorReporter.h"
#include "../util/Disassembler.h"
#include "../primitive/Value.h"


namespace Pulsar {
    class Interpreter {
        public:
            Interpreter(std::string sourceCode);
            void interpret();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Instruction> instructions;

            // Processing Data
            SymbolTable* symbolTable;
            std::vector<Value> values;

            // Output Data
            CompilerError* errors;

            // Other Necessary Data
            const int STACK_MAX = 1024;
            std::vector<std::any> stack;

            int sp;
            int ip;

            // Functions
            void execute();

            void push(std::any value);
            Value pop();

            void runtimeError(std::string message);
    };
}


#endif
