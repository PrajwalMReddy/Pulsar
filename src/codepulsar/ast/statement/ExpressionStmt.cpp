#include "ExpressionStmt.h"


Pulsar::ExpressionStmt::ExpressionStmt(Expression* expression, int line) {
    this->expression = expression;
    this->line = line;
}

void Pulsar::ExpressionStmt::accept(StmtVisitor& visitor) {
    visitor.visitExpressionStatement(this);
}

Pulsar::Expression* Pulsar::ExpressionStmt::getExpression() {
    return this->expression;
}

int Pulsar::ExpressionStmt::getLine() {
    return this->line;
}
