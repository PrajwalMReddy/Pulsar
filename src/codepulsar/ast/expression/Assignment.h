#ifndef CODEPULSAR_ASSIGNMENT_H
#define CODEPULSAR_ASSIGNMENT_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class Assignment: public Expression {
        public:
            Assignment(std::string identifier, Expression* value, int line);
            std::any accept(ExprVisitor& visitor);

            std::string getIdentifier();
            Expression* getValue();
            int getLine();

        private:
            std::string identifier;
            Expression* value;
            int line;
    };
}


#endif
