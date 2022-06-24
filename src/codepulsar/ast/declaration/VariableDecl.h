#ifndef CODEPULSAR_VARIABLEDECL_H
#define CODEPULSAR_VARIABLEDECL_H

#include "../Statement.h"
#include "../Expression.h"
#include "../../lang/Token.h"
#include "../../primitive/PrimitiveType.h"


namespace Pulsar {
    class VariableDecl: public Statement {
        public:
            VariableDecl(Token name, Expression* initializer, Token type, TokenType accessType, bool isGlobal, int line);
            template<typename R>
            R accept(StmtVisitor<R>& visitor);

            Token getName();
            Expression* getInitializer();
            Token getType();

            TokenType getAccessType();
            bool isGlobalVariable();
            int getLine();

            bool isInitialized();

        private:
            Token name;
            Expression* initializer;
            Token type;

            TokenType accessType;
            bool isGlobal;
            int line;
    };
}


#endif
