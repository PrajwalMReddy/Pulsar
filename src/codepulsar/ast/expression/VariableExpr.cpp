#include "VariableExpr.h"


Pulsar::VariableExpr::VariableExpr(std::string name, int localID, bool isGlobal, int line) {
    this->name = name;
    this->localID = localID;
    this->isGlobal = isGlobal;
    this->line = line;
}

std::any Pulsar::VariableExpr::accept(ExprVisitor& visitor) {
    return visitor.visitVariableExpression(this);
}

std::string Pulsar::VariableExpr::getName() {
    return this->name;
}

int Pulsar::VariableExpr::getLocalID() {
    return this->localID;
}

bool Pulsar::VariableExpr::isGlobalVariable() {
    return this->isGlobal;
}

int Pulsar::VariableExpr::getLine() {
    return this->line;
}
