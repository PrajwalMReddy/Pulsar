#include "VariableValidator.h"


Pulsar::VariableValidator::VariableValidator(Statement* program, SymbolTable* symbolTable, CompilerError* errors) {
    this->program = program;
    this->symbolTable = symbolTable;
    this->scope = 0;
    this->variables = std::unordered_map<std::string, int>();
    this->errors = errors;
}

void Pulsar::VariableValidator::validate() {
    if (this->program == nullptr) return;
    this->program->accept(*this);
}

std::any Pulsar::VariableValidator::visitAssignmentExpression(Assignment* expression) {
    expression->getValue()->accept(*this);
    reassignVariable(expression->getIdentifier(), expression->getLine());
    return nullptr;
}

std::any Pulsar::VariableValidator::visitBinaryExpression(Binary* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitCallExpression(Call* expression) {
    return nullptr;
}

std::any Pulsar::VariableValidator::visitGroupingExpression(Grouping* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitLiteralExpression(Literal* expression) {
    return nullptr;
}

std::any Pulsar::VariableValidator::visitLogicalExpression(Logical* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitUnaryExpression(Unary* expression) {
    expression->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitVariableExpression(VariableExpr* expression) {
    getVariable(expression->getName(), expression->getLine());
    return nullptr;
}

std::any Pulsar::VariableValidator::visitBlockStatement(Block* statement) {
    incrementScope();
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }
    dropAndDecrement();

    return nullptr;
}

std::any Pulsar::VariableValidator::visitExpressionStatement(ExpressionStmt* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitFunctionStatement(Function* statement) {
    incrementScope();
    for (int i = 0; i < statement->getParameters()->size(); ++i) {
        addVariable(statement->getParameters()->at(i)->getName(), statement->getLine());
    }
    statement->getStatements()->accept(*this);
    dropAndDecrement();
    return nullptr;
}

std::any Pulsar::VariableValidator::visitIfStatement(If* statement) {
    statement->getCondition()->accept(*this);
    incrementScope();
    statement->getThenBranch()->accept(*this);
    dropAndDecrement();
    if (statement->hasElse()) {
        incrementScope();
        statement->getElseBranch()->accept(*this);
        dropAndDecrement();
    }

    return nullptr;
}

std::any Pulsar::VariableValidator::visitNoneStatement(NoneStmt* statement) {
    return nullptr;
}

std::any Pulsar::VariableValidator::visitPrintStatement(Print* statement) {
    statement->getExpression()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitProgramStatement(Program* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::VariableValidator::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) statement->getValue()->accept(*this);
    return nullptr;
}

std::any Pulsar::VariableValidator::visitVariableStatement(VariableDecl* statement) {
    if (statement->isInitialized()) statement->getInitializer()->accept(*this);
    addVariable(statement->getName().literal, statement->getLine());
    return nullptr;
}

std::any Pulsar::VariableValidator::visitWhileStatement(While* statement) {
    statement->getCondition()->accept(*this);
    incrementScope();
    statement->getStatements()->accept(*this);
    dropAndDecrement();
    return nullptr;
}

void Pulsar::VariableValidator::addVariable(std::string identifier, int line) {
    if (this->variables.find(identifier) != this->variables.end()) newError("Variable " + identifier + " Already Exists In This Scope", line);
    else this->variables.insert({ identifier, this->scope });
}

void Pulsar::VariableValidator::getVariable(std::string identifier, int line) {
    if (this->variables.find(identifier) == this->variables.end()) newError("Variable " + identifier + " Does Not Exist In This Scope", line);
}

void Pulsar::VariableValidator::reassignVariable(std::string identifier, int line) {
    if (this->variables.find(identifier) == this->variables.end()) newError("Variable " + identifier + " Does Not Exist In This Scope", line);
}

void Pulsar::VariableValidator::dropAndDecrement() {
    // Names Of Variables To Drop
    std::vector<std::string> varNames;

    // Searching For All Variables To Drop
    for (auto& var: this->variables) {
        if (var.second == this->scope) varNames.push_back(var.first);
    }

    // Dropping All Marked Variables
    for (auto& varName: varNames) {
        this->variables.erase(varName);
    }

    decrementScope(); // Reduce The Scope Depth
}

void Pulsar::VariableValidator::incrementScope() {
    this->scope++;
}

void Pulsar::VariableValidator::decrementScope() {
    this->scope--;
}

void Pulsar::VariableValidator::newError(std::string message, int line) {
    this->errors->addError("Variable Error", message, line);
}

Pulsar::CompilerError* Pulsar::VariableValidator::getErrors() {
    return this->errors;
}
