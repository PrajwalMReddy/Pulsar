#include "ASTPrinter.h"


Pulsar::ASTPrinter::ASTPrinter() {
    this->indentCount = 0;
}

void Pulsar::ASTPrinter::print(Pulsar::Statement* ast) {
    if (!conditions.debug) return;

    std::cout << "\n-- AST --\n" << std::endl;
    constructTree(ast);
}

void Pulsar::ASTPrinter::constructTree(Pulsar::Statement* ast) {
    if (ast == nullptr) {
        std::cout << "No AST Has Been Generated" << std::endl;
    } else {
        ast->accept(*this); std::cout << std::endl;
    }
}

void Pulsar::ASTPrinter::visitBinaryExpression(Binary* expression) {
    std::cout << "Binary("; expression->getLeft()->accept(*this); std::cout << " " << expression->getOperator() + " "; expression->getRight()->accept(*this); std::cout << ")";
}

void Pulsar::ASTPrinter::visitCallExpression(Call* expression) {
    std::cout << "Call:" << expression->getName().literal << "(";

    for (Expression* expr: *expression->getArguments()) {
        expr->accept(*this);
    }

    std::cout << ")";
}

void Pulsar::ASTPrinter::visitGroupingExpression(Grouping* expression) {
    std::cout << "("; expression->getExpression()->accept(*this); std::cout << ")";
}

void Pulsar::ASTPrinter::visitLiteralExpression(Literal* expression) {
    std::cout << "Literal(" + expression->getValue() << ")";
}

void Pulsar::ASTPrinter::visitLogicalExpression(Logical* expression) {
    std::cout << "Logical("; expression->getLeft()->accept(*this); std::cout << " " << expression->getOperator() + " "; expression->getRight()->accept(*this); std::cout << ")";
}

void Pulsar::ASTPrinter::visitUnaryExpression(Unary* expression) {
    std::cout << "Unary(" << expression->getOperator() << " "; expression->getExpression()->accept(*this); std::cout << ")";
}

void Pulsar::ASTPrinter::visitBlockStatement(Block* statement) {
    std::cout << giveTabs() << "Block(\n";
    blockStatement(statement);
    std::cout << "\n" << giveTabs() + ")";
}

void Pulsar::ASTPrinter::blockStatement(Block* statement) {
    incrementIndentCount();

    for (Statement* stmt: *statement->getStatements()) {
        std::cout << giveTabs(); stmt->accept(*this);
    }

    decrementIndentCount();
}

void Pulsar::ASTPrinter::visitExpressionStatement(ExpressionStmt* statement) {
    std::cout << "Expression("; statement->getExpression()->accept(*this); std::cout << ")" << std::endl;
}

void Pulsar::ASTPrinter::visitIfStatement(If* statement) {
    std::cout << "\n" << giveTabs() << "If("; statement->getCondition()->accept(*this); std::cout << ")(\n";
    blockStatement(statement->getThenBranch()); std::cout << "\n" << giveTabs() << ")";

    if (statement->hasElse()) {
        std::cout << " Else(\n";
        incrementIndentCount();

        statement->getElseBranch()->accept(*this); std::cout << "\n";

        decrementIndentCount();
        std::cout << giveTabs() << ")";
    }

    std::cout << "\n";
}

void Pulsar::ASTPrinter::visitPrintStatement(Print* statement) {
    std::cout << "Print("; statement->getExpression()->accept(*this); std::cout << ")\n";
}

void Pulsar::ASTPrinter::visitWhileStatement(While* statement) {
    std::cout << "\n" << giveTabs() << "While("; statement->getCondition()->accept(*this); std::cout << ")(\n";
    blockStatement(statement->getStatements()); std::cout << "\n" << giveTabs() << ")";
}

std::string Pulsar::ASTPrinter::giveTabs() const {
    return std::string("\t", this->indentCount);
}

void Pulsar::ASTPrinter::incrementIndentCount() {
    this->indentCount++;
}

void Pulsar::ASTPrinter::decrementIndentCount() {
    this->indentCount--;
}
