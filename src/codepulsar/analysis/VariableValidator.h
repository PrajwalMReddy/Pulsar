#ifndef CODEPULSAR_VARIABLEVALIDATOR_H
#define CODEPULSAR_VARIABLEVALIDATOR_H

#include <unordered_map>

#include "../ast/ExprVisitor.h"
#include "../ast/StmtVisitor.h"
#include "../ast/Statement.h"
#include "../lang/CompilerError.h"
#include "../primitive/PrimitiveType.h"
#include "../pulsar/Pulsar.h"
#include "../primitive/PrimitiveType.h"
#include "../variable/SymbolTable.h"


namespace Pulsar {
    class VariableValidator: public ExprVisitor, public StmtVisitor {
    public:
        VariableValidator(Statement* program, SymbolTable* symbolTable, CompilerError* errors);
        void validate();

        // Expression Nodes
        std::any visitAssignmentExpression(Assignment* expression) override;
        std::any visitBinaryExpression(Binary* expression) override;
        std::any visitCallExpression(Call* expression) override;
        std::any visitGroupingExpression(Grouping* expression) override;
        std::any visitLiteralExpression(Literal* expression) override;
        std::any visitLogicalExpression(Logical* expression) override;
        std::any visitUnaryExpression(Unary* expression) override;
        std::any visitVariableExpression(VariableExpr* expression) override;

        // Statement Nodes
        std::any visitBlockStatement(Block* statement) override;
        std::any visitExpressionStatement(ExpressionStmt* statement) override;
        std::any visitFunctionStatement(Function* statement) override;
        std::any visitIfStatement(If* statement) override;
        std::any visitNoneStatement(NoneStmt* statement) override;
        std::any visitPrintStatement(Print* statement) override;
        std::any visitProgramStatement(Program* statement) override;
        std::any visitReturnStatement(Return* statement) override;
        std::any visitVariableStatement(VariableDecl* statement) override;
        std::any visitWhileStatement(While* statement) override;

    private:
        Statement* program;
        SymbolTable* symbolTable;
        int scope;
        std::unordered_map<std::string, int> variables;
        CompilerError* errors;

        // Variables Map API
        void addVariable(std::string identifier, int line);
        void getVariable(std::string identifier, int line);
        void reassignVariable(std::string identifier, int line);

        void dropAndDecrement();
        void incrementScope();
        void decrementScope();

        void newError(std::string message, int line);
        CompilerError* getErrors();
    };
}


#endif
