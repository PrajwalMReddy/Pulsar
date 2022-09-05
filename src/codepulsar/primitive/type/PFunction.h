#ifndef CODEPULSAR_PFUNCTION_H
#define CODEPULSAR_PFUNCTION_H

#include <string>

#include "../Primitive.h"
#include "PNone.h"


namespace Pulsar {
    class PFunction: public Primitive {
        public:
            PFunction(std::string name);

            PrimitiveType getPrimitiveType() override;
            bool isPrimitiveType(PrimitiveType primitiveType) override;
            std::any getPrimitiveValue() override;

            Primitive* unaryNegate() override;
            Primitive* unaryNot() override;

            Primitive* plus(Primitive* primitive) override;
            Primitive* minus(Primitive* primitive) override;
            Primitive* times(Primitive* primitive) override;
            Primitive* div(Primitive* primitive) override;
            Primitive* rem(Primitive* primitive) override;

            Primitive* compareGreater(Primitive* primitive) override;
            Primitive* compareLesser(Primitive* primitive) override;

            std::string toString() override;

        private:
            std::string name;
    };
}


#endif
