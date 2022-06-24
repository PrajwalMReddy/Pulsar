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

std::string Pulsar::ASTPrinter::visitAssignmentExpression(Assignment* expression) {
    return "Assignment(Variable(" + expression->getIdentifier() + ") = " + expression->getValue()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitBinaryExpression(Binary* expression) {
    return "Binary(" + expression->getLeft()->accept(*this) + " " + expression->getOperator() + " " + expression->getRight()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitCallExpression(Call* expression) {
    std::string str;
    str += "Call:" + expression->getName().literal + "(";

    for (Expression* expr: *expression->getArguments()) {
        str += expr->accept(*this) + ",";
    }

    str += ")";
    return str;
}

std::string Pulsar::ASTPrinter::visitGroupingExpression(Grouping* expression) {
    return "(" + expression->getExpression()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitLiteralExpression(Literal* expression) {
    return "Literal(" + expression->getValue() + ")";
}

std::string Pulsar::ASTPrinter::visitLogicalExpression(Logical* expression) {
    return "Logical(" + expression->getLeft()->accept(*this) + " " + expression->getOperator() + " " + expression->getRight()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitUnaryExpression(Unary* expression) {
    return "Unary(" + expression->getOperator() + " " + expression->getExpression()->accept(*this) + ")";
}

std::string Pulsar::ASTPrinter::visitVariableExpression(VariableExpr* expression) {
    return "Variable(" + expression->getName() + ")";
}

std::string Pulsar::ASTPrinter::visitBlockStatement(Block* statement) {
    std::string str;
    str += giveTabs() + "Block(\n";
    str += blockStatement(statement);
    str += "\n" + giveTabs() + ")";
    return str;
}

std::string Pulsar::ASTPrinter::blockStatement(Block* statement) {
    std::string str;
    incrementIndentCount();

    for (Statement* stmt: *statement->getStatements()) {
        str += giveTabs() + stmt->accept(*this);
    }

    decrementIndentCount();
    return str;
}

std::string Pulsar::ASTPrinter::visitExpressionStatement(ExpressionStmt* statement) {
    return "Expression(" + statement->getExpression()->accept(*this) + ")\n";
}

std::string Pulsar::ASTPrinter::visitFunctionStatement(Function* statement) {
    std::string str;
    str += "\n" + giveTabs() + "Function:" + statement->getName() + "(";

    if (statement->getArity() > 0) {
        for (Parameter* param: *statement->getParameters()) {
            str += param->getName() + ",";
        }
    }

    str += ")(\n";
    str += blockStatement(statement->getStatements());
    str += "\n" + giveTabs() + ")";
    return str;
}

std::string Pulsar::ASTPrinter::visitIfStatement(If* statement) {
    std::string str;
    str += "\n" + giveTabs() + "If(" + statement->getCondition()->accept(*this) + ")(\n";
    str += blockStatement(statement->getThenBranch()) + "\n" + giveTabs() + ")";

    if (statement->hasElse()) {
        str += " Else(\n";
        incrementIndentCount();

        str += statement->getElseBranch()->accept(*this) + "\n";

        decrementIndentCount();
        str += giveTabs() + ")";
    }

    str += "\n";
    return str;
}

std::string Pulsar::ASTPrinter::visitPrintStatement(Print* statement) {
    return "Print(" + statement->getExpression()->accept(*this) + ")\n";
}

std::string Pulsar::ASTPrinter::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) {
        return "Return(" + statement->getValue()->accept(*this) + ")\n";
    } else {
        return "Return()\n";
    }
}

std::string Pulsar::ASTPrinter::visitVariableStatement(VariableDecl* statement) {
    std::string str;
    str += "Variable(";
    str += ((statement->isGlobalVariable()) ? "Global:" : "Local:");
    str += statement->getName().literal + " = " + statement->getInitializer()->accept(*this);
    str += ")\n";
    return str;
}

std::string Pulsar::ASTPrinter::visitWhileStatement(While* statement) {
    std::string str;
    str += "\n" + giveTabs() + "While(" + statement->getCondition()->accept(*this) + ")(\n";
    str += blockStatement(statement->getStatements()) + "\n" + giveTabs() + ")";
    return str;
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
