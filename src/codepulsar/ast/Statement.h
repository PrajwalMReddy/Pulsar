#ifndef CODEPULSAR_EXPRESSION_H
#define CODEPULSAR_EXPRESSION_H

#include "Visitor.h"


class Statement {
    public:
        template<class R> R accept(Visitor visitor);
};


#endif
