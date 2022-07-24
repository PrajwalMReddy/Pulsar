#ifndef CODEPULSAR_INSTRUCTION_H
#define CODEPULSAR_INSTRUCTION_H

#include <any>

#include "ByteCode.h"


namespace Pulsar {
    class Instruction {
        public:
            Instruction(ByteCode opcode, std::any operand, int line);

            ByteCode getOpcode();
            std::any getOperand();
            int getLine();

    private:
            ByteCode opcode;
            std::any operand;
            int line;
    };
}


#endif
