#include "Unary.h"


Pulsar::Unary::Unary(std::string operatorType, Expression* right, int line) {
    this->operatorType = operatorType;
    this->right = right;
    this->line = line;
}

std::any Pulsar::Unary::accept(ExprVisitor& visitor) {
    return visitor.visitUnaryExpression(this);
}

std::string Pulsar::Unary::getOperator() {
    return this->operatorType;
}

Pulsar::Expression* Pulsar::Unary::getExpression() {
    return this->right;
}

int Pulsar::Unary::getLine() {
    return this->line;
}