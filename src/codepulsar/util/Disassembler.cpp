#include "Disassembler.h"


Pulsar::Disassembler::Disassembler(Pulsar::SymbolTable* symbolTable, std::vector<Primitive*> values) {
    this->symbolTable = symbolTable;
    this->values = values;
}

void Pulsar::Disassembler::disassemble() {
    if (!conditions.debug) return;

    std::cout << "\n-- Disassembled Bytecode --" << std::endl;
    displayInstructions();
    std::cout << std::endl;
}

void Pulsar::Disassembler::displayInstructions() {
    for (auto& [name, function]: this->symbolTable->getFunctions()) {
        int line = 0;
        int count = 0;
        this->instructions = function.getChunk();

        std::cout << std::endl << "Disassembly Of Function " + name << std::endl;
        for (Instruction instruction: this->instructions) {
            if (instruction.getLine() == line) {
                std::cout << "            " << count << "  | ";
            } else {
                line = instruction.getLine();
                std::cout << "\n" << line << spaces(line) << count << "  | ";
            }

            decideInstructionType(instruction);
            count++;
        }
    }
}

void Pulsar::Disassembler::decideInstructionType(Instruction instruction) {
    switch (instruction.getOpcode()) {
        case OP_ADD:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_MODULO:
        case OP_NEGATE:
        case OP_NOT:
        case OP_COMPARE_EQUAL:
        case OP_COMPARE_GREATER:
        case OP_COMPARE_LESSER:
        case OP_POP:
        case OP_PRINT:
        case OP_RETURN:
            opcodeType(instruction);
            break;

        case OP_CONSTANT:
        case OP_JUMP:
        case OP_JUMP_IF_TRUE:
        case OP_JUMP_IF_FALSE:
        case OP_NEW_GLOBAL:
        case OP_STORE_GLOBAL:
        case OP_LOAD_GLOBAL:
        case OP_SET_LOCAL:
        case OP_GET_LOCAL:
        case OP_NEW_LOCAL:
        case OP_LOAD_FUNCTION:
        case OP_CALL:
            operandType(instruction);
            break;
    }
}

std::string Pulsar::Disassembler::opcodeToString(ByteCode byteCode) {
    switch (byteCode) {
        case OP_NEGATE: return "OP_NEGATE";
        case OP_NOT: return "OP_NOT";
        case OP_ADD: return "OP_ADD";
        case OP_SUBTRACT: return "OP_SUBTRACT";
        case OP_MULTIPLY: return "OP_MULTIPLY";
        case OP_DIVIDE: return "OP_DIVIDE";
        case OP_MODULO: return "OP_MODULO";
        case OP_COMPARE_EQUAL: return "OP_COMPARE_EQUAL";
        case OP_COMPARE_GREATER: return "OP_COMPARE_GREATER";
        case OP_COMPARE_LESSER: return "OP_COMPARE_LESSER";

        case OP_CONSTANT: return "OP_CONSTANT";
        case OP_NEW_GLOBAL: return "OP_NEW_GLOBAL";
        case OP_STORE_GLOBAL: return "OP_STORE_GLOBAL";
        case OP_LOAD_GLOBAL: return "OP_LOAD_GLOBAL";
        case OP_NEW_LOCAL: return "OP_NEW_LOCAL";
        case OP_SET_LOCAL: return "OP_SET_LOCAL";
        case OP_GET_LOCAL: return "OP_GET_LOCAL";

        case OP_JUMP: return "OP_JUMP";
        case OP_JUMP_IF_TRUE: return "OP_JUMP_IF_TRUE";
        case OP_JUMP_IF_FALSE: return "OP_JUMP_IF_FALSE";

        case OP_LOAD_FUNCTION: return "OP_LOAD_FUNCTION";
        case OP_CALL: return "OP_CALL";
        case OP_RETURN: return "OP_RETURN";

        case OP_PRINT: return "OP_PRINT";
        case OP_POP: return "OP_POP";
        default: return "Unsupported OpCode Type";
    }
}

void Pulsar::Disassembler::opcodeType(Pulsar::Instruction instruction) {
    std::cout << opcodeToString(instruction.getOpcode()) << std::endl;
}

// TODO OP_LOAD_FUNCTION and OP_CALL
void Pulsar::Disassembler::operandType(Pulsar::Instruction instruction) {
    if (instruction.getOpcode() == OP_CONSTANT) {
        int operandInt = std::any_cast<int>(instruction.getOperand());
        std::cout << opcodeToString(OP_CONSTANT) << spaces(instruction) << operandInt << " (" << this->values[operandInt]->toString() << ")" << std::endl;
    } else if (instruction.getOpcode() == OP_JUMP || instruction.getOpcode() == OP_JUMP_IF_TRUE || instruction.getOpcode() == OP_JUMP_IF_FALSE) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<int>(instruction.getOperand()) << std::endl;
    } else if (instruction.getOpcode() == OP_STORE_GLOBAL || instruction.getOpcode() == OP_LOAD_GLOBAL) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<std::string>(instruction.getOperand()) << std::endl;
    } else if (instruction.getOpcode() == OP_NEW_GLOBAL) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<Token>(instruction.getOperand()).literal << std::endl;
    } else if (instruction.getOpcode() == OP_SET_LOCAL || instruction.getOpcode() == OP_GET_LOCAL) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<int>(instruction.getOperand()) << std::endl;
    } else if (instruction.getOpcode() == OP_NEW_LOCAL) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<Token>(instruction.getOperand()).literal << std::endl;
    } else if (instruction.getOpcode() == OP_CALL) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<std::string>(instruction.getOperand()) << std::endl;
    } else if (instruction.getOpcode() == OP_LOAD_FUNCTION) {
        std::cout << opcodeToString(instruction.getOpcode()) << spaces(instruction) << std::any_cast<std::string>(instruction.getOperand()) << std::endl;
    }
}

std::string Pulsar::Disassembler::spaces(int line) {
    int length = std::to_string(line).length();
    return giveSpaces(length + 9);
}

std::string Pulsar::Disassembler::spaces(Pulsar::Instruction instruction) {
    int length = opcodeToString(instruction.getOpcode()).length();
    return giveSpaces(length);
}

// Calculates How Many Spaces To Provide Based On The Length Of The Argument Passed In
std::string Pulsar::Disassembler::giveSpaces(int length) {
    std::string str;

    for (int i = 0; i < std::max(0, 20 - length + 1); i++) {
        str += " ";
    }

    return str;
}
