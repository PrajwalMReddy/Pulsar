#include "ASTPrinter.h"


Pulsar::ASTPrinter::ASTPrinter() {
    this->indentCount = 0;
}

void Pulsar::ASTPrinter::print(Pulsar::Expression* ast) {
    if (!conditions.debug) return;

    std::cout << "\n-- AST --\n" << std::endl;
    constructTree(ast);
}

void Pulsar::ASTPrinter::constructTree(Pulsar::Expression* ast) {
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
