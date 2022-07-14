#include "LocalVariable.h"


Pulsar::LocalVariable::LocalVariable(std::string name, Pulsar::PrimitiveType type, bool isInitialized, bool isConstant, int depth) {
    this->name = name;
    this->type = type;
    this->initialized = isInitialized;
    this->constant = isConstant;
    this->depth = depth;
}

std::string Pulsar::LocalVariable::getName() {
    return this->name;
}

Pulsar::PrimitiveType Pulsar::LocalVariable::getType() {
    return this->type;
}

bool Pulsar::LocalVariable::isConstant() {
    return this->constant;
}

int Pulsar::LocalVariable::getDepth() {
    return this->depth;
}

bool Pulsar::LocalVariable::isInitialized() {
    return this->initialized;
}

void Pulsar::LocalVariable::setInitialized() {
    this->initialized = true;
}
