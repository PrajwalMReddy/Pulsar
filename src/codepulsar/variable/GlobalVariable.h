#ifndef CODEPULSAR_GLOBALVARIABLE_H
#define CODEPULSAR_GLOBALVARIABLE_H

#include "../primitive/Primitive.h"


namespace Pulsar {
    class GlobalVariable {
        public:
            GlobalVariable(std::any value, PrimitiveType type, bool isInitialized, bool isConstant);

            std::any getValue();
            PrimitiveType getType();

            bool isConstant();
            bool isInitialized();
            void setInitialized();

        private:
            std::any value;
            PrimitiveType type;

            bool initialized;
            bool constant;
    };
}


#endif
