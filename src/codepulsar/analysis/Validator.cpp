#include "Validator.h"


Pulsar::Validator::Validator(Statement* program, CompilerError* errors) {
    this->program = program;
    this->errors = errors;
}

void Pulsar::Validator::validate() {
    if (this->program == nullptr) return;
    this->program->accept(*this);
}

// TODO
std::any Pulsar::Validator::visitAssignmentExpression(Assignment* expression) {
    expression->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitBinaryExpression(Binary* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

// TODO
std::any Pulsar::Validator::visitCallExpression(Call* expression) {
    return nullptr;
}

std::any Pulsar::Validator::visitGroupingExpression(Grouping* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitLiteralExpression(Literal* expression) {
    return nullptr;
}

std::any Pulsar::Validator::visitLogicalExpression(Logical* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitUnaryExpression(Unary* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

// TODO
std::any Pulsar::Validator::visitVariableExpression(VariableExpr* expression) {
    return nullptr;
}

std::any Pulsar::Validator::visitBlockStatement(Block* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::Validator::visitExpressionStatement(ExpressionStmt* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

// TODO
std::any Pulsar::Validator::visitFunctionStatement(Function* statement) {
    statement->getStatements()->accept(*this);

    return nullptr;
}

std::any Pulsar::Validator::visitIfStatement(If* statement) {
    statement->getCondition()->accept(*this);
    statement->getThenBranch()->accept(*this);
    if (statement->hasElse()) statement->getElseBranch()->accept(*this);

    return nullptr;
}

std::any Pulsar::Validator::visitPrintStatement(Print* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) statement->getValue()->accept(*this);
    return nullptr;
}

// TODO
std::any Pulsar::Validator::visitVariableStatement(VariableDecl* statement) {
    statement->getInitializer()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitWhileStatement(While* statement) {
    statement->getCondition()->accept(*this);
    statement->getStatements()->accept(*this);
    return nullptr;
}

void Pulsar::Validator::newError(std::string message, int line) {
    this->errors->addError("Code Error", message, line);
}

Pulsar::CompilerError* Pulsar::Validator::getErrors() {
    return this->errors;
}