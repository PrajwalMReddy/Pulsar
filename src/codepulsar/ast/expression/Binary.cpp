#include "Binary.h"


Pulsar::Binary::Binary(Expression* left, std::string operatorType, Expression* right, int line) {
    this->left = left;
    this->operatorType = operatorType;
    this->right = right;
    this->line = line;
}

std::any Pulsar::Binary::accept(ExprVisitor& visitor) {
    return visitor.visitBinaryExpression(this);
}

Pulsar::Expression* Pulsar::Binary::getLeft() {
    return this->left;
}

std::string Pulsar::Binary::getOperator() {
    return this->operatorType;
}

Pulsar::Expression* Pulsar::Binary::getRight() {
    return this->right;
}

int Pulsar::Binary::getLine() {
    return this->line;
}
