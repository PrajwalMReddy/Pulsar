#include "If.h"


Pulsar::If::If(Expression* condition, Block* thenBranch, Statement* elseBranch, int line) {
    this->condition = condition;
    this->thenBranch = thenBranch;
    this->elseBranch = elseBranch;
    this->line = line;
}

template<typename R>
R Pulsar::If::accept(StmtVisitor<R>& visitor) {
    visitor.visitIfStatement(this);
}

bool Pulsar::If::hasElse() {
    return this->elseBranch != nullptr;
}

Pulsar::Expression* Pulsar::If::getCondition() {
    return this->condition;
}

Pulsar::Block* Pulsar::If::getThenBranch() {
    return this->thenBranch;
}

Pulsar::Statement* Pulsar::If::getElseBranch() {
    return this->elseBranch;
}

int Pulsar::If::getLine() {
    return this->line;
}
