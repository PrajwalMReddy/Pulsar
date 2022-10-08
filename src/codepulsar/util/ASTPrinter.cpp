#include "ASTPrinter.h"


Pulsar::ASTPrinter::ASTPrinter() {
    this->indentCount = 0;
}

void Pulsar::ASTPrinter::print(Pulsar::Statement* ast, std::string astType) {
    if (!conditions.debug) return;

    std::cout << "\n-- " << astType << " AST --\n" << std::endl;
    constructTree(ast);
}

void Pulsar::ASTPrinter::constructTree(Pulsar::Statement* ast) {
    if (ast == nullptr) {
        std::cout << "No AST Has Been Generated" << std::endl;
    } else {
        std::cout << std::any_cast<std::string>(ast->accept(*this)) << std::endl;
    }
}

std::any Pulsar::ASTPrinter::visitAssignmentExpression(Assignment* expression) {
    return "Assignment(Variable(" + expression->getIdentifier() + ") = " + std::any_cast<std::string>(expression->getValue()->accept(*this)) + ")";
}

std::any Pulsar::ASTPrinter::visitBinaryExpression(Binary* expression) {
    return "Binary(" + std::any_cast<std::string>(expression->getLeft()->accept(*this)) + " " + expression->getOperator() + " " + std::any_cast<std::string>(expression->getRight()->accept(*this)) + ")";
}

std::any Pulsar::ASTPrinter::visitCallExpression(Call* expression) {
    std::string str;
    str += "Call:" + expression->getName().literal + "(";

    for (Expression* expr: *expression->getArguments()) {
        str += std::any_cast<std::string>(expr->accept(*this)) + ",";
    }

    str += ")";
    return str;
}

std::any Pulsar::ASTPrinter::visitGroupingExpression(Grouping* expression) {
    return "(" + std::any_cast<std::string>(expression->getExpression()->accept(*this)) + ")";
}

std::any Pulsar::ASTPrinter::visitLiteralExpression(Literal* expression) {
    return "Literal(" + expression->getValue() + ")";
}

std::any Pulsar::ASTPrinter::visitLogicalExpression(Logical* expression) {
    return "Logical(" + std::any_cast<std::string>(expression->getLeft()->accept(*this)) + " " + expression->getOperator() + " " + std::any_cast<std::string>(expression->getRight()->accept(*this)) + ")";
}

std::any Pulsar::ASTPrinter::visitUnaryExpression(Unary* expression) {
    return "Unary(" + expression->getOperator() + " " + std::any_cast<std::string>(expression->getExpression()->accept(*this)) + ")";
}

std::any Pulsar::ASTPrinter::visitVariableExpression(VariableExpr* expression) {
    return "Variable(" + expression->getName() + ")";
}

std::any Pulsar::ASTPrinter::visitBlockStatement(Block* statement) {
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
        str += giveTabs() + std::any_cast<std::string>(stmt->accept(*this));
    }

    decrementIndentCount();
    return str;
}

std::any Pulsar::ASTPrinter::visitExpressionStatement(ExpressionStmt* statement) {
    return "Expression(" + std::any_cast<std::string>(statement->getExpression()->accept(*this)) + ")\n";
}

std::any Pulsar::ASTPrinter::visitFunctionStatement(Function* statement) {
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

std::any Pulsar::ASTPrinter::visitIfStatement(If* statement) {
    std::string str;
    str += "\n" + giveTabs() + "If(" + std::any_cast<std::string>(statement->getCondition()->accept(*this)) + ")(\n";
    str += blockStatement(statement->getThenBranch()) + "\n" + giveTabs() + ")";

    if (statement->hasElse()) {
        str += " Else(\n";
        incrementIndentCount();

        str += std::any_cast<std::string>(statement->getElseBranch()->accept(*this)) + "\n";

        decrementIndentCount();
        str += giveTabs() + ")";
    }

    str += "\n";
    return str;
}

std::any Pulsar::ASTPrinter::visitNoneStatement(NoneStmt* statement) {
    return "";
}

std::any Pulsar::ASTPrinter::visitPrintStatement(Print* statement) {
    return "Print(" + std::any_cast<std::string>(statement->getExpression()->accept(*this)) + ")\n";
}

std::any Pulsar::ASTPrinter::visitProgramStatement(Program* statement) {
    std::string str;
    str += giveTabs() + "Program(\n";
    str += blockStatement(new Block(statement->getStatements(), 0));
    str += "\n" + giveTabs() + ")";
    return str;
}

std::any Pulsar::ASTPrinter::visitReturnStatement(Return* statement) {
    std::string str;
    if (statement->hasValue()) {
        str = "Return(" + std::any_cast<std::string>(statement->getValue()->accept(*this)) + ")\n";
    } else {
        str = "Return()\n";
    }
    return str;
}

std::any Pulsar::ASTPrinter::visitVariableStatement(VariableDecl* statement) {
    std::string str;
    str += "Variable(";
    str += ((statement->isGlobalVariable()) ? "Global:" : "Local:");

    if (statement->isInitialized()) {
        str += statement->getName().literal + " = " + std::any_cast<std::string>(statement->getInitializer()->accept(*this));
    } else {
        str += "Uninitialized";
    }

    str += ")\n";
    return str;
}

std::any Pulsar::ASTPrinter::visitWhileStatement(While* statement) {
    std::string str;
    str += "\n" + giveTabs() + "While(" + std::any_cast<std::string>(statement->getCondition()->accept(*this)) + ")(\n";
    str += blockStatement(statement->getStatements()) + "\n" + giveTabs() + ")";
    return str;
}

std::string Pulsar::ASTPrinter::giveTabs() const {
    std::string str;

    for (int i = 0; i < this->indentCount; i++) {
        str += "    ";
    }

    return str;
}

void Pulsar::ASTPrinter::incrementIndentCount() {
    this->indentCount++;
}

void Pulsar::ASTPrinter::decrementIndentCount() {
    this->indentCount--;
}
