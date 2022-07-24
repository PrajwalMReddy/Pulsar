#include "Instruction.h"


Pulsar::Instruction::Instruction(ByteCode opcode, std::any operand, int line) {
    this->opcode = opcode;
    this->operand = operand;
    this->line = line;
}

Pulsar::ByteCode Pulsar::Instruction::getOpcode() {
    return this->opcode;
}

std::any Pulsar::Instruction::getOperand() {
    return this->operand;
}

int Pulsar::Instruction::getLine() {
    return this->line;
}
