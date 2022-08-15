#ifndef CODEPULSAR_PNONE_H
#define CODEPULSAR_PNONE_H

#include "../Primitive.h"


namespace Pulsar {
    class PNone: public Primitive {
        public:
            PNone();

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
    };
}


#endif
