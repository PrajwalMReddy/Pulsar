#ifndef CODEPULSAR_STMTVISITOR_H
#define CODEPULSAR_STMTVISITOR_H


namespace Pulsar {
    class StmtVisitor {
        public:
            virtual void visitBlockStatement(class Block* statement) = 0;
            virtual void visitExpressionStatement(class ExpressionStmt* statement) = 0;
            virtual void visitIfStatement(class If* statement) = 0;
    };
}


#endif
