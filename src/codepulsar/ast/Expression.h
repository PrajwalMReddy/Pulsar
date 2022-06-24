#ifndef CODEPULSAR_EXPRESSION_H
#define CODEPULSAR_EXPRESSION_H

#include "ExprVisitor.h"


namespace Pulsar {
    class Expression {
        public:
            template<typename R> R accept(ExprVisitor<R>& visitor);
    };
}


#endif
