#include "GlobalVariable.h"


Pulsar::GlobalVariable::GlobalVariable(Primitive* value, Pulsar::PrimitiveType type, bool initialized, bool constant) {
    this->value = value;
    this->type = type;
    this->initialized = initialized;
    this->constant = constant;
}

Pulsar::Primitive* Pulsar::GlobalVariable::getValue() {
    return this->value;
}

Pulsar::PrimitiveType Pulsar::GlobalVariable::getType() {
    return this->type;
}

bool Pulsar::GlobalVariable::isConstant() {
    return this->constant;
}

bool Pulsar::GlobalVariable::isInitialized() {
    return this->initialized;
}

void Pulsar::GlobalVariable::setInitialized() {
    this->initialized = true;
}
