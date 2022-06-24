#ifndef CODEPULSAR_STMTVISITOR_H
#define CODEPULSAR_STMTVISITOR_H


namespace Pulsar {
    template<typename R>
    class StmtVisitor {
        public:
            virtual R visitBlockStatement(class Block* statement) = 0;
            virtual R visitExpressionStatement(class ExpressionStmt* statement) = 0;
            virtual R visitFunctionStatement(class Function* statement) = 0;
            virtual R visitIfStatement(class If* statement) = 0;
            virtual R visitPrintStatement(class Print* statement) = 0;
            virtual R visitReturnStatement(class Return* statement) = 0;
            virtual R visitVariableStatement(class VariableDecl* statement) = 0;
            virtual R visitWhileStatement(class While* statement) = 0;
    };
}


#endif
