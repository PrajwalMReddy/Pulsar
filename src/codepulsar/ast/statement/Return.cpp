#include "Return.h"


Pulsar::Return::Return(Expression* value, std::string function, int line) {
    this->value = value;
    this->function = function;
    this->line = line;
}

std::any Pulsar::Return::accept(StmtVisitor& visitor) {
    return visitor.visitReturnStatement(this);
}

bool Pulsar::Return::hasValue() {
    return this->value != nullptr;
}

Pulsar::Expression* Pulsar::Return::getValue() {
    return this->value;
}

std::string Pulsar::Return::getFunction() {
    return this->function;
}

int Pulsar::Return::getLine() {
    return this->line;
}
