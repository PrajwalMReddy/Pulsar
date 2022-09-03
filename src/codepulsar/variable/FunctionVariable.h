#ifndef CODEPULSAR_FUNCTIONVARIABLE_H
#define CODEPULSAR_FUNCTIONVARIABLE_H

#include <vector>

#include "../lang/Instruction.h"
#include "../ast/declaration/Function.h"


namespace Pulsar {
    class FunctionVariable {
        public:
            FunctionVariable(Function functionNode, int arity, Pulsar::PrimitiveType returnType);

            std::vector<Instruction> getChunk();
            void setChunk(std::vector<Instruction> chunk);

            Function getFunctionNode();
            int getArity();
            PrimitiveType getReturnType();

        private:
            std::vector<Instruction> chunk;
            Function functionNode;

            int arity;
            PrimitiveType returnType;
    };
}


#endif
