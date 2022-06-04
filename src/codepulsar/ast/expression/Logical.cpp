#include "Logical.h"


Pulsar::Logical::Logical(Expression* left, std::string operatorType, Expression* right, int line) {
    this->left = left;
    this->operatorType = operatorType;
    this->right = right;
    this->line = line;
}

void Pulsar::Logical::accept(ExprVisitor& visitor) {
    visitor.visitLogicalExpression(this);
}

Pulsar::Expression* Pulsar::Logical::getLeft() {
    return this->left;
}

std::string Pulsar::Logical::getOperator() {
    return this->operatorType;
}

Pulsar::Expression* Pulsar::Logical::getRight() {
    return this->right;
}

int Pulsar::Logical::getLine() {
    return this->line;
}
