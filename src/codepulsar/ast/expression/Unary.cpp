#include "Unary.h"


Pulsar::Unary::Unary(std::string operatorType, Expression* right, int line) {
    this->operatorType = operatorType;
    this->right = right;
    this->line = line;
}

template<typename R>
R Pulsar::Unary::accept(ExprVisitor<R>& visitor) {
    visitor.visitUnaryExpression(this);
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