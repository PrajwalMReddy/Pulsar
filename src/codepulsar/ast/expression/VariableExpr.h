#ifndef CODEPULSAR_VARIABLEEXPR_H
#define CODEPULSAR_VARIABLEEXPR_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class VariableExpr: public Expression {
        public:
            VariableExpr(std::string name, int line);
            void accept(ExprVisitor& visitor);

            std::string getName();
            int getLine();

        private:
            std::string name;
            int line;
    };
}


#endif
