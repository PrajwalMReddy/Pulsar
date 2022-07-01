#include "TypeChecker.h"


Pulsar::TypeChecker::TypeChecker(Statement* program, CompilerError* errors) {
    this->program = program;
    this->errors = errors;
}

void Pulsar::TypeChecker::check() {
    if (this->program == nullptr) return;
    this->program->accept(*this);
}

// TODO
std::any Pulsar::TypeChecker::visitAssignmentExpression(Assignment* expression) {
    expression->getValue()->accept(*this);
    return PR_ERROR;
}

std::any Pulsar::TypeChecker::visitBinaryExpression(Binary* expression) {
    PrimitiveType a = std::any_cast<PrimitiveType>(expression->getLeft()->accept(*this));
    PrimitiveType b = std::any_cast<PrimitiveType>(expression->getRight()->accept(*this));

    if (isOfType(a, { PR_BOOLEAN }) || isOfType(b, { PR_BOOLEAN })) {
        if (!isOperation(expression->getOperator(), { "==", "!=" })) {
            newError("Boolean Operands May Not Be Used For Non Equality Checks", expression->getLine());
            return PR_ERROR;
        }
    } else if (a != b) {
        newError("Binary Operations Are Of Different Types", expression->getLine());
        return PR_ERROR;
    }

    if (isOperation(expression->getOperator(), { "==", "!=", "<", "<=", ">", ">=" })) {
        return PR_BOOLEAN;
    } else {
        return a;
    }
}

// TODO
std::any Pulsar::TypeChecker::visitCallExpression(Call* expression) {
    return PR_ERROR;
}

std::any Pulsar::TypeChecker::visitGroupingExpression(Grouping* expression) {
    return std::any_cast<PrimitiveType>(expression->accept(*this));
}

std::any Pulsar::TypeChecker::visitLiteralExpression(Literal* expression) {
    return expression->getType();
}

std::any Pulsar::TypeChecker::visitLogicalExpression(Logical* expression) {
    PrimitiveType a = std::any_cast<PrimitiveType>(expression->getLeft()->accept(*this));
    PrimitiveType b = std::any_cast<PrimitiveType>(expression->getRight()->accept(*this));

    if (!isOfType(a, { PR_BOOLEAN }) || !isOfType(b, { PR_BOOLEAN })) {
        newError("Logical Operation Has Non Boolean Operand(s)", expression->getLine());
        return PR_ERROR;
    }

    return PR_BOOLEAN;
}

std::any Pulsar::TypeChecker::visitUnaryExpression(Unary* expression) {
    PrimitiveType a = std::any_cast<PrimitiveType>(expression->getExpression()->accept(*this));

    if (isOperation(expression->getOperator(), { "!" }) && !isOfType(a, { PR_BOOLEAN })) {
        newError("Unary Not Operation Has Non Boolean Operand", expression->getLine());
        return PR_ERROR;
    } else if (isOperation(expression->getOperator(), { "-" }) && isOfType(a, { PR_BOOLEAN })) {
        newError("Unary Negation Has A Boolean Operand", expression->getLine());
        return PR_ERROR;
    }

    return a;
}

// TODO
std::any Pulsar::TypeChecker::visitVariableExpression(VariableExpr* expression) {
    return PR_ERROR;
}

std::any Pulsar::TypeChecker::visitBlockStatement(Block* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::TypeChecker::visitExpressionStatement(ExpressionStmt* statement) {
    statement->accept(*this);
    return nullptr;
}

std::any Pulsar::TypeChecker::visitFunctionStatement(Function* statement) {
    statement->getStatements()->accept(*this);
    return nullptr;
}

std::any Pulsar::TypeChecker::visitIfStatement(If* statement) {
    PrimitiveType type = std::any_cast<PrimitiveType>(statement->getCondition()->accept(*this));
    statement->getThenBranch()->accept(*this);
    if (statement->hasElse()) statement->getElseBranch()->accept(*this);

    if (type != PR_BOOLEAN) newError("If Statement Has Non Boolean Condition", statement->getLine());
    return nullptr;
}

std::any Pulsar::TypeChecker::visitPrintStatement(Print* statement) {
    statement->accept(*this);
    return nullptr;
}

// TODO
std::any Pulsar::TypeChecker::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) statement->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::TypeChecker::visitVariableStatement(VariableDecl* statement) {
    PrimitiveType variableType = checkType(statement->getType());
    PrimitiveType initializerType = std::any_cast<PrimitiveType>(statement->getInitializer()->accept(*this));

    if ((variableType != initializerType)) {
        newError("Variable Has Been Initialized With The Wrong Type", statement->getLine());
    }

    return nullptr;
}

std::any Pulsar::TypeChecker::visitWhileStatement(While* statement) {
    PrimitiveType type = std::any_cast<PrimitiveType>(statement->getCondition()->accept(*this));
    statement->getStatements()->accept(*this);

    if (type != PR_BOOLEAN) newError("While Statement Has Non Boolean Condition", statement->getLine());

    return nullptr;
}

PrimitiveType Pulsar::TypeChecker::checkType(Token type) {
    std::string typeLiteral = type.literal;

    if (typeLiteral == "boolean") return PR_BOOLEAN;
    else if (typeLiteral == "char") return PR_CHARACTER;
    else if (typeLiteral == "double") return PR_DOUBLE;
    else if (typeLiteral == "int") return PR_INTEGER;
    else if (typeLiteral == "void") return PR_VOID;
    else return PR_ERROR;
}

bool Pulsar::TypeChecker::isOfType(PrimitiveType toCompare, std::vector<PrimitiveType> types) {
    for (PrimitiveType type: types) {
        if (toCompare == type) return true;
    }

    return false;
}

bool Pulsar::TypeChecker::isOperation(std::string toCompare, std::vector<std::string> operations) {
    for (std::string operation: operations) {
        if (toCompare == operation) return true;
    }

    return false;
}

void Pulsar::TypeChecker::newError(std::string message, int line) {
    this->errors->addError("Type Error", message, line);
}

Pulsar::CompilerError* Pulsar::TypeChecker::getErrors() {
    return this->errors;
}
