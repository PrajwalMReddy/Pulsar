#ifndef CODEPULSAR_VALUE_H
#define CODEPULSAR_VALUE_H

#include <any>

#include "PrimitiveType.h"


namespace Pulsar {
    class Value {
        public:
            Value(std::any value, PrimitiveType type);

            std::any getValue();
            PrimitiveType getType();

        private:
            std::any value;
            PrimitiveType type;
    };
}


#endif
