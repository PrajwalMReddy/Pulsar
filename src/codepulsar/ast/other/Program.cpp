#include "Program.h"


Pulsar::Program::Program(std::vector<Statement*>* statements) {
    this->statements = statements;
}

std::any Pulsar::Program::accept(Pulsar::StmtVisitor& visitor) {
    return visitor.visitProgramStatement(this);
}

std::vector<Pulsar::Statement*>* Pulsar::Program::getStatements() {
    return this->statements;
}
