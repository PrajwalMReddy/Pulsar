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
        std::cout << ast->accept(*this) << std::endl;
    }
}

std::string Pulsar::ASTPrinter::visitGroupingExpression(Pulsar::Grouping* expression) {
    return "(" + expression->getExpression()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitLiteralExpression(Pulsar::Literal* expression) {
    return "Literal(" + expression->getValue() + ")";
}
