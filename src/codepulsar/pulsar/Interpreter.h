#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <string>

#include "ByteCodeCompiler.h"
#include "../util/ErrorReporter.h"
#include "../util/Disassembler.h"


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
            std::vector<Primitive*> values;

            // Output Data
            CompilerError* errors;

            // Other Necessary Data
            const int STACK_MAX = 1024;
            std::vector<Primitive*> stack;

            int sp;
            int ip;

            // Functions
            void execute();

            void push(Primitive* value);
            Primitive* pop();

            void runtimeError(std::string message);
    };
}


#endif
