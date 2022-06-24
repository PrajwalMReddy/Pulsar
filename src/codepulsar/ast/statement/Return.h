#ifndef CODEPULSAR_RETURN_H
#define CODEPULSAR_RETURN_H

#include "../Statement.h"
#include "../Expression.h"


namespace Pulsar {
    class Return: public Statement {
        public:
            Return(Expression* value, int line);
            template<typename R>
            R accept(StmtVisitor<R>& visitor);

            Expression* getValue();
            int getLine();

            bool hasValue();

        private:
            Expression* value;
            int line;
    };
}


#endif
