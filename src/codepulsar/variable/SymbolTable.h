#ifndef CODEPULSAR_SYMBOLTABLE_H
#define CODEPULSAR_SYMBOLTABLE_H

#include <string>
#include <map>
#include <any>

#include "../primitive/PrimitiveType.h"
#include "GlobalVariable.h"


namespace Pulsar {
    class SymbolTable {
        public:
            SymbolTable();

            // Global Variable Core Functions
            std::any getGlobalValue(std::string name);
            PrimitiveType getGlobalType(std::string name);
            bool isGlobalConstant(std::string name);
            bool isGlobalInitialized(std::string name);
            void setGlobalInitialized(std::string name);

            // Global Variable Extended Functions
            void addGlobalVariable(std::string name, std::any value, PrimitiveType type, bool isInitialized, bool isConstant);
            void reassignGlobalVariable(std::string name, std::any value);
            bool containsGlobalVariable(std::string name);

        private:
            std::map<std::string, GlobalVariable> globalVariables;
    };
}


#endif
