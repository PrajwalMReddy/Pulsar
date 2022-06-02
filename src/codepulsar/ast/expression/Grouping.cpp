#include "Grouping.h"


Pulsar::Grouping::Grouping(Expression* expression, int line) {
    this->expression = expression;
    this->line = line;
}

void Pulsar::Grouping::accept(ExprVisitor& visitor) {
    visitor.visitGroupingExpression(this);
}

Pulsar::Expression* Pulsar::Grouping::getExpression() {
    return this->expression;
}

int Pulsar::Grouping::getLine() {
    return this->line;
}
