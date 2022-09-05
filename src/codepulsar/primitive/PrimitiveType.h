#ifndef CODEPULSAR_PRIMITIVETYPE_H
#define CODEPULSAR_PRIMITIVETYPE_H


namespace Pulsar {
    enum PrimitiveType {
        PR_INTEGER, PR_DOUBLE,
        PR_BOOLEAN, PR_CHARACTER,
        PR_FUNCTION,

        // Other Types
        PR_VOID, PR_ERROR,
    };
}


#endif
