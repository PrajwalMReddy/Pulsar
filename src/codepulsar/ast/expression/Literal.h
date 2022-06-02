#ifndef CODEPULSAR_LITERAL_H
#define CODEPULSAR_LITERAL_H

#include <string>

#include "../Expression.h"
#include "../../primitive/PrimitiveType.h"


namespace Pulsar {
    class Literal: public Expression {
        public:
            Literal(std::string value, PrimitiveType type, int line);
            void accept(ExprVisitor& visitor);

            std::string getValue();
            PrimitiveType getType();
            int getLine();
    
        private:
            std::string value;
            PrimitiveType type;
            int line;
    };
}


#endif
