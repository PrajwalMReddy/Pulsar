#ifndef CODEPULSAR_PCHARACTER_H
#define CODEPULSAR_PCHARACTER_H

#include "../Primitive.h"
#include "PNone.h"


namespace Pulsar {
    class PCharacter: public Primitive {
        public:
            PCharacter(char value);

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
            char value;
    };
}


#endif
