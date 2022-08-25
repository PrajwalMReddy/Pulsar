#ifndef CODEPULSAR_PINTEGER_H
#define CODEPULSAR_PINTEGER_H

#include "../Primitive.h"
#include "PNone.h"
#include "PBoolean.h"


namespace Pulsar {
    class PInteger: public Primitive {
        public:
            PInteger(int value);

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
            int value;
    };
}


#endif
