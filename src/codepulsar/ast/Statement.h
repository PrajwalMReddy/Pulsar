#ifndef CODEPULSAR_STATEMENT_H
#define CODEPULSAR_STATEMENT_H

#include "StmtVisitor.h"


namespace Pulsar {
    class Statement {
        public:
            template<typename R> R accept(StmtVisitor<R>& visitor);
    };
}


#endif
