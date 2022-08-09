#ifndef CODEPULSAR_DISASSEMBLER_H
#define CODEPULSAR_DISASSEMBLER_H

#include <vector>

#include "../lang/Instruction.h"
#include "../variable/SymbolTable.h"
#include "../pulsar/Pulsar.h"


namespace Pulsar {
    class Disassembler {
        public:
            Disassembler(std::vector<Instruction> instructions, SymbolTable* symbolTable, std::vector<std::any> values);
            void disassemble();

        private:
            // Input Data
            std::vector<Instruction> instructions;
            SymbolTable* symbolTable;
            std::vector<std::any> values;

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
