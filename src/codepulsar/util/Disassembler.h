#ifndef CODEPULSAR_DISASSEMBLER_H
#define CODEPULSAR_DISASSEMBLER_H

#include <vector>

#include "../lang/Instruction.h"
#include "../variable/SymbolTable.h"
#include "../pulsar/Pulsar.h"
#include "../primitive/Value.h"
#include "../primitive/type/PInteger.h"
#include "../primitive/type/PDouble.h"
#include "../primitive/type/PCharacter.h"
#include "../primitive/type/PBoolean.h"


namespace Pulsar {
    class Disassembler {
        public:
            Disassembler(std::vector<Instruction> instructions, SymbolTable* symbolTable, std::vector<Value> values);
            void disassemble();

        private:
            // Input Data
            std::vector<Instruction> instructions;
            SymbolTable* symbolTable;
            std::vector<Value> values;

            // Functions
            void displayInstructions();
            void decideInstructionType(Instruction instruction);

            std::string opcodeToString(ByteCode byteCode);

            void opcodeType(Instruction instruction);
            void operandType(Instruction instruction);

            std::string spaces(int line);
            std::string spaces(Instruction instruction);
            std::string giveSpaces(int length);
    };
}


#endif
