#include "Return.h"


Pulsar::Return::Return(Expression* value, int line) {
    this->value = value;
    this->line = line;
}

template<typename R>
R Pulsar::Return::accept(StmtVisitor<R>& visitor) {
    visitor.visitReturnStatement(this);
}

bool Pulsar::Return::hasValue() {
    return this->value != nullptr;
}

Pulsar::Expression* Pulsar::Return::getValue() {
    return this->value;
}

int Pulsar::Return::getLine() {
    return this->line;
}
