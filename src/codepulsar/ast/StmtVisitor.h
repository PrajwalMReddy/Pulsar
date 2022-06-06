#ifndef CODEPULSAR_STMTVISITOR_H
#define CODEPULSAR_STMTVISITOR_H


namespace Pulsar {
    class StmtVisitor {
        public:
            virtual void visitBlockStatement(class Block* statement) = 0;
            virtual void visitExpressionStatement(class ExpressionStmt* statement) = 0;
            virtual void visitFunctionStatement(class Function* statement) = 0;
            virtual void visitIfStatement(class If* statement) = 0;
            virtual void visitPrintStatement(class Print* statement) = 0;
            virtual void visitReturnStatement(class Return* statement) = 0;
            virtual void visitVariableStatement(class VariableDecl* statement) = 0;
            virtual void visitWhileStatement(class While* statement) = 0;
    };
}


#endif
