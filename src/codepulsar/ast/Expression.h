#ifndef CODEPULSAR_EXPRESSION_H
#define CODEPULSAR_EXPRESSION_H

#include "ExprVisitor.h"


namespace Pulsar {
    class Expression {
        public:
            virtual void accept(ExprVisitor& visitor) = 0;
    };
}


#endif
