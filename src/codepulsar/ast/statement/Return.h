#ifndef CODEPULSAR_RETURN_H
#define CODEPULSAR_RETURN_H

#include <string>

#include "../Statement.h"
#include "../Expression.h"


namespace Pulsar {
    class Return: public Statement {
        public:
            Return(Expression* value, std::string function, int line);
            std::any accept(StmtVisitor& visitor);

            Expression* getValue();
            std::string getFunction();
            int getLine();

            bool hasValue();

        private:
            Expression* value;
            std::string function;
            int line;
    };
}


#endif
