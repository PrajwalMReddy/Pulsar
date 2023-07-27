#ifndef CODEPULSAR_LOCALVARIABLE_H
#define CODEPULSAR_LOCALVARIABLE_H

#include <string>

#include "../primitive/PrimitiveType.h"


namespace Pulsar {
    class LocalVariable {
        public:
            LocalVariable(std::string name, PrimitiveType type, std::string function, bool isInitialized, bool isConstant, int depth);

            std::string getName();
            PrimitiveType getType();
            std::string getFunction();

            bool isConstant();
            int getDepth();
            bool isInitialized();
            void setInitialized();

        private:
            std::string name;
            PrimitiveType type;
            std::string function;

            bool initialized;
            bool constant;
            int depth;
    };
}


#endif
