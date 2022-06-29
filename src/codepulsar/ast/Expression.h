#ifndef CODEPULSAR_EXPRESSION_H
#define CODEPULSAR_EXPRESSION_H

#include <any>

#include "ExprVisitor.h"


namespace Pulsar {
    class Expression {
        public:
            virtual std::any accept(ExprVisitor& visitor) = 0;
    };
}


#endif
