#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <string>

#include "ByteCodeCompiler.h"
#include "../util/ErrorReporter.h"
#include "../util/Disassembler.h"
#include "../lang/CallFrame.h"
#include "../primitive/type/PFunction.h"


namespace Pulsar {
    class Interpreter {
        public:
            Interpreter(std::string sourceCode);
            void interpret();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Instruction> instructions;
            std::string currentFunction;

            // Processing Data
            SymbolTable* symbolTable;
            std::vector<Primitive*> values;

            // Output Data
            CompilerError* errors;

            // Other Necessary Data
            CallFrame* currentFrame;
            int callFrameCount;

            std::vector<CallFrame*> callFrames;
            std::vector<Primitive*> stack;

            const int FRAMES_MAX = 64;
            const int STACK_MAX = FRAMES_MAX * 1024;

            int sp;
            int ip;

            // Functions
            void setUp();
            void execute();

            void unaryOperation(ByteCode code);
            void binaryOperation(ByteCode code);
            void compareOperation(ByteCode code);
            void conditionalJump(ByteCode code, Instruction instruction);
            void loadGlobal(Instruction instruction);

            void callFunction(Instruction instruction);
            void returnFunction();

            void push(Primitive* value);
            Primitive* pop();

            void runtimeError(std::string message);
    };
}


#endif
