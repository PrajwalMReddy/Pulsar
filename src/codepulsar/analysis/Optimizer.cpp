#include "Optimizer.h"


Pulsar::Optimizer::Optimizer(Statement* rawProgram) {
    this->rawProgram = rawProgram;
    this->optimizedProgram = nullptr;
}

Pulsar::Statement* Pulsar::Optimizer::optimize() {
    if (this->rawProgram == nullptr) return this->rawProgram;

    this->rawProgram->accept(*this);
    return this->rawProgram;
}

std::any Pulsar::Optimizer::visitAssignmentExpression(Assignment* expression) {
    expression->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitBinaryExpression(Binary* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitCallExpression(Call* expression) {
    return nullptr;
}

std::any Pulsar::Optimizer::visitGroupingExpression(Grouping* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitLiteralExpression(Literal* expression) {
    return nullptr;
}

std::any Pulsar::Optimizer::visitLogicalExpression(Logical* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitUnaryExpression(Unary* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitVariableExpression(VariableExpr* expression) {
    return nullptr;
}

std::any Pulsar::Optimizer::visitBlockStatement(Block* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::Optimizer::visitExpressionStatement(ExpressionStmt* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitFunctionStatement(Function* statement) {
    statement->getStatements()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitIfStatement(If* statement) {
    statement->getCondition()->accept(*this);
    statement->getThenBranch()->accept(*this);
    if (statement->hasElse()) statement->getElseBranch()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitNoneStatement(NoneStmt* statement) {
    return nullptr;
}

std::any Pulsar::Optimizer::visitPrintStatement(Print* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitProgramStatement(Program* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::Optimizer::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) statement->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitVariableStatement(VariableDecl* statement) {
    if (statement->isInitialized()) statement->getInitializer()->accept(*this);
    return nullptr;
}

std::any Pulsar::Optimizer::visitWhileStatement(While* statement) {
    statement->getCondition()->accept(*this);
    statement->getStatements()->accept(*this);
    return nullptr;
}
