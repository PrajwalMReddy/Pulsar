#include "VariableDecl.h"


Pulsar::VariableDecl::VariableDecl(Token name, Expression* initializer, PrimitiveType type,
                                   TokenType accessType, bool isGlobal, int line): name(name), type(type) {
    this->initializer = initializer;
    this->type = type;

    this->accessType = accessType;
    this->isGlobal = isGlobal;
    this->line = line;
}

std::any Pulsar::VariableDecl::accept(StmtVisitor& visitor) {
    return visitor.visitVariableStatement(this);
}

bool Pulsar::VariableDecl::isInitialized() {
    return this->initializer != nullptr;
}

Pulsar::Token Pulsar::VariableDecl::getName() {
    return this->name;
}

Pulsar::Expression* Pulsar::VariableDecl::getInitializer() {
    return this->initializer;
}

Pulsar::PrimitiveType Pulsar::VariableDecl::getType() {
    return this->type;
}

Pulsar::TokenType Pulsar::VariableDecl::getAccessType() {
    return this->accessType;
}

bool Pulsar::VariableDecl::isGlobalVariable() {
    return this->isGlobal;
}

int Pulsar::VariableDecl::getLine() {
    return this->line;
}
