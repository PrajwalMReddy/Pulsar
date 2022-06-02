#include "Literal.h"


Pulsar::Literal::Literal(std::string value, PrimitiveType type, int line) {
    this->value = value;
    this->type = type;
    this->line = line;
}

void Pulsar::Literal::accept(ExprVisitor& visitor) {
    visitor.visitLiteralExpression(this);
}

std::string Pulsar::Literal::getValue() {
    return this->value;
}

PrimitiveType Pulsar::Literal::getType() {
    return this->type;
}

int Pulsar::Literal::getLine() {
    return this->line;
}
