#include "VariableExpr.h"


Pulsar::VariableExpr::VariableExpr(std::string name, bool isGlobal, int line) {
    this->name = name;
    this->isGlobal = isGlobal;
    this->line = line;
}

std::any Pulsar::VariableExpr::accept(ExprVisitor& visitor) {
    return visitor.visitVariableExpression(this);
}

std::string Pulsar::VariableExpr::getName() {
    return this->name;
}

bool Pulsar::VariableExpr::isGlobalVariable() {
    return this->isGlobal;
}

int Pulsar::VariableExpr::getLine() {
    return this->line;
}
