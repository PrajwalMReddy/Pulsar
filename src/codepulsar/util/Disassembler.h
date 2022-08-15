#ifndef CODEPULSAR_DISASSEMBLER_H
#define CODEPULSAR_DISASSEMBLER_H

#include <vector>

#include "../lang/Instruction.h"
#include "../variable/SymbolTable.h"
#include "../pulsar/Pulsar.h"
#include "../primitive/type/PInteger.h"
#include "../primitive/type/PDouble.h"
#include "../primitive/type/PCharacter.h"
#include "../primitive/type/PBoolean.h"


namespace Pulsar {
    class Disassembler {
        public:
            Disassembler(std::vector<Instruction> instructions, SymbolTable* symbolTable, std::vector<Primitive*> values);
            void disassemble();

            static std::string opcodeToString(ByteCode byteCode);

        private:
            // Input Data
            std::vector<Instruction> instructions;
            SymbolTable* symbolTable;
            std::vector<Primitive*> values;

            // Functions
            void displayInstructions();
            void decideInstructionType(Instruction instruction);

            void opcodeType(Instruction instruction);
            void operandType(Instruction instruction);

            std::string spaces(int line);
            std::string spaces(Instruction instruction);
            std::string giveSpaces(int length);
    };
}


#endif
