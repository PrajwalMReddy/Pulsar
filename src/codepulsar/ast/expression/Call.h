#ifndef CODEPULSAR_CALL_H
#define CODEPULSAR_CALL_H

#include <vector>

#include "../Expression.h"
#include "../../lang/Token.h"


namespace Pulsar {
    class Call : public Expression {
        public:
            Call(Token name, std::vector<Expression*>* arguments);
            void accept(ExprVisitor& visitor);

            int getArity();

            Token getName();
            std::vector<Expression*>* getArguments();
            int getLine();

        private:
            Token name;
            std::vector<Expression*>* arguments;
            int line;
    };
}


#endif
