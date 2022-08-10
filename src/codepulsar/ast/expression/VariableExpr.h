#ifndef CODEPULSAR_VARIABLEEXPR_H
#define CODEPULSAR_VARIABLEEXPR_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class VariableExpr: public Expression {
        public:
            VariableExpr(std::string name, int localID, bool isGlobal, int line);
            std::any accept(ExprVisitor& visitor);

            std::string getName();
            int getLocalID();
            bool isGlobalVariable();
            int getLine();

        private:
            std::string name;
            int localID;
            bool isGlobal;
            int line;
    };
}


#endif
