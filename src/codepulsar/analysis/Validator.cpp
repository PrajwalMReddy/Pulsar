#include "Validator.h"


Pulsar::Validator::Validator(Statement* program, SymbolTable* symbolTable, CompilerError* errors) {
    this->program = program;
    this->symbolTable = symbolTable;
    this->errors = errors;
}

void Pulsar::Validator::validate() {
    if (this->program == nullptr) return;

    generalValidation();
    this->program->accept(*this);
}

void Pulsar::Validator::generalValidation() {
    int line = 1;

    if (this->symbolTable->getFunctions().find("main") == this->symbolTable->getFunctions().end()) {
        newError("The Main Function Was Not Found", line);
    } else if (this->symbolTable->getFunctions().find("main")->second.getFunctionNode().getParameters()->size() != 0) {
        // TODO Temporary Restriction
        newError("The Main Function Cannot Take Parameters", this->symbolTable->getFunctions().find("main")->second.getFunctionNode().getLine());
    }
}

std::any Pulsar::Validator::visitAssignmentExpression(Assignment* expression) {
    if (!expression->isGlobalAssignment() && this->symbolTable->isLocalConstant(expression->getIdentifier())) {
        newError("Local Variable '" + expression->getIdentifier() + "' Is A Constant And Cannot Be Reassigned", expression->getLine());
    } else if (expression->isGlobalAssignment() && this->symbolTable->isGlobalConstant(expression->getIdentifier())) {
        newError("Global Variable '" + expression->getIdentifier() + "' Is A Constant And Cannot Be Reassigned", expression->getLine());
    }

    expression->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitBinaryExpression(Binary* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::Validator::visitCallExpression(Call* expression) {
    if (this->symbolTable->getFunctions().find(expression->getName().literal) == this->symbolTable->getFunctions().end()) {
        newError("Function '" + expression->getName().literal + "' Was Not Found", expression->getLine());
    } else if (this->symbolTable->getFunctions().find(expression->getName().literal)->second.getArity() != expression->getArity()) {
        newError("Function '" + expression->getName().literal + "' Expects " + std::to_string(this->symbolTable->getFunctions().find(expression->getName().literal)->second.getArity()) + " Argument(s); "
                + std::to_string(expression->getArity()) + " Provided", expression->getLine());
    }

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

std::any Pulsar::Validator::visitVariableExpression(VariableExpr* expression) {
    std::string name = expression->getName();
    int line = expression->getLine();

    if (!expression->isGlobalVariable()) {
        if (!this->symbolTable->containsLocalVariable(name)) {
            newError("Local Variable '" + name + "' Is Used But Never Defined", line);
        } else if (!this->symbolTable->isLocalInitialized(name)) {
            newError("Local Variable '" + name + "' Has Not Been Initialized", line);
        }
    } else {
        if (!this->symbolTable->containsGlobalVariable(name)) {
            newError("Global Variable '" + name + "' Does Not Exist", line);
        } else if (!this->symbolTable->isGlobalInitialized(name)) {
            newError("Global Variable '" + name + "' Has Not Been Initialized", line);
        }
    }

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

std::any Pulsar::Validator::visitFunctionStatement(Function* statement) {
    statement->getStatements()->accept(*this);

    for (Parameter* parameter: *statement->getParameters()) {
        if (parameter->getType() == PR_ERROR) newError("Invalid Function Parameter(s) For Function " + statement->getName(), statement->getLine());
    }

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

std::any Pulsar::Validator::visitVariableStatement(VariableDecl* statement) {
    if (statement->isInitialized()) statement->getInitializer()->accept(*this);
    bool isInitialized = statement->isInitialized();

    if (!statement->isGlobalVariable() && this->symbolTable->isLocalInitialized(statement->getName().literal) && !isInitialized) {
        newError("Local Constants Must Be Initialized While Being Declared", statement->getLine());
    } else if (statement->isGlobalVariable() && this->symbolTable->isGlobalConstant(statement->getName().literal) && !isInitialized) {
        newError("Global Constants Must Be Initialized While Being Declared", statement->getLine());
    }

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