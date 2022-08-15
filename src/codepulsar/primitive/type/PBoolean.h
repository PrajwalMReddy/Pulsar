#ifndef CODEPULSAR_PBOOLEAN_H
#define CODEPULSAR_PBOOLEAN_H

#include "../Primitive.h"
#include "PNone.h"


namespace Pulsar {
    class PBoolean: public Primitive {
        public:
            PBoolean(bool value);

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
            bool value;
    };
}


#endif
