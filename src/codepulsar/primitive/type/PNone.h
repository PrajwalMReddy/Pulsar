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
    };
}


#endif
