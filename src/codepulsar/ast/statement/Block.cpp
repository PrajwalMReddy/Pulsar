#include "Block.h"


Pulsar::Block::Block(std::vector<Statement*>* statements, int line) {
    this->statements = statements;
    this->line = line;
}

std::any Pulsar::Block::accept(StmtVisitor& visitor) {
    return visitor.visitBlockStatement(this);
}

std::vector<Pulsar::Statement*>* Pulsar::Block::getStatements() {
    return this->statements;
}

int Pulsar::Block::getLine() {
    return this->line;
}
