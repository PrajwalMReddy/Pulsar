#ifndef CODEPULSAR_STMTVISITOR_H
#define CODEPULSAR_STMTVISITOR_H

#include <any>


namespace Pulsar {
    class StmtVisitor {
        public:
            virtual std::any visitBlockStatement(class Block* statement) = 0;
            virtual std::any visitExpressionStatement(class ExpressionStmt* statement) = 0;
            virtual std::any visitFunctionStatement(class Function* statement) = 0;
            virtual std::any visitIfStatement(class If* statement) = 0;
            virtual std::any visitPrintStatement(class Print* statement) = 0;
            virtual std::any visitReturnStatement(class Return* statement) = 0;
            virtual std::any visitVariableStatement(class VariableDecl* statement) = 0;
            virtual std::any visitWhileStatement(class While* statement) = 0;
    };
}


#endif
