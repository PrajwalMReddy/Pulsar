#include "Print.h"


Pulsar::Print::Print(Expression* expression, int line) {
    this->expression = expression;
    this->line = line;
}

template<typename R>
R Pulsar::Print::accept(StmtVisitor<R>& visitor) {
    visitor.visitPrintStatement(this);
}

Pulsar::Expression* Pulsar::Print::getExpression() {
    return this->expression;
}

int Pulsar::Print::getLine() {
    return this->line;
}
