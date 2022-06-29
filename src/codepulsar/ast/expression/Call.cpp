#include "Call.h"


Pulsar::Call::Call(Token name, std::vector<Expression*>* arguments): name(name) {
    this->arguments = arguments;
    this->line = name.line;
}

std::any Pulsar::Call::accept(ExprVisitor& visitor) {
    return visitor.visitCallExpression(this);
}

int Pulsar::Call::getArity() {
    return this->arguments->size();
}

Pulsar::Token Pulsar::Call::getName() {
    return this->name;
}

std::vector<Pulsar::Expression*>* Pulsar::Call::getArguments() {
    return this->arguments;
}

int Pulsar::Call::getLine() {
    return this->line;
}
