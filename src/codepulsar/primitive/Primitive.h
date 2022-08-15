#ifndef CODEPULSAR_PRIMITIVE_H
#define CODEPULSAR_PRIMITIVE_H

#include <string>
#include <any>

#include "PrimitiveType.h"


namespace Pulsar {
    class Primitive {
        public:
            virtual PrimitiveType getPrimitiveType() = 0;
            virtual bool isPrimitiveType(PrimitiveType primitiveType) = 0;
            virtual std::any getPrimitiveValue() = 0;

            virtual Primitive* unaryNegate() = 0;
            virtual Primitive* unaryNot() = 0;

            virtual Primitive* plus(Primitive* primitive) = 0;
            virtual Primitive* minus(Primitive* primitive) = 0;
            virtual Primitive* times(Primitive* primitive) = 0;
            virtual Primitive* div(Primitive* primitive) = 0;
            virtual Primitive* rem(Primitive* primitive) = 0;

            virtual Primitive* compareGreater(Primitive* primitive) = 0;
            virtual Primitive* compareLesser(Primitive* primitive) = 0;

            virtual std::string toString() = 0;
    };
}


#endif
