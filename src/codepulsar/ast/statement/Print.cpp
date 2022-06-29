#include "Print.h"


Pulsar::Print::Print(Expression* expression, int line) {
    this->expression = expression;
    this->line = line;
}

std::any Pulsar::Print::accept(StmtVisitor& visitor) {
    return visitor.visitPrintStatement(this);
}

Pulsar::Expression* Pulsar::Print::getExpression() {
    return this->expression;
}

int Pulsar::Print::getLine() {
    return this->line;
}
