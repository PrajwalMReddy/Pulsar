#include "FunctionVariable.h"


Pulsar::FunctionVariable::FunctionVariable(Function functionNode, int arity, Pulsar::PrimitiveType returnType): functionNode(functionNode) {
    this->functionNode = functionNode;
    this->arity = arity;
    this->returnType = returnType;
}

std::vector<Pulsar::Instruction> Pulsar::FunctionVariable::getChunk() {
    return this->chunk;
}

void Pulsar::FunctionVariable::setChunk(std::vector<Instruction> chunk) {
    this->chunk = chunk;
}

Pulsar::Function Pulsar::FunctionVariable::getFunctionNode() {
    return this->functionNode;
}

int Pulsar::FunctionVariable::getArity() {
    return this->arity;
}

Pulsar::PrimitiveType Pulsar::FunctionVariable::getReturnType() {
    return this->returnType;
}
