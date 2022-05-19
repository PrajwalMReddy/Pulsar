#ifndef CODEPULSAR_EXPRESSION_H
#define CODEPULSAR_EXPRESSION_H

#include "Visitor.h"


class Expression {
    public:
        template<class R> R accept(Visitor visitor);
};


#endif
