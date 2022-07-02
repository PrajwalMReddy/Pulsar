#ifndef CODEPULSAR_VARIABLEDECL_H
#define CODEPULSAR_VARIABLEDECL_H

#include "../Statement.h"
#include "../Expression.h"
#include "../../lang/Token.h"
#include "../../primitive/PrimitiveType.h"


namespace Pulsar {
    class VariableDecl: public Statement {
        public:
            VariableDecl(Token name, Expression* initializer, PrimitiveType type, TokenType accessType, bool isGlobal, int line);
            std::any accept(StmtVisitor& visitor);

            Token getName();
            Expression* getInitializer();
            PrimitiveType getType();

            TokenType getAccessType();
            bool isGlobalVariable();
            int getLine();

            bool isInitialized();

        private:
            Token name;
            Expression* initializer;
            PrimitiveType type;

            TokenType accessType;
            bool isGlobal;
            int line;
    };
}


#endif
