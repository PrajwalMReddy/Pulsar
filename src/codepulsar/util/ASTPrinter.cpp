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

void Pulsar::ASTPrinter::visitGroupingExpression(Pulsar::Grouping* expression) {
    std::cout << "("; expression->getExpression()->accept(*this); std::cout << ")";
}

void Pulsar::ASTPrinter::visitLiteralExpression(Pulsar::Literal* expression) {
    std::cout << "Literal(" + expression->getValue() << ")";
}
