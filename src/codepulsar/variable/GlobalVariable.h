#ifndef CODEPULSAR_GLOBALVARIABLE_H
#define CODEPULSAR_GLOBALVARIABLE_H

#include "../primitive/Primitive.h"


namespace Pulsar {
    class GlobalVariable {
        public:
            GlobalVariable(Primitive* value, PrimitiveType type, bool isInitialized, bool isConstant);

            Primitive* getValue();
            PrimitiveType getType();

            bool isConstant();
            bool isInitialized();
            void setInitialized();

        private:
            Primitive* value;
            PrimitiveType type;

            bool initialized;
            bool constant;
    };
}


#endif
