#include "VariableExpr.h"


Pulsar::VariableExpr::VariableExpr(std::string name, int line) {
    this->name = name;
    this->line = line;
}

void Pulsar::VariableExpr::accept(ExprVisitor& visitor) {
    visitor.visitVariableExpression(this);
}

std::string Pulsar::VariableExpr::getName() {
    return this->name;
}

int Pulsar::VariableExpr::getLine() {
    return this->line;
}
