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

            std::any unaryNegate() override;
            std::any unaryNot() override;

            std::any plus(std::any primitive) override;
            std::any minus(std::any primitive) override;
            std::any times(std::any primitive) override;
            std::any div(std::any primitive) override;
            std::any rem(std::any primitive) override;

            std::any compareGreater(std::any primitive) override;
            std::any compareLesser(std::any primitive) override;

            std::string toString() override;

        private:
            char value;
    };
}


#endif
