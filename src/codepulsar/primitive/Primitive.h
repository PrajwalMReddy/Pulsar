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

            virtual std::any unaryNegate() = 0;
            virtual std::any unaryNot() = 0;

            virtual std::any plus(std::any primitive) = 0;
            virtual std::any minus(std::any primitive) = 0;
            virtual std::any times(std::any primitive) = 0;
            virtual std::any div(std::any primitive) = 0;
            virtual std::any rem(std::any primitive) = 0;

            virtual std::any compareGreater(std::any primitive) = 0;
            virtual std::any compareLesser(std::any primitive) = 0;

            virtual std::string toString() = 0;
    };
}


#endif
